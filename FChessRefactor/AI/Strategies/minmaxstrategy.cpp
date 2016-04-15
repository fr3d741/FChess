#include <QDebug>
#include <limits>
#include "minmaxstrategy.h"
#include "../decisiontree.h"
#include "../../Interfaces/IBoard.h"
#include "../../Utils/utility.h"

namespace Ai {

MinMaxStrategy::MinMaxStrategy()
{
}

AiData::NodePtr MinMaxStrategy::SelectNode(Ai::DecisionTree *tree, std::shared_ptr<IBoard> board)
{
    _lastSelectedNode = tree->Root();
    Analyze(board);
    QList<AiData::NodePtr> path = SelectMaxValuedNode(_lastSelectedNode);
    _lastSelectedNode = path[1];
    tree->SelectedNode(_lastSelectedNode);

    qDebug() << "---------";
    while(!path.isEmpty())
    {
        auto item = path.takeFirst();
        qDebug() << "***";
        qDebug() << AiData::toString(*item);
    }
    return _lastSelectedNode;
}

int MinMaxStrategy::ValueOf(AiData::NodePtr node)
{
    return node->value;
}

QList<AiData::NodePtr> MinMaxStrategy::SelectMaxValuedNode(AiData::NodePtr node)
{
    if (node->childrenNodes.isEmpty())
        return QList<AiData::NodePtr>{node};

    QList<AiData::NodePtr> maxNodeList;
    int maxValue = -INT_MAX;
    for(QList<AiData::NodePtr>::iterator it = node->childrenNodes.begin(); it != node->childrenNodes.end(); ++it)
    {
        QList<AiData::NodePtr> ptr = SelectMinValuedNode(*it);
        if (maxValue < ptr.first()->value)
        {
            maxValue = ptr.first()->value;
            maxNodeList = ptr;
        }
    }

    node->value += maxNodeList.first()->value;
    maxNodeList.push_front(node);
    return maxNodeList;
}

QList<AiData::NodePtr> MinMaxStrategy::SelectMinValuedNode(AiData::NodePtr node)
{
    if (node->childrenNodes.isEmpty())
        return QList<AiData::NodePtr>{node};

    QList<AiData::NodePtr> minNodeList;
    int minValue = INT_MAX;
    for(QList<AiData::NodePtr>::iterator it = node->childrenNodes.begin(); it != node->childrenNodes.end(); ++it)
    {
        QList<AiData::NodePtr> ptr = SelectMaxValuedNode(*it);
        if (ptr.first()->value < minValue)
        {
            minValue = ptr.first()->value;
            minNodeList = ptr;
        }
    }

    node->value += minNodeList.first()->value;
    minNodeList.push_front(node);
    return minNodeList;
}

void MinMaxStrategy::Analyze(std::shared_ptr<IBoard> board)
{
    AiData::State aiState = Utils::ConvertToState(board);
    AnalyzeNode(_lastSelectedNode, aiState);
}

void MinMaxStrategy::AnalyzeNode(std::shared_ptr<AiData::StateNode> node, AiData::State& state)
{
    auto children = node->childrenNodes;
    node->value = AiData::ValueOfState(state, node->playerColor);

    for(QList<std::shared_ptr<AiData::StateNode>>::iterator it = children.begin(); it != children.end(); ++it)
    {
        AiData::State currentState = AiData::Apply((*it)->move, state);
        AnalyzeNode(*it, currentState);
    }
}

}
