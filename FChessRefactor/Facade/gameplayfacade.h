#ifndef GAMEPLAYFACADE_H
#define GAMEPLAYFACADE_H

#include <memory>
#include <QObject>

class GameplayFacade : public QObject
{
    Q_OBJECT

    static std::shared_ptr<GameplayFacade> _instance;

    explicit GameplayFacade();
public:
    static std::shared_ptr<GameplayFacade> Instance();


signals:

public slots:

};

#endif // GAMEPLAYFACADE_H
