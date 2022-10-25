QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = Dialog
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=               \
    main.cpp             \
    mainwindow.cpp       \
    circlebutton.cpp     \
    horizontalbutton.cpp \
    verticalbutton.cpp   \
#    generator.cpp       \


HEADERS +=               \
    mainwindow.h         \
    circlebutton.h       \
    horizontalbutton.h   \
    verticalbutton.h     \
#    generator.h         \
