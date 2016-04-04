#include <QDebug>
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
    connect( VisualObserver::Instance().get(), SIGNAL(signalCellSelected(int, int)), SLOT(slotCellSelected(int,int)));
    connect( VisualObserver::Instance().get(), SIGNAL(signalMouseOverCell(QVariant)), SLOT(slotMouseOverCell(QVariant)));
    connect( this, SIGNAL(signalUpdateView()), VisualObserver::Instance().get(), SIGNAL(signalUpdateView()));
}

void PlayerLayer::slotMouseOver(int x, int y)
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    int h = board->sizeVerical();
    int w = board->sizeHorizontal();
    QSize s = puppets::FigureInterface::IconSize();

    _layerImg = QImage(s.width() * w, s.height() * h, QImage::Format_ARGB32_Premultiplied);
    _layerImg.fill(0);
    QPainter painter(&_layerImg);

    drawRect(painter, Qt::red, x, y);
    emit signalUpdateView();
}

void PlayerLayer::slotCellSelected(int x, int y)
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    int h = board->sizeVerical();
    int w = board->sizeHorizontal();
    QSize s = puppets::FigureInterface::IconSize();

    _layerImg = QImage(s.width() * w, s.height() * h, QImage::Format_ARGB32_Premultiplied);
    _layerImg.fill(0);
    QPainter painter(&_layerImg);

    drawRect(painter, Qt::green, x, y);

    emit signalUpdateView();
}

void PlayerLayer::slotMouseOverCell(QVariant variant)
{
    Defs::MovePrimitive m = variant.value<Defs::MovePrimitive>();
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    int h = board->sizeVerical();
    int w = board->sizeHorizontal();
    QSize s = puppets::FigureInterface::IconSize();
    s.rwidth() *= w;
    s.rheight() *= h;

    if (s != _layerImg.size())
    {
        _layerImg = QImage(s.width() * w, s.height() * h, QImage::Format_ARGB32_Premultiplied);
    }

    _layerImg.fill(0);
    QPainter painter(&_layerImg);

    drawRect(painter, Qt::green, m.from.x, m.from.y);
    drawRect(painter, Qt::red, m.to.x, m.to.y);

    emit signalUpdateView();
}

const QImage &PlayerLayer::LayerImage()
{
    return _layerImg;
}

void PlayerLayer::drawRect(QPainter &painter, QColor c, int x, int y)
{
    QSize s = puppets::FigureInterface::IconSize();

    QRect r(x * s.width(), y * s.height(), s.width(), s.height() );
    QPen p(c);
    p.setWidth(2);
    painter.setPen(p);
    painter.drawRect(r);
}
