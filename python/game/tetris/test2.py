import pygame
import random
import sys
from typing import List, Tuple

# 初始化pygame
pygame.init()

# 游戏常量
SCREEN_WIDTH = 850
SCREEN_HEIGHT = 700
GRID_SIZE = 30
GRID_WIDTH = 10
GRID_HEIGHT = 20
OFFSET_X = 250
OFFSET_Y = 50

# 颜色定义（使用更鲜艳的颜色）
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (40, 40, 40)
DARK_GRAY = (20, 20, 20)
CYAN = (0, 255, 255)
YELLOW = (255, 255, 0)
PURPLE = (255, 0, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 100, 255)
ORANGE = (255, 165, 0)

# 方块形状定义
SHAPES = [
    [[1, 1, 1, 1]],  # I
    [[1, 1], [1, 1]],  # O
    [[0, 1, 0], [1, 1, 1]],  # T
    [[1, 1, 0], [0, 1, 1]],  # S
    [[0, 1, 1], [1, 1, 0]],  # Z
    [[1, 0, 0], [1, 1, 1]],  # L
    [[0, 0, 1], [1, 1, 1]]   # J
]

SHAPE_COLORS = [CYAN, YELLOW, PURPLE, GREEN, RED, BLUE, ORANGE]


class Particle:
    """粒子特效类"""
    def __init__(self, x: int, y: int, color: Tuple[int, int, int]):
        self.x = x
        self.y = y
        self.vx = random.uniform(-5, 5)
        self.vy = random.uniform(-10, -2)
        self.color = color
        self.life = 60
        self.size = random.randint(3, 8)

    def update(self):
        self.x += self.vx
        self.y += self.vy
        self.vy += 0.5  # 重力
        self.life -= 1

    def draw(self, screen: pygame.Surface):
        if self.life > 0:
            alpha = int(255 * (self.life / 60))
            color = (*self.color, alpha)
            s = pygame.Surface((self.size * 2, self.size * 2), pygame.SRCALPHA)
            pygame.draw.circle(s, color, (self.size, self.size), self.size)
            screen.blit(s, (int(self.x - self.size), int(self.y - self.size)))


class Tetromino:
    """俄罗斯方块类"""
    def __init__(self, x: int, y: int):
        self.shape_index = random.randint(0, len(SHAPES) - 1)
        self.shape = SHAPES[self.shape_index]
        self.color = SHAPE_COLORS[self.shape_index]
        self.x = x
        self.y = y
        self.rotation = 0

    def get_shape(self) -> List[List[int]]:
        """获取当前旋转状态的形状"""
        return self.shape

    def rotate(self):
        """旋转方块"""
        self.shape = list(zip(*self.shape[::-1]))


class TetrisGame:
    """俄罗斯方块游戏主类"""
    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Tetris Game")
        self.clock = pygame.time.Clock()

        # 使用支持中文的系统字体
        try:
            self.font = pygame.font.SysFont('microsoftyahei', 36)
            self.small_font = pygame.font.SysFont('microsoftyahei', 24)
        except:
            # 如果微软雅黑不可用，尝试其他中文字体
            try:
                self.font = pygame.font.SysFont('simhei', 36)
                self.small_font = pygame.font.SysFont('simhei', 24)
            except:
                # 如果都不可用，使用默认字体
                self.font = pygame.font.SysFont('arial', 36)
                self.small_font = pygame.font.SysFont('arial', 24)

        self.grid = [[0 for _ in range(GRID_WIDTH)] for _ in range(GRID_HEIGHT)]
        self.grid_colors = [[BLACK for _ in range(GRID_WIDTH)] for _ in range(GRID_HEIGHT)]

        self.current_piece = Tetromino(GRID_WIDTH // 2 - 1, 0)
        self.next_piece = Tetromino(GRID_WIDTH // 2 - 1, 0)

        self.score = 0
        self.level = 1
        self.lines_cleared = 0
        self.fall_time = pygame.time.get_ticks()
        self.fall_speed = 500  # 毫秒

        self.particles = []
        self.game_over = False

        self.animation_offset = 0
        self.clear_animation = []

        # 按键重复延迟
        self.move_delay = 100  # 毫秒
        self.last_move_time = 0
        self.rotate_delay = 200  # 旋转延迟
        self.last_rotate_time = 0

        # 重启反馈
        self.restart_flash = 0

    def reset_game(self):
        """重置游戏"""
        self.grid = [[0 for _ in range(GRID_WIDTH)] for _ in range(GRID_HEIGHT)]
        self.grid_colors = [[BLACK for _ in range(GRID_WIDTH)] for _ in range(GRID_HEIGHT)]

        self.current_piece = Tetromino(GRID_WIDTH // 2 - 1, 0)
        self.next_piece = Tetromino(GRID_WIDTH // 2 - 1, 0)

        self.score = 0
        self.level = 1
        self.lines_cleared = 0
        self.fall_time = pygame.time.get_ticks()
        self.fall_speed = 500

        self.particles = []
        self.game_over = False

        self.last_move_time = 0
        self.last_rotate_time = 0
        self.restart_flash = 30  # 闪烁30帧

    def draw_grid(self):
        """绘制游戏网格"""
        # 绘制背景渐变
        for y in range(GRID_HEIGHT):
            color_value = 20 + int((y / GRID_HEIGHT) * 30)
            color = (color_value, color_value, color_value + 10)
            pygame.draw.rect(self.screen, color,
                           (OFFSET_X, OFFSET_Y + y * GRID_SIZE,
                            GRID_WIDTH * GRID_SIZE, GRID_SIZE))

        # 绘制网格线
        for x in range(GRID_WIDTH + 1):
            pygame.draw.line(self.screen, GRAY,
                           (OFFSET_X + x * GRID_SIZE, OFFSET_Y),
                           (OFFSET_X + x * GRID_SIZE, OFFSET_Y + GRID_HEIGHT * GRID_SIZE))
        for y in range(GRID_HEIGHT + 1):
            pygame.draw.line(self.screen, GRAY,
                           (OFFSET_X, OFFSET_Y + y * GRID_SIZE),
                           (OFFSET_X + GRID_WIDTH * GRID_SIZE, OFFSET_Y + y * GRID_SIZE))

    def draw_block(self, x: int, y: int, color: Tuple[int, int, int], alpha: int = 255):
        """绘制单个方块（带发光效果）"""
        pos_x = OFFSET_X + x * GRID_SIZE
        pos_y = OFFSET_Y + y * GRID_SIZE

        # 外发光效果
        glow_surface = pygame.Surface((GRID_SIZE + 10, GRID_SIZE + 10), pygame.SRCALPHA)
        glow_color = (*color, alpha // 3)
        pygame.draw.rect(glow_surface, glow_color, (0, 0, GRID_SIZE + 10, GRID_SIZE + 10), border_radius=5)
        self.screen.blit(glow_surface, (pos_x - 5, pos_y - 5))

        # 主方块
        block_surface = pygame.Surface((GRID_SIZE - 2, GRID_SIZE - 2), pygame.SRCALPHA)
        block_color = (*color, alpha)
        pygame.draw.rect(block_surface, block_color, (0, 0, GRID_SIZE - 2, GRID_SIZE - 2), border_radius=3)

        # 高光效果
        highlight_color = tuple(min(c + 80, 255) for c in color) + (alpha // 2,)
        pygame.draw.rect(block_surface, highlight_color, (2, 2, GRID_SIZE - 10, GRID_SIZE - 10), border_radius=2)

        self.screen.blit(block_surface, (pos_x + 1, pos_y + 1))

    def draw_piece(self, piece: Tetromino, offset_x: int = 0, offset_y: int = 0, alpha: int = 255):
        """绘制方块"""
        shape = piece.get_shape()
        for y, row in enumerate(shape):
            for x, cell in enumerate(row):
                if cell:
                    self.draw_block(piece.x + x + offset_x, piece.y + y + offset_y, piece.color, alpha)

    def draw_ghost(self):
        """绘制虚影（显示方块将落在哪里）"""
        ghost_y = self.current_piece.y
        while self.valid_move(self.current_piece.x, ghost_y + 1, self.current_piece.shape):
            ghost_y += 1

        shape = self.current_piece.get_shape()
        for y, row in enumerate(shape):
            for x, cell in enumerate(row):
                if cell:
                    self.draw_block(self.current_piece.x + x, ghost_y + y, self.current_piece.color, 50)

    def draw_ui(self):
        """绘制UI界面"""
        # 左侧信息栏
        # 标题
        title = self.font.render("俄罗斯方块", True, WHITE)
        self.screen.blit(title, (20, 30))

        # 分数
        score_text = self.small_font.render(f"得分: {self.score}", True, WHITE)
        self.screen.blit(score_text, (30, 100))

        # 等级
        level_text = self.small_font.render(f"等级: {self.level}", True, WHITE)
        self.screen.blit(level_text, (30, 135))

        # 消除行数
        lines_text = self.small_font.render(f"消除: {self.lines_cleared}", True, WHITE)
        self.screen.blit(lines_text, (30, 170))

        # 操作说明
        controls = [
            "操作说明:",
            "← → : 移动",
            "↑ : 旋转",
            "↓ : 快速下落",
            "空格: 瞬间落地"
        ]
        for i, text in enumerate(controls):
            control_text = self.small_font.render(text, True, WHITE)
            self.screen.blit(control_text, (30, 250 + i * 30))

        # 右侧预览区
        # 下一个方块标题
        next_text = self.small_font.render("下一个方块:", True, WHITE)
        self.screen.blit(next_text, (OFFSET_X + GRID_WIDTH * GRID_SIZE + 30, 80))

        # 绘制下一个方块预览（使用像素坐标而不是网格坐标）
        preview_x = OFFSET_X + GRID_WIDTH * GRID_SIZE + 50
        preview_y = 130
        shape = self.next_piece.get_shape()
        for y, row in enumerate(shape):
            for x, cell in enumerate(row):
                if cell:
                    pos_x = preview_x + x * GRID_SIZE
                    pos_y = preview_y + y * GRID_SIZE
                    # 绘制预览方块
                    block_surface = pygame.Surface((GRID_SIZE - 2, GRID_SIZE - 2), pygame.SRCALPHA)
                    pygame.draw.rect(block_surface, self.next_piece.color,
                                   (0, 0, GRID_SIZE - 2, GRID_SIZE - 2), border_radius=3)
                    self.screen.blit(block_surface, (pos_x + 1, pos_y + 1))

    def valid_move(self, new_x: int, new_y: int, shape: List[List[int]]) -> bool:
        """检查移动是否有效"""
        for y, row in enumerate(shape):
            for x, cell in enumerate(row):
                if cell:
                    grid_x = new_x + x
                    grid_y = new_y + y

                    if grid_x < 0 or grid_x >= GRID_WIDTH or grid_y >= GRID_HEIGHT:
                        return False
                    if grid_y >= 0 and self.grid[grid_y][grid_x]:
                        return False
        return True

    def lock_piece(self):
        """锁定当前方块到网格"""
        shape = self.current_piece.get_shape()
        for y, row in enumerate(shape):
            for x, cell in enumerate(row):
                if cell:
                    grid_y = self.current_piece.y + y
                    grid_x = self.current_piece.x + x
                    if 0 <= grid_y < GRID_HEIGHT:
                        self.grid[grid_y][grid_x] = 1
                        self.grid_colors[grid_y][grid_x] = self.current_piece.color

    def clear_lines(self):
        """清除完整的行"""
        lines_to_clear = []
        for y in range(GRID_HEIGHT):
            if all(self.grid[y]):
                lines_to_clear.append(y)

        if lines_to_clear:
            # 生成粒子特效
            for y in lines_to_clear:
                for x in range(GRID_WIDTH):
                    color = self.grid_colors[y][x]
                    for _ in range(10):
                        px = OFFSET_X + x * GRID_SIZE + GRID_SIZE // 2
                        py = OFFSET_Y + y * GRID_SIZE + GRID_SIZE // 2
                        self.particles.append(Particle(px, py, color))

            # 清除行
            for y in lines_to_clear:
                del self.grid[y]
                del self.grid_colors[y]
                self.grid.insert(0, [0 for _ in range(GRID_WIDTH)])
                self.grid_colors.insert(0, [BLACK for _ in range(GRID_WIDTH)])

            # 更新分数
            lines_count = len(lines_to_clear)
            self.lines_cleared += lines_count
            self.score += lines_count * 100 * self.level

            # 提升等级
            self.level = self.lines_cleared // 10 + 1
            self.fall_speed = max(100, 500 - (self.level - 1) * 50)

    def hard_drop(self):
        """瞬间落地"""
        drop_distance = 0
        while self.valid_move(self.current_piece.x, self.current_piece.y + 1, self.current_piece.shape):
            self.current_piece.y += 1
            drop_distance += 1

        self.score += drop_distance * 2
        self.lock_piece()
        self.clear_lines()
        self.spawn_new_piece()

    def spawn_new_piece(self):
        """生成新方块"""
        self.current_piece = self.next_piece
        self.next_piece = Tetromino(GRID_WIDTH // 2 - 1, 0)

        if not self.valid_move(self.current_piece.x, self.current_piece.y, self.current_piece.shape):
            self.game_over = True

    def update(self):
        """更新游戏状态"""
        # 更新重启闪烁效果
        if self.restart_flash > 0:
            self.restart_flash -= 1

        if self.game_over:
            return

        # 自动下落
        current_time = pygame.time.get_ticks()
        if current_time - self.fall_time > self.fall_speed:
            if self.valid_move(self.current_piece.x, self.current_piece.y + 1, self.current_piece.shape):
                self.current_piece.y += 1
            else:
                self.lock_piece()
                self.clear_lines()
                self.spawn_new_piece()
            self.fall_time = current_time

        # 更新粒子
        self.particles = [p for p in self.particles if p.life > 0]
        for particle in self.particles:
            particle.update()

    def draw(self):
        """绘制游戏画面"""
        self.screen.fill(DARK_GRAY)

        self.draw_grid()

        # 绘制已锁定的方块
        for y in range(GRID_HEIGHT):
            for x in range(GRID_WIDTH):
                if self.grid[y][x]:
                    self.draw_block(x, y, self.grid_colors[y][x])

        # 绘制虚影
        self.draw_ghost()

        # 绘制当前方块
        self.draw_piece(self.current_piece)

        # 绘制UI
        self.draw_ui()

        # 绘制粒子特效
        for particle in self.particles:
            particle.draw(self.screen)

        # 重启闪烁效果（放在最后以确保可见）
        if self.restart_flash > 0:
            flash_alpha = int((self.restart_flash / 30) * 150)
            flash_surface = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.SRCALPHA)
            flash_surface.fill((100, 255, 100, flash_alpha))
            self.screen.blit(flash_surface, (0, 0))

        # 游戏结束提示
        if self.game_over:
            game_over_text = self.font.render("游戏结束!", True, RED)
            restart_text = self.small_font.render("按 R 键或 回车键 重新开始", True, WHITE)
            quit_text = self.small_font.render("按 ESC 退出游戏", True, GRAY)
            text_rect = game_over_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 20))
            restart_rect = restart_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 30))
            quit_rect = quit_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 70))

            # 半透明背景
            overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.SRCALPHA)
            overlay.fill((0, 0, 0, 180))
            self.screen.blit(overlay, (0, 0))

            self.screen.blit(game_over_text, text_rect)
            self.screen.blit(restart_text, restart_rect)
            self.screen.blit(quit_text, quit_rect)

        pygame.display.flip()

    def handle_input(self):
        """处理输入"""
        current_time = pygame.time.get_ticks()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False

            if event.type == pygame.KEYDOWN:
                # ESC键退出游戏
                if event.key == pygame.K_ESCAPE:
                    return False

                if self.game_over:
                    # 游戏结束时按R或回车重新开始
                    print(f"游戏结束时按下的键: {event.key}, 键名: {pygame.key.name(event.key)}")
                    print(f"pygame.K_r = {pygame.K_r}, pygame.K_RETURN = {pygame.K_RETURN}")

                    # 多种方式检测R键
                    key_is_r = False
                    if event.key == pygame.K_r:
                        key_is_r = True
                        print("通过 pygame.K_r 检测到R键")
                    # if event.key == 114:  # r的ASCII码
                    #     key_is_r = True
                    #     print("通过ASCII码114检测到R键")
                    # if hasattr(event, 'unicode') and event.unicode.lower() == 'r':
                    #     key_is_r = True
                    #     print(f"通过unicode检测到R键: {event.unicode}")

                    if key_is_r or event.key == pygame.K_RETURN:
                        print("检测到R键或回车键，正在重启游戏...")
                        self.reset_game()
                    continue

                # 即时响应按键（首次按下）
                if event.key == pygame.K_LEFT:
                    if self.valid_move(self.current_piece.x - 1, self.current_piece.y, self.current_piece.shape):
                        self.current_piece.x -= 1
                        self.last_move_time = current_time

                elif event.key == pygame.K_RIGHT:
                    if self.valid_move(self.current_piece.x + 1, self.current_piece.y, self.current_piece.shape):
                        self.current_piece.x += 1
                        self.last_move_time = current_time

                elif event.key == pygame.K_DOWN:
                    if self.valid_move(self.current_piece.x, self.current_piece.y + 1, self.current_piece.shape):
                        self.current_piece.y += 1
                        self.score += 1
                        self.last_move_time = current_time

                elif event.key == pygame.K_UP:
                    rotated_shape = list(zip(*self.current_piece.shape[::-1]))
                    if self.valid_move(self.current_piece.x, self.current_piece.y, rotated_shape):
                        self.current_piece.rotate()
                        self.last_rotate_time = current_time

                elif event.key == pygame.K_SPACE:
                    self.hard_drop()

        # 持续按键检测（长按快速移动）
        if not self.game_over and current_time - self.last_move_time > self.move_delay:
            keys = pygame.key.get_pressed()

            if keys[pygame.K_LEFT]:
                if self.valid_move(self.current_piece.x - 1, self.current_piece.y, self.current_piece.shape):
                    self.current_piece.x -= 1
                    self.last_move_time = current_time

            elif keys[pygame.K_RIGHT]:
                if self.valid_move(self.current_piece.x + 1, self.current_piece.y, self.current_piece.shape):
                    self.current_piece.x += 1
                    self.last_move_time = current_time

            if keys[pygame.K_DOWN]:
                if self.valid_move(self.current_piece.x, self.current_piece.y + 1, self.current_piece.shape):
                    self.current_piece.y += 1
                    self.score += 1
                    self.last_move_time = current_time

        return True

    def run(self):
        """运行游戏主循环"""
        running = True
        while running:
            running = self.handle_input()
            self.update()
            self.draw()
            self.clock.tick(60)

        pygame.quit()
        sys.exit()


if __name__ == "__main__":
    game = TetrisGame()
    game.run()
