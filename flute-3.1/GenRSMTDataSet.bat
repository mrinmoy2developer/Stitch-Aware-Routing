@echo off
set Degree=%1
set NoOfNets=%2

if "%Degree%"=="" (
    echo Degree is required.
    exit /b
)

if "%NoOfNets%"=="" (
    echo NoOfNets is required.
    exit /b
)

REM Execute the loop
setlocal enabledelayedexpansion
set a=0
set "fname=RSMT-%Degree%-%NoOfNets%.txt"

:loop
if !a! geq %NoOfNets% (
    goto :done
)

rand-pts -r %Degree% >> %fname%
set /a a+=1
goto :loop

:done
echo The RSMTs are generated in the file %fname%
