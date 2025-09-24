#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Cool Tetris with effects — improved version
- 支持按住左右/下键连续移动/软降
- Game Over 时按 Enter 重启（也支持 R）
- 右侧控制提示更新为 "Enter restart"
- Next 列表缩减为 3 个，避免文字重叠
"""

import math
import random
import sys
from dataclasses import dataclass
from typing import List, Tuple, Optional, Dict

import pygame

# ------------- Config -------------
GRID_W, GRID_H = 10, 20
CELL = 32  # pixel size per cell
BORDER = 8
PANEL_W = 7  # side panel cells width (visual; not grid cells)
FPS = 60

WINDOW_W = BORDER * 2 + GRID_W * CELL + PANEL_W * CELL + 32
WINDOW_H = BORDER * 2 + GRID_H * CELL

DROP_START_DELAY = 1000  # ms (level 1 gravity)
LOCK_DELAY = 500  # ms
SOFT_DROP_MULT = 20  # faster than gravity
FLASH_TIME = 300  # ms for line clear flash
PARTICLE_COUNT_PER_BLOCK = 10
MOVE_REPEAT = 120  # 左右长按移动间隔(ms)

# ------------- Tetromino Data -------------
# (x, y) coordinates for rotation state 0; others generated with rotation
TETROMINO_SHAPES = {
    'I': [(0, 1), (1, 1), (2, 1), (3, 1)],
    'O': [(1, 0), (2, 0), (1, 1), (2, 1)],
    'T': [(1, 0), (0, 1), (1, 1), (2, 1)],
    'S': [(1, 1), (2, 1), (0, 2), (1, 2)],
    'Z': [(0, 1), (1, 1), (1, 2), (2, 2)],
    'J': [(0, 0), (0, 1), (1, 1), (2, 1)],
    'L': [(2, 0), (0, 1), (1, 1), (2, 1)],
}

# Nice neon-like colors
COLORS = {
    'I': (0, 255, 255),
    'O': (255, 223, 0),
    'T': (186, 85, 211),
    'S': (50, 205, 50),
    'Z': (255, 69, 58),
    'J': (65, 105, 225),
    'L': (255, 140, 0),
    'GHOST': (200, 200, 200),
}

BG_COLOR = (14, 14, 20)
GRID_LINE_COLOR = (35, 35, 50)
PANEL_BG = (20, 20, 28)
TEXT_COLOR = (230, 230, 240)

# ------------- Utility -------------
def rotate_point(x, y, cw=True):
    """Rotate (x, y) around origin by 90 degrees."""
    return (y, -x) if cw else (-y, x)

def create_rotations(coords):
    # Generate 4 rotation states
    states = []
    pts = coords[:]
    origin = (1.5, 1.5) if coords == TETROMINO_SHAPES['I'] else (1, 1)
    # Move so that origin at 0,0 then rotate around it
    cx, cy = origin
    base = [(x - cx, y - cy) for x, y in coords]
    for i in range(4):
        states.append([(round(x + cx), round(y + cy)) for (x, y) in base])
        base = [rotate_point(x, y, cw=True) for (x, y) in base]
    return states

ROTATIONS = {k: create_rotations(v) for k, v in TETROMINO_SHAPES.items()}
DIRS = ['N', 'E', 'S', 'W']

@dataclass
class Piece:
    kind: str
    x: int
    y: int
    rot: int = 0

    def cells(self) -> List[Tuple[int, int]]:
        return [(self.x + dx, self.y + dy) for dx, dy in ROTATIONS[self.kind][self.rot]]

    def moved(self, dx=0, dy=0, drot=0):
        return Piece(self.kind, self.x + dx, self.y + dy, (self.rot + drot) % 4)

@dataclass
class Particle:
    x: float
    y: float
    vx: float
    vy: float
    life: float
    color: Tuple[int, int, int]
    size: float

class Bag:
    def __init__(self):
        self.pool = []
    def next(self):
        if not self.pool:
            self.pool = list(TETROMINO_SHAPES.keys())
            random.shuffle(self.pool)
        return self.pool.pop()

class Tetris:
    def __init__(self):
        self.grid = [[None for _ in range(GRID_W)] for _ in range(GRID_H)]
        self.bag = Bag()
        self.next_queue = [self.bag.next() for _ in range(5)]
        self.hold: Optional[str] = None
        self.hold_used = False
        self.spawn_new_piece()
        self.score = 0
        self.level = 1
        self.lines_cleared_total = 0
        self.drop_timer = 0
        self.lock_timer: Optional[int] = None
        self.state = 'playing'
        self.flash_rows: List[int] = []
        self.flash_timer = 0
        self.particles: List[Particle] = []
        self.move_dir = 0  # 当前方向 (-1=左, 1=右, 0=无)
        self.move_delay = 0  # 延迟计时器

    def spawn_new_piece(self):
        kind = self.next_queue.pop(0)
        self.next_queue.append(self.bag.next())
        self.current = Piece(kind, 3, 0, 0)
        self.hold_used = False
        if not self.is_valid(self.current):
            self.state = 'gameover'

    def is_valid(self, piece: Piece) -> bool:
        for x, y in piece.cells():
            if x < 0 or x >= GRID_W or y < 0 or y >= GRID_H:
                return False
            if self.grid[y][x] is not None:
                return False
        return True

    def hard_drop(self):
        dist = 0
        p = self.current
        while self.is_valid(p.moved(dy=1)):
            p = p.moved(dy=1)
            dist += 1
        self.current = p
        self.lock_piece()
        self.score += 2 * dist

    def soft_drop(self):
        if self.is_valid(self.current.moved(dy=1)):
            self.current = self.current.moved(dy=1)
            self.score += 1

    def move(self, dx):
        if self.is_valid(self.current.moved(dx=dx)):
            self.current = self.current.moved(dx=dx)
            self.lock_timer = None

    def rotate(self, cw=True):
        rotated = self.current.moved(drot=(1 if cw else -1))
        if self.is_valid(rotated):
            self.current = rotated

    def hold_piece(self):
        if self.hold_used:
            return
        if self.hold is None:
            self.hold = self.current.kind
            self.spawn_new_piece()
        else:
            self.current.kind, self.hold = self.hold, self.current.kind
            self.current.x, self.current.y, self.current.rot = 3, 0, 0
            if not self.is_valid(self.current):
                self.state = 'gameover'
        self.hold_used = True

    def ghost_piece(self) -> Piece:
        p = self.current
        while self.is_valid(p.moved(dy=1)):
            p = p.moved(dy=1)
        return p

    def fix_to_grid(self):
        for x, y in self.current.cells():
            self.grid[y][x] = self.current.kind

    def lock_piece(self):
        self.fix_to_grid()
        self.check_clears()
        if self.state != 'gameover':
            self.spawn_new_piece()
        self.lock_timer = None

    def check_clears(self):
        rows = [y for y in range(GRID_H) if all(self.grid[y][x] for x in range(GRID_W))]
        if rows:
            self.flash_rows = rows
            self.flash_timer = FLASH_TIME

    def apply_line_clear(self):
        if not self.flash_rows:
            return
        for y in self.flash_rows:
            del self.grid[y]
            self.grid.insert(0, [None for _ in range(GRID_W)])
        n = len(self.flash_rows)
        self.lines_cleared_total += n
        add = {1: 100, 2: 300, 3: 500, 4: 800}.get(n, 0) * self.level
        self.score += add
        self.level = 1 + self.lines_cleared_total // 10
        self.flash_rows = []

    def gravity_interval(self) -> int:
        return max(60, int(DROP_START_DELAY * (0.85 ** (self.level - 1))))

    def tick(self, dt_ms: int, keys):
        if self.state != 'playing':
            return

        # if keys[pygame.K_LEFT]:
        #     if self.move_dir != -1:
        #         self.move_dir = -1
        #         self.move_delay = MOVE_REPEAT
        # elif keys[pygame.K_RIGHT]:
        #     if self.move_dir != 1:
        #         self.move_dir = 1
        #         self.move_delay = MOVE_REPEAT
        # else:
        #     self.move_dir = 0
        #     self.move_delay = 0
        # 持续按住移动
        if self.move_dir != 0:
            self.move_delay -= dt_ms
            if self.move_delay <= 0:
                self.move(self.move_dir)
                self.move_delay = MOVE_REPEAT

        # 软降
        if keys[pygame.K_DOWN]:
            self.soft_drop()

        # 闪烁消除处理
        if self.flash_timer > 0:
            self.flash_timer -= dt_ms
            if self.flash_timer <= 0:
                self.apply_line_clear()

        # 自然下落
        self.drop_timer += dt_ms
        interval = self.gravity_interval()
        if self.drop_timer >= interval:
            self.drop_timer = 0
            if self.is_valid(self.current.moved(dy=1)):
                self.current = self.current.moved(dy=1)
            else:
                if self.lock_timer is None:
                    self.lock_timer = 0
                else:
                    self.lock_timer += interval
                if self.lock_timer >= LOCK_DELAY: self.lock_piece()




def block_surface(color):
    surf = pygame.Surface((CELL, CELL), pygame.SRCALPHA)
    glow = tuple(color)
    pygame.draw.rect(surf, (*glow, 60), (1, 1, CELL-2, CELL-2), border_radius=10)
    pygame.draw.rect(surf, (*glow, 120), (3, 3, CELL-6, CELL-6), border_radius=8)
    pygame.draw.rect(surf, (*glow, 230), (4, 4, CELL-8, CELL-8), border_radius=6)
    pygame.draw.rect(surf, (255, 255, 255, 60), (6, 6, CELL-12, (CELL-12)//2), border_radius=6)
    return surf

def draw_text(surface, text, size, pos, center=False, bold=False):
    font = pygame.font.SysFont("arial", size, bold=bold)
    s = font.render(text, True, TEXT_COLOR)
    r = s.get_rect()
    if center:
        r.center = pos
    else:
        r.topleft = pos
    surface.blit(s, r)

def draw_block(screen, x, y, kind):
    if kind not in BLOCK_CACHE:
        BLOCK_CACHE[kind] = block_surface(COLORS[kind])
    screen.blit(BLOCK_CACHE[kind], (BORDER + x * CELL, BORDER + y * CELL))

def draw_grid_background(screen):
    grid_rect = pygame.Rect(BORDER, BORDER, GRID_W*CELL, GRID_H*CELL)
    pygame.draw.rect(screen, PANEL_BG, grid_rect, border_radius=16)
    for y in range(GRID_H + 1):
        pygame.draw.line(screen, GRID_LINE_COLOR, (BORDER, BORDER + y*CELL), (BORDER + GRID_W*CELL, BORDER + y*CELL), 1)
    for x in range(GRID_W + 1):
        pygame.draw.line(screen, GRID_LINE_COLOR, (BORDER + x*CELL, BORDER), (BORDER + x*CELL, BORDER + GRID_H*CELL), 1)

def draw_piece(screen, piece: Piece, ghost=False):
    for x, y in piece.cells():
        if ghost:
            rect = pygame.Rect(BORDER + x*CELL + 4, BORDER + y*CELL + 4, CELL-8, CELL-8)
            pygame.draw.rect(screen, COLORS['GHOST'], rect, width=2, border_radius=6)
        else:
            draw_block(screen, x, y, piece.kind)

def draw_panel(screen, title, area_rect: pygame.Rect):
    pygame.draw.rect(screen, PANEL_BG, area_rect, border_radius=16)
    draw_text(screen, title, 22, (area_rect.x + 12, area_rect.y + 8), bold=True)

def draw_mini_piece(screen, kind, rect: pygame.Rect):
    cells = ROTATIONS[kind][0]
    xs = [x for x, y in cells]
    ys = [y for x, y in cells]
    w = (max(xs) - min(xs) + 1)
    h = (max(ys) - min(ys) + 1)
    scale = min((rect.w - 20) / (w * CELL), (rect.h - 20) / (h * CELL))
    surf = pygame.Surface((rect.w, rect.h), pygame.SRCALPHA)
    for x, y in cells:
        px = (x - min(xs)) * CELL * scale + (rect.w - w * CELL * scale) / 2
        py = (y - min(ys)) * CELL * scale + (rect.h - h * CELL * scale) / 2
        bs = int(CELL * scale)
        block = pygame.transform.smoothscale(BLOCK_CACHE[kind], (bs, bs))
        surf.blit(block, (px, py))
    screen.blit(surf, rect)

def render(t: Tetris, screen):
    screen.fill(BG_COLOR)
    draw_grid_background(screen)
    ghost = t.ghost_piece()
    draw_piece(screen, ghost, ghost=True)
    for y in range(GRID_H):
        for x in range(GRID_W):
            k = t.grid[y][x]
            if k:
                draw_block(screen, x, y, k)
    if t.flash_timer > 0 and t.flash_rows:
        alpha = int(180 * (t.flash_timer / FLASH_TIME))
        flash = pygame.Surface((GRID_W*CELL, CELL), pygame.SRCALPHA)
        flash.fill((255, 255, 255, alpha))
        for row in t.flash_rows:
            screen.blit(flash, (BORDER, BORDER + row*CELL))
    draw_piece(screen, t.current)
    panel_rect = pygame.Rect(BORDER + GRID_W*CELL + 16, BORDER, PANEL_W*CELL, GRID_H*CELL)
    draw_panel(screen, "TETRIS+", panel_rect)
    draw_text(screen, f"Score", 20, (panel_rect.x + 12, panel_rect.y + 48), bold=True)
    draw_text(screen, f"{t.score}", 28, (panel_rect.x + 12, panel_rect.y + 76))
    draw_text(screen, f"Level", 20, (panel_rect.x + 12, panel_rect.y + 112), bold=True)
    draw_text(screen, f"{t.level}", 28, (panel_rect.x + 12, panel_rect.y + 140))
    hold_rect = pygame.Rect(panel_rect.x + 12, panel_rect.y + 190, panel_rect.w - 24, 100)
    draw_panel(screen, "HOLD", hold_rect)
    if t.hold:
        draw_mini_piece(screen, t.hold, hold_rect)
    next_rect = pygame.Rect(panel_rect.x + 12, panel_rect.y + 310, panel_rect.w - 24, 240)
    draw_panel(screen, "NEXT", next_rect)
    for i, k in enumerate(t.next_queue[:3]):
        r = pygame.Rect(next_rect.x + 10, next_rect.y + 40 + i*70, 120, 60)
        draw_mini_piece(screen, k, r)
    draw_text(screen, "←/→ move", 16, (panel_rect.x + 14, panel_rect.bottom - 90))
    draw_text(screen, "Z / X rotate", 16, (panel_rect.x + 14, panel_rect.bottom - 70))
    draw_text(screen, "↓ soft • SPACE hard", 16, (panel_rect.x + 14, panel_rect.bottom - 50))
    draw_text(screen, "C hold • Enter restart", 16, (panel_rect.x + 14, panel_rect.bottom - 30))
    if t.state == 'gameover':
        overlay = pygame.Surface((GRID_W*CELL, GRID_H*CELL), pygame.SRCALPHA)
        overlay.fill((0, 0, 0, 160))
        screen.blit(overlay, (BORDER, BORDER))
        draw_text(screen, "GAME OVER", 48, (BORDER + GRID_W*CELL//2, BORDER + GRID_H*CELL//2 - 20), center=True, bold=True)
        draw_text(screen, f"Score: {t.score}", 28, (BORDER + GRID_W*CELL//2, BORDER + GRID_H*CELL//2 + 28), center=True)

BLOCK_CACHE: Dict[str, pygame.Surface] = {}

def main():
    pygame.init()
    pygame.display.set_caption("TETRIS+ (cool effects)")
    screen = pygame.display.set_mode((WINDOW_W, WINDOW_H))
    clock = pygame.time.Clock()
    for k in COLORS:
        if k != 'GHOST':
            BLOCK_CACHE[k] = block_surface(COLORS[k])
    while True:
        game = Tetris()
        running = True
        while running:
            dt = clock.tick(FPS)
            keys = pygame.key.get_pressed()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    return
                elif event.type == pygame.KEYDOWN and game.state == 'playing':
                    if event.key == pygame.K_SPACE:
                        game.hard_drop()
                    elif event.key == pygame.K_z:
                        game.rotate(cw=False)
                    elif event.key in (pygame.K_UP, pygame.K_x):
                        game.rotate(cw=True)
                    elif event.key == pygame.K_c:
                        game.hold_piece()

                    if event.key == pygame.K_LEFT:
                        game.move(-1)
                        game.move_dir = -1
                        game.move_delay = 150  # 初始延迟(ms)
                    elif event.key == pygame.K_RIGHT:
                        game.move(1)
                        game.move_dir = 1
                        game.move_delay = 150
                elif event.type == pygame.KEYUP and game.state == 'playing':
                    if event.key in (pygame.K_LEFT, pygame.K_RIGHT):
                        game.move_dir = 0
                        game.move_delay = 0
                elif event.type == pygame.KEYDOWN and game.state == 'gameover':
                    if event.key in (pygame.K_RETURN, pygame.K_r):
                        running = False



            game.tick(dt, keys)
            render(game, screen)
            pygame.display.flip()

if __name__ == "__main__":
    main()
