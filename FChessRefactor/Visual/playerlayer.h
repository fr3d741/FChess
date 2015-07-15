#ifndef PLAYERLAYER_H
#define PLAYERLAYER_H

#include <QObject>

class PlayerLayer : public QObject
{
    Q_OBJECT
public:
    explicit PlayerLayer(QObject *parent = 0);

signals:

public slots:
    void slotMouseOver(int, int);
};

#endif // PLAYERLAYER_H
