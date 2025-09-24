#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Cool Tetris with effects — single-file pygame implementation
Author: ChatGPT
Python 3.9+ recommended
Dependencies: pygame (pip install pygame)
"""

import math
import random
import sys
import time
from dataclasses import dataclass, field
from typing import List, Tuple, Optional, Dict

import pygame

# ------------- 游戏配置 -------------
GRID_W, GRID_H = 10, 20     # 游戏网格宽度和高度（单位：格子数）
CELL = 32                   # 每个格子的像素大小
BORDER = 8                  # 游戏区域边框大小
PANEL_W = 7                 # 侧边面板宽度（视觉宽度，非网格格子数）
FPS = 60                    # 游戏帧率

# 计算窗口尺寸
WINDOW_W = BORDER * 2 + GRID_W * CELL + PANEL_W * CELL + 32
WINDOW_H = BORDER * 2 + GRID_H * CELL

# 游戏机制参数
DROP_START_DELAY = 1000        # 初始下落延迟（毫秒，对应等级1的重力）
LOCK_DELAY = 500               # 方块锁定延迟（毫秒）
SOFT_DROP_MULT = 20            # 软降速倍数（比正常重力快多少倍）
FLASH_TIME = 300               # 消除行闪烁时间（毫秒）
PARTICLE_COUNT_PER_BLOCK = 10  # 每个方块产生的粒子数量

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

# 霓虹灯风格的方块颜色
COLORS = {
    'I': (0, 255, 255),     # 青色
    'O': (255, 223, 0),     # 金色
    'T': (186, 85, 211),    # 紫色
    'S': (50, 205, 50),     # 绿色
    'Z': (255, 69, 58),     # 红色
    'J': (65, 105, 225),    # 蓝色
    'L': (255, 140, 0),     # 橙色
    'GHOST': (200, 200, 200),  # 幽灵方块颜色（灰色）
}

# 界面颜色
BG_COLOR = (14, 14, 20)         # 背景颜色（深蓝黑）
GRID_LINE_COLOR = (35, 35, 50)  # 网格线颜色
PANEL_BG = (20, 20, 28)         # 面板背景颜色
TEXT_COLOR = (230, 230, 240)    # 文本颜色（浅灰）


# ------------- 工具函数 -------------
def rotate_point(x, y, cw=True):
    """围绕原点旋转点(x, y)90度（顺时针或逆时针）"""
    return (y, -x) if cw else (-y, x)


def create_rotations(coords):
    """为方块创建4个旋转状态"""
    states = []
    # 确定旋转中心（I形方块特殊处理）
    origin = (1.5, 1.5) if coords == TETROMINO_SHAPES['I'] else (1, 1)
    cx, cy = origin
    # 将坐标转换为相对于旋转中心
    base = [(x - cx, y - cy) for x, y in coords]

    # 生成4个旋转状态
    for i in range(4):
        states.append([(round(x + cx), round(y + cy)) for (x, y) in base])
        base = [rotate_point(x, y, cw=True) for (x, y) in base]  # 旋转坐标
    return states

# 预计算所有方块的旋转状态
ROTATIONS = {k: create_rotations(v) for k, v in TETROMINO_SHAPES.items()}

# 超级旋转系统（简化版踢墙表）
KICKS = {
    # (从, 到): 踢墙测试偏移量
    ('N', 'E'): [(0, 0), (-1, 0), (-1, -1), (0, 2), (-1, 2)],
    ('E', 'S'): [(0, 0), (1, 0), (1, -1), (0, 2), (1, 2)],
    ('S', 'W'): [(0, 0), (1, 0), (1, 1), (0, -2), (1, -2)],
    ('W', 'N'): [(0, 0), (-1, 0), (-1, 1), (0, -2), (-1, -2)],
}
DIRS = ['N', 'E', 'S', 'W']  # 方向缩写：北、东、南、西

# ------------- 数据类 -------------
@dataclass
class Piece:
    """表示当前下落的方块"""
    kind: str
    x: int
    y: int
    rot: int = 0  # 0..3

    def cells(self) -> List[Tuple[int, int]]:
        """返回方块占据的所有格子坐标"""
        return [(self.x + dx, self.y + dy) for dx, dy in ROTATIONS[self.kind][self.rot]]

    def moved(self, dx=0, dy=0, drot=0):
        """返回移动/旋转后的新方块"""
        return Piece(self.kind, self.x + dx, self.y + dy, (self.rot + drot) % 4)

@dataclass
class Particle:
    """表示一个粒子效果"""
    x: float
    y: float
    vx: float
    vy: float
    life: float
    color: Tuple[int, int, int]
    size: float

# ------------- 游戏逻辑 -------------
class Bag:
    """7-bag随机生成器（确保每7个方块包含所有类型）"""

    def __init__(self):
        self.pool = []

    def next(self):
        """获取下一个方块类型"""
        if not self.pool:
            self.pool = list(TETROMINO_SHAPES.keys())
            random.shuffle(self.pool)
        return self.pool.pop()


class Tetris:
    """主游戏类，管理游戏状态和逻辑"""

    def __init__(self):
        # 初始化游戏网格（None表示空，字符串表示方块类型）
        self.grid = [[None for _ in range(GRID_W)] for _ in range(GRID_H)]
        self.bag = Bag()  # 方块生成器
        self.next_queue = [self.bag.next() for _ in range(5)]  # 下一个方块队列
        self.hold: Optional[str] = None  # 暂存的方块
        self.hold_used = False  # 当前回合是否已使用暂存功能

        self.spawn_new_piece()  # 生成新方块

        # 游戏状态
        self.score = 0
        self.level = 1
        self.lines_cleared_total = 0

        # 计时器
        self.drop_timer = 0  # 下落计时器
        self.lock_timer: Optional[int] = None  # 锁定计时器

        # 游戏状态和效果
        self.state = 'playing'  # 游戏状态：playing或gameover
        self.flash_rows: List[int] = []  # 需要闪烁的行
        self.flash_timer = 0  # 闪烁计时器
        self.particles: List[Particle] = []  # 粒子效果列表

        self.last_move_was_soft_drop = False  # 上次移动是否为软降

    def spawn_new_piece(self):
        """生成新方块"""
        kind = self.next_queue.pop(0) if self.next_queue else self.bag.next()
        self.next_queue.append(self.bag.next())  # 补充队列
        self.current = Piece(kind, x=3, y=0, rot=0)  # 创建新方块
        self.hold_used = False  # 重置暂存使用状态

        # 检查游戏是否结束（新方块无法放置）
        if not self.is_valid(self.current):
            self.state = 'gameover'

    def is_valid(self, piece: Piece) -> bool:
        """检查方块位置是否有效（不超出边界且不与其他方块重叠）"""
        for x, y in piece.cells():
            # 检查边界
            if x < 0 or x >= GRID_W or y < 0 or y >= GRID_H:
                return False
            # 检查是否与已有方块重叠
            if self.grid[y][x] is not None:
                return False
        return True

    def hard_drop(self):
        """执行硬降（立即下落到底部）"""
        dist = 0
        p = self.current
        # 计算可以下落的最大距离
        while self.is_valid(p.moved(dy=1)):
            p = p.moved(dy=1)
            dist += 1
        self.current = p
        self.lock_piece()  # 锁定方块
        self.score += 2 * dist  # 硬降奖励分数

    def soft_drop(self):
        """执行软降（加速下落）"""
        if self.is_valid(self.current.moved(dy=1)):
            self.current = self.current.moved(dy=1)
            self.score += 1  # 软降奖励分数
            self.last_move_was_soft_drop = True
        else:
            self.last_move_was_soft_drop = False

    def move(self, dx):
        """水平移动方块"""
        if self.is_valid(self.current.moved(dx=dx)):
            self.current = self.current.moved(dx=dx)
            self.lock_timer = None  # 重置锁定计时器（移动后重新计算锁定时间）

    def rotate(self, cw=True):
        """旋转方块（顺时针或逆时针）"""
        fr = DIRS[self.current.rot]  # 当前方向
        to = DIRS[(self.current.rot + (1 if cw else -1)) % 4]  # 目标方向

        # I形方块使用特殊踢墙表
        kicks = (KICKS.get((fr, to), [(0, 0)]) if self.current.kind != 'I' else
                 [(0, 0), (-2, 0), (1, 0), (-2, -1), (1, 2)])

        # 尝试所有可能的踢墙偏移
        for kx, ky in kicks:
            rotated = self.current.moved(drot=(1 if cw else -1)).moved(dx=kx, dy=ky)
            if self.is_valid(rotated):
                self.current = rotated
                self.lock_timer = None  # 重置锁定计时器
                return

    def hold_piece(self):
        """暂存当前方块"""
        if self.hold_used:  # 每回合只能使用一次暂存
            return

        if self.hold is None:
            # 第一次暂存，直接存储当前方块并生成新方块
            self.hold = self.current.kind
            self.spawn_new_piece()
        else:
            # 交换当前方块和暂存方块
            self.current.kind, self.hold = self.hold, self.current.kind
            self.current.x, self.current.y, self.current.rot = 3, 0, 0  # 重置位置

            # 检查游戏是否结束
            if not self.is_valid(self.current):
                self.state = 'gameover'
        self.hold_used = True  # 标记已使用暂存

    def ghost_piece(self) -> Piece:
        """返回幽灵方块（显示方块最终落点）"""
        p = self.current
        while self.is_valid(p.moved(dy=1)):
            p = p.moved(dy=1)
        return p

    def fix_to_grid(self):
        """将当前方块固定到网格中"""
        for x, y in self.current.cells():
            self.grid[y][x] = self.current.kind

    def lock_piece(self):
        """锁定当前方块并检查消除行"""
        self.fix_to_grid()
        self.check_clears()  # 检查是否有行可以消除

        if self.state != 'gameover':
            self.spawn_new_piece()  # 生成新方块

        self.lock_timer = None  # 重置锁定计时器

    def check_clears(self):
        """检查并标记需要消除的行"""
        # 找出所有已填满的行
        rows = [y for y in range(GRID_H) if all(self.grid[y][x] is not None for x in range(GRID_W))]

        if rows:
            self.flash_rows = rows  # 记录需要闪烁的行
            self.flash_timer = FLASH_TIME  # 设置闪烁计时器

            # 为消除的方块创建粒子效果
            for y in rows:
                for x in range(GRID_W):
                    kind = self.grid[y][x]
                    if kind:
                        for _ in range(PARTICLE_COUNT_PER_BLOCK // 2):
                            # 随机角度和速度
                            ang = random.uniform(0, 2 * math.pi)
                            speed = random.uniform(0.5, 3.0)
                            vx = math.cos(ang) * speed
                            vy = math.sin(ang) * speed - random.uniform(0.5, 2.0)  # 稍微向上

                            # 创建粒子
                            self.particles.append(Particle(
                                x=(x + 0.5) * CELL + BORDER,
                                y=(y + 0.5) * CELL + BORDER,
                                vx=vx, vy=vy,
                                life=random.uniform(0.6, 1.2),
                                color=COLORS[kind],
                                size=random.uniform(2, 4),
                            ))

        # Delay removal until flash is done; handled in update()

    def apply_line_clear(self):
        """实际执行行消除（在闪烁后调用）"""
        if not self.flash_rows:
            return

        # 移除已满的行并在顶部添加新行
        for y in self.flash_rows:
            del self.grid[y]
            self.grid.insert(0, [None for _ in range(GRID_W)])

        # 更新分数和等级
        n = len(self.flash_rows)
        self.lines_cleared_total += n
        # 根据消除行数计算分数（Tetris标准计分）
        add = {1: 100, 2: 300, 3: 500, 4: 800}.get(n, 0) * self.level
        self.score += add
        # 每消除10行提升一个等级
        self.level = 1 + self.lines_cleared_total // 10
        self.flash_rows = []  # 清空闪烁行列表

    def gravity_interval(self) -> int:
        """根据当前等级计算重力间隔（等级越高下落越快）"""
        # 速度随等级提升（最低限制为60ms）
        return max(60, int(DROP_START_DELAY * (0.85 ** (self.level - 1))))

    def tick(self, dt_ms: int, keys):
        """游戏主循环的每帧更新"""
        if self.state != 'playing':
            return

        # 更新粒子效果
        for p in self.particles[:]:
            p.x += p.vx * 60 * (dt_ms / 1000)  # 更新位置
            p.y += p.vy * 60 * (dt_ms / 1000)
            p.vy += 0.08 * 60 * (dt_ms / 1000)  # 重力效果
            p.life -= dt_ms / 1000  # 减少生命周期

            # 移除生命周期结束的粒子
            if p.life <= 0:
                self.particles.remove(p)

        # 闪烁计时器更新
        if self.flash_timer > 0:
            self.flash_timer -= dt_ms
            if self.flash_timer <= 0:
                self.apply_line_clear()  # 闪烁结束后实际消除行

        # 重力/下落逻辑
        self.drop_timer += dt_ms
        interval = self.gravity_interval()

        # 软降加速
        soft = keys[pygame.K_DOWN]
        if soft:
            interval //= SOFT_DROP_MULT

        # 检查是否应该下落
        if self.drop_timer >= interval:
            self.drop_timer = 0
            if self.is_valid(self.current.moved(dy=1)):
                self.current = self.current.moved(dy=1)  # 下落一格
            else:
                # 开始锁定延迟计时
                if self.lock_timer is None:
                    self.lock_timer = 0
                else:
                    self.lock_timer += interval
                    # 锁定延迟到达后锁定方块
                    if self.lock_timer >= LOCK_DELAY:
                        self.lock_piece()

    # ------------- 绘制辅助函数 -------------

def draw_rounded_rect(surface, rect, color, radius=8):
    """绘制圆角矩形"""
    x, y, w, h = rect
    # 绘制矩形主体
    pygame.draw.rect(surface, color, (x + radius, y, w - 2 * radius, h))
    pygame.draw.rect(surface, color, (x, y + radius, w, h - 2 * radius))
    # 绘制四个圆角
    pygame.draw.circle(surface, color, (x + radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + w - radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + radius, y + h - radius), radius)
    pygame.draw.circle(surface, color, (x + w - radius, y + h - radius), radius)

def block_surface(color):
    """创建具有霓虹效果的方块表面"""
    surf = pygame.Surface((CELL, CELL), pygame.SRCALPHA)  # 透明表面
    glow = tuple(color)  # 确保是元组而不是pygame.Color

    # 外发光效果
    pygame.draw.rect(surf, (*glow, 60), (1, 1, CELL - 2, CELL - 2), border_radius=10)
    pygame.draw.rect(surf, (*glow, 120), (3, 3, CELL - 6, CELL - 6), border_radius=8)
    # 实体部分
    pygame.draw.rect(surf, (*glow, 230), (4, 4, CELL - 8, CELL - 8), border_radius=6)
    # 高光效果
    pygame.draw.rect(surf, (255, 255, 255, 60), (6, 6, CELL - 12, (CELL - 12) // 2), border_radius=6)

    return surf


def draw_block(screen, x, y, kind):
    """在指定位置绘制方块"""
    if kind not in BLOCK_CACHE:
        BLOCK_CACHE[kind] = block_surface(COLORS[kind])
    screen.blit(BLOCK_CACHE[kind], (BORDER + x * CELL, BORDER + y * CELL))


def draw_grid_background(screen):
    """绘制网格背景"""
    grid_rect = pygame.Rect(BORDER, BORDER, GRID_W * CELL, GRID_H * CELL)
    pygame.draw.rect(screen, PANEL_BG, grid_rect, border_radius=16)  # 绘制背景

    # 绘制网格线
    for y in range(GRID_H + 1):
        pygame.draw.line(screen, GRID_LINE_COLOR, (BORDER, BORDER + y * CELL),
                         (BORDER + GRID_W * CELL, BORDER + y * CELL), 1)
    for x in range(GRID_W + 1):
        pygame.draw.line(screen, GRID_LINE_COLOR, (BORDER + x * CELL, BORDER),
                         (BORDER + x * CELL, BORDER + GRID_H * CELL), 1)


def draw_text(surface, text, size, pos, center=False, bold=False):
    """绘制文本"""
    font = pygame.font.SysFont("arial", size, bold=bold)
    s = font.render(text, True, TEXT_COLOR)
    r = s.get_rect()
    if center:
        r.center = pos
    else:
        r.topleft = pos
    surface.blit(s, r)

def draw_panel(screen, title, area_rect: pygame.Rect):
    """绘制面板（带标题的圆角矩形）"""
    draw_rounded_rect(screen, area_rect, PANEL_BG, radius=16)
    draw_text(screen, title, 22, (area_rect.x + 12, area_rect.y + 8), bold=True)

def draw_piece(screen, piece: Piece, ghost=False):
    """绘制方块（普通或幽灵）"""
    for x, y in piece.cells():
        if ghost:
            # 绘制幽灵方块（轮廓）
            rect = pygame.Rect(BORDER + x*CELL + 4, BORDER + y*CELL + 4, CELL-8, CELL-8)
            pygame.draw.rect(screen, COLORS['GHOST'], rect, width=2, border_radius=6)
        else:
            draw_block(screen, x, y, piece.kind)


def render(t: Tetris, screen, shake_offset=(0, 0)):
    """渲染游戏画面"""
    screen.fill(BG_COLOR)  # 清屏

    # 绘制网格背景
    draw_grid_background(screen)

    # 绘制幽灵方块
    ghost = t.ghost_piece()
    draw_piece(screen, ghost, ghost=True)

    # 绘制已固定的方块
    for y in range(GRID_H):
        for x in range(GRID_W):
            k = t.grid[y][x]
            if k:
                draw_block(screen, x, y, k)

    # 绘制行消除闪烁效果
    if t.flash_timer > 0 and t.flash_rows:
        alpha = int(180 * (t.flash_timer / FLASH_TIME))  # 计算透明度
        flash = pygame.Surface((GRID_W * CELL, CELL), pygame.SRCALPHA)
        flash.fill((255, 255, 255, alpha))
        for row in t.flash_rows:
            screen.blit(flash, (BORDER, BORDER + row * CELL))

    # 绘制当前方块
    draw_piece(screen, t.current)

    # 绘制粒子效果
    for p in t.particles:
        s = pygame.Surface((int(p.size * 2), int(p.size * 2)), pygame.SRCALPHA)
        # 根据生命周期设置透明度
        pygame.draw.circle(s, (*p.color, int(255 * max(0, min(1, p.life)))),
                           (int(p.size), int(p.size)), int(p.size))
        screen.blit(s, (p.x - p.size + shake_offset[0], p.y - p.size + shake_offset[1]))

    # 绘制侧边面板
    panel_rect = pygame.Rect(BORDER + GRID_W * CELL + 16, BORDER, PANEL_W * CELL, GRID_H * CELL)
    draw_panel(screen, "TETRIS+", panel_rect)

    # 绘制分数和等级
    draw_text(screen, f"Score", 20, (panel_rect.x + 12, panel_rect.y + 40), bold=True)
    draw_text(screen, f"{t.score}", 28, (panel_rect.x + 12, panel_rect.y + 65))
    draw_text(screen, f"Level", 20, (panel_rect.x + 12, panel_rect.y + 95), bold=True)
    draw_text(screen, f"{t.level}", 28, (panel_rect.x + 12, panel_rect.y + 120))

    # 绘制暂存区域
    hold_rect = pygame.Rect(panel_rect.x + 12, panel_rect.y + 160, panel_rect.w - 24, 90)
    draw_panel(screen, "HOLD", hold_rect)
    if t.hold:
        draw_mini_piece(screen, t.hold, hold_rect)

    # 绘制下一个方块预览
    # next_rect = pygame.Rect(panel_rect.x + 12, panel_rect.y + 260, panel_rect.w - 24, panel_rect.h - 322)
    # draw_panel(screen, "NEXT", next_rect)
    # for i, k in enumerate(t.next_queue[:5]):
    #     r = pygame.Rect(next_rect.x + 10, next_rect.y + 40 + i * 70, 120, 60)
    #     draw_mini_piece(screen, k, r)
    next_rect = pygame.Rect(panel_rect.x + 12, panel_rect.y + 260, panel_rect.w - 24, 220)
    draw_panel(screen, "NEXT", next_rect)
    for i, k in enumerate(t.next_queue[:5]):
        r = pygame.Rect(next_rect.x + 10, next_rect.y + 30 + i*40, next_rect.w - 20, 35)
        draw_mini_piece(screen, k, r)

    # 绘制控制提示
    draw_text(screen, "←/→ move", 16, (panel_rect.x + 14, panel_rect.bottom - 110))
    draw_text(screen, "Z / X rotate", 16, (panel_rect.x + 14, panel_rect.bottom - 90))
    draw_text(screen, "↓ soft • SPACE hard", 16, (panel_rect.x + 14, panel_rect.bottom - 70))
    draw_text(screen, "C hold • R restart", 16, (panel_rect.x + 14, panel_rect.bottom - 50))

    # 绘制游戏结束画面
    if t.state == 'gameover':
        overlay = pygame.Surface((GRID_W * CELL, GRID_H * CELL), pygame.SRCALPHA)
        overlay.fill((0, 0, 0, 160))  # 半透明黑色覆盖层
        screen.blit(overlay, (BORDER, BORDER))
        draw_text(screen, "GAME OVER", 48,
                  (BORDER + GRID_W * CELL // 2, BORDER + GRID_H * CELL // 2 - 20),
                  center=True, bold=True)
        draw_text(screen, f"Score: {t.score}", 28,
                  (BORDER + GRID_W * CELL // 2, BORDER + GRID_H * CELL // 2 + 28),
                  center=True)


def draw_mini_piece(screen, kind, rect: pygame.Rect):
    """在指定矩形内绘制小型方块（用于预览和暂存）"""
    cells = ROTATIONS[kind][0]  # 获取方块的默认旋转状态
    xs = [x for x, y in cells]
    ys = [y for x, y in cells]
    w = (max(xs) - min(xs) + 1)  # 计算方块宽度
    h = (max(ys) - min(ys) + 1)  # 计算方块高度

    # 计算缩放比例以适应矩形
    scale = min((rect.w - 20) / (w * CELL), (rect.h - 20) / (h * CELL))

    # 创建临时表面绘制小型方块
    surf = pygame.Surface((rect.w, rect.h), pygame.SRCALPHA)
    for x, y in cells:
        # 计算方块位置（居中显示）
        px = (x - min(xs)) * CELL * scale + (rect.w - w * CELL * scale) / 2
        py = (y - min(ys)) * CELL * scale + (rect.h - h * CELL * scale) / 2
        bs = int(CELL * scale)  # 计算缩放后的方块大小

        # 绘制缩放后的方块
        block = pygame.transform.smoothscale(BLOCK_CACHE[kind], (bs, bs))
        surf.blit(block, (px, py))

    screen.blit(surf, rect)


# 方块表面缓存（避免重复创建）
BLOCK_CACHE: Dict[str, pygame.Surface] = {}


# ------------- 主循环 -------------
def main():
    """游戏主函数"""
    pygame.init()
    pygame.display.set_caption("TETRIS+ (cool effects)")
    screen = pygame.display.set_mode((WINDOW_W, WINDOW_H))
    clock = pygame.time.Clock()

    # 预构建方块表面缓存
    for k in COLORS:
        if k != 'GHOST':
            BLOCK_CACHE[k] = block_surface(COLORS[k])

    game = Tetris()  # 创建游戏实例

    # 设置按键重复（用于平滑的DAS）
    pygame.key.set_repeat(140, 40)

    running = True
    shake = 0  # 屏幕抖动效果
    last_time = pygame.time.get_ticks()

    while running:
        dt = clock.tick(FPS)  # 控制帧率
        keys = pygame.key.get_pressed()  # 获取按键状态

        # 处理事件
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN and game.state == 'playing':
                if event.key == pygame.K_LEFT:
                    game.move(-1)  # 左移
                elif event.key == pygame.K_RIGHT:
                    game.move(1)  # 右移
                elif event.key == pygame.K_DOWN:
                    game.soft_drop()  # 软降
                elif event.key == pygame.K_SPACE:
                    game.hard_drop()  # 硬降
                    shake = 8  # 硬降时屏幕抖动
                elif event.key == pygame.K_z:
                    game.rotate(cw=False)  # 逆时针旋转
                elif event.key == pygame.K_UP or event.key == pygame.K_x:
                    game.rotate(cw=True)  # 顺时针旋转
                elif event.key == pygame.K_c:
                    game.hold_piece()  # 暂存方块
            elif event.type == pygame.KEYDOWN and game.state == 'gameover':
                if event.key == pygame.K_r:
                    game = Tetris()  # 重新开始游戏

        game.tick(dt, keys)  # 更新游戏状态

        # 屏幕抖动效果（消除行和硬降时）
        if game.flash_rows:
            shake = max(shake, 4)
        if shake > 0:
            shake -= 1
            offset = (random.randint(-shake, shake), random.randint(-shake, shake))
        else:
            offset = (0, 0)

        render(game, screen, shake_offset=offset)  # 渲染游戏
        pygame.display.flip()  # 更新显示

    pygame.quit()
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as e:
        print("Error:", e)
        pygame.quit()
