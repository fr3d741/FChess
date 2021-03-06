#include <QDebug>
#include <QTimer>
#include <limits>
#include <chrono>
#include "minmaxstrategy.h"
#include "../decisiontree.h"
#include "../../Interfaces/IBoard.h"
#include "../../Utils/utility.h"

using namespace std::chrono;

namespace Ai {

MinMaxStrategy::MinMaxStrategy()
{
}

MinMaxStrategy::MinMaxStrategy(std::shared_ptr<IBoard> board, Defs::EColors color)
    :QObject()
    ,QRunnable()
    ,_board(board)
    ,_color(color)
{
}

AiData::NodePtr MinMaxStrategy::SelectNode(Ai::DecisionTree *tree, std::shared_ptr<IBoard> board)
{
    _lastSelectedNode = tree->Root();
    qDebug() << "Analyze";
    Analyze(board);
    qDebug() << "select MinMax";
    QList<AiData::NodePtr> path;
    if (_color == Defs::White)
      path = SelectMaxValuedNode(_lastSelectedNode);
    else
      path = SelectMinValuedNode(_lastSelectedNode);

    if (0 < path.size())
      _lastSelectedNode = path[1];
    tree->SelectedNode(_lastSelectedNode);

    return _lastSelectedNode;
}

void MinMaxStrategy::run()
{
    auto t1 = steady_clock::now();
    DecisionTree decisionTree;
    qDebug() << "*** Build tree ***";

    decisionTree.BuildTree(_board, _color);
    auto selected = SelectNode(&decisionTree, _board);

    int figure = _board->GetFigureInPosition(selected->move.from.x, selected->move.from.y);
    if (figure == 0)
    {
        //decisionTree.saveTreeGraph("D:\\tmp\\wrong_move.dot");
        qDebug() << "Wrong move: " << figure;
    }

    auto t2 = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    qDebug() << time_span.count() << " seconds ";
    emit signalSelectedNode(selected);
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
