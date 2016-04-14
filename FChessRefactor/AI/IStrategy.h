#ifndef ISTRATEGY_H
#define ISTRATEGY_H
namespace Ai {
class DecisionTree;
}

namespace AiData{
struct StateNode;
}

#include <memory>

namespace Ai {

class IStrategy
{
public:
    virtual std::shared_ptr<AiData::StateNode> SelectNode(DecisionTree* tree) = 0;
};

}

#endif // ISTRATEGY_H
