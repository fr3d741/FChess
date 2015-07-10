#ifndef BOARDRENDERERIMPL_H
#define BOARDRENDERERIMPL_H

#include <QObject>
#include "../Interfaces/BoardRendererInterface.h"

class BoardRendererImpl : public BoardRendererInterface
{
    Q_OBJECT
public:
    explicit BoardRendererImpl();

signals:

public slots:

    // BoardRendererInterface interface
public:
    QImage Render(Board* board);
};

#endif // BOARDRENDERERIMPL_H
