#ifndef GLOBAL_H
#define GLOBAL_H

#include <QTextCodec>


#define QDEBUG 0
#define DEBUG_LED_OPER 0

#define FromQString(x) QTextCodec::codecForLocale()->fromUnicode(x).toStdString()
#define ToQString(x) QTextCodec::codecForLocale()->toUnicode((x).c_str())


#endif // GLOBAL_H
