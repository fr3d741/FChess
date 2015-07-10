#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

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
            FigureInterface *createFigure( Defs::EColors color, Defs::EFigures figure );

            static const std::auto_ptr< FigureFactory > Instance();

        private:
            FigureFactory();

            static std::auto_ptr< FigureFactory >   _globalInst;

            QMap< int, QString >             _texturePaths;
    };
}

#endif // FIGUREFACTORY_H
