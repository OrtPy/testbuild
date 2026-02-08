@echo off
setlocal

REM Install the built debug APK to the connected device.
REM Usage:
REM   run_install.bat

set ROOT=%~dp0
set APK=%ROOT%dist\LwpLocalRpcHarness_debug.apk

if not exist "%APK%" (
  echo [ERROR] APK not found: "%APK%"
  echo         Please run build.bat first.
  exit /b 1
)

echo [1/2] adb install -r ...
adb install -r "%APK%"
if errorlevel 1 (
  echo [ERROR] adb install failed.
  exit /b 1
)

echo [2/2] Launching app...
adb shell monkey -p com.example.lwprpcharness -c android.intent.category.LAUNCHER 1 >nul

echo [OK] Done.
exit /b 0
