#ifndef UTILITY_H
#define UTILITY_H

class IBoard;

#include <memory>

#include "../AI/data.h"

namespace Utils{
    AiData::State ConvertToState(std::shared_ptr<IBoard> board);
}

#endif // UTILITY_H
