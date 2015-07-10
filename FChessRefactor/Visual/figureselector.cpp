#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVariant>
#include <QEvent>
#include <QMouseEvent>

#include "figureselector.h"
#include "../Interfaces/figure.h"

FigureSelector::FigureSelector(QWidget *parent)
    :QDialog(parent)
    ,_selectedLabel(0)
{
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout( layout );
    QDialogButtonBox* bbox = new QDialogButtonBox();
    layout->addWidget( bbox );
    bbox->addButton( "Select", QDialogButtonBox::AcceptRole );
    connect( bbox, SIGNAL(accepted()), this, SLOT(accept()));

    QLabel* label = 0;

    QHBoxLayout* whites = new QHBoxLayout();
    QHBoxLayout* blacks = new QHBoxLayout();

    _whiteFrame.setLayout( whites );
    _blackFrame.setLayout( blacks );

    layout->insertWidget( 0, &_whiteFrame );
    layout->insertWidget( 0, &_blackFrame );
    layout->insertWidget( 0, new QLabel( "Select a figure for promotion:" ) );
    for ( QMap< int, puppets::FigureInterface* >::iterator it = puppets::ChessFigures.begin(); it != puppets::ChessFigures.end(); ++it )
    {
        int fig = it.key();
        if ( fig & Defs::King )
        {
            continue;
        }

        if ( fig & Defs::White )
        {
            QFrame* frame = new QFrame(this);
            QHBoxLayout* hFrameLayout = new QHBoxLayout;
            label = new QLabel(frame);
            frame->setLayout( hFrameLayout );
            hFrameLayout->addWidget( label );
            label->installEventFilter(this);
            label->setPixmap( it.value()->iconPixmap() );
            label->setProperty( "figure", QVariant( fig ) );
            whites->addWidget( frame );
        }
        else if ( fig & Defs::Black )
        {
            QFrame* frame = new QFrame(this);
            QHBoxLayout* hFrameLayout = new QHBoxLayout;
            label = new QLabel(frame);
            frame->setLayout( hFrameLayout );
            hFrameLayout->addWidget( label );
            label->installEventFilter(this);
            label->setPixmap( it.value()->iconPixmap() );
            label->setProperty( "figure", QVariant( fig ) );
            blacks->addWidget( frame );
        }
    }

}

bool FigureSelector::eventFilter( QObject * watched, QEvent* event )
{
    QLabel* l = dynamic_cast<QLabel*>( watched );
    QMouseEvent* ev = dynamic_cast<QMouseEvent*>( event );
    if ( l && event->type() == QEvent::MouseButtonPress && ev->buttons() == Qt::LeftButton )
    {
        if ( _selectedLabel )
        {
            QFrame* fr = dynamic_cast<QFrame*>( _selectedLabel->parent() );
            if ( fr )
            {
                fr->setFrameStyle( QFrame::NoFrame );
                fr->setLineWidth( 0 );
            }
        }
        _selectedLabel = l;
        QFrame* fr = dynamic_cast<QFrame*>( l->parent() );
        if ( fr )
        {
            fr->setFrameStyle( QFrame::Box );
            fr->setLineWidth( 2 );
        }
        return true;
    }

return false;
}

int FigureSelector::getFigure( Defs::EColors color )
{
    if ( color == Defs::White )
    {
        _blackFrame.setVisible( false );
        _whiteFrame.setVisible( true );
    }
    else if ( color == Defs::Black )
    {
        _blackFrame.setVisible( true );
        _whiteFrame.setVisible( false );
    }

    int result = exec();
    if ( result == QDialog::Accepted )
    {
        return _selectedLabel->property( "figure" ).toInt();
    }

return -1;
}
