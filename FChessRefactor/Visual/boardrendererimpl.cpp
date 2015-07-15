#include <QDebug>
#include <QWidget>
#include <QPainter>
#include "boardrendererimpl.h"
#include "../Facade/gameplayfacade.h"
#include "../Observers/gameplayobserver.h"
#include "../Interfaces/figure.h"

BoardRendererImpl::BoardRendererImpl() :
    BoardRendererInterface()
{
    connect( GameplayObserver::Instance().get(), SIGNAL(signalBoardChanged(std::shared_ptr<Board>)), SLOT(slotBoardChanged(std::shared_ptr<Board>)) );
}

void BoardRendererImpl::slotBoardChanged(std::shared_ptr<Board> board)
{
    Render(board.get());
}

QImage BoardRendererImpl::Render(Board* board)
{
    int h = board->sizeVerical();
    int w = board->sizeHorizontal();
    QSize s = puppets::FigureInterface::IconSize();

    _layerImg = QImage(s.width() * w, s.height() * h, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&_layerImg);
    //Defs::Cell ** cells = board->BoardState();
    Defs::Cell ** cells = Board::boardState;

    for ( int i = 0; i < w; ++i )
    {
        for ( int j = 0; j < h; ++j )
        {
            //! Coloring board
            if ( cells[i][j].cellColor == Defs::White )
            {
                QColor wc( 255, 206, 158, 255);
                painter.fillRect( i * s.width(), j * s.height(), s.width(), s.height(), wc );
            }
            else
            {
                QColor bc( 209, 139, 71, 255);
                painter.fillRect( i * s.width(), j * s.height(), s.width(), s.height(), bc );
            }

            //! Draw puppets
            if ( puppets::PuppetContainer::Instance()->contains( cells[i][j].figure ) )
            {
                QRect r(i * s.width(), j * s.height(), s.width(), s.height());
                painter.drawImage(r, puppets::PuppetContainer::Instance()->value(cells[i][j].figure)->iconImage() );
            }
        }
    }

    return _layerImg;
}

const QImage &BoardRendererImpl::LayerImage()
{
    Render(GameplayFacade::Instance()->GetBoard());
    return _layerImg;
}
