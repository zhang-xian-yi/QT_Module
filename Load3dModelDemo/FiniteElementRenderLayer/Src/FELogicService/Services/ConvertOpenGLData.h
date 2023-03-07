#ifndef CONVERTOPENGLDATA_H
#define CONVERTOPENGLDATA_H

#include "Src/FELogicService/DataEntity/FEFileData.h"
#include "Src/FELogicService/OpenGLEntity/FEModel.h"
//将FEFileData 转换为OpenGL渲染所需要的数据

class ConvertOpenGLData
{
public:
    //将文件数据转化内opengl所需要的内部数据
    QSharedPointer<FEModel> Convert(QSharedPointer<FEFileData> pFEFileData);

private:
    QSharedPointer<FEModel> m_pFEModel;//有限元数据
};

#endif // CONVERTOPENGLDATA_H
