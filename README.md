# modgcc (map_cmake 分支)

本目录是 `modgcc` 的 CMake 化实验分支工作区：
- 仍然以 **GCC C++20 Modules + module-map** 为核心（保留 `-fmodule-mapper=module-map`）。
- CMake 只负责“编排命令”，实际编译参数与原 tasks 方式一致。

## 环境要求

- Windows
- MinGW GCC（示例：`D:\C++\mingw64\bin\g++.exe`，版本 15.2.0）
- CMake（示例：`D:\C++\CMake\bin\cmake.exe`）
- Ninja（示例：`D:\C++\ninja\ninja.exe`）

> 注意：`.vscode/tasks.json` 里使用了以上**绝对路径**。如果你的安装路径不同，需要自行改成你的路径。

## 关键文件与约定

- `module-map`
  - 必须是 **LF** 换行（CRLF 会导致 g++ 报 `failed reading mapper`）。
  - `.gitattributes` 已强制该文件保持 LF。
- 标准库 header-unit 的共享 CMI 目录（示例）：`D:\C++\gcc_prebuild_stdlib_gcm\15_2_0\D-`
  - `module-map` 里把 `<iostream>/<format>` 的 `.gcm` 映射到该共享目录。
- 本工程自己的模块缓存：仓库根目录 `gcm.cache`（例如 `employee.gcm`）。

## 用 VS Code Tasks 构建/清理

打开 VS Code：`终端(Terminal) -> 运行任务(Run Task...)`，选择下列任务。

### 1) 清理

任务：`清理 CMake 构建产物(还原工程本来面目)`
- 含义：删除整个 `build` 目录 + 根目录 `gcm.cache` + 根目录旧 `main.exe`（如果存在）+ `compile_commands.json`。
- 适用：想从“干净状态”重新配置/构建；或切换 preset 后清理残留。

等价命令（PowerShell）：
```powershell
$root = (Resolve-Path .).Path
Remove-Item -LiteralPath (Join-Path $root 'build') -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath (Join-Path $root 'gcm.cache') -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath (Join-Path $root 'main.exe') -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath (Join-Path $root 'compile_commands.json') -Force -ErrorAction SilentlyContinue
```

任务：`清理 gcm.cache(可选)`
- 含义：只删除根目录 `gcm.cache`。

等价命令（cmd）：
```bat
if exist ".\gcm.cache" rmdir /s /q ".\gcm.cache"
```

### 2) CMake（使用 preset）

本工程有两套 CMake preset（见 `CMakePresets.json`）：
- `ninja-gcc`：普通构建（默认不预编译 stdlib CMI）
- `ninja-gcc-precompile-stdlib`：构建前自动预编译 `<iostream>/<format>` 并同步到共享 CMI 目录

任务：`CMake: configure (ninja-gcc)`
- 含义：配置生成目录 `build/ninja-gcc`。

等价命令：
```powershell
D:\C++\CMake\bin\cmake.exe --preset ninja-gcc
```

任务：`CMake: build (ninja-gcc)`
- 含义：构建 `ninja-gcc` preset。
- 依赖：已设置 `dependsOn`，会先自动执行对应 configure。

等价命令：
```powershell
D:\C++\CMake\bin\cmake.exe --preset ninja-gcc
D:\C++\CMake\bin\cmake.exe --build --preset ninja-gcc
```

任务：`CMake: configure (ninja-gcc-precompile-stdlib)`

等价命令：
```powershell
D:\C++\CMake\bin\cmake.exe --preset ninja-gcc-precompile-stdlib
```

任务：`CMake: build (ninja-gcc-precompile-stdlib)`
- 含义：构建并（按需）预编译标准库 header-unit CMI，再生成可执行文件。
- 依赖：已设置 `dependsOn`，会先自动执行对应 configure。

等价命令：
```powershell
D:\C++\CMake\bin\cmake.exe --preset ninja-gcc-precompile-stdlib
D:\C++\CMake\bin\cmake.exe --build --preset ninja-gcc-precompile-stdlib
```

> 输出位置：CMake 构建生成的 `main.exe` 会落在对应 build 目录中（例如 `build/ninja-gcc/main.exe`）。

### 3) 旧式 g++ tasks（备用/对照）

这些任务不走 CMake，直接调用 g++ 复刻 modules 编译链路。

任务：`预编译 <iostream>`

等价命令：
```powershell
D:\C++\mingw64\bin\g++.exe -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header iostream
```

任务：`预编译 <format>`（依赖 `预编译 <iostream>`）

等价命令：
```powershell
D:\C++\mingw64\bin\g++.exe -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header format
```

任务：`拷贝 std gcm 到共享目录(显示返回码)`（依赖 `预编译 <format>`）
- 含义：把 `gcm.cache\D-` 下生成的 header-unit `.gcm` 复制到共享目录（示例：`D:\C++\gcc_prebuild_stdlib_gcm\15_2_0\D-`）。

等价命令（PowerShell，近似逻辑）：
```powershell
$src = ".\gcm.cache\D-"
$dst = "D:\C++\gcc_prebuild_stdlib_gcm\15_2_0\D-"
New-Item -ItemType Directory -Force -Path $dst | Out-Null
xcopy /E /I /Y ($src + "\*") $dst
exit $LASTEXITCODE
```

任务：`编译 C++20 模块项目`
- 含义：直接用 g++ 编译 `mymodules/employee.cppm` + `src/main.cpp`。
- 关键：必须在仓库根目录运行（因为使用 `-fmodule-mapper=module-map`，并依赖 `module-map` 的相对路径/`$root .`）。
- 输出：生成在仓库根目录 `main.exe`（这是旧方式；CMake 构建输出在 build 目录）。
- 备注：如需观察 CMI 读写路径，可自行额外添加 `-flang-info-module-cmi`。

等价命令：
```powershell
D:\C++\mingw64\bin\g++.exe `
  -std=c++20 -fmodules-ts -g -fdiagnostics-color=always -flang-info-module-cmi `
  -fmodule-mapper=module-map `
  .\mymodules\employee.cppm .\src\main.cpp `
  -o .\main.exe
```

## 常见问题

- VS Code 的 Problems 里出现 `writing CMI 'gcm.cache/employee.gcm'`
  - 这是 g++ 在启用 `-flang-info-module-cmi` 时输出的 `note:`（用于观察 CMI 的读/写路径）。
  - VS Code/CMake Tools 可能会把这类 `note` 收集进 Problems。
  - 这不是编译错误；不想看到的话，把构建命令里的 `-flang-info-module-cmi` 去掉即可。

- CMake configure 里出现 `CMAKE_C_COMPILER` 未被使用的 warning
  - 这是因为本工程只启用了 `CXX` 语言；当前 preset 里仍设置了 `CMAKE_C_COMPILER`。
  - 不影响构建；如你希望消掉 warning，可以在 `CMakePresets.json` 移除该变量。
