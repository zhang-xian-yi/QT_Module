#include "JSONParseUtil.h"


JSONParseUtil::JSONParseUtil()
{
    m_pwriterinfo = new  Json::FastWriter();
    m_preaderinfo = new Json::Reader(Json::Features::strictMode());
}
JSONParseUtil::~JSONParseUtil()
{
    delete m_pwriterinfo;
    delete m_preaderinfo;
}

std::string JSONParseUtil::array2JsonStr(std::string key[], int key_array_len, std::string value[])
{
    Json::Value  writevalueinfo;
    for( int i = 0;i<key_array_len;++i)
    {
        writevalueinfo[ key[i] ] = value[i];
    }
    std::string result = m_pwriterinfo->write(writevalueinfo);
    //std::cout<<"result:"<<result;
    return result;
}

Json::Value JSONParseUtil::translateJson(const std::string strData)
{
    Json::Value root;
    if (m_preaderinfo->parse(strData, root))
    {
       return root;
    }
    return nullptr;
}

std::string JSONParseUtil::getValueByKey(std::string jsonStr, std::string key)
{
    Json::Value root = translateJson(jsonStr);
    return root[key].toStyledString();
}
