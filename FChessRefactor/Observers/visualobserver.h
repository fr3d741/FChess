#ifndef VISUALOBSERVER_H
#define VISUALOBSERVER_H

#include <QObject>
#include "../Interfaces/singleton.h"

class VisualObserver : public QObject, public Singleton<VisualObserver>
{
    friend class Singleton<VisualObserver>;
    Q_OBJECT

    explicit VisualObserver();
public:

signals:
    void signalMouseOver(int, int);

    /*
     * \brief this should be connected through Queued to an update slot
    */
    void signalUpdateView();

public slots:

};

#endif // VISUALOBSERVER_H
