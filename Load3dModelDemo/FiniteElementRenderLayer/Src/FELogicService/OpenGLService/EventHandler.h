#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


class EventHandler:public QObject
{
    Q_OBJECT
public:
    EventHandler();
public:
    bool OnEvent(QEvent& e);

private:

};

#endif // EVENTHANDLER_H
