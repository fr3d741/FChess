#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "../Interfaces/IBoard.h"
#include "data.h"

namespace Ai {

class DecisionTree
{
    typedef QList<std::shared_ptr<AiData::StateNode>> ChildrenList;

    struct StateParameter{
        std::shared_ptr<AiData::StateNode> rootNode;
        AiData::State &state;
        std::shared_ptr<IBoard> replica;
        Defs::EColors color;
    };

    std::shared_ptr<AiData::StateNode> _rootNode;
    std::shared_ptr<AiData::StateNode> _lastSelectedNode;
    int _maxDepth;
public:
    DecisionTree();

    void BuildTree(std::shared_ptr<IBoard> board, Defs::EColors color);

    std::shared_ptr<AiData::StateNode> Root();
    std::shared_ptr<AiData::StateNode> LastSelectedNode();
    void SelectedNode(std::shared_ptr<AiData::StateNode> node);

    void UpdateLastSelectedNode(std::shared_ptr<IBoard> board);

    void saveTreeGraph(QString path);
private:
    Defs::EColors AlternateColor(Defs::EColors color);
    void AddPossibleMovesToNode(StateParameter parameter);
    void BuildStateForChildren(StateParameter parameter, int actDepth);
    void BuildStateTree(StateParameter parameter);

    int treeDepth(std::shared_ptr<AiData::StateNode> node) const;
    int leafNodes(std::shared_ptr<AiData::StateNode> node);
    QString dumpTreeGraph(std::shared_ptr<AiData::StateNode> node, unsigned long &id);
};

}

#endif // DECISIONTREE_H
