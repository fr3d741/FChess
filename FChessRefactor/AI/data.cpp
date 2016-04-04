#include "data.h"

#include "../Interfaces/figure.h"
#include "../Factories/figurefactory.h"

namespace AiData {

//State StateNode::rootState;

int ValueOfState(Figure* state, int maxX, int maxY, Defs::EColors color)
{
    int sum = 0;
    for (int x = 0; x < maxX * maxY; ++x)
    {
        int value = 0;
        switch(state[x].type)
        {
            case Defs::King:
                value = 12;
                break;
            case Defs::Queen:
                value = 9;
                break;
            case Defs::Rook:
                value = 6;
                break;
            case Defs::Knight:
                value = 3;
                break;
            case Defs::Bishop:
                value = 2;
                break;
            case Defs::Pawn:
                value = 1;
            default:
                value = 0;
        }
        sum += value * (state[x].color & color?1:-1);
    }

return sum;
}


QList<Position> ConvertToPositions(Defs::state &state)
{
    QList<Position> list;
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
            if (state.test(c))
            {
                Position p;
                p.y = (AInt8)j;
                p.x = (AInt8)i;
                list.push_back(p);
            }

    return list;
}


void BuildStateTree(StateNode &rootNode, State &state)
{
//    for(int i = 0, c = 0; i < 8; ++i)
//        for(int j = 0; j < 8; ++j, ++c)
//        {
//            AInt8 figure = state[i][j];
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
//                rootNode.childrenNodes.push_back(node);
//            }
//        }
}

}
