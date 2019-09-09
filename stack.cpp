#include "stack.h"

Stack::Stack(const std::vector<Monster>& bestiaryVec)
{
    srand(time(NULL));

    for(int i = 0; i < Options::s_stackSize; i++){
        int index = (Options::s_seed * std::rand() ) % bestiaryVec.size(); // 0 - 4
        m_stack.push_back(bestiaryVec.at(index));
    }
}

std::vector<Monster>& Stack::GetStack(){
    return m_stack;
}
