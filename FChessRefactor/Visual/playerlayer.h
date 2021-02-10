#ifndef PLAYERLAYER_H
#define PLAYERLAYER_H

#include <QObject>
#include <QVariant>
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

    void slotCellSelected(int x, int y);

    void slotMouseOverCell(QVariant variant);

    // LayerInterface interface
public:
    const QImage &LayerImage();

private:
    void drawRect(QPainter& painter, QColor c, int x, int y);
};

#endif // PLAYERLAYER_H
