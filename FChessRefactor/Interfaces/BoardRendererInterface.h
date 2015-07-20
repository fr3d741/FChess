#ifndef BOARDRENDERERINTERFACE_H
#define BOARDRENDERERINTERFACE_H

#include <memory>
#include <QImage>
#include "../board.h"

/*
 * \brief Bridge pattern for handling different implementations of rendering
*/
class BoardRendererInterface
{
    public:
        //TODO: change pointer to smart pointer
        virtual QImage Render(std::shared_ptr<Board> board) = 0;
};

#endif // BOARDRENDERERINTERFACE_H
