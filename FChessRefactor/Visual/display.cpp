#include <QPainter>

#include "display.h"
#include "../Interfaces/figure.h"
#include "boardrendererimpl.h"

namespace chessVisialization
{

Display::Display(QWidget *parent, Qt::WindowFlags f )
    :QWidget(parent, f)
    ,_renderers()
    ,_cellOverCursor( -1, -1)
    ,_cellSelected( -1, -1 )
    ,_board(0)
{
    setMouseTracking( true );
    _renderers.push_back(new BoardRendererImpl());
}

void Display::setBoard( Board* board )
{
    _board = board;
}

void Display::boardChanged()
{
    generateImage();
    update();
}

void Display::generateImage()
{
    Defs::Cell** cells = Defs::boardState;
    if ( !cells )
    {
        emit signalMessage( QString("NULL Board!") );
        return;
    }

//    int x = _board->sizeHorizontal();
//    int y = _board->sizeVerical();
//    int w = width();
//    int h = height();
//    int cw = w / x;
//    int ch = h / y;
//    int side = std::min( cw, ch );
//    _displayImage = QImage( x * side, y * side, QImage::Format_ARGB32 );
//    QPainter painter( &_displayImage );
//    for ( int i = 0; i < x; ++i )
//    {
//        for ( int j = 0; j < y; ++j )
//        {
//            //! Coloring board
//            if ( cells[i][j].cellColor == Defs::White )
//            {
//                QColor wc( 255, 206, 158);
//                painter.fillRect( i * side, j * side, side, side, wc );
//            }
//            else
//            {
//                QColor bc( 209, 139, 71);
//                painter.fillRect( i * side, j * side, side, side, bc );
//            }

//            //! Draw puppets
//            if ( puppets::ChessFigures.contains( cells[i][j].figure ) )
//            {
//                QRect r(i * side, j * side, side, side);
//                painter.drawImage(r, puppets::ChessFigures[cells[i][j].figure]->iconImage() );
//            }
//        }
//    }

    _displayImage = _renderers[0]->Render(_board);

//    if ( _board->currentPlayer() )
//    {
//        _cellOverCursor = _board->currentPlayer()->cellOverCursor();
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

}

void Display::resizeEvent( QResizeEvent* )
{
    generateImage();
}

void Display::slotCellChanged( int x, int y )
{
    _cellOverCursor.first   = x;
    _cellOverCursor.second  = y;
    generateImage();
    update();
}

void Display::mousePressEvent(QMouseEvent* event )
{
//    if ( event->button() == Qt::LeftButton )
//    {
//        if ( _board->cellPressed( _cellOverCursor.first, _cellOverCursor.second ) )
//        {
//            generateImage();
//            update();
//        }
//    }
}

void Display::mouseMoveEvent( QMouseEvent* event )
{
//    if ( event->button() == Qt::NoButton )
//    {
//        //! Update cursor's position
//        QRect r( 0, 0, _displayImage.width(), _displayImage.height() );
//        QPoint p = event->pos();
//        if ( r.contains( p ) )
//        {
//            _cellOverCursor.first   = p.x() / ( r.width() / _board->sizeHorizontal() );
//            _cellOverCursor.second  = p.y() / ( r.height() / _board->sizeVerical() );
//            generateImage();
//            update();
//        }
//    }
}

const QImage& Display::displayImage()
{
    return _displayImage;
}

void Display::paintEvent( QPaintEvent * )
{
    QPainter p(this);
    //p.drawImage( rect(), _displayImage );
    p.drawImage( QPoint(0,0), _displayImage );
}

void Display::leaveEvent( QEvent * )
{
    _cellOverCursor.first = -1;
    _cellOverCursor.second = -1;
}

}
