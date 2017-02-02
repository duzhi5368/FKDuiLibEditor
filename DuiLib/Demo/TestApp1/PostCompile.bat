echo off
copy /y Res\test1.xml ..\..\..\Bin\Debug\test1.xml
copy /y Res\test1.xml ..\..\..\Bin\Release\test1.xml
xcopy Res\Icon ..\..\..\Bin\Debug\Icon\ /e
xcopy Res\Icon ..\..\..\Bin\Release\Icon\ /e
pause