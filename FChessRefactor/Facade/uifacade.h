#ifndef UIFACADE_H
#define UIFACADE_H

namespace chessVisialization{
    class Display;
}

class Player;

#include <QObject>
#include <memory>
#include "../Interfaces/singleton.h"

class UiFacade : public QObject, public Singleton<UiFacade>
{
    Q_OBJECT

    friend class Singleton<UiFacade>;

    chessVisialization::Display* _display = nullptr;

    explicit UiFacade();
public:

    QWidget* CreateDisplayWidget(QWidget* parent = 0);

    void NextPlayer(std::shared_ptr<Player> player);

    void UpdateUi();
signals:

public slots:
};

#endif // UIFACADE_H
