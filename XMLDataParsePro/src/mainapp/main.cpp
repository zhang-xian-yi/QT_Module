#include <QCoreApplication>
#include <QDir>
#include "xmldataparse/xmldataparsehandle.h"
#include "xmldataparse/descxmlstruct.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XMLDataParseHandle parser;
    QString path = QDir::currentPath();
    path += "/test.xml";

    TagTree * tree = parser.startParseXMLFile(path);


    return a.exec();
}
