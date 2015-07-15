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
    void slotBoardChanged(std::shared_ptr<Board> board);

    // BoardRendererInterface interface
public:
    QImage Render(Board* board);

    // LayerInterface interface
    const QImage &LayerImage();
};

#endif // BOARDRENDERERIMPL_H
