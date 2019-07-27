#ifndef STATSTRACKER_H
#define STATSTRACKER_H


struct StatsTracker
{
public:
    StatsTracker() = delete;
// player

    static int s_seed;
    static int s_stackSize;
    static int s_turn;
};



#endif // STATSTRACKER_H
