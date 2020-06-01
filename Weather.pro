QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Icon Weather/Cloudy_Moon_big.png \
    Icon Weather/Cloudy_Moon_small.png \
    Icon Weather/Cloudy_Sunny_big.png \
    Icon Weather/Cloudy_Sunny_small.png.png \
    Icon Weather/Cloudy_big.png \
    Icon Weather/Cloudy_small.png \
    Icon Weather/Drip_big.png \
    Icon Weather/Drip_small.png \
    Icon Weather/Foggy_Cloud_big.png \
    Icon Weather/Foggy_Cloud_small.png \
    Icon Weather/Foggy_big.png \
    Icon Weather/Foggy_small.png \
    Icon Weather/Lightning_Cloudy_big.png \
    Icon Weather/Lightning_Cloudy_small.png \
    Icon Weather/Lightning_big.png \
    Icon Weather/Lightning_small.png \
    Icon Weather/Moon_big.png \
    Icon Weather/Moon_small.png \
    Icon Weather/Rainin_big.png \
    Icon Weather/Raining_Moon_big.png \
    Icon Weather/Raining_Moon_small.png \
    Icon Weather/Raining_Sun_big.png \
    Icon Weather/Raining_Sun_small.png \
    Icon Weather/Raining_small.png \
    Icon Weather/Snow_Clody_big.png \
    Icon Weather/Snow_Clody_small.png \
    Icon Weather/Snowing_big.png \
    Icon Weather/Snowing_small.png \
    Icon Weather/Snowy_big.png \
    Icon Weather/Snowy_small.png \
    Icon Weather/Sunny_big.png \
    Icon Weather/Sunny_small.png \
    Icon Weather/Windy_big.png \
    Icon Weather/Windy_small.png \
    Icon Weather/iconfinder_Foggy_5729388.png \
    Icon Weather/iconfinder_Raining_5729383(1).png \
    Icon Weather/iconfinder_Raining_5729383(2).png \
    Icon Weather/iconfinder_Raining_5729383.png
