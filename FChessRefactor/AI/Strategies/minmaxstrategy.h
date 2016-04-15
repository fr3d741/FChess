#ifndef MINMAXSTRATEGY_H
#define MINMAXSTRATEGY_H

#include <QMap>

#include "../IStrategy.h"
#include "../data.h"

namespace Ai{

class MinMaxStrategy : public IStrategy
{
    AiData::NodePtr _lastSelectedNode;
public:
    MinMaxStrategy();

    AiData::NodePtr SelectNode(DecisionTree* tree, std::shared_ptr<IBoard> board);
private:
    int ValueOf(AiData::NodePtr node);
    QList<AiData::NodePtr> SelectMaxValuedNode(AiData::NodePtr node);
    QList<AiData::NodePtr> SelectMinValuedNode(AiData::NodePtr node);
    void Analyze(std::shared_ptr<IBoard> board);
    void AnalyzeNode(std::shared_ptr<AiData::StateNode> node, AiData::State &state);
};

}

#endif // MINMAXSTRATEGY_H
