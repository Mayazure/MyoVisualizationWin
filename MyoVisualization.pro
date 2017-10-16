#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T11:55:22
#
#-------------------------------------------------

QT       += core gui
QT    += datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

contains(TARGET, qml.*) {
    QT += qml quick
}

TARGET = MyoVisualization
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    datacollector.cpp \
    adapter.cpp \
    qcustomplot.cpp \
    graphwindow.cpp \
    podwindow.cpp \
    myobutton.cpp \
    scatterwindow.cpp \
    scatterdatamodifier.cpp \
    scatterwindow.cpp \
    fileadapter.cpp

HEADERS  += mainwindow.h \
    myo/cxx/detail/ThrowOnError.hpp \
    myo/cxx/impl/Hub_impl.hpp \
    myo/cxx/impl/Myo_impl.hpp \
    myo/cxx/impl/Pose_impl.hpp \
    myo/cxx/DeviceListener.hpp \
    myo/cxx/Hub.hpp \
    myo/cxx/Myo.hpp \
    myo/cxx/Pose.hpp \
    myo/cxx/Quaternion.hpp \
    myo/cxx/Vector3.hpp \
    myo/libmyo/detail/visibility.h \
    myo/libmyo.h \
    myo/myo.hpp \
    datacollector.h \
    adapter.h \
    qcustomplot.h \
    graphwindow.h \
    podwindow.h \
    myobutton.h \
    scatterwindow.h \
    scatterdatamodifier.h \
    scatterwindow.h \
    fileadapter.h

FORMS    += mainwindow.ui \
    graphwindow.ui \
    podwindow.ui \
    scatterwindow.ui \
    scatterwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lmyo64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lmyo64

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES +=

RESOURCES += \
    icon.qrc
RC_FILE = icon.rc
