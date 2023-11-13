@echo on
cd ../../build

:: 删除所有文件（除了 CMakeLists.txt）
for /r %%i in (*) do if "%%~nxi" neq "CMakeLists.txt" del "%%i"

:: 删除所有子目录
for /d %%i in (*) do if "%%~nxi" neq "CMakeLists.txt" rmdir /s /q "%%i"