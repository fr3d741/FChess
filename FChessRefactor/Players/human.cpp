#include "human.h"
#include "../Visual/display.h"
#include "../Observers/visualobserver.h"
#include "../Interfaces/figure.h"

Human::Human( Defs::EColors color, QObject *parent )
    :Player(color, parent)
{
    connect(this, SIGNAL(signalMouseOver(int,int)), VisualObserver::Instance().get(), SIGNAL(signalMouseOver(int,int)));
}

bool Human::isValidCell( Defs::Cell& sourceCell )
{
    if ( sourceCell.figure && ( sourceCell.figure & _playerColor ) )
    {
        return true;
    }

return false;
}

bool Human::isValidCellForTarget( Defs::Cell* targetCell )
{
    if ( targetCell->figure && ( targetCell->figure & _playerColor ) )
    {
        return true;
    }

return false;
}

bool Human::eventFilter( QObject * watched, QEvent * event )
{
    chessVisialization::Display* disp = dynamic_cast<chessVisialization::Display*>( watched );
    QMouseEvent* mouseEvent = dynamic_cast< QMouseEvent* >( event );
    if ( mouseEvent )
    {
        if ( mouseEvent->type() == QEvent::MouseButtonPress )
        {
            if ( mouseEvent->button() == Qt::LeftButton )
            {
                emit signalCellPressed( _cellOverCursor.first, _cellOverCursor.second );
                //disp->boardChanged();
                return true;
            }
        }
        else if ( mouseEvent->type() == QEvent::MouseMove )
        {
            if ( mouseEvent->button() == Qt::NoButton )
            {
                //! Update cursor's position
                QSize s = puppets::FigureInterface::IconSize();
                QRect r(0, 0, s.width() * HORIZONTAL_SIZE, s.height() * VERTICAL_SIZE);
                QPoint p = mouseEvent->pos();
                if ( r.contains( p ) )
                {
                    _cellOverCursor.first   = p.x() / ( r.width() / HORIZONTAL_SIZE );
                    _cellOverCursor.second  = p.y() / ( r.height() / VERTICAL_SIZE );
                    emit signalMouseOver(_cellOverCursor.first, _cellOverCursor.second);
                    return true;
                }
            }
        }
    }

return false;
}

std::pair< int, int >& Human::cellOverCursor()
{
    return _cellOverCursor;
}
