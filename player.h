#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMessageBox>

#include <vector>
#include <array>
#include <utility>
#include <string>
#include "options.h"
#include "monster.h"

class Player
{
public:
    Player();
    std::array<Monster, 5>& Hand();
    std::array<Monster, 7>& Field();
    int& ActionPoints();
    int& HealthPoints();
    bool* EmptyHand();
    bool* EmptyField();
    int& CardsInHand();
    int& CardsOnField();
    int& HandSelected();
    int& FieldSelected();
private:
    std::array<Monster, 5> m_hand;
    std::array<Monster, 7> m_field;
    int  m_actionPoints;
    int  m_healthPoints;
    bool m_emptyHand[5] = {true, true, true, true, true};
    bool m_emptyField[7] = {true, true, true, true, true, true, true};
    int  m_cardsInHand;
    int  m_cardsOnField;
    int  m_handSelected;
    int  m_fieldSelected;
};

#endif // PLAYER_H
