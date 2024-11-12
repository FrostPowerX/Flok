@echo off

echo %1 Solution Dir
echo %2 Target Dir

del "%~1bin\FlappyGame.pdb"

xcopy "%~1res" "%~2res" /i /y /s
tar --create --file=FlappyGame_.zip -C "%~1bin" .

pause