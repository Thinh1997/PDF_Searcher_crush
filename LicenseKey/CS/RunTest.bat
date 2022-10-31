@echo off
setlocal
call dotnet run
exit /b %errorlevel%
endlocal
