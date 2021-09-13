# Шаблон проекта - динамическая библиотека (DLL)
TEMPLATE = lib
# Задаем те библиотеки QT, которые нам пригодятся
QT -= gui
QT += xml

# Имя итогового файла DLL и путь, куда он должен быть помещен после
# сборки
TARGET = ep1m
DESTDIR = $$(RRS_DEV_ROOT)/modules/$$join(TARGET,,,)

# Библиотеки симулятора, с которыми компонуется DLL локомотива
LIBS += -L$$(RRS_DEV_ROOT)/bin -lCfgReader
LIBS += -L$$(RRS_DEV_ROOT)/bin -lphysics
LIBS += -L$$(RRS_DEV_ROOT)/bin -lvehicle
LIBS += -L$$(RRS_DEV_ROOT)/bin -ldevice
LIBS += -L$$(RRS_DEV_ROOT)/bin -lfilesystem

# Путь к необходимым заголовочным файлам
INCLUDEPATH += ./include
INCLUDEPATH += $$(RRS_DEV_ROOT)/sdk/include

# Указываем файлы, включаемые в проект
HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
