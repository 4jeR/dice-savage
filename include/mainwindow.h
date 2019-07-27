#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QPalette>

#include "player.h"
#include "stack.h"
#include "options.h"
#include "statstracker.h"

#include "monster.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_exit_clicked();

    void on_button_about_clicked();

    void on_button_back_clicked();

    void on_button_bestiary_clicked();

    void on_rbutton_sort_clicked();


    void on_list_monsters_itemClicked(QListWidgetItem *item);

    void on_button_start_clicked();

    void on_button_getCard_clicked();


    void on_button_options_clicked();

    void on_slider_ap_valueChanged(int value);


    void on_slider_hp_valueChanged(int value);

    void on_slider_stackSize_valueChanged(int value);

    void on_lineEdit_seed_returnPressed();

    void on_slider_cardPickCost_valueChanged(int value);

    void on_slider_turnIncome_valueChanged(int value);

    void on_button_endTurn_clicked();

    void on_button_card_1_selected_clicked();

    void on_button_card_2_selected_clicked();

    void on_button_card_3_selected_clicked();

    void on_button_card_4_selected_clicked();

    void on_button_card_5_selected_clicked();



    void on_button_summon_clicked();

    void on_button_playerBF_card1_selected_clicked();

    void on_button_playerBF_card2_selected_clicked();

    void on_button_playerBF_card3_selected_clicked();

    void on_button_playerBF_card4_selected_clicked();

    void on_button_playerBF_card5_selected_clicked();

    void on_button_playerBF_card6_selected_clicked();

    void on_button_playerBF_card7_selected_clicked();

    void on_button_fight_clicked();

    void GetCard(Player* p, bool flag);
    void SummonMonster(Player* p, bool flag);
    void Fight(Player* attacker, Player* defensor, const int attackIDX,const int defIDX);
    void CheckForEndGame(Player* p1, Player* p2);

    void Attack(bool isPlayerAttacker);


private:
    Ui::MainWindow *ui;
    Player* player;
    Player* enemy;
    Stack* stack;

    QImage emptycardimg;


    std::vector<Monster> bestiary;
};











#endif // MAINWINDOW_H
