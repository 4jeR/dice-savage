# DiceSavage
Turn-based card game written in C++ with the support of Qt and STL.

# About
This is the implementation of basic card-game, which represents the fantasy monsters fighting on the field.
The goal of the game is to defeat enemy player by lowering his health points to 0. 
Each monster has the name, level and the number of dices, which represents his dueling power. To attack the enemy player, first it is required to slay all his remaining monsters on the field.
Players are alternately performing turn, in which they can pick a card from stack, summon monster and attack the enemy monsters
(or player itself).

Application has been made using Qt Creator with the Object Oriented Programming paradigm.
All graphics are self-made.


# Implemented features
* simple GUI menu,
* options block - to let user adjust everything for himself (costs of actions, stats of players, seed, etc.),
* basic enemy NPC behaviour algorithm,
* bestiary of all possible creatures in the game is loaded from the file (and also the graphics),
* on each game start, the stack is being randomized from the possible monsters in game,
* possibility to check all possible monsters and their stats

# Fight system
Duel between two monsters is carried out with the following algorithm:
* each monster has its dices (some of them are *broken*),
* all dices are rolled, with the possible values from 1 to 6 (*broken: 1 to 3*),
* dices are sorted, and only the biggest values from each monster's set are compared,
* the owner of smaller amount loses one dice and the next turn of duel is started,
* if amounts are equal, both monsters lose one dice,
* monsters fight until they don't have any dices left.

# Screenshots from the game
* game
![game](https://user-images.githubusercontent.com/38592844/61994389-ca1de900-b079-11e9-8e8e-15aa09b15e67.png)

* main menu
![menu](https://user-images.githubusercontent.com/38592844/61994401-0b15fd80-b07a-11e9-996c-623ab5c8ee19.png)

* bestiary
![bestiary](https://user-images.githubusercontent.com/38592844/61994408-2aad2600-b07a-11e9-9d61-cc2c77a96760.png)

* options
![options](https://user-images.githubusercontent.com/38592844/61994415-47495e00-b07a-11e9-82f1-bab9ad557105.png)
