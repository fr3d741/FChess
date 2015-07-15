#include "human.h"
#include "../Visual/display.h"

Human::Human( Defs::EColors color, QObject *parent )
    :Player(color, parent)
{
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
                QRect r( 0, 0, disp->displayImage().width(), disp->displayImage().height() );
                QPoint p = mouseEvent->pos();
                if ( r.contains( p ) )
                {
                    _cellOverCursor.first   = p.x() / ( r.width() / HORIZONTAL_SIZE );
                    _cellOverCursor.second  = p.y() / ( r.height() / VERTICAL_SIZE );
                    emit signalMouseOver(_cellOverCursor.first, _cellOverCursor.second);
                    emit signalEventFiltered();
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
