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
    int log_level;
public:
    void InitOpenGLFunc();
    QOpenGLFunctions_3_3_Core* GetGLFunc();
private:
    QOpenGLFunctions_3_3_Core* m_pGLFuncs;
};

#define FILENAME (QFileInfo(__FILE__).fileName().toStdString().c_str())
#define FUNCNAME __FUNCTION__
#define LINENO __LINE__

#define dout ((qDebug().nospace() << FUNCNAME << "(" << FILENAME << ":" << LINENO << "):").space())
#define tab(n) (QByteArray((n) * 4, ' ').data())

#define NO_LOG 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO 3

#define logLV       GlobalData::GetInstance().log_level
#define pGlFuncs    GlobalData::GetInstance().GetGLFunc()

#endif // GLOBALDATA_H
