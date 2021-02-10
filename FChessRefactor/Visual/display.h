#ifndef Display_H
#define Display_H

#include <QWidget>
#include <QMouseEvent>
#include "../messageinterface.h"
#include "../Interfaces/LayerInterface.h"

namespace chessVisialization
{

class Display : public QWidget, public MessageInterface
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0, Qt::WindowFlags f = Qt::Widget );

signals:
    void signalMessage( QString );

    void signalError( QString );

public slots:
    void slotRotateRight();

    void slotRotateLeft();

protected:

    virtual void paintEvent( QPaintEvent* );
    
protected:
    QVector<LayerInterface*> _layers;

};

}

#endif // Display_H
