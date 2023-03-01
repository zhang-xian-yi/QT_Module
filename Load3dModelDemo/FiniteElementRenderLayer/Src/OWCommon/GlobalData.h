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

};
#endif // GLOBALDATA_H
