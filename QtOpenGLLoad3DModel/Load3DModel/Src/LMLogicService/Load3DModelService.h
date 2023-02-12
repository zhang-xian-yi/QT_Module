#ifndef LOAD3DMODELSERVICE_H
#define LOAD3DMODELSERVICE_H

class Scene; //场景

namespace Load3dModelNS
{
    class Load3DModelService
    {
    public:
        Load3DModelService();
        ~Load3DModelService();
    public:
        Scene* Load3DModelFromFile(const QString& modelPath);
    private:
        Scene *m_host;
    };
}



#endif // LOAD3DMODELSERVICE_H
