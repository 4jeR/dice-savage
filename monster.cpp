#include "monster.h"
#include <QMessageBox>

Monster::Monster(QString name, QPixmap pixmap, int lvl, float dices):
    m_name(name), m_pixmap(pixmap), m_lvl(lvl), m_dices(dices), m_canAttack(true)
{}

Monster::Monster(const Monster& m)
{
    m_name = QString(m.m_name);
    m_pixmap = m.m_pixmap;
    m_lvl = m.m_lvl;
    m_dices = m.m_dices;
    m_canAttack = m.m_canAttack;
}


bool Monster::operator<(const Monster& rhs){
    return m_name < rhs.m_name;
}


Monster& Monster::operator=(const Monster& rhs){
    m_name = rhs.m_name;
    m_pixmap = rhs.m_pixmap;
    m_lvl = rhs.m_lvl;
    m_dices = rhs.m_dices;
    m_canAttack = rhs.m_canAttack;

    return *this;
}


QString Monster::Name()const{
    return m_name;
}


QPixmap& Monster::PixMap(){
    return m_pixmap;
}


int Monster::Lvl()const{
    return m_lvl;
}


float Monster::Dices()const{
    return m_dices;
}


bool& Monster::CanAttack(){
    return m_canAttack;
}


int Monster::CalculateDamage()const{
    int dmg = 0;
    int size = static_cast<int>( floor(m_dices) );

    for(int i = 0; i < size; ++i)
        dmg += std::rand() % 6 + 1;

    if(int(10.0 * m_dices )% 10 == 5){
        dmg += std::rand() % 3 + 1;
    }

    return dmg;
}
