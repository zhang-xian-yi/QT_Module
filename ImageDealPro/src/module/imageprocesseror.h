#ifndef IMAGEPROCESSEROR_H
#define IMAGEPROCESSEROR_H

#include <QObject>
#include <QString>
class ImageProcesserorPrivate;

class ImageProcesseror : public QObject
{
    Q_OBJECT
    Q_ENUMS(ImageAlgorithm)
    //将该属性注册到元对象系统中
    Q_PROPERTY(QString source_file READ getSourceFile)
    Q_PROPERTY(ImageAlgorithm algorithm READ getAlgorithm)
public:
    explicit ImageProcesseror(QObject *parent = nullptr);
    enum ImageAlgorithm{
        Gray = 0,
        Binarize,
        Negative,
        Emboss,
        Sharpen,
        Soften,
        AlgorithmCount
    };
    QString getSourceFile()const;
    ImageAlgorithm getAlgorithm()const;
    void setTempPath(QString tmp_path);
signals:
    //通知关注者 图像处理完毕
    void finished(QString new_file_);
    //供用户程序调用
    void progress(int value_);
public slots:
    void process(QString file_,ImageAlgorithm algorithm_);
    void abort(QString file_,ImageAlgorithm algorithm_);
private:
    //预先声明的类 只能用指针引用
    ImageProcesserorPrivate *m_d;
};

#endif // IMAGEPROCESSEROR_H
