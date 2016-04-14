#ifndef RANDOMSTRATEGY_H
#define RANDOMSTRATEGY_H

#include "../IStrategy.h"

namespace Ai{

class RandomStrategy : public IStrategy
{
    std::shared_ptr<AiData::StateNode> _lastSelectedNode;
public:
    RandomStrategy();

    std::shared_ptr<AiData::StateNode> SelectNode(DecisionTree* tree);
};

}

#endif // RANDOMSTRATEGY_H
