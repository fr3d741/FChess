#include <QPainter>

#include "playerlayer.h"

#include "../board.h"
#include "../Observers/visualobserver.h"
#include "../Facade/gameplayfacade.h"
#include "../Interfaces/figure.h"

PlayerLayer::PlayerLayer(QObject *parent) :
    QObject(parent)
{
    connect( VisualObserver::Instance().get(), SIGNAL(signalMouseOver(int, int)), SLOT(slotMouseOver(int,int)));
    connect( this, SIGNAL(signalUpdateView()), VisualObserver::Instance().get(), SIGNAL(signalUpdateView()));
}

void PlayerLayer::slotMouseOver(int x, int y)
{
    Board* board = GameplayFacade::Instance()->GetBoard();
    int h = board->sizeVerical();
    int w = board->sizeHorizontal();
    QSize s = puppets::FigureInterface::IconSize();

    _layerImg = QImage(s.width() * w, s.height() * h, QImage::Format_ARGB32_Premultiplied);
    _layerImg.fill(0);
    QPainter painter(&_layerImg);

    QPen p(QColor( 255, 0, 0, 128));
    QRect r(x * s.width(), y * s.height(), s.width(), s.height() );
    painter.setPen(p);
    painter.drawRect(r);

    emit signalUpdateView();
}

const QImage &PlayerLayer::LayerImage()
{
    return _layerImg;
}
