#ifndef PLAYERLAYER_H
#define PLAYERLAYER_H

#include <QObject>
#include "../Interfaces/LayerInterface.h"

class PlayerLayer : public QObject, public LayerInterface
{
    Q_OBJECT

    QImage  _layerImg;
public:
    explicit PlayerLayer(QObject *parent = 0);

signals:
    void signalUpdateView();

public slots:
    void slotMouseOver(int x, int y);

    // LayerInterface interface
public:
    const QImage &LayerImage();
};

#endif // PLAYERLAYER_H
