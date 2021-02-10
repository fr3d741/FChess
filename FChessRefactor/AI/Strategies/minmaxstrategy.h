#ifndef MINMAXSTRATEGY_H
#define MINMAXSTRATEGY_H

#include <QObject>
#include <QRunnable>

#include "../IStrategy.h"
#include "../data.h"

namespace Ai{

class MinMaxStrategy : public QObject, public IStrategy, public QRunnable
{
    Q_OBJECT
    AiData::NodePtr _lastSelectedNode;
    std::shared_ptr<IBoard> _board;
    Defs::EColors _color;
public:
    MinMaxStrategy();

    MinMaxStrategy(std::shared_ptr<IBoard> board, Defs::EColors color);

    AiData::NodePtr SelectNode(DecisionTree* tree, std::shared_ptr<IBoard> board);

    virtual void run();

    Q_SIGNAL void signalSelectedNode(AiData::NodePtr);

private:
    int ValueOf(AiData::NodePtr node);
    QList<AiData::NodePtr> SelectMaxValuedNode(AiData::NodePtr node);
    QList<AiData::NodePtr> SelectMinValuedNode(AiData::NodePtr node);
    void Analyze(std::shared_ptr<IBoard> board);
    void AnalyzeNode(std::shared_ptr<AiData::StateNode> node, AiData::State &state);
};

}

#endif // MINMAXSTRATEGY_H
