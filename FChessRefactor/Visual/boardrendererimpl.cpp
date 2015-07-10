#include <QWidget>
#include <QPainter>
#include "boardrendererimpl.h"
#include "../Interfaces/figure.h"

BoardRendererImpl::BoardRendererImpl() :
    BoardRendererInterface()
{
}

QImage BoardRendererImpl::Render(Board* board)
{
    int h = board->sizeVerical();
    int w = board->sizeHorizontal();
    QSize s = puppets::FigureInterface::IconSize();

    QImage img(s.width() * w, s.height() * h, QImage::Format_ARGB32);
    QPainter painter(&img);
    Defs::Cell ** cells = board->BoardState();

//    int x = _board->sizeHorizontal();
//    int y = _board->sizeVerical();
//    int w = width();
//    int h = height();
//    int cw = w / x;
//    int ch = h / y;
    //int side = std::min( cw, ch );
    for ( int i = 0; i < w; ++i )
    {
        for ( int j = 0; j < h; ++j )
        {
            //! Coloring board
            if ( cells[i][j].cellColor == Defs::White )
            {
                QColor wc( 255, 206, 158);
                painter.fillRect( i * s.width(), j * s.height(), s.width(), s.height(), wc );
            }
            else
            {
                QColor bc( 209, 139, 71);
                painter.fillRect( i * s.width(), j * s.height(), s.width(), s.height(), bc );
            }

            //! Draw puppets
            if ( puppets::ChessFigures.contains( cells[i][j].figure ) )
            {
                QRect r(i * s.width(), j * s.height(), s.width(), s.height());
                painter.drawImage(r, puppets::ChessFigures[cells[i][j].figure]->iconImage() );
            }
        }
    }

//    if ( board->currentPlayer() )
//    {
//        //_cellOverCursor = _board->currentPlayer()->cellOverCursor();
//    }

//    if ( _cellOverCursor.first != -1 && _cellOverCursor.second != -1 )
//    {
//        QColor selected( 255, 0, 0 );
//        painter.setPen( selected );
//        painter.drawRect( _cellOverCursor.first * side, _cellOverCursor.second * side, side, side );
//    }

//    std::pair<int, int>& cellSelected = _board->selectedCell();
//    if ( cellSelected.first != -1 && cellSelected.second != -1 )
//    {
//        QColor selected( 0, 255, 0 );
//        painter.setPen( selected );
//        painter.drawRect( cellSelected.first * side, cellSelected.second * side, side, side );
//    }

    return img;
}
