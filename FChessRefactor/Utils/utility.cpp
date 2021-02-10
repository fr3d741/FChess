#include "utility.h"

#include "../Interfaces/IBoard.h"

namespace Utils
{

AiData::State ConvertToState(std::shared_ptr<IBoard> board)
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

}
