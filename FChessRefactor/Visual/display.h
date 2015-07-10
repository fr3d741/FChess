#ifndef Display_H
#define Display_H

#include <QWidget>
#include <QMouseEvent>
#include "../messageinterface.h"
#include "../Defines.h"
#include "../board.h"
#include "../Interfaces/BoardRendererInterface.h"

extern Defs::Cell** Defs::boardState;

namespace chessVisialization
{

class Display : public QWidget, public MessageInterface
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0, Qt::WindowFlags f = 0 );

    void setBoard( Board* board );

    const QImage& displayImage();

signals:
    virtual void signalMessage( QString );

    virtual void signalError( QString );

public slots:
    void boardChanged();

    void slotCellChanged( int, int );

protected:
    void generateImage();

    virtual void paintEvent( QPaintEvent* );
    
    virtual void resizeEvent( QResizeEvent* );

    virtual void mousePressEvent( QMouseEvent* event );

    virtual void mouseMoveEvent( QMouseEvent* event );

    virtual void leaveEvent( QEvent * );
protected:
    QVector<BoardRendererInterface*> _renderers;

    std::pair< int, int >   _cellOverCursor;

    std::pair< int, int >   _cellSelected;

    Board*                  _board;

    QImage                  _displayImage;
};

}

#endif // Display_H
