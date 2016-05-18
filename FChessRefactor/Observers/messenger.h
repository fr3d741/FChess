#ifndef MESSENGER_H
#define MESSENGER_H

#include <QObject>
#include "../Interfaces/singleton.h"

class Messenger : public QObject, public Singleton<Messenger>
{
    Q_OBJECT

    friend class Singleton<Messenger>;

    explicit Messenger();
public:

signals:
    void signalMessageToGUI(QString);
};

#endif // MESSENGER_H
