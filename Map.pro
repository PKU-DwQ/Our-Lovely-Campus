QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source_file/chatdialog.cpp \
    source_file/imageviewer.cpp \
    main.cpp \
    source_file/mapicon.cpp \
    source_file/movingicon.cpp \
    source_file/navigationwidget.cpp \
    source_file/coverwidget.cpp  \
    source_file/pathgenerator.cpp

HEADERS += \
    head_file/chatdialog.h \
    head_file/imageviewer.h \
    head_file/mapicon.h \
    head_file/movingicon.h \
    head_file/navigationwidget.h \
    head_file/coverwidget.h  \
    head_file/pathgenerator.h

FORMS += \
    chatdialog.ui \
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
    image_database/cover.png \


RESOURCES += \
    basic_data.qrc \
    cat.qrc \
    swan.qrc \
    turtle.qrc
