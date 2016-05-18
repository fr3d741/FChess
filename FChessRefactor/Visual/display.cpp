#include <QPainter>

#include "display.h"
#include "../Interfaces/figure.h"
#include "boardrendererimpl.h"
#include "../Observers/gameplayobserver.h"
#include "../Observers/visualobserver.h"
#include "playerlayer.h"

namespace chessVisialization
{

Display::Display(QWidget *parent, Qt::WindowFlags f )
    :QWidget(parent, f)
    ,_layers()
{
    setMouseTracking( true );
    _layers.push_back(new BoardRendererImpl());
    _layers.push_back(new PlayerLayer(this));

    connect(VisualObserver::Instance().get(), SIGNAL(signalUpdateView()), SLOT(update()), Qt::QueuedConnection);
}

void Display::slotRotateRight()
{

}

void Display::slotRotateLeft()
{

}

void Display::paintEvent( QPaintEvent * )
{
    QPainter p(this);
    //p.drawImage( rect(), _displayImage );
    p.setCompositionMode(QPainter::CompositionMode_SourceOver);
    for(QVector<LayerInterface*>::iterator it = _layers.begin(); it != _layers.end(); ++it) {
        p.drawImage( QPoint(0,0), (*it)->LayerImage() );
    }
}

}
