TEMPLATE = lib

QT += core
QT += gui
QT += widgets
QT += opengl
QT += xml

TARGET = mfdu-display

DESTDIR = $$(RRS_DEV_ROOT)/modules/ra3-head

LIBS += -L$$(RRS_DEV_ROOT)/bin -ldisplay
LIBS += -L$$(RRS_DEV_ROOT)/bin -lCfgReader


INCLUDEPATH += ./include
INCLUDEPATH += $$(RRS_DEV_ROOT)/sdk/include


HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
RESOURCES += $$files(./resources/*.qrc)
