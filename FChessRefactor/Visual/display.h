#ifndef Display_H
#define Display_H

#include <QWidget>
#include <QMouseEvent>
#include "../messageinterface.h"
#include "../Defines.h"
#include "../board.h"
#include "../Interfaces/LayerInterface.h"

namespace chessVisialization
{

class Display : public QWidget, public MessageInterface
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0, Qt::WindowFlags f = 0 );

signals:
    virtual void signalMessage( QString );

    virtual void signalError( QString );

public slots:

protected:

    virtual void paintEvent( QPaintEvent* );
    
protected:
    QVector<LayerInterface*> _layers;

};

}

#endif // Display_H
