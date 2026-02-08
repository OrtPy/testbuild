@echo off
setlocal EnableExtensions EnableDelayedExpansion

REM Build Debug APK and collect artifacts into .\dist\
REM Usage: build.bat

set ROOT=%~dp0
set APPDIR=%ROOT%app
set DIST=%ROOT%dist

if not exist "%APPDIR%\gradlew.bat" (
  echo [ERROR] gradlew.bat not found: "%APPDIR%\gradlew.bat"
  exit /b 1
)

pushd "%APPDIR%" || exit /b 1

echo [1/2] Building debug APK...
call gradlew.bat --no-daemon :app:assembleDebug
if errorlevel 1 (
  echo [ERROR] Gradle build failed.
  popd
  exit /b 1
)

popd

echo [2/2] Collecting artifacts...
call "%ROOT%scripts\collect_artifacts.bat"
if errorlevel 1 (
  echo [ERROR] Failed to collect artifacts.
  exit /b 1
)

echo [OK] Done.
echo   APK : "%DIST%\LwpLocalRpcHarness_debug.apk"
echo   LIB : "%DIST%\lib\armeabi-v7a\"
exit /b 0
