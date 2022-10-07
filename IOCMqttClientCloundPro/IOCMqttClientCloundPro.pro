#-------------------------------------------------
#
# Project created by QtCreator 2020-06-19T13:11:55
#
#-------------------------------------------------

QT       += core gui network
QT       += charts
QT       += sql
QT       += widgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IOCMqttClientCloundPro
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

include(src/mainwight/mainwight.pri)
include(src/databases/mysql.pri)
include(src/ui/ui.pri)
include(src/module/module.pri)


INCLUDEPATH  += $$PWD/src/mainwight
INCLUDEPATH  += $$PWD/src/databases
INCLUDEPATH  += $$PWD/src/ui/line_chart
INCLUDEPATH  += $$PWD/src/ui/user_info
INCLUDEPATH  += $$PWD/src/ui/led_control
INCLUDEPATH  += $$PWD/src/module/bean
INCLUDEPATH  += $$PWD/src/module/json
INCLUDEPATH  += $$PWD/src/module/deal_msg
INCLUDEPATH  += $$PWD/src/module/qtmqtt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS   += -L$$PWD/lib/ -llibmysql
LIBS   += -L$$PWD/lib/ -lJSONParseUtil

LIBS   += -L$$PWD/lib/ -lQt5Mqtt



MOC_DIR = temp/moc
RCC_DIR = temp/rccr
OBJECTS_DIR = temp/obj
UI_HEADERS_DIR = temp/ui
DESTDIR = bin/

win32:RC_FILE = icon.rc
RESOURCES += \
    image.qrc
