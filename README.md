# modgcc_branch_mapperservercmake 使用说明

本仓库用于演示/验证 GCC C++20 Modules（含 header-unit/CMI）与 `g++-mapper-server` 的配合，同时提供两套构建方式：

- **直接用 g++ 编译**（对应 VS Code Task：`编译 C++20 模块项目`）
- **通过 CMake + Ninja 构建**（对应 VS Code Task：`CMake: ...`）

> 本文档以当前工程内已写死的工具路径为准（例如 `D:\\C++\\mingw64\\bin\\g++.exe`）。若你的环境路径不同，请同步修改 `.vscode/tasks.json` 与 `CMakePresets.json`。

---

## 前置依赖（按当前配置）

- Windows + PowerShell
- CMake：`D:/C++/CMake/bin/cmake.exe`（见 `.vscode/settings.json`）
- Ninja：`D:/C++/ninja/ninja.exe`（见 `CMakePresets.json`）
- MinGW GCC/G++：`D:/C++/mingw64/bin/gcc.exe`、`D:/C++/mingw64/bin/g++.exe`
- `g++-mapper-server`：需要在 `PATH` 中可找到（直接编译任务里使用 `|@g++-mapper-server ...`）
- 共享 stdlib CMI 目录（示例）：`D:\\C++\\gcc_prebuild_stdlib_gcm\\15_2_0`（其下包含 `D-` 目录）

目录结构（关键点）：

- `mymodules/employee.cppm`：示例模块
- `src/main.cpp`：示例主程序
- `module-map`：mapper-server 相关配置
- `gcm.cache/`：本地生成的 header-unit CMI 缓存（可选）
- `build/`：CMake 构建目录

---

## 如何运行 VS Code Tasks

- 打开命令面板：`Ctrl+Shift+P` → `Tasks: Run Task` → 选择对应任务
- 或直接 `Ctrl+Shift+B` 运行“默认构建任务”（若存在多个默认构建任务，VS Code 可能会提示选择）

任务定义文件：`.vscode/tasks.json`

---

## VS Code 默认构建（Ctrl+Shift+B）怎么选

- 本工程里同时存在多个“build 组”的任务（例如 `CMake: build (ninja-gcc)`、`CMake: build (ninja-gcc-precompile-stdlib)`、`编译 C++20 模块项目`）。
- 当你按 `Ctrl+Shift+B`：
  - 如果 VS Code 能确定唯一的默认构建任务，会直接执行。
  - 如果有多个候选，会弹出列表让你选择要跑哪个。

建议：

- 想走 CMake/Ninja：选 `CMake: build (ninja-gcc)` 或 `CMake: build (ninja-gcc-precompile-stdlib)`。
- 想验证 mapper-server + 共享 CMI 目录是否正常：选 `编译 C++20 模块项目`。

---

## 使用 CMake Tools 扩展（可选）

如果你安装了 VS Code 的 **CMake Tools** 扩展，并且工作区设置了 `cmake.useCMakePresets=always`（本工程已设置），则可以直接用 Presets 工作流：

- 选择配置预设：`Ctrl+Shift+P` → `CMake: Select Configure Preset` → 选择 `ninja-gcc` 或 `ninja-gcc-precompile-stdlib`
- 配置生成：`Ctrl+Shift+P` → `CMake: Configure`
- 构建：`Ctrl+Shift+P` → `CMake: Build`

说明：

- 这些命令本质上等价于本文前面列出的 `cmake --preset ...` 与 `cmake --build --preset ...`。
- 如果你更喜欢“可复现的脚本化命令”，继续使用 Tasks 或直接命令行即可。

---

## Tasks 说明与等价命令

下面每个小节：

- **用途/含义**：这个 Task 做什么
- **何时使用**：什么时候建议跑
- **等价命令（不使用 Task）**：在终端里手动执行的命令

### 1) 清理 CMake 构建产物(还原工程本来面目)

**用途/含义**

- 删除：`build/`、`gcm.cache/`、仓库根目录可能存在的 `main.exe`、`compile_commands.json`

**等价命令（PowerShell）**

在仓库根目录执行：

```powershell
$root = "$PWD"
$build = Join-Path $root 'build'
$gcm = Join-Path $root 'gcm.cache'
$exeRoot = Join-Path $root 'main.exe'
$cc = Join-Path $root 'compile_commands.json'

if (Test-Path -LiteralPath $build) { Remove-Item -LiteralPath $build -Recurse -Force }
if (Test-Path -LiteralPath $gcm) { Remove-Item -LiteralPath $gcm -Recurse -Force }
if (Test-Path -LiteralPath $exeRoot) { Remove-Item -LiteralPath $exeRoot -Force }
if (Test-Path -LiteralPath $cc) { Remove-Item -LiteralPath $cc -Force }
```

---

### 2) CMake: configure (ninja-gcc)

**用途/含义**

- 使用 `CMakePresets.json` 中的 `ninja-gcc` 预设生成 Ninja 工程
- 生成目录：`build/ninja-gcc`

**等价命令**

```powershell
D:\C++\CMake\bin\cmake.exe --preset ninja-gcc
```

---

### 3) CMake: build (ninja-gcc)

**用途/含义**

- 构建 `ninja-gcc` 预设对应的 build 目录
- 该任务会先依赖执行 `CMake: configure (ninja-gcc)`

**等价命令**

```powershell
D:\C++\CMake\bin\cmake.exe --build --preset ninja-gcc
```

如需查看更详细的 Ninja 命令行，可加 `-- -v`：

```powershell
D:\C++\CMake\bin\cmake.exe --build --preset ninja-gcc -- -v
```

---

### 4) CMake: configure (ninja-gcc-precompile-stdlib)

**用途/含义**

- 使用预设 `ninja-gcc-precompile-stdlib` 生成工程
- 该预设继承 `ninja-gcc`，并额外设置 `MODGCC_PRECOMPILE_STDLIB=ON`
- 生成目录：`build/ninja-gcc-precompile-stdlib`

**等价命令**

```powershell
D:\C++\CMake\bin\cmake.exe --preset ninja-gcc-precompile-stdlib
```

---

### 5) CMake: build (ninja-gcc-precompile-stdlib)

**用途/含义**

- 构建 `ninja-gcc-precompile-stdlib` 预设
- 因 `MODGCC_PRECOMPILE_STDLIB=ON`：构建时会先在本仓库生成 std header-unit 的 CMI（`gcm.cache/D-`），并同步到共享目录，再编译 `main.exe`

**等价命令**

```powershell
D:\C++\CMake\bin\cmake.exe --build --preset ninja-gcc-precompile-stdlib
```

建议调试时加 `-- -v`：

```powershell
D:\C++\CMake\bin\cmake.exe --build --preset ninja-gcc-precompile-stdlib -- -v
```

---

### 6) 清理 gcm.cache(可选)

**用途/含义**

- 只删除 `gcm.cache/`，用于强制重新生成本地 header-unit CMI

**等价命令（CMD）**

```bat
if exist "%CD%\gcm.cache" rmdir /s /q "%CD%\gcm.cache"
```

---

### 7) 预编译 <iostream>

**用途/含义**

- 用 GCC 的 header-unit 能力为 `<iostream>` 生成 CMI
- 生成位置通常在仓库根目录 `gcm.cache/D-/.../iostream.gcm`

**等价命令**

```powershell
D:\C++\mingw64\bin\g++.exe -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header iostream
```

---

### 8) 预编译 <format>

**用途/含义**

- 预编译 `<format>`，任务依赖于 `预编译 <iostream>`（顺序执行）

**等价命令**

```powershell
D:\C++\mingw64\bin\g++.exe -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header format
```

---

### 9) 拷贝 std gcm 到共享目录(显示返回码)

**用途/含义**

- 把 `gcm.cache\D-` 下生成的 stdlib CMI 复制到共享目录（示例：`D:\\C++\\gcc_prebuild_stdlib_gcm\\15_2_0\\D-`）
- 便于后续编译直接复用共享 CMI，加快增量构建

**等价命令（PowerShell + xcopy）**

```powershell
$src = "$PWD\gcm.cache\D-"
$dst = "D:\C++\gcc_prebuild_stdlib_gcm\15_2_0\D-"

if (-not (Test-Path -LiteralPath $src)) {
  throw "stdlib cache not found: $src"
}
New-Item -ItemType Directory -Force -Path $dst | Out-Null
xcopy /E /I /Y "$src\*" $dst
$LASTEXITCODE
```

---

### 10) 编译 C++20 模块项目（直接 g++）

**用途/含义**

- 不经过 CMake，直接调用 g++ 编译：`employee.cppm` + `main.cpp`
- 使用 `g++-mapper-server` 进行模块映射（含 stdlib CMI 的共享目录）
- 输出可执行文件：仓库根目录 `main.exe`

**等价命令**

```powershell
D:\C++\mingw64\bin\g++.exe \
  -std=c++20 \
  -fmodules-ts \
  -g \
  -fdiagnostics-color=always \
  -flang-info-module-cmi \
  "-fmodule-mapper=|@g++-mapper-server -r D:\C++\gcc_prebuild_stdlib_gcm\15_2_0 -f -n" \
  "$PWD\mymodules\employee.cppm" \
  "$PWD\src\main.cpp" \
  -o "$PWD\main.exe"
```

> 注意：这里 `-fmodule-mapper=...` 必须作为 **一个整体参数** 传给 g++（外面要加引号），否则其中的 `-f/-n` 可能会被误解析成 g++ 自身参数。

---

## CMake 构建输出位置

- `ninja-gcc`：`build/ninja-gcc/main.exe`
- `ninja-gcc-precompile-stdlib`：`build/ninja-gcc-precompile-stdlib/main.exe`

直接 g++ 任务输出在仓库根目录：`main.exe`

---

## 常见问题

### Q1: 为什么 CMake 构建里要区分 precompile-stdlib？

- `ninja-gcc`：默认 **不**自动预编译标准库 header-unit，直接依赖共享 CMI 目录里的 `iostream.gcm/format.gcm`（更快、更干净）。
- `ninja-gcc-precompile-stdlib`：用于“从干净环境一键生成 stdlib CMI 并同步到共享目录”，适合升级 GCC/stdlib 或共享目录缺失时。
