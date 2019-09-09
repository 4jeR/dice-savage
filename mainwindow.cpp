#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->button_card_1_selected->setVisible(false);
    ui->button_card_2_selected->setVisible(false);
    ui->button_card_3_selected->setVisible(false);
    ui->button_card_4_selected->setVisible(false);
    ui->button_card_5_selected->setVisible(false);

    ui->text_about->setVisible(false);
    ui->button_back->setVisible(false);
    ui->list_monsters->setVisible(false);
    ui->rbutton_sort->setVisible(false);
    ui->box_playerCards->setVisible(false);
    ui->label_cardAbout->setVisible(false);
    ui->label_arrow->setVisible(false);
    ui->label_arrowBF->setVisible(false);

    ui->box_battleField->setVisible(false);
    ui->box_playerGUI->setVisible(false);
    ui->box_enemy->setVisible(false);

    ui->lineEdit_seed->setVisible(false);
    ui->options_seed->setVisible(false);

    ui->slider_ap->setVisible(false);
    ui->options_ap->setVisible(false);
    ui->options_ap_min->setVisible(false);
    ui->options_ap_max->setVisible(false);
    ui->lcd_options_ap->setVisible(false);
    ui->lcd_options_ap->display(ui->slider_ap->value());

    ui->lcd_turn->setVisible(false);
    ui->label_turn->setVisible(false);
    ui->button_endTurn->setVisible(false);

    ui->slider_hp->setVisible(false);
    ui->options_hp->setVisible(false);
    ui->options_hp_min->setVisible(false);
    ui->options_hp_max->setVisible(false);
    ui->lcd_options_hp->setVisible(false);
    ui->lcd_options_hp->display(ui->slider_hp->value());

    ui->slider_stackSize->setVisible(false);
    ui->options_stackSize->setVisible(false);
    ui->options_stack_min->setVisible(false);
    ui->options_stack_max->setVisible(false);
    ui->lcd_options_stackSize->setVisible(false);
    ui->lcd_options_stackSize->display(ui->slider_stackSize->value());

    ui->slider_cardPickCost->setVisible(false);
    ui->options_cardPickCost->setVisible(false);
    ui->options_cardPickCost_min->setVisible(false);
    ui->options_cardPickCost_max->setVisible(false);
    ui->lcd_options_cardPickCost->setVisible(false);
    ui->lcd_options_cardPickCost->display(ui->slider_cardPickCost->value());

    ui->slider_turnIncome->setVisible(false);
    ui->options_turnIncome->setVisible(false);
    ui->options_turnIncome_min->setVisible(false);
    ui->options_turnIncome_max->setVisible(false);
    ui->lcd_options_turnIncome->setVisible(false);
    ui->lcd_options_turnIncome->display(ui->slider_turnIncome->value());

    ui->label_enemy_card1->setVisible(false);
    ui->label_enemy_card2->setVisible(false);
    ui->label_enemy_card3->setVisible(false);
    ui->label_enemy_card4->setVisible(false);
    ui->label_enemy_card5->setVisible(false);

    ui->button_getCard->setVisible(false);
    ui->label_actionPoint->setVisible(false);

    ui->lcd_ap->setVisible(false);
    ui->lcd_hp->setVisible(false);
    ui->lcd_stack->setVisible(false);

    Options::s_seed = ui->lineEdit_seed->text().toInt();
    Options::s_actionPoints = ui->lcd_options_ap->value();
    Options::s_healthPoints = ui->lcd_options_hp->value();
    Options::s_stackSize = ui->lcd_options_stackSize->value();
    Options::s_pickCardCost = ui->lcd_options_cardPickCost->value();
    Options::s_turnIncome = ui->lcd_options_turnIncome->value();

    QPixmap pixmap(QDir::currentPath() + "/../DiceSavage/graphics/bestiary.png");
    int w = ui->label_cardAbout->width();
    int h = ui->label_cardAbout->height();
    ui->label_cardAbout->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    QFile file(QDir::currentPath() + "/../DiceSavage/bestiary.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString name = in.readLine();
        pixmap = QPixmap(QDir::currentPath() + "/../DiceSavage/graphics/cards/" + name + ".png");
        QString lvl = in.readLine();
        QString dices = in.readLine();
        bestiary.push_back(Monster(name, pixmap, lvl.toInt(), dices.toFloat()));
        QListWidgetItem* item = new QListWidgetItem(QIcon(QDir::currentPath() + "/../DiceSavage/graphics/" + lvl + "lvl.png"), name);
        item->setData(Qt::UserRole, lvl);
        ui->list_monsters->addItem(item);
    }

    file.close();

    struct {
        bool operator()(const Monster& a, const Monster& b) const
        {
            return a.Lvl() < b.Lvl();
        }
    } monsterLess;

    std::sort(bestiary.begin(), bestiary.end(), monsterLess);
    ui->list_monsters->sortItems();

    connect(ui->list_monsters, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_list_monsters_itemClicked));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete enemy;
    delete stack;
}

void MainWindow::on_button_exit_clicked()
{
    this->close();
}

void MainWindow::on_button_about_clicked()
{
    ui->button_start->setVisible(false);
    ui->button_options->setVisible(false);
    ui->button_bestiary->setVisible(false);
    ui->button_about->setVisible(false);
    ui->button_exit->setVisible(false);

    ui->text_about->setVisible(true);
    ui->button_back->setVisible(true);
}

void MainWindow::on_button_back_clicked()
{
    ui->label_cardAbout->setVisible(false);
    ui->list_monsters->setVisible(false);
    ui->button_back->setVisible(false);
    ui->text_about->setVisible(false);
    ui->rbutton_sort->setVisible(false);
    ui->label_cardAbout->setVisible(false);

    ui->button_start->setVisible(true);
    ui->button_options->setVisible(true);
    ui->button_bestiary->setVisible(true);
    ui->button_about->setVisible(true);
    ui->button_exit->setVisible(true);


    ui->lineEdit_seed->setVisible(false);
    ui->options_seed->setVisible(false);

    ui->slider_ap->setVisible(false);
    ui->options_ap->setVisible(false);
    ui->options_ap_min->setVisible(false);
    ui->options_ap_max->setVisible(false);
    ui->lcd_options_ap->setVisible(false);

    ui->slider_hp->setVisible(false);
    ui->options_hp->setVisible(false);
    ui->options_hp_min->setVisible(false);
    ui->options_hp_max->setVisible(false);
    ui->lcd_options_hp->setVisible(false);

    ui->slider_stackSize->setVisible(false);
    ui->options_stackSize->setVisible(false);
    ui->options_stack_min->setVisible(false);
    ui->options_stack_max->setVisible(false);
    ui->lcd_options_stackSize->setVisible(false);

    ui->slider_cardPickCost->setVisible(false);
    ui->options_cardPickCost->setVisible(false);
    ui->options_cardPickCost_min->setVisible(false);
    ui->options_cardPickCost_max->setVisible(false);
    ui->lcd_options_cardPickCost->setVisible(false);

    ui->slider_turnIncome->setVisible(false);
    ui->options_turnIncome->setVisible(false);
    ui->options_turnIncome_min->setVisible(false);
    ui->options_turnIncome_max->setVisible(false);
    ui->lcd_options_turnIncome->setVisible(false);

    ui->list_monsters->setCurrentItem(NULL);
}

void MainWindow::on_button_bestiary_clicked()
{
    ui->button_start->setVisible(false);
    ui->button_options->setVisible(false);
    ui->button_bestiary->setVisible(false);
    ui->button_about->setVisible(false);
    ui->button_exit->setVisible(false);

    QPixmap pixmap(QDir::currentPath() + "/../DiceSavage/graphics/bestiary.png");
    int w = ui->label_cardAbout->width();
    int h = ui->label_cardAbout->height();
    ui->label_cardAbout->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    ui->label_cardAbout->setVisible(true);
    ui->list_monsters->setVisible(true);
    ui->button_back->setVisible(true);
    ui->rbutton_sort->setVisible(true);
}


void MainWindow::on_rbutton_sort_clicked()
{
    if(ui->rbutton_sort->isChecked()){
        QFile file(QDir::currentPath() + "/../DiceSavage/bestiary.txt");
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

        for(int i = 0; i < ui->list_monsters->count(); ++i){
            QString lvl = QString::number(bestiary.at(i).Lvl());
            QString name = bestiary.at(i).Name();
            ui->list_monsters->item(i)->setIcon(QIcon(QDir::currentPath() + "/../DiceSavage/graphics/" + lvl + "lvl.png"));
            ui->list_monsters->item(i)->setText(name);
        }
    }
    else
        ui->list_monsters->sortItems();
}


void MainWindow::on_list_monsters_itemClicked(QListWidgetItem *item)
{
    QPixmap qpixmap(QDir::currentPath() + "/../DiceSavage/graphics/cards/" + item->text() + ".png");
    int w = ui->label_cardAbout->width();
    int h = ui->label_cardAbout->height();
    ui->label_cardAbout->setPixmap(qpixmap.scaled(w,h,Qt::KeepAspectRatio));
}


void MainWindow::on_button_start_clicked()
{
    ui->button_start->setVisible(false);
    ui->button_options->setVisible(false);
    ui->button_about->setVisible(false);
    ui->button_bestiary->setVisible(false);
    ui->button_exit->setVisible(false);

    ui->box_playerCards->setVisible(true);
    ui->box_battleField->setVisible(true);

    StatsTracker::s_seed         = Options::s_seed;
    StatsTracker::s_stackSize    = Options::s_stackSize;
    StatsTracker::s_turn         = 1;

    ui->button_getCard->setText("pick a card [" + QString::number(Options::s_pickCardCost) + " AP ]");

    player = new Player();
    enemy = new Player();
    stack = new Stack(bestiary);

    QPixmap pixmap(QDir::currentPath() + "/../DiceSavage/graphics/empty_card.png");
    int w = ui->label_card1->width();
    int h = ui->label_card1->height();

    emptycardimg = pixmap.toImage();

    ui->label_card1->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_card2->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_card3->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_card4->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_card5->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    w = ui->label_enemy_card1->width();
    h = ui->label_enemy_card1->height();

    ui->label_enemy_card1->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemy_card2->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemy_card3->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemy_card4->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemy_card5->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));

    w = ui->label_enemyBF_card1->width();
    h = ui->label_enemyBF_card1->height();

    ui->label_enemyBF_card1->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemyBF_card2->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemyBF_card3->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemyBF_card4->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemyBF_card5->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemyBF_card6->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_enemyBF_card7->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));

    ui->label_playerBF_card1->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_playerBF_card2->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_playerBF_card3->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_playerBF_card4->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_playerBF_card5->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_playerBF_card6->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
    ui->label_playerBF_card7->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));

    pixmap = QPixmap(QDir::currentPath() + "/../DiceSavage/graphics/card_templateBack.png");
    w = ui->label_stack->width();
    h = ui->label_stack->height();
    ui->label_stack->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    pixmap = QPixmap(QDir::currentPath() + "/../DiceSavage/graphics/action_point.png");
    w = ui->label_actionPoint->width();
    h = ui->label_actionPoint->height();
    ui->label_actionPoint->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_enemyAP->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    pixmap = QPixmap(QDir::currentPath() + "/../DiceSavage/graphics/hp.png");
    w = ui->label_healthPoints->width();
    h = ui->label_healthPoints->height();
    ui->label_healthPoints->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_enemyHP->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    pixmap = QPixmap(QDir::currentPath() + "/../DiceSavage/graphics/arrow.png");
    w = ui->label_arrow->width();
    h = ui->label_arrow->height();
    ui->label_arrow->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_arrowBF->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));

    ui->button_getCard->setVisible(true);
    ui->label_actionPoint->setVisible(true);
    ui->lcd_ap->setVisible(true);
    ui->lcd_hp->setVisible(true);
    ui->lcd_stack->setVisible(true);

    ui->lcd_turn->setVisible(true);
    ui->label_turn->setVisible(true);
    ui->button_endTurn->setVisible(true);
    ui->box_playerGUI->setVisible(true);
    ui->box_enemy->setVisible(true);

    ui->button_card_1_selected->setVisible(true);
    ui->button_card_2_selected->setVisible(true);
    ui->button_card_3_selected->setVisible(true);
    ui->button_card_4_selected->setVisible(true);
    ui->button_card_5_selected->setVisible(true);

    ui->label_enemy_card1->setVisible(true);
    ui->label_enemy_card2->setVisible(true);
    ui->label_enemy_card3->setVisible(true);
    ui->label_enemy_card4->setVisible(true);
    ui->label_enemy_card5->setVisible(true);

    ui->lcd_ap->display(player->ActionPoints());
    ui->lcd_hp->display(player->HealthPoints());
    ui->lcd_enemyAP->display(enemy->ActionPoints());
    ui->lcd_enemyHP->display(enemy->HealthPoints());

    ui->lcd_stack->display(StatsTracker::s_stackSize);
    ui->lcd_income->display(Options::s_turnIncome);
}


void MainWindow::GetCard(Player* p, bool flag){ // true - player, false - enemy
    if(p->CardsInHand() == 5 ){
        if(flag)
            QMessageBox::information(this, "Info", "Full hand!");
        return;
    }
    else if(p->ActionPoints() < Options::s_pickCardCost ){
        if(flag)
            QMessageBox::information(this, "Info", "No action points to pick a card from stack!");
        return;
    }
    else if(StatsTracker::s_stackSize == 0){
        if(flag)
            QMessageBox::information(this, "Info", "Stack empty!!");
        return;
    }

    else if(p->ActionPoints() >= Options::s_pickCardCost && p->CardsInHand() <= 4){
        int index = 0;
        for(unsigned i = 0; i < 5; ++i){
            if(p->EmptyHand()[i]){
                index = i;
                p->EmptyHand()[i] = false;
                break;
            }
        }

        QPixmap qpixmap((flag) ? stack->GetStack().back().PixMap() : QDir::currentPath() + "/../DiceSavage/graphics/card_templateBack.png");

        p->Hand()[index] = Monster(stack->GetStack().back());
        stack->GetStack().pop_back();
        --StatsTracker::s_stackSize;

        int w = (flag) ? ui->label_card1->width() : ui->label_enemy_card1->width() ;
        int h = (flag) ? ui->label_card1->height() : ui->label_enemy_card1->height();

        switch(index){
            case 0:
                if(flag)
                    ui->label_card1->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                else
                    ui->label_enemy_card1->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                break;
            case 1:
                if(flag)
                    ui->label_card2->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                else
                    ui->label_enemy_card2->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                break;
            case 2:
                if(flag)
                    ui->label_card3->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                else
                    ui->label_enemy_card3->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                break;
            case 3:
                if(flag)
                    ui->label_card4->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                else
                    ui->label_enemy_card4->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                break;
            case 4:
                if(flag)
                    ui->label_card5->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                else
                    ui->label_enemy_card5->setPixmap(qpixmap.scaled(w, h, Qt::KeepAspectRatio));
                break;
            default:
                break;
        }

        p->ActionPoints() -= Options::s_pickCardCost;
        ++(p->CardsInHand());
        (flag) ? ui->lcd_ap->display(p->ActionPoints()) : ui->lcd_enemyAP->display(p->ActionPoints());
        ui->lcd_stack->display(StatsTracker::s_stackSize);
    }
}

void MainWindow::on_button_getCard_clicked()
{
    GetCard(player, true);
}


void MainWindow::on_button_options_clicked()
{
    ui->button_start->setVisible(false);
    ui->button_options->setVisible(false);
    ui->button_bestiary->setVisible(false);
    ui->button_about->setVisible(false);
    ui->button_exit->setVisible(false);

    ui->lineEdit_seed->setVisible(true);
    ui->options_seed->setVisible(true);

    ui->slider_ap->setVisible(true);
    ui->options_ap->setVisible(true);
    ui->options_ap_min->setVisible(true);
    ui->options_ap_max->setVisible(true);
    ui->lcd_options_ap->setVisible(true);

    ui->slider_hp->setVisible(true);
    ui->options_hp->setVisible(true);
    ui->options_hp_min->setVisible(true);
    ui->options_hp_max->setVisible(true);
    ui->lcd_options_hp->setVisible(true);

    ui->slider_stackSize->setVisible(true);
    ui->options_stackSize->setVisible(true);
    ui->options_stack_min->setVisible(true);
    ui->options_stack_max->setVisible(true);
    ui->lcd_options_stackSize->setVisible(true);

    ui->slider_cardPickCost->setVisible(true);
    ui->options_cardPickCost->setVisible(true);
    ui->options_cardPickCost_min->setVisible(true);
    ui->options_cardPickCost_max->setVisible(true);
    ui->lcd_options_cardPickCost->setVisible(true);

    ui->slider_turnIncome->setVisible(true);
    ui->options_turnIncome->setVisible(true);
    ui->options_turnIncome_min->setVisible(true);
    ui->options_turnIncome_max->setVisible(true);
    ui->lcd_options_turnIncome->setVisible(true);
    ui->lcd_options_turnIncome->display(ui->slider_turnIncome->value());

    ui->button_back->setVisible(true);
}

void MainWindow::on_slider_ap_valueChanged(int value)
{
    ui->lcd_options_ap->display(static_cast<double>(value));
    Options::s_actionPoints = value;
}


void MainWindow::on_slider_hp_valueChanged(int value)
{
    ui->lcd_options_hp->display(static_cast<double>(value));
    Options::s_healthPoints = value;
}


void MainWindow::on_slider_stackSize_valueChanged(int value)
{
    ui->lcd_options_stackSize->display(static_cast<double>(value));
    Options::s_stackSize = value;
}


void MainWindow::on_lineEdit_seed_returnPressed()
{
    Options::s_seed = ui->lineEdit_seed->text().toInt();
}


void MainWindow::on_slider_cardPickCost_valueChanged(int value)
{
    ui->lcd_options_cardPickCost->display(static_cast<double>(value));
    Options::s_pickCardCost = value;
}

void MainWindow::on_slider_turnIncome_valueChanged(int value)
{
    ui->lcd_options_turnIncome->display(static_cast<double>(value));
    Options::s_turnIncome = value;
}

void MainWindow::on_button_endTurn_clicked()
{
    if(enemy->ActionPoints() >= 4)
        GetCard(enemy, false);

    while(enemy->CardsInHand() != 0){
         enemy->HandSelected() = std::rand()%5;
         if(!enemy->EmptyHand()[enemy->HandSelected()]){
             break;
         }
    }
    SummonMonster(enemy, false);

    if(enemy->CardsOnField() >= 3){

        for(int i = 0; i < 7; ++i){
            enemy->FieldSelected() = i;
            if(!enemy->EmptyField()[enemy->FieldSelected()])
                Attack(false);
        }
    }

    player->ActionPoints() += Options::s_turnIncome;
    enemy->ActionPoints() += Options::s_turnIncome;

    if(StatsTracker::s_turn % 2 == 0)
        ++Options::s_turnIncome;

    ui->lcd_income->display(Options::s_turnIncome);

    for(int i = 0; i < 7; ++i){
        player -> Field()[i].CanAttack() = true;
        enemy  -> Field()[i].CanAttack() = true;
    }

    ++StatsTracker::s_turn;
    ui->lcd_turn->display(StatsTracker::s_turn);

    ui->lcd_ap->display(player->ActionPoints());
    ui->lcd_hp->display(player->HealthPoints());

    ui->lcd_enemyAP->display(enemy->ActionPoints());
    ui->lcd_enemyHP->display(enemy->HealthPoints());

}

void MainWindow::on_button_card_1_selected_clicked()
{
    if(!player->EmptyHand()[0]){
        int newX = ui->label_card1->x() + 70;
        int newY = ui->label_card1->y() - 45;

        ui->label_arrow->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40,newY + 40)));
        ui->label_arrow->setVisible(true);
        player->HandSelected() = 0;
        ui->button_summon->setText("summon [" + QString::number(2 * player->Hand()[player->HandSelected()].Lvl()) + " AP]");

    }
}

void MainWindow::on_button_card_2_selected_clicked()
{
    if(!player->EmptyHand()[1]){
        int newX = ui->label_card2->x() + 70;
        int newY = ui->label_card2->y() - 45;

        ui->label_arrow->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40,newY + 40)));
        ui->label_arrow->setVisible(true);
        player->HandSelected() = 1;
        ui->button_summon->setText("summon [" + QString::number(2 * player->Hand()[player->HandSelected()].Lvl()) + " AP]");
    }
}

void MainWindow::on_button_card_3_selected_clicked()
{
    if(!player->EmptyHand()[2]){
        int newX = ui->label_card3->x() + 70;
        int newY = ui->label_card3->y() - 45;

        ui->label_arrow->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40,newY + 40)));
        ui->label_arrow->setVisible(true);
        player->HandSelected() = 2;
        ui->button_summon->setText("summon [" + QString::number(2 * player->Hand()[player->HandSelected()].Lvl()) + " AP]");
    }
}

void MainWindow::on_button_card_4_selected_clicked()
{
    if(!player->EmptyHand()[3]){
        int newX = ui->label_card4->x() + 70;
        int newY = ui->label_card4->y() - 45;

        ui->label_arrow->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40,newY + 40)));
        ui->label_arrow->setVisible(true);
        player->HandSelected() = 3;
        ui->button_summon->setText("summon [" + QString::number(2 * player->Hand()[player->HandSelected()].Lvl()) + " AP]");
    }
}

void MainWindow::on_button_card_5_selected_clicked()
{
    if(! player->EmptyHand()[4]){
        int newX = ui->label_card5->x() + 70;
        int newY = ui->label_card5->y() - 45;

        ui->label_arrow->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40,newY + 40)));
        ui->label_arrow->setVisible(true);
        player->HandSelected() = 4;
        ui->button_summon->setText("summon [" + QString::number(2 * player->Hand()[player->HandSelected()].Lvl()) + " AP]");

    }
}

void MainWindow::SummonMonster(Player* p, bool flag){
    if(p->HandSelected() == 5 ){
        if(flag)
            QMessageBox::information(this, "info", "Select monster which has to be summoned!");
        return;
    }

    else if(p->CardsOnField() == 7){
        if(flag)
            QMessageBox::information(this, "info", "Full field!");
        return;
    }

    else if(p->Hand()[p->HandSelected()].Lvl() * 2 > p->ActionPoints() ){
        if(flag)
            QMessageBox::information(this, "info", "Not enough action points (2 * monster level) to summon");
        return;
    }

    else if(p->Hand()[p->HandSelected()].Lvl() * 2 <= p->ActionPoints()){
        int cost = p->Hand()[p->HandSelected()].Lvl() * 2;
        int index = 0;
        for(int i = 0; i < 7; ++i){
            if(p->EmptyField()[i]){
                index = i;
                p->EmptyField()[i] = false;
                break;
            }
        }
        p->Field()[index] = p->Hand()[p->HandSelected()];
        QPixmap pixmap(p->Hand()[p->HandSelected()].PixMap());
        int w = ui->label_playerBF_card1->width();
        int h = ui->label_playerBF_card1->height();

        switch(index){
            case 0:
                if(flag)
                    ui->label_playerBF_card1->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                    ui->label_enemyBF_card1->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 1:
                if(flag)
                    ui->label_playerBF_card2->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                    ui->label_enemyBF_card2->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 2:
                if(flag)
                    ui->label_playerBF_card3->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                    ui->label_enemyBF_card3->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 3:
                if(flag)
                    ui->label_playerBF_card4->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                    ui->label_enemyBF_card4->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 4:
                if(flag)
                    ui->label_playerBF_card5->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                    ui->label_enemyBF_card5->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 5:
                if(flag)
                    ui->label_playerBF_card6->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                    ui->label_enemyBF_card6->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 6:
                if(flag)
                    ui->label_playerBF_card7->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                    ui->label_enemyBF_card7->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            default:
                 break;
        }

        pixmap = QPixmap(QDir::currentPath() + "/../DiceSavage/graphics/empty_card.png");
        w = (flag) ? ui->label_card1->width() : ui->label_enemy_card1->width() ;
        h = (flag) ? ui->label_card1->height() : ui->label_enemy_card1->height();

        switch(p->HandSelected()){
            case 0:
                 if(flag)
                    ui->label_card1->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                 else
                    ui->label_enemy_card1->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                 break;
            case 1:
                if(flag)
                   ui->label_card2->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                   ui->label_enemy_card2->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 2:
                if(flag)
                   ui->label_card3->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                   ui->label_enemy_card3->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 3:
                if(flag)
                   ui->label_card4->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                   ui->label_enemy_card4->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            case 4:
                if(flag)
                   ui->label_card5->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                else
                   ui->label_enemy_card5->setPixmap(pixmap.scaled(w, h,Qt::KeepAspectRatio));
                break;
            default:
                 break;
        }

        p->EmptyField()[index] = false;
        p->EmptyHand()[p->HandSelected()] = true; 
        p->ActionPoints() -= cost;
        ui->lcd_ap->display(p->ActionPoints());
        --p->CardsInHand();
        ++p->CardsOnField();
        p->HandSelected() = 5; 
    }
}

void MainWindow::on_button_summon_clicked()
{
    SummonMonster(player, true);
    ui->label_arrow->setVisible(false);
}

void MainWindow::on_button_playerBF_card1_selected_clicked()
{
    if(!player->EmptyField()[0]){
        int newX = ui->label_playerBF_card1->x() + 30;
        int newY = ui->label_playerBF_card1->y() - 25;
        ui->label_arrowBF->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40, newY + 40)));
        ui->label_arrowBF->setVisible(true);
        player->FieldSelected() = 0;
    }
}

void MainWindow::on_button_playerBF_card2_selected_clicked()
{
    if(!player->EmptyField()[1]){
        int newX = ui->label_playerBF_card2->x() + 30;
        int newY = ui->label_playerBF_card2->y() - 25;
        ui->label_arrowBF->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40, newY + 40)));
        ui->label_arrowBF->setVisible(true);
        player->FieldSelected() = 1;
    }
}

void MainWindow::on_button_playerBF_card3_selected_clicked()
{
    if(!player->EmptyField()[2]){
        int newX = ui->label_playerBF_card3->x() + 30;
        int newY = ui->label_playerBF_card3->y() - 25;
        ui->label_arrowBF->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40, newY + 40)));
        ui->label_arrowBF->setVisible(true);
        player->FieldSelected() = 2;
    }
}

void MainWindow::on_button_playerBF_card4_selected_clicked()
{
    if(!player->EmptyField()[3]){
        int newX = ui->label_playerBF_card4->x() + 30;
        int newY = ui->label_playerBF_card4->y() - 25;
        ui->label_arrowBF->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40, newY + 40)));
        ui->label_arrowBF->setVisible(true);
        player->FieldSelected() = 3;
    }
}

void MainWindow::on_button_playerBF_card5_selected_clicked()
{
    if(!player->EmptyField()[4]){
        int newX = ui->label_playerBF_card5->x() + 30;
        int newY = ui->label_playerBF_card5->y() - 25;
        ui->label_arrowBF->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40, newY + 40)));
        ui->label_arrowBF->setVisible(true);
        player->FieldSelected() = 4;
    }
}

void MainWindow::on_button_playerBF_card6_selected_clicked()
{
    if(!player->EmptyField()[5]){
        int newX = ui->label_playerBF_card6->x() + 30;
        int newY = ui->label_playerBF_card6->y() - 25;
        ui->label_arrowBF->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40, newY + 40)));
        ui->label_arrowBF->setVisible(true);
        player->FieldSelected() = 5;
    }
}

void MainWindow::on_button_playerBF_card7_selected_clicked()
{
    if(!player->EmptyField()[6]){
        int newX = ui->label_playerBF_card7->x() + 30;
        int newY = ui->label_playerBF_card7->y() - 25;
        ui->label_arrowBF->setGeometry(QRect(QPoint(newX, newY),QPoint(newX + 40, newY + 40)));
        ui->label_arrowBF->setVisible(true);
        player->FieldSelected() = 6;
    }
}


void MainWindow::Attack(bool isPlayerAttacker){
    if(StatsTracker::s_turn <= 2){
        if(isPlayerAttacker)
            QMessageBox::information(this, "info", "Cannot attack in the first two turns!");
        return;
    }
    else if(isPlayerAttacker){
        if(player->FieldSelected() == 7){
                QMessageBox::information(this, "info", "Select monster which has to perform attack!");
            return;
        }

        if(player->Field()[player->FieldSelected()].CanAttack()){
            int dmg;
            if(enemy->CardsOnField() == 0){
                dmg = player->Field()[player->FieldSelected()].CalculateDamage() / player->Field()[player->FieldSelected()].Lvl() ;
                QMessageBox::information(this, "info", "attacking enemy with the power: " + QString::number(dmg));
                enemy->HealthPoints() -= dmg;
                ui->lcd_enemyHP->display(enemy->HealthPoints());
                CheckForEndGame(player, enemy);
            }
            else{
                int idx;
                do { idx = std::rand()%7; } while(enemy->EmptyField()[idx]);
                QMessageBox::information(this, "info", "Your monster has been encountered by enemy " + enemy->Field()[idx].Name());
                Fight(player, enemy, player->FieldSelected(), idx);
            }
            player->Field()[player->FieldSelected()].CanAttack() = false;
        }
        else {
            QMessageBox::information(this, "info", "This monster has already attacked in this turn!");
        }
    }

    else if(!isPlayerAttacker){
        QMessageBox::information(this, "info", "Enemy attacks!");
        QMessageBox::information(this, "info", "Attacking from monster of index: " + QString::number(enemy->FieldSelected()));
        if(enemy->Field()[enemy->FieldSelected()].CanAttack()){
            if(player->CardsOnField() == 0){
                int dmg = enemy->Field()[enemy->FieldSelected()].CalculateDamage() / enemy->Field()[enemy->FieldSelected()].Lvl() ;
                QMessageBox::information(this, "info", "enemy is attacking with the power: " + QString::number(dmg));
                player->HealthPoints() -= dmg;
                ui->lcd_hp->display(player->HealthPoints());
                CheckForEndGame(player, enemy);
            }
            else{
                int idx;
                do { idx = std::rand()%7; } while(player->EmptyField()[idx]);
                QMessageBox::information(this, "info", "Enemy monster has been encountered by your " + player->Field()[idx].Name());
                Fight(player, enemy, idx, enemy->FieldSelected());
            }
            enemy->Field()[enemy->FieldSelected()].CanAttack() = false;
        } 
    }
}


void MainWindow::on_button_fight_clicked()
{
    Attack(true);
}

void MainWindow::CheckForEndGame(Player* p1, Player* p2){
    if(p1->HealthPoints() <= 0){
        QMessageBox::information(this, "info", "### GG! Enemy wins! ###");
        this->close();
    }
    else if(p2->HealthPoints() <= 0){
        QMessageBox::information(this, "info", "### GG! Player wins! ###");
        this->close();
    }
}



void MainWindow::Fight(Player* attacker, Player* defensor,const int attackIDX,const int defIDX){
    int dices1 = static_cast<int>( ceil( attacker->Field()[attackIDX].Dices() ) );
    int dices2 = static_cast<int>( ceil( defensor->Field()[defIDX].Dices() ) );
    QMessageBox::information(this, "info", "dices1: " + QString::number(dices1) + ", dices2: " + QString::number(dices2));
    do{
        std::vector<int> values1;
        std::vector<int> values2;

        for(int i = 0; i < dices1; ++i){
            if(i==dices1-1 && (int(10.0 * attacker->Field()[attackIDX].Dices() ) % 10 == 5))
                values1.push_back(std::rand() % 3 + 1);
            else
                values1.push_back(std::rand() % 6 + 1);
        }

        for(int i = 0; i < dices2; ++i){
            if(i==dices2-1 && (int(10.0 * defensor->Field()[defIDX].Dices() ) % 10 == 5))
                values2.push_back(std::rand() % 3 + 1);
            else
                values2.push_back(std::rand() % 6 + 1);
        }

        std::sort(values1.begin(), values1.end(), std::greater_equal<int>());
        std::sort(values2.begin(), values2.end(), std::greater_equal<int>());

        QMessageBox::information(this, "info", "player rolls:");

        for(unsigned i = 0; i < values1.size()-1; ++i)
            QMessageBox::information(this, "info", QString::number(values1[i]));

        QMessageBox::information(this, "info", QString::number(values1[values1.size()-1]));
        QMessageBox::information(this, "info", "enemy rolls:");

        for(unsigned i = 0; i < values2.size()-1; ++i)
            QMessageBox::information(this, "info", QString::number(values2[i]));

        QMessageBox::information(this, "info", QString::number(values2[values2.size()-1]));

        if(values1[0] > values2[0])
            --dices2;
        else if(values1[0] < values2[0])
            --dices1;
        else if(values1[0] == values2[0]){
            --dices1;
            --dices2;
        }
    }while(dices1 && dices2);

    QPixmap pmap(QDir::currentPath() + "/../DiceSavage/graphics/empty_card.png");
    int w = ui->label_enemyBF_card1->width();
    int h = ui->label_enemyBF_card1->height();

    if(dices1 == 0 && dices2 == 0){
        QMessageBox::information(this, "info" , "Tie!");
        attacker->EmptyField()[attackIDX] = true;
        defensor->EmptyField()[defIDX] = true;
        --attacker->CardsOnField();
        --defensor->CardsOnField();
        ui->label_arrowBF->setVisible(false);
    }
    else if(dices1 == 0){
        QMessageBox::information(this, "info" ,
                                 "Enemy wins! Received: " + QString::number(attacker->Field()[attackIDX].Lvl() / 2 ) + " action points");

        attacker->EmptyField()[attackIDX] = true;
        --attacker->CardsOnField();
        defensor->ActionPoints() += defensor->Field()[defIDX].Lvl() / 2;
        ui->lcd_enemyAP->display(defensor->ActionPoints());
        ui->label_arrowBF->setVisible(false);
    }

    else if(dices2 == 0){
         QMessageBox::information(this, "info" ,
                                  "Player wins! Received: " + QString::number(attacker->Field()[attackIDX].Lvl() / 2 ) + " action points");

        defensor->EmptyField()[defIDX] = true;
        --defensor->CardsOnField();
        attacker->ActionPoints() += attacker->Field()[attackIDX].Lvl() / 2;
        ui->lcd_ap->display(attacker->ActionPoints());
    }

    if(dices1 == 0){
        switch(attackIDX){
            case 0:
                ui->label_playerBF_card1->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 1:
                ui->label_playerBF_card2->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 2:
                ui->label_playerBF_card3->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 3:
                ui->label_playerBF_card4->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 4:
                ui->label_playerBF_card5->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 5:
                ui->label_playerBF_card6->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 6:
                ui->label_playerBF_card7->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            default:
            break;
        }
    }

    if(dices2 == 0){
        switch(defIDX){
            case 0:
                ui->label_enemyBF_card1->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 1:
                ui->label_enemyBF_card2->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 2:
                ui->label_enemyBF_card3->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 3:
                ui->label_enemyBF_card4->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 4:
                ui->label_enemyBF_card5->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 5:
                ui->label_enemyBF_card6->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            case 6:
                ui->label_enemyBF_card7->setPixmap(pmap.scaled(w, h,Qt::KeepAspectRatio));
            break;

            default:
            break;
        }
    }
}