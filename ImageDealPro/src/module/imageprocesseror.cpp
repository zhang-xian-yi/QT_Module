#include "imageprocesseror.h"
#include <QThreadPool>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QRunnable>
#include <QEvent>
#include <QCoreApplication>
#include <QPointer>
#include <QUrl>
#include <QImage>
#include <QDebug>
#include <QDir>
#include <QImageReader>

//所有调用 图片处理算法的函数指针声明
typedef void (*AlgorithmFunction)(QString source_file,QString dest_file);

class AlgorithmRunnable;
class ExcutedEvent:public QEvent
{
public:
    ExcutedEvent(AlgorithmRunnable* r):
        QEvent(evType()),
        m_runnable(r)
    {

    }

    static QEvent::Type evType()
    {
        if(s_ev_type == QEvent::None)
        {
            s_ev_type = (QEvent::Type)registerEventType();
        }
        return  s_ev_type;
    }
public:
    AlgorithmRunnable* m_runnable;
private:
    static QEvent::Type s_ev_type;
};


QEvent::Type ExcutedEvent::s_ev_type = QEvent::None;

static void _gray(QString source_file,QString dest_file)
{
    qDebug()<<"_gray  source:"<<source_file<<"\tdest file:   "<<dest_file;
    static QImageReader reader(source_file);
    reader.setDecideFormatFromContent(true);

    static QImage image;
    if(reader.canRead() && reader.read(&image))
    {
        qDebug()<<"_gray abort  the file is null";
        return;
    }
    int width =image.width();
    int height = image.height();
    QRgb color;
    int gray;
    for(int i = 0;i<width;++i)
    {
        for(int k =0;k<height;++k)
        {
            color = image.pixel(i,k);
            gray = qGray(color);
            image.setPixel(i,k,qRgba(gray,gray,gray,qAlpha(color)));
        }
    }

    image.save(dest_file);
    qDebug()<<"_gray save";
}
static void _binarize(QString source_file,QString dest_file)
{
    qDebug()<<"_binarize  source:"<<source_file<<"\tdest file:   "<<dest_file;
    QImage image(source_file);
    if( image.isNull())
    {
        return;
    }
    int width = image.width();
    int height = image.height();
    QRgb color;
    QRgb avg;
    QRgb black = qRgb(0,0,0);
    QRgb white = qRgb(255,255,255);
    for(int i = 0;i<width;++i)
    {
        for(int k = 0;k<height;++k)
        {
            color = image.pixel(i,k);
            avg = ( qRed(color) + qGreen(color) + qBlue(color) )/3;
            image.setPixel(i,k,avg >=128 ? white : black);
        }
    }
    image.save(dest_file);
}
static void _negative(QString source_file,QString dest_file)
{
    qDebug()<<"_negative  source:"<<source_file<<"\tdest file:   "<<dest_file;
}
static void _emboss(QString source_file,QString dest_file)
{
    qDebug()<<"_emboss  source:"<<source_file<<"\tdest file:   "<<dest_file;
}
static void _sharpen(QString source_file,QString dest_file)
{
    qDebug()<<"_sharpen  source:"<<source_file<<"\tdest file:   "<<dest_file;
}
static void _soften(QString source_file,QString dest_file)
{
    qDebug()<<"_soften  source:"<<source_file<<"\tdest file:   "<<dest_file;
}

//定义一个函数指针数组 拥有枚举个数的数组
static AlgorithmFunction g_functions[ImageProcesseror::AlgorithmCount] = {
    _gray,
    _binarize,
    _negative,
    _emboss,
    _sharpen,
    _soften
};


class AlgorithmRunnable:public QRunnable
{
public:
    AlgorithmRunnable(QString source_file,QString dest_file,ImageProcesseror::ImageAlgorithm algorithm,QObject* observer):
      m_observer(observer),
      m_source_file_path(source_file),
      m_dest_file_path(dest_file),
      m_algoritrm(algorithm)
    {
    }
    ~AlgorithmRunnable(){
    }

    void run()
    {
        g_functions[m_algoritrm](m_source_file_path,m_dest_file_path);
        QCoreApplication::postEvent(m_observer,new ExcutedEvent(this));
    }
public:
    QPointer<QObject> m_observer;
    QString m_source_file_path;
    QString m_dest_file_path;
    ImageProcesseror::ImageAlgorithm m_algoritrm;
};




class ImageProcesserorPrivate:public QObject
{
public:
    ImageProcesserorPrivate(ImageProcesseror* processor):
        QObject(processor),
        m_processor(processor),
        m_tmp_path(QDir::currentPath())
    {
        ExcutedEvent::evType();
    }
    ~ImageProcesserorPrivate(){}

    bool event(QEvent* e)
    {
        if(ExcutedEvent::evType()  == e->type())
        {
            ExcutedEvent * ee = (ExcutedEvent*) e;
            if(m_runnables.contains(ee->m_runnable) )
            {
                 m_notifiedAlgorithm = ee->m_runnable->m_algoritrm;
                 m_notified_source_file = ee->m_runnable->m_source_file_path;
                 emit m_processor->finished(ee->m_runnable->m_dest_file_path);
                 m_runnables.removeOne(ee->m_runnable);
            }
            delete ee->m_runnable;
            return true;
        }
        return QObject::event(e);
    }

    void process(QString source_file_path,ImageProcesseror::ImageAlgorithm algorithm)
    {
        QFileInfo fi(source_file_path);
        QString dest_file = QString("%1/%2_%3").arg(m_tmp_path).arg((int)algorithm).arg(fi.fileName());
        AlgorithmRunnable * r = new AlgorithmRunnable(source_file_path,dest_file,algorithm,this);
        m_runnables.append(r);
        r->setAutoDelete(false);
        QThreadPool::globalInstance()->start(r);
    }

public:
    ImageProcesseror* m_processor;
    QList<AlgorithmRunnable*> m_runnables;
    QString m_notified_source_file;
    ImageProcesseror::ImageAlgorithm m_notifiedAlgorithm;
    QString m_tmp_path;
};



ImageProcesseror::ImageProcesseror(QObject *parent) : QObject(parent)
  ,m_d(new ImageProcesserorPrivate(this))
{
}

QString ImageProcesseror::getSourceFile()const
{
    return m_d->m_notified_source_file;
}

ImageProcesseror::ImageAlgorithm ImageProcesseror::getAlgorithm() const
{
    return m_d->m_notifiedAlgorithm;
}

void ImageProcesseror::setTempPath(QString tmp_path)
{
    m_d->m_tmp_path = tmp_path;
}

void ImageProcesseror::process(QString file,ImageAlgorithm algorithm)
{
    m_d->process(file,algorithm);
}

void ImageProcesseror::abort(QString file,ImageAlgorithm algorithm)
{
    int size = m_d->m_runnables.size();
    AlgorithmRunnable *r;
    for(int i = 0;i<size;++i)
    {
        r = m_d->m_runnables.at(i);
        if(r->m_source_file_path == file && r->m_algoritrm == algorithm)
        {
            m_d->m_runnables.removeAt(i);
            break;
        }
    }
}

