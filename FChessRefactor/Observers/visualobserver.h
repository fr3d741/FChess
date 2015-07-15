#ifndef VISUALOBSERVER_H
#define VISUALOBSERVER_H

#include <QObject>

class VisualObserver : public QObject
{
    Q_OBJECT
public:
    explicit VisualObserver(QObject *parent = 0);

signals:

public slots:

};

#endif // VISUALOBSERVER_H
