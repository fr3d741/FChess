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
    void Analyze(std::shared_ptr<IBoard> board);

    std::shared_ptr<AiData::StateNode> Root();
    void SelectedNode(std::shared_ptr<AiData::StateNode> node);

    AiData::State ConvertToState(std::shared_ptr<IBoard> board);
    void UpdateLastSelectedNode(std::shared_ptr<IBoard> board);
private:
    Defs::EColors AlternateColor(Defs::EColors color);
    void CreateChildNodes(StateParameter parameter);
    void BuildStateForChildren(StateParameter parameter, int actDepth);
    void BuildStateTree(StateParameter parameter);
    void AnalyzeNode(std::shared_ptr<AiData::StateNode> node, AiData::State &state);

    int treeDepth(std::shared_ptr<AiData::StateNode> node) const;
    int leafNodes(std::shared_ptr<AiData::StateNode> node);
    QString dumpTreeGraph(std::shared_ptr<AiData::StateNode> node, unsigned long &id);
    void saveTreeGraph(QString path);
};

}

#endif // DECISIONTREE_H
