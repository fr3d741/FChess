#include <QDebug>
#include <QWidget>
#include <QPainter>
#include "boardrendererimpl.h"
#include "../Facade/gameplayfacade.h"
#include "../Observers/gameplayobserver.h"
#include "../Factories/figurefactory.h"
#include "../Interfaces/figure.h"

BoardRendererImpl::BoardRendererImpl() :
    BoardRendererInterface()
{
    connect( GameplayObserver::Instance().get(), SIGNAL(signalBoardChanged(std::shared_ptr<IBoard>)), SLOT(slotBoardChanged(std::shared_ptr<IBoard>)) );
}

void BoardRendererImpl::slotBoardChanged(std::shared_ptr<IBoard> board)
{
    Render(board);
}

QImage BoardRendererImpl::Render(std::shared_ptr<IBoard> board)
{
    int h = board->sizeVerical();
    int w = board->sizeHorizontal();
    QSize s = puppets::FigureInterface::IconSize();

    _layerImg = QImage(s.width() * w + 10, s.height() * h + 10, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&_layerImg);

    for ( int i = 0; i < w; ++i )
    {
        for ( int j = 0; j < h; ++j )
        {
            //! Coloring board
            if ( board->cell({i, j}).cellColor == Defs::White )
            {
                QColor wc( 255, 206, 158, 255);
                painter.fillRect( i * s.width(), j * s.height(), s.width(), s.height(), wc );
            }
            else
            {
                QColor bc( 209, 139, 71, 255);
                painter.fillRect( i * s.width(), j * s.height(), s.width(), s.height(), bc );
            }

            //! Draw puppets
            QRect r(i * s.width(), j * s.height(), s.width(), s.height());
            painter.drawImage(r, puppets::FigureFactory::IconImage(board->GetFigureInPosition(i, j)));
        }

        QRect rtextVertical(_layerImg.width()-10, i * s.height(), 10, s.height());
        QTextOption optionVertical;
        optionVertical.setAlignment(Qt::AlignCenter);
        painter.drawText(rtextVertical, QString("%1").arg(i), optionVertical);

        QRect rtext(i * s.width(), _layerImg.height()-10, s.width(), 10);
        QTextOption option;
        option.setAlignment(Qt::AlignCenter);
        painter.drawText(rtext, QString("%1").arg(i), option);
    }

    return _layerImg;
}

const QImage &BoardRendererImpl::LayerImage()
{
    Render(GameplayFacade::Instance()->GetBoard());
    return _layerImg;
}
