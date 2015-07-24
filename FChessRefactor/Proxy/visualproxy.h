#ifndef VISUALPROXY_H
#define VISUALPROXY_H

#include <QObject>

#include "../Defines.h"

class VisualProxy : public QObject
{
    Q_OBJECT

    static VisualProxy* _instance;

    explicit VisualProxy(QObject *parent = 0);
public:
    static void CreateInstance(QObject* parent);

    static VisualProxy* Instance();

    static Defs::EFigures FigurePicker(Defs::EColors color);
signals:

public slots:

private slots:
    void slotDeleted();

};

#endif // VISUALPROXY_H
