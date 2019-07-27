# DiceSavage
Turn-based card game written in C++ with the support of Qt.

# About
This is the implementation of basic card-game, which represents the fantasy monsters fighting on the field.
Two players summon cards on the field to The goal of the game is to defeat enemy player by lowering his health points to 0. 
Each monster has the name, level and the number of dices, which represent his dueling power. 
Players are alternately performing turn, in which they can pick a card from stack, summon monster and attack the enemy monsters.
(or player itself).

Application has been made using Qt Creator, with the Object Oriented Programming paradigm.
All graphics are self-made.


# Implemented features
* simple GUI menu,
* options block - to let user adjust everything for himself (costs of actions, stats of players, seed, etc.),
* basic enemy NPC behaviour algorithm implemented,
* bestiary of all possible creatures in the game is loaded from the file (and also the graphics),
* on each game start, the stack is being randomized from the possible monsters in game,
* opportunity to check all possible monsters and their stats

