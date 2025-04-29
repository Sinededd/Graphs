QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    expressionitem.cpp \
    griditem.cpp \
    main.cpp \
    mainwindow.cpp \
    mathexpression.cpp \
    mathformconverter.cpp \
    mathparser.cpp \
    paintingarea.cpp \
    paintingscene.cpp

HEADERS += \
    expressionitem.h \
    griditem.h \
    mainwindow.h \
    mathexpression.h \
    mathformconverter.h \
    mathparser.h \
    paintingarea.h \
    paintingscene.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Geoo/Geoo.qss
