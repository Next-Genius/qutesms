# -------------------------------------------------
# Project created by QtCreator 2009-04-16T12:04:36
# -------------------------------------------------
QT += xml \
    network
TARGET = QuteSms
TEMPLATE = app
DEPENDPATH += . resources
ICON = resources/icon32.ico

SOURCES += contact.cpp \
    member.cpp \
    contacts.cpp \
    messages.cpp \
    message.cpp \
    smshttp.cpp \
    main.cpp
HEADERS += smshttp.h \
    contacts.h \
    contact.h \
    member.h \
    messages.h \
    message.h
FORMS += smshttp.ui \
    contacts.ui \
    messages.ui \
    message.ui \
    contact.ui \
    member.ui \
    add.ui \
    help.ui
RESOURCES += resources/resources.qrc
