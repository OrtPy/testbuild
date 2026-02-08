@echo off
setlocal EnableExtensions EnableDelayedExpansion

REM Collect built APK and copy native libs into .\dist\
REM Called by ..\build.bat

set "ROOT=%~dp0.."
for %%I in ("%ROOT%") do set "ROOT=%%~fI"
set "DIST=%ROOT%\dist"
set "APK_SRC=%ROOT%\app\app\build\outputs\apk\debug\app-debug.apk"
set "APK_DST=%DIST%\LwpLocalRpcHarness_debug.apk"

if not exist "%APK_SRC%" (
  echo [ERROR] APK not found: "%APK_SRC%"
  exit /b 1
)

if not exist "%DIST%" mkdir "%DIST%" >nul 2>&1

copy /Y "%APK_SRC%" "%APK_DST%" >nul
if errorlevel 1 (
  echo [ERROR] Failed to copy APK.
  exit /b 1
)

REM ---------------------------------------------------------------------------
REM Preferred: copy libs from Gradle intermediates (no unpack required)
REM AGP may place merged libs in different folders depending on version.
REM ---------------------------------------------------------------------------

set "LIBSRC="
if exist "%ROOT%\app\app\build\intermediates\merged_native_libs\debug\out\lib" (
  set "LIBSRC=%ROOT%\app\app\build\intermediates\merged_native_libs\debug\out\lib"
) else if exist "%ROOT%\app\app\build\intermediates\merged_jni_libs\debug\out\lib" (
  set "LIBSRC=%ROOT%\app\app\build\intermediates\merged_jni_libs\debug\out\lib"
) else if exist "%ROOT%\app\app\build\intermediates\stripped_native_libs\debug\out\lib" (
  set "LIBSRC=%ROOT%\app\app\build\intermediates\stripped_native_libs\debug\out\lib"
)

if not "%LIBSRC%"=="" (
  if exist "%DIST%\lib" rmdir /S /Q "%DIST%\lib" >nul 2>&1
  mkdir "%DIST%\lib" >nul 2>&1

  REM robocopy returns 0-7 as success
  robocopy "%LIBSRC%" "%DIST%\lib" /E /NFL /NDL /NJH /NJS /NP >nul
  if errorlevel 8 (
    echo [ERROR] Failed to copy lib folder from Gradle intermediates (robocopy errorlevel=%errorlevel%).
    echo         Source: "%LIBSRC%"
    exit /b 1
  )

  REM sanity check
  if not exist "%DIST%\lib\armeabi-v7a" (
    echo [WARN] Copied libs, but "%DIST%\lib\armeabi-v7a" not found.
    echo        Source: "%LIBSRC%"
  )

  exit /b 0
)

REM ---------------------------------------------------------------------------
REM Fallback: unpack APK as zip and copy lib/
REM ---------------------------------------------------------------------------

set "UNPACK=%DIST%\apk_unpacked"
set "TMPZIP=%DIST%\_apk_tmp.zip"

if exist "%UNPACK%" rmdir /S /Q "%UNPACK%" >nul 2>&1
if exist "%TMPZIP%" del /F /Q "%TMPZIP%" >nul 2>&1
copy /Y "%APK_DST%" "%TMPZIP%" >nul

set "EXTRACT_OK=0"

REM 1) tar.exe (Windows 10/11 built-in)
if exist "%SystemRoot%\System32\tar.exe" (
  mkdir "%UNPACK%" >nul 2>&1
  "%SystemRoot%\System32\tar.exe" -xf "%TMPZIP%" -C "%UNPACK%" >nul 2>&1
  if not errorlevel 1 set "EXTRACT_OK=1"
)

REM 2) PowerShell Expand-Archive (call absolute path to avoid PATH/macros)
if "%EXTRACT_OK%"=="0" (
  set "PSEXE=%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe"
  if exist "%PSEXE%" (
    "%PSEXE%" -NoProfile -ExecutionPolicy Bypass -Command ^
      "$ErrorActionPreference='Stop'; Expand-Archive -Force '%TMPZIP%' '%UNPACK%'" >nul 2>&1
    if not errorlevel 1 set "EXTRACT_OK=1"
  )
)

if "%EXTRACT_OK%"=="0" (
  echo [ERROR] Failed to unpack APK.
  echo         Try one of these:
  echo           - Ensure "%SystemRoot%\System32\tar.exe" exists
  echo           - Ensure PowerShell is installed/enabled
  echo           - Install 7-Zip and add 7z.exe to PATH (then we can switch to 7z x)
  exit /b 1
)

if exist "%DIST%\lib" rmdir /S /Q "%DIST%\lib" >nul 2>&1
mkdir "%DIST%\lib" >nul 2>&1

if exist "%UNPACK%\lib" (
  robocopy "%UNPACK%\lib" "%DIST%\lib" /E /NFL /NDL /NJH /NJS /NP >nul
  if errorlevel 8 (
    echo [ERROR] Failed to copy lib folder from unpacked APK (robocopy errorlevel=%errorlevel%).
    exit /b 1
  )
) else (
  echo [WARN] No lib folder found in unpacked APK.
)

del /F /Q "%TMPZIP%" >nul 2>&1

exit /b 0
