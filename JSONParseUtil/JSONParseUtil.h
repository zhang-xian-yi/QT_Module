#ifndef JSONPARSEUTIL_H
#define JSONPARSEUTIL_H

#include "jsonparseutil_global.h"
#include <QString>


class JSONPARSEUTILSHARED_EXPORT JSONParseUtil
{
public:
    JSONParseUtil();
    ~JSONParseUtil();
    std::string array2JsonStr(std::string key[],int key_array_len,std::string value[]);
    std::string getValueByKey(std::string jsonStr,std::string key);
private:
    Json::Value translateJson(const std::string strData);
private:
    Json::FastWriter* m_pwriterinfo;
    Json::Reader *m_preaderinfo;
};

#endif // JSONPARSEUTIL_H
