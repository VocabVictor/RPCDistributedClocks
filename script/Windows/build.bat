@echo on
SETLOCAL EnableDelayedExpansion

:: 清空cmake文件
call clean

:: 设置构建类型，默认为 Release，也可以通过命令行参数指定为 Debug
set BUILD_TYPE=Release
if "%1" neq "" (
    set BUILD_TYPE=%1
)

:: 设置 CMake 项目的根目录为脚本所在目录的上两级
set SCRIPT_DIR=%~dp0
set PROJECT_ROOT_DIR=%SCRIPT_DIR%\..\..\

:: 规范化项目根目录路径
for %%i in ("%PROJECT_ROOT_DIR%") do set PROJECT_ROOT_DIR=%%~fi

:: 设置构建目录
set BUILD_DIR=%PROJECT_ROOT_DIR%build

:: 创建构建目录（如果不存在）
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

:: 进入构建目录
cd "%BUILD_DIR%"

:: 运行 CMake 配置
echo Configuring...
cmake . -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

:: 构建项目
echo Building...
cmake --build . --config %BUILD_TYPE%

:: 返回原始目录
cd "%SCRIPT_DIR%"

:: 结束
echo Build finished.
ENDLOCAL
