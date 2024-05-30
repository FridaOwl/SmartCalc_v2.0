QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/model_calculator.cc \
    ../model/model_credit.cc \
    ../model/model_deposit.cc \
    ../model/polish_notation.cc \
    ../model/string_validation.cc \
    creditwindow.cpp \
    depositwindow.cpp \
    graphwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../controller/controller.h \
    ../model/model_calculator.h \
    ../model/model_credit.h \
    ../model/model_deposit.h \
    ../model/polish_notation.h \
    ../model/string_validation.h \
    creditwindow.h \
    depositwindow.h \
    graphwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    graphwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

