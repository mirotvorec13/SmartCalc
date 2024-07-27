QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
QMAKE_CFLAGS_WARN_ON -= -Wextra
QMAKE_CXXFLAGS_WARN_ON -= -Wextra


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    PlotLibrary/qcustomplot.h \
    creditcalc.h \
    mainwindow.h \
    PlotView.h \
    validator.h

SOURCES += \
    PlotLibrary/qcustomplot.cpp \
    creditcalc.cpp \
    main.cpp \
    mainwindow.cpp \
    PlotView.cpp \
    validator.cpp

DESTDIR = SmartCalc

LIBS += -L../backend -l:s21_calc.a

FORMS += \
    PlotView.ui \
    creditcalc.ui \
    mainwindow.ui

macx:ICON = ../src/imagess/app.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    PlotLibrary/GPL.txt


