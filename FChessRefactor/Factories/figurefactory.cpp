#include "figurefactory.h"

#include "../Figures/bishop.h"
#include "../Figures/king.h"
#include "../Figures/knight.h"
#include "../Figures/pawn.h"
#include "../Figures/queen.h"
#include "../Figures/rook.h"

#include "../Interfaces/figure.h"

namespace puppets
{

std::shared_ptr<FigureInterface> FigureFactory::createFigure(std::shared_ptr<Board> board, Defs::EColors color, int figure )
{
    return createFigure(board, color, (Defs::EFigures)(figure & 0xF8));
}

std::shared_ptr<FigureInterface> FigureFactory::createFigure(std::shared_ptr<Board> board, Defs::EColors color, Defs::EFigures figure)
{
    switch (figure)
    {
        case Defs::Pawn:
            return std::shared_ptr<FigureInterface>(new Pawn( board, color ));
        case Defs::Knight:
            return std::shared_ptr<FigureInterface>(new Knight( board, color ));
        case Defs::Rook:
            return std::shared_ptr<FigureInterface>(new Rook( board, color ));
        case Defs::Bishop:
            return std::shared_ptr<FigureInterface>(new Bishop( board, color ));
        case Defs::King:
            return std::shared_ptr<FigureInterface>(new King( board, color ));
        case Defs::Queen:
            return std::shared_ptr<FigureInterface>(new Queen( board, color ));
        default:
            return std::shared_ptr<FigureInterface>(new FigureInterface(board, color, figure));
    }
}

QString FigureFactory::IconPath(int id)
{
    switch(id)
    {
        case Defs::White | Defs::Pawn: return QString( ":/icon/figure/pawn_w.png" );
        case Defs::White | Defs::Knight: return QString( ":/icon/figure/knight_w.png" );
        case Defs::White | Defs::Rook: return QString( ":/icon/figure/rook_w.png" );
        case Defs::White | Defs::Bishop: return QString( ":/icon/figure/bishop_w.png" );
        case Defs::White | Defs::King: return QString( ":/icon/figure/king_w.png" );
        case Defs::White | Defs::Queen: return QString( ":/icon/figure/queen_w.png" );

        case Defs::Black | Defs::Pawn: return QString( ":/icon/figure/pawn_b.png" );
        case Defs::Black | Defs::Knight: return QString( ":/icon/figure/knight_b.png" );
        case Defs::Black | Defs::Rook: return QString( ":/icon/figure/rook_b.png" );
        case Defs::Black | Defs::Bishop: return QString( ":/icon/figure/bishop_b.png" );
        case Defs::Black | Defs::King: return QString( ":/icon/figure/king_b.png" );
        case Defs::Black | Defs::Queen: return QString( ":/icon/figure/queen_b.png" );
        default:break;
    }

    return QString("");
}

QImage FigureFactory::IconImage(int id)
{
    QString path = IconPath(id);
    if (path.length())
        return QImage(IconPath(id));

    return QImage();
}

} // end namespace
