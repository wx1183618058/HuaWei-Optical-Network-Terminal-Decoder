#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T15:00:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = huawei
TEMPLATE = app
#CONFIG += static
CONFIG(static): DEFINES += QUAZIP_STATIC
TRANSLATIONS += chinese.ts

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        huawei.cpp \
        cfgfile.cpp \
        xmlfile.cpp \
        aescrypt.cpp


HEADERS += \
        huawei.h \
        cfgfile.h \
        xmlfile.h \
        aescrypt.h


FORMS += \
        huawei.ui


RESOURCES += \
    res.qrc

win32 {
RC_FILE += \
    logo.rc
}

#quzaip
INCLUDEPATH += $$PWD/../quazip
DEPENDPATH += $$PWD/../quazip
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../quazip/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../quazip/debug/ -lquazipd
else:unix: LIBS += -L$$OUT_PWD/../quazip/ -lquazip
static {
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../quazip/release/libquazip.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../quazip/debug/libquazipd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../quazip/release/quazip.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../quazip/debug/quazipd.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../quazip/libquazip.a
}

#xyssl
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../xyssl/release/ -lxyssl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../xyssl/debug/ -lxyssl
else:unix: LIBS += -L$$OUT_PWD/../xyssl/ -lxyssl

INCLUDEPATH += $$PWD/../xyssl
DEPENDPATH += $$PWD/../xyssl

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xyssl/release/libxyssl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xyssl/debug/libxyssl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xyssl/release/xyssl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xyssl/debug/xyssl.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../xyssl/libxyssl.a

#zlib
INCLUDEPATH += $ZLIB
LIBS += -L $ZLIB -lz
