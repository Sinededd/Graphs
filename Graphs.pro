QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Math/mathchecker.cpp \
    Math/mathexpression.cpp \
    Math/mathformconverter.cpp \
    Math/mathparser.cpp \
    expressionitem.cpp \
    griditem.cpp \
    main.cpp \
    mainwindow.cpp \
    paintingarea.cpp \
    paintingscene.cpp \
    sceneitem.cpp

HEADERS += \
    Math/mathchecker.h \
    Math/mathexpression.h \
    Math/mathformconverter.h \
    Math/mathparser.h \
    expressionitem.h \
    griditem.h \
    mainwindow.h \
    paintingarea.h \
    paintingscene.h \
    sceneitem.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Geoo/Geoo.qss \
    README.md
