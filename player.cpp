#include "player.h"

Player::Player()
{
    m_actionPoints = Options::s_actionPoints;
    m_healthPoints = Options::s_healthPoints;
    m_cardsInHand = 0;
    m_cardsOnField = 0;
    m_handSelected = 5;
    m_fieldSelected = 7;
}



std::array<Monster, 5>& Player::Hand(){
    return m_hand;
}


std::array<Monster, 7>& Player::Field(){
    return m_field;
}



int& Player::ActionPoints(){
    return m_actionPoints;
}


int& Player::HealthPoints(){
    return m_healthPoints;
}



bool* Player::EmptyHand(){
    return m_emptyHand;
}


bool* Player::EmptyField(){
    return m_emptyField;
}



int& Player::CardsInHand(){
    return m_cardsInHand;
}


int& Player::CardsOnField(){
    return m_cardsOnField;
}



int& Player::HandSelected(){
    return m_handSelected;
}


int& Player::FieldSelected(){
    return m_fieldSelected;
}

