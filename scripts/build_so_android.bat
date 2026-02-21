@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem Build liblwplocal.so using Android NDK + CMake (Ninja).
rem Outputs: out\arm64-v8a\liblwplocal.so and out\armeabi-v7a\liblwplocal.so

call :detect_ndk
if "%NDK%"=="" (
  echo [ERROR] Android NDK not found.
  echo Set ANDROID_NDK_HOME or install NDK under Android SDK.
  exit /b 1
)

set TOOLCHAIN=%NDK%\build\cmake\android.toolchain.cmake
if not exist "%TOOLCHAIN%" (
  echo [ERROR] toolchain file not found: "%TOOLCHAIN%"
  exit /b 1
)

where cmake >nul 2>nul
if errorlevel 1 (
  echo [ERROR] cmake not found in PATH.
  exit /b 1
)

where ninja >nul 2>nul
if errorlevel 1 (
  echo [ERROR] ninja not found in PATH. Install Ninja or use Visual Studio CMake tools.
  exit /b 1
)

set PLATFORM=android-21

for %%A in (armeabi-v7a arm64-v8a) do (
  echo === Building %%A ===
  set BDIR=build\%%A
  cmake -S .. -B "!BDIR!" -G Ninja ^
    -DANDROID_ABI=%%A ^
    -DANDROID_PLATFORM=%PLATFORM% ^
    -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN%" ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DEF2_USE_REAL_GLES=ON

  if errorlevel 1 exit /b 1

  cmake --build "!BDIR!" -j
  if errorlevel 1 exit /b 1

  if not exist out\%%A mkdir out\%%A

  rem CMake typically places the .so in the build dir root.
  if exist "!BDIR!\liblwplocal.so" (
    copy /Y "!BDIR!\liblwplocal.so" "out\%%A\liblwplocal.so" >nul
  ) else (
    for /r "!BDIR!" %%F in (liblwplocal.so) do (
      copy /Y "%%F" "out\%%A\liblwplocal.so" >nul
      goto :copied_%%A
    )
    :copied_%%A
  )
  echo [OK] out\%%A\liblwplocal.so
  rem Optional: bundle original libgnustl_shared.so next to liblwplocal.so for on-device comparison.
  if exist "bundle\%%A\libgnustl_shared.so" (
    copy /Y "bundle\%%A\libgnustl_shared.so" "out\%%A\libgnustl_shared.so" >nul
    echo [OK] out\%%A\libgnustl_shared.so
  )
)

echo === Done ===
exit /b 0

:detect_ndk
if not "%ANDROID_NDK_HOME%"=="" (
  set NDK=%ANDROID_NDK_HOME%
  exit /b 0
)
if not "%ANDROID_NDK_ROOT%"=="" (
  set NDK=%ANDROID_NDK_ROOT%
  exit /b 0
)
rem Try common SDK locations
if not "%ANDROID_SDK_ROOT%"=="" (
  set SDK=%ANDROID_SDK_ROOT%
) else if not "%LOCALAPPDATA%"=="" (
  set SDK=%LOCALAPPDATA%\Android\Sdk
)

if "%SDK%"=="" exit /b 0
if not exist "%SDK%\ndk" exit /b 0

rem Pick the lexicographically last ndk folder (usually newest).
set NDK=
for /f "delims=" %%D in ('dir /b /ad "%SDK%\ndk" 2^>nul') do (
  set NDKCAND=%SDK%\ndk\%%D
  set NDK=!NDKCAND!
)
exit /b 0
