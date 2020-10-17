
QT  += sql

HEADERS += \
    $$PWD/sqlglobal.h

include($$PWD/sqlite/sqlite.pri)
include($$PWD/entity/entity.pri)
#include($$PWD/mysql/mysql.pri)

INCLUDEPATH += $$PWD/sqlite/
INCLUDEPATH += $$PWD
