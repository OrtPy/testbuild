@echo off
setlocal
set APP_HOME=%~dp0
set CLASSPATH=%APP_HOME%gradle\wrapper\gradle-wrapper.jar

if not "%JAVA_HOME%"=="" (
  set JAVA_EXEC=%JAVA_HOME%\bin\java.exe
) else (
  set JAVA_EXEC=java
)

"%JAVA_EXEC%" -classpath "%CLASSPATH%" org.gradle.wrapper.GradleWrapperMain %*
endlocal
