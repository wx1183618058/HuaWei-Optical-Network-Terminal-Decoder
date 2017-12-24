#-------------------------------------------------
#
# Project created by QtCreator 2017-12-23T18:46:45
#
#-------------------------------------------------

QT       -= core gui

TARGET = xyssl
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    aes.c \
    arc4.c \
    base64.c \
    bignum.c \
    certs.c \
    debug.c \
    des.c \
    dhm.c \
    havege.c \
    md2.c \
    md4.c \
    md5.c \
    net.c \
    padlock.c \
    rsa.c \
    sha1.c \
    sha2.c \
    sha4.c \
    ssl_cli.c \
    ssl_srv.c \
    ssl_tls.c \
    timing.c \
    x509parse.c

HEADERS += \
    aes.h \
    arc4.h \
    base64.h \
    bignum.h \
    bn_mul.h \
    certs.h \
    config.h \
    debug.h \
    des.h \
    dhm.h \
    havege.h \
    md2.h \
    md4.h \
    md5.h \
    net.h \
    openssl.h \
    padlock.h \
    rsa.h \
    sha1.h \
    sha2.h \
    sha4.h \
    ssl.h \
    timing.h \
    x509.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    xyssl.pro.user \
    Makefile
