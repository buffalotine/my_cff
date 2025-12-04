QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application.cpp \
    config/navigationconfig.cpp \
    service/pefileservice.cpp \
    view/addressconverterview.cpp \
    view/dosheaderview.cpp \
    view/fileheaderview.cpp \
    view/hexeditorview.cpp \
    view/optionalheaderview.cpp \
    view/mainwindow.cpp \
    view/navigationview.cpp \
    view/notimplementview.cpp \
    view/ntheaderview.cpp \
    view/sectionheaderview.cpp


HEADERS += \
    enums/navigationitemtypeenum.h \
    config/navigationconfig.h \
    service/pefileservice.h \
    view/addressconverterview.h \
    view/dosheaderview.h \
    view/fileheaderview.h \
    view/hexeditorview.h \
    view/optionalheaderview.h \
    view/mainwindow.h \
    utils/logger.h \
    view/navigationview.h \
    view/notimplementview.h \
    view/ntheaderview.h \
    view/sectionheaderview.h



FORMS += \
    ui/mainwindow.ui \
    ui/notimplementview.ui \
    ui/hexeditorview.ui \
    ui/sectionheaderview.ui \
    ui/sectionheaderview.ui \
    ui/addressconverterview.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
