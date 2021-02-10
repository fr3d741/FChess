#ifndef BOARDRENDERERINTERFACE_H
#define BOARDRENDERERINTERFACE_H

#include <memory>
#include <QImage>
#include "../Interfaces/IBoard.h"

/*
 * \brief Bridge pattern for handling different implementations of rendering
*/
class BoardRendererInterface
{
    public:
        //TODO: change pointer to smart pointer
        virtual QImage Render(std::shared_ptr<IBoard> board) = 0;
};

#endif // BOARDRENDERERINTERFACE_H
