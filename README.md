# 2048 游戏

这是一个使用 C 语言和 Raylib 库实现的 2048 游戏。

## 文件说明

- `main_2048.c` - 独立的 2048 游戏主程序
- `build_2048.bat` - Windows 编译和运行脚本
- `run_debug.bat` - 调试模式批处理脚本
- `setup_vscode.bat` - VS Code 配置快速设置脚本
- `DEBUG_GUIDE.md` - 详细的调试配置指南
- `game_2048_adapter.c` - 游戏大厅适配器版本（需要 game_hall）
- `game_2048_interface.h` - 游戏大厅适配器头文件

## 快速开始

### 方法 1：一键配置 VS Code 调试（最简单）

1. 双击运行 `setup_vscode.bat`
2. 在 VS Code 中打开 `main_2048.c`
3. 按 F5 键开始调试！

### 方法 2：快速运行游戏

双击运行 `build_2048.bat` 即可编译并运行游戏

### 方法 3：调试模式

双击运行 `run_debug.bat`，可以选择：
- 直接运行游戏
- 在 GDB 中调试
- 仅编译不运行

### 方法 4：手动编译

在命令行中执行：

```bash
gcc main_2048.c -o 2048_game.exe -lraylib -lopengl32 -lgdi32 -lwinmm
2048_game.exe
```

## VS Code 调试设置

如果 `setup_vscode.bat` 无法运行，请参照 `DEBUG_GUIDE.md` 中的说明手动配置 VS Code。

## 游戏控制

- 方向键 (↑ ↓ ← →)：移动方块
- R：重新开始游戏
- ESC：关闭窗口

## 游戏规则

- 使用方向键移动所有方块
- 相同数字的方块相遇时会合并成双倍的数字
- 每次移动后会在随机位置生成新的 2 或 4
- 目标是创建一个 2048 的方块！
- 如果无法移动方块且没有空白位置，游戏结束

## 系统要求

- Windows 操作系统
- GCC 编译器（MinGW）
- Raylib 库
