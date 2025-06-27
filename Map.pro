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
    image_database/cover.png \
    test/0.png \
    test/1.png \
    test/10.png \
    test/11.png \
    test/12.png \
    test/13.png \
    test/14.png \
    test/15.png \
    test/16.png \
    test/17.png \
    test/18.png \
    test/19.png \
    test/2.png \
    test/3.png \
    test/4.png \
    test/5.png \
    test/6.png \
    test/7.png \
    test/8.png \
    test/9.png

RESOURCES += \
    image.qrc
