#ifndef COMPUTER_H
#define COMPUTER_H

#include <QVariant>

#include "../Interfaces/player.h"
#include "../AI/data.h"
#include "../AI/decisiontree.h"
#include "../AI/IStrategy.h"

class Computer : public Player
{
    Q_OBJECT
    std::pair<int, int> _cellOverCursor;
    AiData::StateNode _root;
    bool _rootValid;
    Ai::DecisionTree _decisionTree;
    std::shared_ptr<Ai::IStrategy> _strategy;
public:
    Computer(Defs::EColors color, QObject *parent = 0);

    virtual std::pair< int, int >& cellOverCursor();

    void SetStrategy(std::shared_ptr<Ai::IStrategy> strategy);
signals:
    void signalMove(QVariant);

protected slots:
    void slotPlayerChanged(std::shared_ptr<Player> player);


};

#endif // COMPUTER_H
