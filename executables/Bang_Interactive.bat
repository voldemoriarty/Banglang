@echo off
echo Choose from 'Examples' folder or make a new text file.
echo [Demo] Enter Source: "Examples\Calculate_e.txt"
echo.
set /p source=Enter Source:
echo %source%
bangc %source% blabla
echo.
pause