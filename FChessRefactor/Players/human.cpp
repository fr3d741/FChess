#include "human.h"
#include "../Visual/display.h"
#include "../Observers/visualobserver.h"
#include "../Interfaces/figure.h"

Human::Human( Defs::EColors color, QObject *parent )
    :Player(color, parent)
    ,_cellSelected(-1,-1)
{
    connect(this, SIGNAL(signalMouseOver(int,int)), VisualObserver::Instance().get(), SIGNAL(signalMouseOver(int,int)));
    connect(this, SIGNAL(signalCellSelected(int,int)), VisualObserver::Instance().get(), SIGNAL(signalCellSelected(int,int)));
    connect(this, SIGNAL(signalMouseOverCell(QVariant)), VisualObserver::Instance().get(), SIGNAL(signalMouseOverCell(QVariant)));
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

bool Human::eventFilter( QObject * , QEvent * event )
{
    QMouseEvent* mouseEvent = dynamic_cast< QMouseEvent* >( event );
    if ( mouseEvent )
    {
        QPoint p = getCellIndices( mouseEvent->pos() );
        if ( mouseEvent->type() == QEvent::MouseButtonPress && mouseEvent->button() == Qt::LeftButton )
        {
            if (isValid(_cellSelected))
            {
                Defs::MovePrimitive m;
                m.from = _cellSelected;
                m.to = std::pair<int,int>(p.x(), p.y());
                emit signalMouseOverCell(QVariant::fromValue(m));
            }
            else
            {
                _cellSelected.first = p.x();
                _cellSelected.second = p.y();
                emit signalCellSelected( p.x(), p.y() );
            }
            return true;
        }
        else if ( mouseEvent->type() == QEvent::MouseMove && mouseEvent->button() == Qt::NoButton )
        {
            //! Update cursor's position
            if (isValid(_cellSelected))
            {
                Defs::MovePrimitive m;
                m.from = _cellSelected;
                m.to = std::pair<int,int>(p.x(), p.y());
                emit signalMouseOverCell(QVariant::fromValue(m));
            }
            else
            {
                emit signalMouseOver(p.x(), p.y());
            }
            return true;
        }
    }

return false;
}

std::pair< int, int >& Human::cellOverCursor()
{
    return _cellOverCursor;
}

QPoint Human::getCellIndices(QPoint position)
{
    QSize s = puppets::FigureInterface::IconSize();
    QPoint p;
    p.rx() = position.x() / s.width();
    p.ry() = position.y() / s.height();

    p.rx() = std::max(std::min( p.x(), HORIZONTAL_SIZE ), std::max(p.x(), 0));
    p.ry() = std::max(std::min( p.y(), VERTICAL_SIZE ), std::max(p.y(), 0));

return p;
}

bool Human::isValid(const std::pair<int, int> &coord)
{
    return  0 <= coord.first && coord.first < HORIZONTAL_SIZE && 0 <= coord.second && coord.second < VERTICAL_SIZE;
}
