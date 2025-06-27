QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    foganimationwidget.cpp \
    imageviewer.cpp \
    main.cpp \
    mapicon.cpp \
    movingicon.cpp \
    navigationwidget.cpp \
    coverwidget.cpp

HEADERS += \
    foganimationwidget.h \
    foganimationwidget.hmationwidget.h \
    imageviewer.h \
    mapicon.h \
    movingicon.h \
    navigationwidget.h \
    coverwidget.h

FORMS += \
    movingicon.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icon/1.jpg \
    icon/2.jpg \
    image_database/cover.png

RESOURCES += \
    image.qrc
