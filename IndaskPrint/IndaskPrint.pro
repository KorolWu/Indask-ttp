QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bitmaps.cpp \
    Camera/MyCamera.cpp \
    Camera/camerawidget.cpp \
    Delegate/labeldelegateV1.cpp \
    Delta/dmcnetcontrol.cpp \
    #ImageHandle/FileDecoder.cpp \
    ImageHandle/ImageDataHelper.cpp \
    ImageHandle/ImageSplitHelper.cpp \
    axisstatuswidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pccandhdcstatuswidget.cpp \
    pccwork.cpp \
    sharedata.cpp \
    stdafx.cpp \
    ttpdevice.cpp

HEADERS += \
    Bitmaps.h \
    Camera/MyCamera.h \
    Camera/camerawidget.h \
    Common.h \
    Delegate/labeldelegateV1.h \
    Delta/DataStruct.h \
    Delta/dmcnetcontrol.h \
    #ImageHandle/FileDecoder.h \
    ImageHandle/ImageDataHelper.h \
    ImageHandle/ImageSplitHelper.h \
    axisstatuswidget.h \
    mainwindow.h \
    pccandhdcstatuswidget.h \
    pccwork.h \
    sharedata.h \
    stdafx.h \
    ttpdevice.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/SDK/include
LIBS += -L$$PWD/SDK/lib/ -lPrinterInterface
#LIBS += -L$$PWD/SDK/lib/ -lEtherCAT_DLL_x64
LIBS += -L$$PWD/SDK/lib/ -lPCI_DMC_x64
LIBS += -L$$PWD/SDK/lib/ -lDataBaseManager
LIBS += -L$$PWD/SDK/lib/ -lMvCameraControl
LIBS += -L$$PWD/SDK/lib/ -lQsLog2
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
