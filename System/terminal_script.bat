@REM @echo off
@REM :loop
@REM cls
@REM type temp_messages.txt
@REM timeout /t 1 > nul
@REM goto loop


@echo off
setlocal enabledelayedexpansion

REM Get the initial file size
set "prevSize=0"

:loop
REM Get the current size of the file
for %%F in (temp_messages.txt) do (
    set "currSize=%%~zF"
)

REM Check if the size has changed
if not "!currSize!"=="!prevSize!" (
    cls
    type temp_messages.txt
    set "prevSize=!currSize!"
)

timeout /t 1 > nul
goto loop