#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

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
    class FigureFactory : public Singleton<FigureFactory>
    {
        friend class Singleton<FigureFactory>;

        public:
            FigureInterface *createFigure( Defs::EColors color, Defs::EFigures figure );

        private:
            FigureFactory();

            QMap< int, QString >             _texturePaths;
    };
}

#endif // FIGUREFACTORY_H
