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
    Icon_image/cat/click/21.png \
    Icon_image/cat/click/22.png \
    Icon_image/cat/click/23.png \
    Icon_image/cat/click/24.png \
    Icon_image/cat/click/25.png \
    Icon_image/cat/click/26.png \
    Icon_image/cat/click/27.png \
    Icon_image/cat/click/28.png \
    Icon_image/cat/click/29.png \
    Icon_image/cat/click/30.png \
    Icon_image/cat/click/31.png \
    Icon_image/cat/click/32.png \
    Icon_image/cat/click/33.png \
    Icon_image/cat/click/34.png \
    Icon_image/cat/click/35.png \
    Icon_image/cat/click/36.png \
    Icon_image/cat/normal/1.png \
    Icon_image/cat/normal/10.png \
    Icon_image/cat/normal/11.png \
    Icon_image/cat/normal/12.png \
    Icon_image/cat/normal/13.png \
    Icon_image/cat/normal/14.png \
    Icon_image/cat/normal/15.png \
    Icon_image/cat/normal/16.png \
    Icon_image/cat/normal/17.png \
    Icon_image/cat/normal/18.png \
    Icon_image/cat/normal/19.png \
    Icon_image/cat/normal/2.png \
    Icon_image/cat/normal/20.png \
    Icon_image/cat/normal/21.png \
    Icon_image/cat/normal/22.png \
    Icon_image/cat/normal/23.png \
    Icon_image/cat/normal/24.png \
    Icon_image/cat/normal/25.png \
    Icon_image/cat/normal/26.png \
    Icon_image/cat/normal/27.png \
    Icon_image/cat/normal/28.png \
    Icon_image/cat/normal/29.png \
    Icon_image/cat/normal/3.png \
    Icon_image/cat/normal/30.png \
    Icon_image/cat/normal/31.png \
    Icon_image/cat/normal/32.png \
    Icon_image/cat/normal/33.png \
    Icon_image/cat/normal/34.png \
    Icon_image/cat/normal/35.png \
    Icon_image/cat/normal/36.png \
    Icon_image/cat/normal/4.png \
    Icon_image/cat/normal/5.png \
    Icon_image/cat/normal/6.png \
    Icon_image/cat/normal/7.png \
    Icon_image/cat/normal/8.png \
    Icon_image/cat/normal/9.png \
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
