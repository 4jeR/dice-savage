#ifndef STACK_H
#define STACK_H

#include <QString>
#include <vector>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include <string>
#include <algorithm>
#include <string>
#include <utility>

#include "monster.h"
#include "options.h"

class Stack
{
public:

    Stack(const std::vector<Monster>& bestiaryVec);

    std::vector<Monster>& GetStack();
private:
    std::vector<Monster> m_stack;
};

#endif // STACK_H
