#ifndef FIGURESELECTOR_H
#define FIGURESELECTOR_H

#include <QDialog>
#include <QFrame>
#include <QLabel>

#include "../Defines.h"

class FigureSelector : public QDialog
{
    Q_OBJECT
public:
    explicit FigureSelector(QWidget *parent = 0);

    int getFigure( Defs::EColors color );

    virtual bool eventFilter ( QObject * watched, QEvent * event );

signals:
    
public slots:

protected:
    QLabel* _selectedLabel;
    QFrame _whiteFrame;
    QFrame _blackFrame;
};

#endif // FIGURESELECTOR_H
