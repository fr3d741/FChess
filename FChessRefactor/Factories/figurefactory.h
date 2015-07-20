#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

class Board;

namespace puppets{
class FigureInterface;
}

#include <memory>
#include <QMap>

#include "../Defines.h"
#include "../Interfaces/singleton.h"

namespace puppets
{
    /*!
    * \brief Factory class for creating chess figures
    */
    class FigureFactory
    {
        public:
            static std::shared_ptr<FigureInterface> createFigure( std::shared_ptr<Board> board, Defs::EColors color, int figure );

            static std::shared_ptr<FigureInterface> createFigure( std::shared_ptr<Board> board, Defs::EColors color, Defs::EFigures figure );

            static QString IconPath(int id);

            static QImage IconImage(int id);

        private:

            FigureFactory();
    };
}

#endif // FIGUREFACTORY_H
