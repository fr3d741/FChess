#include <QDebug>
#include <QTime>

#include "computer.h"

#include "../Observers/gameplayobserver.h"
#include "../Facade/gameplayfacade.h"
#include "../board.h"
#include "../AI/data.h"
#include "../Factories/figurefactory.h"
#include "../Interfaces/figure.h"

void BuildStateTree(AiData::StateNode &rootNode, AiData::State &state, std::shared_ptr<IBoard> replica, Defs::EColors color)
{
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
        {
            AInt8 figure = state[i][j];
            if (!figure || !(figure & color))
                continue;

            std::shared_ptr<puppets::FigureInterface> figureIns = puppets::FigureFactory::createFigure(replica, figure);
            Defs::state reachableCells;
            figureIns->reachableCells(reachableCells, QPair<int,int>(i, j));
            AiData::Position from;
            from.x = (AInt8)i;
            from.y = (AInt8)j;
            QList<AiData::Position> converted = AiData::ConvertToPositions(reachableCells);
            while(!converted.isEmpty())
            {
                AiData::Position p = converted.takeFirst();
                AiData::StateNode node;
                node.move.from = from;
                node.move.to = p;
                rootNode.childrenNodes.push_back(node);
            }
        }
}


Computer::Computer(Defs::EColors color, QObject *parent)
    :Player(color, parent)
{
    auto instance = GameplayObserver::Instance();
    connect(instance.get(), SIGNAL(signalPlayerChanged(std::shared_ptr<Player>)), SLOT(slotPlayerChanged(std::shared_ptr<Player>)));
    connect(this, SIGNAL(signalMove(QVariant)), GameplayObserver::Instance().get(), SIGNAL(signalMove(QVariant)));
}

std::pair< int, int >& Computer::cellOverCursor()
{
    return _cellOverCursor;
}

void Computer::slotPlayerChanged(std::shared_ptr<Player> player)
{
    if (player.get() != this)
        return;

    auto instance = GameplayFacade::Instance();
    std::shared_ptr<IBoard> board = instance->GetBoard();
    std::shared_ptr<IBoard> replica = board->replicate(Defs::Move());
    AiData::Figure* state = new AiData::Figure[64];
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
            state[c].data = (AInt8)board->GetFigureInPosition(i, j);

    AiData::StateNode root;
    root.value = AiData::ValueOfState(state, 8, 8, color());

    AiData::State aiState;
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
        {
            int figure = replica->GetFigureInPosition(i, j);
            aiState[i][j] = (AInt8)figure;
        }
    BuildStateTree(root, aiState, replica, color());
    qDebug() << root.childrenNodes.size();

//    for(int i = 0, c = 0; i < 8; ++i)
//        for(int j = 0; j < 8; ++j, ++c)
//        {
//            int figure = replica->GetFigureInPosition(i, j);
//            AiData::StateNode::rootState[i][j] = (AInt8)figure;
//            if (!figure)
//                continue;

//            std::shared_ptr<puppets::FigureInterface> figureIns = puppets::FigureFactory::createFigure(replica, figure);
//            Defs::state reachableCells;
//            figureIns->reachableCells(reachableCells, QPair<int,int>(i, j));
//            AiData::Position from;
//            from.x = (AInt8)i;
//            from.y = (AInt8)j;
//            QList<AiData::Position> converted = AiData::ConvertToPositions(reachableCells);
//            while(converted.isEmpty())
//            {
//                AiData::Position p = converted.takeFirst();
//                AiData::StateNode node;
//                node.move.from = from;
//                node.move.to = p;
//                root.childrenNodes.push_back(node);
//            }
//        }
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int index = qrand() % ((root.childrenNodes.size() + 1) - 0) + 0;
    AiData::StateNode selected = root.childrenNodes[index];
    Defs::MovePrimitive move;
    move.from.x = selected.move.from.x;
    move.from.y = selected.move.from.y;
    move.to.x = selected.move.to.x;
    move.to.y = selected.move.to.y;
    emit signalMove(QVariant::fromValue(move));
}

