#ifndef BOARDRENDERERINTERFACE_H
#define BOARDRENDERERINTERFACE_H

#include <QObject>
#include <QImage>
#include "../board.h"

/*
 * \brief Bridge pattern for handling different implementations of rendering
*/
class BoardRendererInterface : public QObject
{
    public:
        //TODO: change pointer to smart pointer
        virtual QImage Render(Board* board) = 0;
};

#endif // BOARDRENDERERINTERFACE_H
