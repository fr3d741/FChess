#include <QFile>
#include <QTime>
#include <QDebug>
#include <QStringBuilder>

#include "decisiontree.h"
#include "aiboard.h"

#include "../Interfaces/figure.h"
#include "../Factories/figurefactory.h"

namespace Ai
{

DecisionTree::DecisionTree()
    :_rootNode(nullptr)
    ,_lastSelectedNode(nullptr)
    ,_maxDepth(2)
{
}

AiData::State DecisionTree::ConvertToState(std::shared_ptr<IBoard> board)
{
    AiData::State aiState;
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
        {
            int figure = board->GetFigureInPosition(i, j);
            aiState[i][j] = (AInt8)figure;
        }

    return aiState;
}

void DecisionTree::BuildTree(std::shared_ptr<IBoard> board, Defs::EColors color)
{
    AiData::State aiState = ConvertToState(board);

    if (_rootNode == nullptr)
    {
        _rootNode = std::shared_ptr<AiData::StateNode>(new AiData::StateNode);
        _rootNode->playerColor = color;
        _lastSelectedNode = _rootNode;
    }
    else
        UpdateLastSelectedNode(board);

    BuildStateTree({_lastSelectedNode, aiState, std::shared_ptr<IBoard>(new AiBoard(aiState)), color});
    Analyze(board);
}

void DecisionTree::UpdateLastSelectedNode(std::shared_ptr<IBoard> board)
{
    Defs::Move move = board->lastMove();
    AiData::Movement aiMovement
    {
        AiData::ConvertToPosition(move.from.x, move.from.y),
        AiData::ConvertToPosition(move.to.x, move.to.y)
    };

    ChildrenList children = _lastSelectedNode->childrenNodes;
    for(ChildrenList::iterator it = children.begin(); it != children.end(); ++it)
    {
        if ((*it)->move == aiMovement)
        {
            _lastSelectedNode = *it;
            break;
        }
    }
}

void DecisionTree::Analyze(std::shared_ptr<IBoard> board)
{
    AiData::State aiState = ConvertToState(board);
    AnalyzeNode(_lastSelectedNode, aiState);
}

std::shared_ptr<AiData::StateNode> DecisionTree::Root()
{
    return _rootNode;
}

void DecisionTree::SelectedNode(std::shared_ptr<AiData::StateNode> node)
{
    _lastSelectedNode = node;
}

Defs::EColors DecisionTree::AlternateColor(Defs::EColors color)
{
    return color == Defs::White?Defs::Black:Defs::White;
}

void DecisionTree::CreateChildNodes(StateParameter parameter)
{
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
        {
            AInt8 figure = parameter.state[i][j];
            if (!figure || !(figure & parameter.color))
                continue;

            std::shared_ptr<puppets::FigureInterface> figureIns = puppets::FigureFactory::createFigure(parameter.replica, figure);
            Defs::state reachableCells;
            figureIns->reachableCells(reachableCells, QPair<int,int>(i, j));
            AiData::Position from;
            from.x = (AInt8)i;
            from.y = (AInt8)j;
            QList<AiData::Position> converted = AiData::ConvertToPositions(reachableCells);
            while(!converted.isEmpty())
            {
                AiData::Position p = converted.takeFirst();
                std::shared_ptr<AiData::StateNode> node = std::shared_ptr<AiData::StateNode>(new AiData::StateNode);
                node->move.from = from;
                node->move.to = p;
                node->playerColor = parameter.color;
                parameter.rootNode->childrenNodes.push_back(node);
            }
        }
}

void DecisionTree::BuildStateForChildren(DecisionTree::StateParameter parameter, int actDepth)
{
    if (actDepth == _maxDepth)
        return;

    auto node = parameter.rootNode;
    auto children = node->childrenNodes;
    for(ChildrenList::iterator it = children.begin(); it != children.end(); ++it)
    {
        AiData::State state = AiData::Apply((*it)->move, parameter.state);
        std::shared_ptr<IBoard> board = std::shared_ptr<IBoard>(new AiBoard(state));
        Defs::EColors alternateColor = AlternateColor(parameter.color);
        CreateChildNodes({*it,state, board, alternateColor});
        BuildStateForChildren({*it,state, board, alternateColor}, actDepth + 1);
    }
}

void DecisionTree::BuildStateTree(DecisionTree::StateParameter parameter)
{
    CreateChildNodes(parameter);
    BuildStateForChildren(parameter, 0);
    qDebug() << "hehe";
    qDebug() << "depth: " << treeDepth(_rootNode);
    qDebug() << "leafs: " << leafNodes(_rootNode);
    saveTreeGraph("d:\\tmp\\graph.txt");
}

void DecisionTree::AnalyzeNode(std::shared_ptr<AiData::StateNode> node, AiData::State& state)
{
    node->value = AiData::ValueOfState(state, node->playerColor);
    auto children = node->childrenNodes;
    for(ChildrenList::iterator it = children.begin(); it != children.end(); ++it)
    {
        AiData::State currentState = AiData::Apply((*it)->move, state);
        AnalyzeNode(*it, currentState);
    }
}

int DecisionTree::treeDepth(std::shared_ptr<AiData::StateNode> node) const
{
    if (node->childrenNodes.isEmpty())
        return 1;

    auto children = node->childrenNodes;
    int mDepth = 0;
    for(ChildrenList::iterator it = children.begin(); it != children.end(); ++it)
    {
        mDepth = std::max(treeDepth(*it), mDepth);
    }

return mDepth + 1;
}

int DecisionTree::leafNodes(std::shared_ptr<AiData::StateNode> node)
{
    if (node->childrenNodes.isEmpty())
        return 1;

    int sum = 0;
    auto children = node->childrenNodes;
    for(ChildrenList::iterator it = children.begin(); it != children.end(); ++it)
    {
        sum += leafNodes(*it);
    }

    return sum;
}

QString DecisionTree::dumpTreeGraph(std::shared_ptr<AiData::StateNode> node, unsigned long& id)
{
    unsigned long myId = id;
   QString txt;
   ChildrenList children = node->childrenNodes;
   for (ChildrenList::iterator it = children.begin(); it != children.end(); ++it)
   {
       ++id;
       QString m = QString("%1,%2=>%3,%4").arg((*it)->move.from.x).arg((*it)->move.from.y).arg((*it)->move.to.x).arg((*it)->move.to.y);
       txt = txt + QString("%1 -> %2[label=\"%3\"];\n").arg(myId).arg(id).arg(m);
       txt = txt + dumpTreeGraph(*it, id);
   }
   return txt;
}

void DecisionTree::saveTreeGraph(QString path)
{
    unsigned long id = 0L;
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << "digraph{";
    stream << dumpTreeGraph(_rootNode, id);
    stream << "}";
    file.close();
}

}
