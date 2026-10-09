# VS Code 调试 2048 游戏配置指南

## 方法一：手动配置（推荐）

### 1. 修改 tasks.json

在 `.vscode/tasks.json` 中添加以下配置，将 Raylib 库链接参数添加到 args 数组：

```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc.exe 生成活动文件",
            "command": "U:\\WinGW\\mingw64\\bin\\gcc.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-lraylib",
                "-lopengl32",
                "-lgdi32",
                "-lwinmm"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        },
        {
            "type": "cppbuild",
            "label": "Build 2048 Game",
            "command": "U:\\WinGW\\mingw64\\bin\\gcc.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${workspaceFolder}\\main_2048.c",
                "-o",
                "${workspaceFolder}\\2048_game.exe",
                "-lraylib",
                "-lopengl32",
                "-lgdi32",
                "-lwinmm"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": "build",
            "detail": "构建 2048 游戏。"
        }
    ],
    "version": "2.0.0"
}
```

### 2. 创建 launch.json

在 `.vscode` 目录下创建 `launch.json` 文件：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "调试 2048 游戏",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/2048_game.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "U:/WinGW/mingw64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "Build 2048 Game"
        },
        {
            "name": "调试活动文件",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "U:/WinGW/mingw64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: gcc.exe 生成活动文件"
        }
    ]
}
```

## 方法二：使用批处理脚本快速运行

直接双击 `build_2048.bat` 文件即可编译并运行游戏。

## 方法三：命令行编译

在项目目录下打开命令行，执行：

```bash
gcc main_2048.c -o 2048_game.exe -lraylib -lopengl32 -lgdi32 -lwinmm
2048_game.exe
```

## 使用说明

配置完成后：

1. 打开 `main_2048.c` 文件
2. 按 `F5` 键或点击调试按钮
3. 选择 "调试 2048 游戏" 配置
4. 游戏会自动编译并启动

或者直接在 `main_2048.c` 打开的情况下按 `Ctrl+Shift+B` 构建，然后运行生成的 `.exe` 文件。
