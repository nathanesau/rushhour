######################################################################
# Automatically generated by qmake (3.1) Mon Jan 18 18:56:39 2021
######################################################################

TEMPLATE = app
TARGET = rushhour
INCLUDEPATH += .

QT += widgets

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/car.h \
           src/common.h \
           src/controllers/rushHour.h \
           src/utility/string.h \
           src/widgets/boardWidget.h \
           src/widgets/levelWidget.h \
           src/widgets/mainWidget.h \
           src/widgets/mainWindow.h \
           src/widgets/squareWidget.h
SOURCES += src/car.cpp \
           src/main.cpp \
           src/utility/string.cpp \
           src/widgets/boardWidget.cpp \
           src/widgets/levelWidget.cpp \
           src/widgets/mainWidget.cpp \
           src/widgets/mainWindow.cpp \
           src/widgets/squareWidget.cpp