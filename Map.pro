QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    source_file/imagewidget.cpp \
    source_file/mapicon.cpp \
    source_file/movingicon.cpp \
    source_file/navigationwidget.cpp \
    source_file/coverwidget.cpp  \
    source_file/pathgenerator.cpp \
    source_file/chatdialog.cpp \
    source_file/imageviewer.cpp

HEADERS += \
    head_file/chatdialog.h \
    head_file/imageviewer.h \
    head_file/imagewidget.h \
    head_file/mapicon.h \
    head_file/movingicon.h \
    head_file/navigationwidget.h \
    head_file/coverwidget.h  \
    head_file/pathgenerator.h \

FORMS += \
    ui/chatdialog.ui \
    ui/imagewidget.ui \
    ui/movingicon.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.json \
    image_database/cover.png \


RESOURCES += \
    rc/basic_data.qrc \
    rc/cat.qrc \
    rc/crane.qrc \
    rc/gecko.qrc \
    rc/swan.qrc \
    rc/turtle.qrc
