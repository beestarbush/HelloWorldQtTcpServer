QT -= gui
QT += core network sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApplicationData.cpp \
    ApplicationLogic.cpp \
    database/DatabaseController.cpp \
    dataobjects/IDataObject.cpp \
    dataobjects/NodeInfoDataObject.cpp \
    dataobjects/RfidReaderDataObject.cpp \
    communication/tcp/TcpController.cpp \
    communication/tcp/TcpHandler.cpp \
    communication/MessageParser.cpp \
    main.cpp \
    utils/Utils.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ApplicationData.h \
    ApplicationLogic.h \
    ReaderDataCallback.h \
    database/DatabaseController.h \
    database/DatabaseDefinitions.h \
    dataobjects/IDataObject.h \
    dataobjects/NodeInfoDataObject.h \
    dataobjects/RfidReaderDataObject.h \
    communication/MessageDefinitions.h \
    communication/MessageParser.h \
    communication/tcp/TcpController.h \
    communication/tcp/TcpHandler.h \
    utils/Utils.h
