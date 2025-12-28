QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bookmessageeditview.cpp \
    bookmessageview.cpp \
    borrowbookeditview.cpp \
    borrowselect.cpp \
    loginview.cpp \
    main.cpp \
    masterview.cpp \
    readerfileeditview.cpp \
    readerfileview.cpp \
    recordview.cpp \
    welcomeview.cpp

HEADERS += \
    bookmessageeditview.h \
    bookmessageview.h \
    borrowbookeditview.h \
    borrowselect.h \
    loginview.h \
    masterview.h \
    readerfileeditview.h \
    readerfileview.h \
    recordview.h \
    welcomeview.h

FORMS += \
    bookmessageeditview.ui \
    bookmessageview.ui \
    borrowbookeditview.ui \
    borrowselect.ui \
    loginview.ui \
    masterview.ui \
    readerfileeditview.ui \
    readerfileview.ui \
    recordview.ui \
    welcomeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
