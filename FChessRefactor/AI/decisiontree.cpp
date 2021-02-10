#include <assert.h>
#include <QFile>
#include <QTime>
#include <QDebug>
#include <QStringBuilder>

#include <Figures/FigureGlobals.h>

#include "decisiontree.h"
#include "aiboard.h"

#include "../Interfaces/figure.h"
#include "../Factories/figurefactory.h"
#include "../Utils/utility.h"

namespace Ai
{

DecisionTree::DecisionTree()
    :_rootNode(nullptr)
    ,_lastSelectedNode(nullptr)
    ,_maxDepth(3)
{
}

void DecisionTree::BuildTree(std::shared_ptr<IBoard> board, Defs::EColors color)
{
    AiData::State aiState = Utils::ConvertToState(board);

    _rootNode = std::shared_ptr<AiData::StateNode>(new AiData::StateNode);
    _rootNode->playerColor = color;
    _lastSelectedNode = _rootNode;

    BuildStateTree({_lastSelectedNode, aiState, std::shared_ptr<IBoard>(new AiBoard(aiState)), color});
}

void DecisionTree::UpdateLastSelectedNode(std::shared_ptr<IBoard> board)
{
    if (board->GetHistory().isEmpty())
        return;

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

std::shared_ptr<AiData::StateNode> DecisionTree::Root()
{
    return _rootNode;
}

std::shared_ptr<AiData::StateNode> DecisionTree::LastSelectedNode()
{
    return _lastSelectedNode;
}

void DecisionTree::SelectedNode(std::shared_ptr<AiData::StateNode> node)
{
    _lastSelectedNode = node;
}

Defs::EColors DecisionTree::AlternateColor(Defs::EColors color)
{
    return color == Defs::White?Defs::Black:Defs::White;
}

void DecisionTree::AddPossibleMovesToNode(StateParameter parameter)
{
  for (int i = 0, c = 0; i < 8; ++i) 
  {
    for (int j = 0; j < 8; ++j, ++c)
    {
      AInt8 figure = parameter.state[i][j];
      if (!figure || !(figure & parameter.color))
        continue;

      Defs::state reachableCells;
      QPair<int, int> cell(i, j);
      FigureGlobals::reachableCells(parameter.replica.get(), reachableCells, cell, parameter.color);

      AiData::Position from;
      from.x = (AInt8)i;
      from.y = (AInt8)j;
      assert(0 <= from.x && from.x < 8);
      assert(0 <= from.y && from.y < 8);
      for (int i = 0, c = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j, ++c)
        {
          if (!reachableCells.test(c))
            continue;

          auto p = AiData::ConvertToPosition(i, j);
          std::shared_ptr<AiData::StateNode> node = std::shared_ptr<AiData::StateNode>(new AiData::StateNode);
          node->move.from = from;
          node->move.to = p;
          assert(0 <= node->move.to.x && node->move.to.x < 8);
          assert(0 <= node->move.to.y && node->move.to.y < 8);
          node->playerColor = AlternateColor(parameter.color);
          parameter.rootNode->childrenNodes.push_back(node);
        }
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
        AddPossibleMovesToNode({*it,state, board, alternateColor});
        BuildStateForChildren({*it,state, board, alternateColor}, actDepth + 1);
    }
}

void DecisionTree::BuildStateTree(DecisionTree::StateParameter parameter)
{
    AddPossibleMovesToNode(parameter);
    BuildStateForChildren(parameter, 0);
//    qDebug() << "hehe";
//    qDebug() << "depth: " << treeDepth(_rootNode);
//    qDebug() << "leafs: " << leafNodes(_rootNode);
    //saveTreeGraph("d:\\tmp\\graph.txt");
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
