# Шаблон проекта - динамическая библиотека (DLL)
TEMPLATE = lib
# Задаем те библиотеки QT, которые нам пригодятся
QT -= gui
QT += xml

# Имя итогового файла DLL и путь, куда он должен быть помещен после
# сборки
TARGET = joint-ra3-sme
DESTDIR = $$(RRS_DEV_ROOT)/modules/ra3-head

# Библиотеки симулятора, с которыми компонуется DLL локомотива
LIBS += -L$$(RRS_DEV_ROOT)/bin -lCfgReader
LIBS += -L$$(RRS_DEV_ROOT)/bin -lphysics
LIBS += -L$$(RRS_DEV_ROOT)/bin -lvehicle
LIBS += -L$$(RRS_DEV_ROOT)/bin -ldevice
LIBS += -L$$(RRS_DEV_ROOT)/bin -lfilesystem

# Путь к необходимым заголовочным файлам
INCLUDEPATH += ./include
INCLUDEPATH += ../ra3-equipment/include
INCLUDEPATH += $$(RRS_DEV_ROOT)/sdk/include

# Указываем файлы, включаемые в проект
HEADERS += $$files(./include/*.h)
HEADERS += $$files(../ra3-equipment/include/*.h)
SOURCES += $$files(./src/*.cpp)
