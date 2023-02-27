#ifndef GLOBALDATA_H
#define GLOBALDATA_H

class GlobalData
{
private:
    GlobalData();
    ~GlobalData();
    GlobalData(GlobalData& instance) = delete;
    GlobalData& operator=(const GlobalData& instance) = delete;
public:
    static GlobalData& GetInstance()
    {
        static GlobalData instance;
        return instance;
    }
public:
    bool InitOpenGLFuncEnv();//初始化opengl函数调用环境
public:
    QOpenGLFunctions_4_5_Core* pGLFuncs;
};

#define FILENAME (QFileInfo(__FILE__).fileName().toStdString().c_str())
#define FUNCNAME __FUNCTION__
#define LINENO __LINE__

#define dout ((qDebug().nospace() << FUNCNAME << "(" << FILENAME << ":" << LINENO << "):").space())
//所有的opengl函数指针容器的智能指针返回
#define pGLF    GlobalData::GetInstance().pGLFuncs
#endif // GLOBALDATA_H
