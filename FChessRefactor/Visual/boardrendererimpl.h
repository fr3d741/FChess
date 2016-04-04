#ifndef BOARDRENDERERIMPL_H
#define BOARDRENDERERIMPL_H

class Board;

#include <memory>
#include <QObject>
#include "../Interfaces/BoardRendererInterface.h"
#include "../Interfaces/LayerInterface.h"

class BoardRendererImpl : public QObject, public BoardRendererInterface, public LayerInterface
{
    Q_OBJECT

    QImage _layerImg;
public:
    explicit BoardRendererImpl();

signals:

public slots:
    void slotBoardChanged(std::shared_ptr<IBoard> board);

    // BoardRendererInterface interface
public:
    QImage Render(std::shared_ptr<IBoard> board);

    // LayerInterface interface
    const QImage &LayerImage();
};

#endif // BOARDRENDERERIMPL_H
