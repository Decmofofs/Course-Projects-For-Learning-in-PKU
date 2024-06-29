QT       += core gui
QT       += qml
QT       += quickwidgets
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    HeightGraphOperator.cpp \
    STrandom.cpp \
    color_extension.cpp \
    heightgraph.cpp \
    height_reader.cpp \
    hydraulicerosionwidget.cpp \
    math_expand.cpp \
    main.cpp \
    mainwindow.cpp \
    midpointwidget.cpp \
    objwriter.cpp \
    perlinnoisewidget.cpp \
    picturewidget.cpp \
    setcolor.cpp \
    valuenoise.cpp \
    valuenoisewidget.cpp \
    view3dwidget.cpp \
    PerlinNoise.cpp \
    MidPoint.cpp \
    HydraulicErosion.cpp

HEADERS += \
    STrandom.h \
    color_extension.h \
    hydraulicerosionwidget.h \
    mainwindow.h \
    heightgraph.h \
    height_reader.h \
    math_expand.h \
    midpointwidget.h \
    objwriter.h \
    perlinnoisewidget.h \
    picturewidget.h \
    setcolor.h \
    valuenoise.h \
    valuenoisewidget.h \
    view3dwidget.h \
    PerLinNoise.h \
    MidPoint.h \
    HydraulicErosion.h

FORMS += \
    hydraulicerosionwidget.ui \
    mainwindow.ui \
    midpointwidget.ui \
    perlinnoisewidget.ui \
    picturewidget.ui \
    setcolor.ui \
    valuenoisewidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qml start.qml
