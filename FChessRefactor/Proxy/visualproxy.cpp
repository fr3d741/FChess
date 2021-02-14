#include <assert.h>
#include <QWidget>

#include "visualproxy.h"
#include "../Visual/figureselector.h"

VisualProxy* VisualProxy::_instance = nullptr;

VisualProxy::VisualProxy(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(destroyed()), SLOT(slotDeleted()));
}

void VisualProxy::CreateInstance(QObject *parent)
{
    assert(dynamic_cast<QWidget*>(parent) != 0);
    if (_instance == nullptr)
    {
        _instance = new VisualProxy(parent);
    }
}

VisualProxy *VisualProxy::Instance()
{
    assert(_instance != 0);
    return _instance;
}

Defs::EFigures VisualProxy::FigurePicker(Defs::EColors color)
{
    QWidget* parentW = dynamic_cast<QWidget*>(_instance->parent());
    FigureSelector fs(parentW);

    Ftype result = fs.getFigure(color);

return Defs::getFigure(result);
}

void VisualProxy::slotDeleted()
{
    _instance = nullptr;
}
