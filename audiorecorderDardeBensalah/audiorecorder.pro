TEMPLATE = app
TARGET = audiorecorder

QT += charts multimedia

win32:INCLUDEPATH += $$PWD

HEADERS = \
    audiodevices.h \
    audiorecorder.h \
    audiolevel.h \
    form_patient.h \
    widget.h \
    xyseriesiodevice.h

SOURCES = \
    audiodevices.cpp \
    form_patient.cpp \
    main.cpp \
    audiorecorder.cpp \
    audiolevel.cpp \
    widget.cpp \
    xyseriesiodevice.cpp

FORMS += audiorecorder.ui \
    audiodevicesbase.ui \
    form_patient.ui

target.path = $$[QT_INSTALL_EXAMPLES]/multimedia/audiorecorder
INSTALLS += target

QT+=widgets
include(../shared/shared.pri)
