#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

class IBoard;

namespace puppets{
class FigureInterface;
}

#include <memory>
#include <QMap>

#include "../Defines.h"

namespace puppets
{
    /*!
    * \brief Factory class for creating chess figures
    */
    class FigureFactory
    {
        public:
            static std::shared_ptr<FigureInterface> createFigure(std::shared_ptr<IBoard> board, Ftype figure );

            static std::shared_ptr<FigureInterface> createFigure(std::shared_ptr<IBoard> board, Defs::EColors color, Ftype figure );

            static std::shared_ptr<FigureInterface> createFigure(std::shared_ptr<IBoard> board, Defs::EColors color, Defs::EFigures figure );

            static QString IconPath(Ftype id);

            static QImage IconImage(Ftype id);

        private:

            FigureFactory();
    };
}

#endif // FIGUREFACTORY_H
