#ifndef ISTRATEGY_H
#define ISTRATEGY_H
namespace Ai {
class DecisionTree;
}

namespace AiData{
struct StateNode;
}

class IBoard;

#include <memory>

namespace Ai {

class IStrategy
{
public:

    virtual std::shared_ptr<AiData::StateNode> SelectNode(DecisionTree* tree, std::shared_ptr<IBoard> board) = 0;
};

}

#endif // ISTRATEGY_H
