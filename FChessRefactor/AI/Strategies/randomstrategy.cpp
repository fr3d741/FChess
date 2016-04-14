#include <QTime>

#include "randomstrategy.h"
#include "../data.h"
#include "../decisiontree.h"

namespace Ai {

RandomStrategy::RandomStrategy()
{
}

std::shared_ptr<AiData::StateNode> RandomStrategy::SelectNode(Ai::DecisionTree *tree)
{
    if (_lastSelectedNode == nullptr)
    {
        _lastSelectedNode = tree->Root();
    }

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int index = qrand() % ((_lastSelectedNode->childrenNodes.size()) - 0) + 0;
    std::shared_ptr<AiData::StateNode> selected = _lastSelectedNode->childrenNodes[index];
    _lastSelectedNode->childrenNodes.clear();
    _lastSelectedNode->childrenNodes.push_back(selected);
    _lastSelectedNode = selected;
    tree->SelectedNode(_lastSelectedNode);

    return selected;

}

}
