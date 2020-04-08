QT       += core gui printsupport opengl
#QT += androidextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QCUSTOMPLOT_USE_OPENGL
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CsvFileProcessor.cpp \
    src/CustomFileDialog.cpp \
    src/DataMath.cpp \
    src/QCustomPlot/qcustomplot.cpp \
    src/main.cpp \
    src/SimpleCsvLogAnalyzer.cpp

HEADERS += \
    src/CsvFileProcessor.h \
    src/CustomFileDialog.h \
    src/DataMath.h \
    src/QCustomPlot/qcustomplot.h \
    src/SimpleCsvLogAnalyzer.h

FORMS += \
    src/CustomFileDialog.ui \
    src/DataMath.ui \
    src/SimpleCsvLogAnalyzer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/res/values/libs.xml \
    images/timer.png

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
} else {
    RC_ICONS += "images/analyzing_icon.ico"
}
