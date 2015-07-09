#ifndef RULES_H
#define RULES_H

#include <list>

#include "Defines.h"

bool isGameEnd( Defs::Cell** , std::pair<int, int>&  );

void validMoves( Defs::Cell** , std::pair<int, int>& , std::list< std::pair<int, int> >&  );

/*!
* \brief class containing rules and determines end of game
*/
class Rules
{
public:
    explicit Rules();
    
protected:

};

#endif // RULES_H
