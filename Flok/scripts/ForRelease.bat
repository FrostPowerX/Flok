@echo off

echo %1 Solution Dir
echo %2 Target Dir
echo %3 Delete pdb

if "%3~" == "1" del "%~2\Flok.pdb"

xcopy "%~1res" "%~2\res" /i /y /s
tar --create --file=Flok_.zip -C "%~2" .

pause