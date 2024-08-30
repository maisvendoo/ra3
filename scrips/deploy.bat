set ADDON_NAME=ra3
set VERSION=v3.0.1
set DIR_NAME=%ADDON_NAME%-%VERSION%

set PKG_DIR=..\..\package

rem Создаем каталог для пакета
mkdir %PKG_DIR%
mkdir %PKG_DIR%\%DIR_NAME%

rem Создаем структуру каталогов
mkdir %PKG_DIR%\%DIR_NAME%\cfg
mkdir %PKG_DIR%\%DIR_NAME%\docs
mkdir %PKG_DIR%\%DIR_NAME%\data
mkdir %PKG_DIR%\%DIR_NAME%\modules\
mkdir %PKG_DIR%\%DIR_NAME%\modules\%ADDON_NAME%-head
mkdir %PKG_DIR%\%DIR_NAME%\modules\%ADDON_NAME%-middle

rem Копируем модули
xcopy /E /Y ..\..\modules\%ADDON_NAME%-head\*.dll %PKG_DIR%\%DIR_NAME%\modules\%ADDON_NAME%-head
xcopy /E /Y ..\..\modules\%ADDON_NAME%-middle\*.dll %PKG_DIR%\%DIR_NAME%\modules\%ADDON_NAME%-middle

rem Копируем конфиги
xcopy /E /Y ..\cfg\*.* %PKG_DIR%\%DIR_NAME%\cfg\

rem Копируем ресурсы
xcopy /E /Y ..\data\*.* %PKG_DIR%\%DIR_NAME%\data\

rem Копируем документацию
xcopy /E /Y ..\docs\*.pdf %PKG_DIR%\%DIR_NAME%\docs\

rem Архифируем в 7zip
cd %PKG_DIR%\%DIR_NAME%
7z a -r ..\%DIR_NAME%.7z 
cd ..\..\%ADDON_NAME%\scripts