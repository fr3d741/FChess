#include "human.h"
#include "../Visual/display.h"
#include "../Observers/visualobserver.h"
#include "../Observers/gameplayobserver.h"
#include "../Interfaces/figure.h"
#include "../Utils/validator.h"

Human::Human( Defs::EColors color, QObject *parent )
    :Player(color, parent)
    ,_cellSelected({-1,-1})
{
    connect(this, SIGNAL(signalMouseOver(int,int)), VisualObserver::Instance().get(), SIGNAL(signalMouseOver(int,int)));
    connect(this, SIGNAL(signalCellSelected(int,int)), VisualObserver::Instance().get(), SIGNAL(signalCellSelected(int,int)));
    connect(this, SIGNAL(signalMouseOverCell(QVariant)), VisualObserver::Instance().get(), SIGNAL(signalMouseOverCell(QVariant)));
    connect(this, SIGNAL(signalMove(QVariant)), GameplayObserver::Instance().get(), SIGNAL(signalMove(QVariant)));
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
                m.to = {p.x(), p.y()};
                if (_cellSelected == m.to)
                {
                    invalidate(_cellSelected);
                    return true;
                }

                emit signalMove(QVariant::fromValue(m));
                invalidate(_cellSelected);
            }
            else
            {
                if (!Validator::isValidCell(p.x(), p.y(), _playerColor))
                    return false;

                _cellSelected.x = p.x();
                _cellSelected.y = p.y();
                Defs::MovePrimitive m;
                m.from = _cellSelected;
                m.to = {p.x(), p.y()};
                emit signalMouseOverCell(QVariant::fromValue(m));
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
                m.to = {p.x(), p.y()};
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

bool Human::isValid(const Defs::Position &coord)
{
    return  0 <= coord.y && coord.y < VERTICAL_SIZE && 0 <= coord.x && coord.x < HORIZONTAL_SIZE;
}

void Human::invalidate(Defs::Position &position)
{
    position.y = position.x = -1;
}
