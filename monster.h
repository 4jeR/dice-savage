#ifndef MONSTER_H
#define MONSTER_H
#include <QString>
#include <typeinfo>
#include <cmath>
#include <QPixmap>

class Monster
{
public:
    Monster(QString name="empty", QPixmap pixmap = QPixmap(), int lvl = 0, float dices = 0.0);
    Monster(const Monster& rhs);

    bool operator<(const Monster& rhs);
    Monster& operator=(const Monster& rhs);

    QString Name()const;
    QPixmap& PixMap();
    bool& CanAttack();
    int Lvl()const;
    float Dices()const;
    int CalculateDamage()const;
private:
    QString m_name;
    QPixmap m_pixmap;
    int m_lvl;
    float m_dices;
    bool m_canAttack;
};

#endif // MONSTER_H
