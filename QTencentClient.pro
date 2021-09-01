QT       += core gui network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatform.cpp \
    clientadapter.cpp \
    clientsockethandler.cpp \
    friendlistform.cpp \
    iohandler.cpp \
    itemwidget.cpp \
    main.cpp \
    mymsgitem.cpp \
    mytest.cpp \
    qlabel_doubleclick.cpp \
    registerform.cpp \
    signinform.cpp \

HEADERS += \
    chatform.h \
    clientadapter.h \
    clientsockethandler.h \
    friendlistform.h \
    iohandler.h \
    itemwidget.h \
    mymsgitem.h \
    mytest.h \
    qlabel_doubleclick.h \
    registerform.h \
    signinform.h

FORMS += \
    chatform.ui \
    friendlistform.ui \
    itemwidget.ui \
    mymsgitem.ui \
    registerform.ui \
    signinform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
