#include "blackjacktable.h"
#include "ui_blackjacktable.h"
#include <string>
#include <QMediaPlayer>
#include <QDebug>
#include "card.h"
#include "game.h"
#include "deckstack.h"
#include "player.h"


//int userGameTypeChoice;
//starts game
Game * game = new Game();


BlackJackTable::BlackJackTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BlackJackTable)
{
    //sets the corresponding widgets to visible or non-visible based on the starting state of the ui
    ui->setupUi(this);

    ui->hitButton->setVisible(false);
    ui->stayButton->setVisible(false);
    ui->scoreLabel->setText("My score is: " );
    ui->playerCounter->setVisible(false);
    ui->playerLabel->setVisible(false);
    ui->statsButton->setVisible(false);
    ui->userButton->setVisible(false);
    ui->scoreLabel->setVisible(false);
    ui->playerConfirmationButton->setVisible(false);
    ui->statsProgress->setVisible(false);
    ui->nameInput->setVisible(false);
    ui->nameLabel->setVisible(false);
    ui->runningLabel->setVisible(false);
    ui->buyInLabel->setVisible(false);
    ui->buyInLineEdit->setVisible(false);
    ui->minBetLabel->setVisible(false);
    ui->minBetLineEdit->setVisible(false);
    ui->deckCountSpinBox->setVisible(false);
    ui->DeckLabel->setVisible(false);
    ui->NextRoundButton->setVisible(false);
    ui->BetLineEdit->setVisible(false);
    ui->BetLabel->setVisible(false);
    ui->doubleDownButton->setVisible(false);
    ui->userHandScoreLabel->setVisible(false);
    ui->moneyLabel->setVisible(false);
    ui->ExitGameButton->setVisible(false);
    ui->card1Label->setVisible(false);
    ui->card2Label->setVisible(false);
    ui->card3Label->setVisible(false);
    ui->card4Label->setVisible(false);




    musicPlayer = new QMediaPlayer();
    //musicPlayer->setMedia(QUrl::fromLocalFile("qrc:/backgroundMusic/music.mp3"));

    show();

}

BlackJackTable::~BlackJackTable()
{
    delete ui;
}
void BlackJackTable::assignCard1Image(Card card)
{
    QString filename = "C:/Users/dc_wa/Desktop/PNG-cards-1.3/" + QString::fromStdString(card.getValue()) + "_of_" + QString::fromStdString(card.getSuit()) + ".png";
    ui->card1Label->setPixmap(QPixmap(filename));

}
void BlackJackTable::assignCard2Image(Card card)
{
    QString filename = "C:/Users/dc_wa/Desktop/PNG-cards-1.3/" + QString::fromStdString(card.getValue()) + "_of_" + QString::fromStdString(card.getSuit()) + ".png";
    ui->card2Label->setPixmap(QPixmap(filename));

}
void BlackJackTable::assignCard3Image(Card card)
{
    QString filename = "C:/Users/dc_wa/Desktop/PNG-cards-1.3/" + QString::fromStdString(card.getValue()) + "_of_" + QString::fromStdString(card.getSuit()) + ".png";
    ui->card3Label->setPixmap(QPixmap(filename));

}
void BlackJackTable::assignCard4Image(Card card)
{
    QString filename = "C:/Users/dc_wa/Desktop/PNG-cards-1.3/" + QString::fromStdString(card.getValue()) + "_of_" + QString::fromStdString(card.getSuit()) + ".png";
    ui->card4Label->setPixmap(QPixmap(filename));

}

//Sets the actions for when the user clicks play game
void BlackJackTable::on_PlayGameButton_clicked()
{
    ui->PlayGameButton->deleteLater();
    ui->userButton->setVisible(true);
    ui->statsButton->setVisible(true);

    //Starts the music
    musicPlayer->setMedia(QUrl::fromLocalFile("C:/Users/dc_wa/Desktop/COP3503ProjectGUI/music.mp3"));
    musicPlayer->setVolume(50);
    musicPlayer->play();
    qDebug() << musicPlayer->errorString();
    qDebug() << musicPlayer->isAudioAvailable();
    qDebug() << musicPlayer->state();


}




//sets the actions associated with clicking the user mode button
void BlackJackTable::on_userButton_clicked()
{
    ui->playerLabel->setVisible(true);
    ui->playerCounter->setVisible(true);
    ui->playerConfirmationButton->setVisible(true);
    ui->nameLabel->setVisible(true);
    ui->nameInput->setVisible(true);
    ui->buyInLabel->setVisible(true);
    ui->buyInLineEdit->setVisible(true);
    ui->minBetLabel->setVisible(true);
    ui->minBetLineEdit->setVisible(true);
    ui->deckCountSpinBox->setVisible(true);
    ui->DeckLabel->setVisible(true);
    ui->moneyLabel->setVisible(true);

    ui->statsButton->deleteLater();
    ui->userButton->deleteLater();

std::cout << "Hello" << std::endl;
    game->runPlayingMode();
}
//gets the amount of players the user requests to play with
void BlackJackTable::on_playerCounter_valueChanged(int arg1)
{
   game->setNumPlayers(ui->playerCounter->value());
}

//starts the the game in user mode and displays the essential game ui
void BlackJackTable::on_playerConfirmationButton_clicked()
{
    ui->playerLabel->deleteLater();
    ui->playerCounter->deleteLater();
    ui->nameInput->deleteLater();
    ui->nameLabel->deleteLater();
    ui->buyInLabel->deleteLater();
    ui->buyInLineEdit->deleteLater();
    ui->minBetLabel->deleteLater();
    ui->minBetLineEdit->deleteLater();
    ui->deckCountSpinBox->deleteLater();
    ui->DeckLabel->deleteLater();
    ui->playerConfirmationButton->deleteLater();


    ui->BetLabel->setVisible(true);
    ui->BetLineEdit->setVisible(true);


    //ui->card1Label->setPixmap(card->getPix());
    //ui->card2Label->setPixmap(card->getPix());
}

//sets the actions associated with clicking stats mode
void BlackJackTable::on_statsButton_clicked()
{
    ui->userButton->deleteLater();
    ui->statsButton->deleteLater();
    ui->statsProgress->setVisible(true);
    ui->runningLabel->setVisible(true);
    game->runSimulationMode();
}





//user inputs a name and then gets assigned to the label above their associated slot in the game
void BlackJackTable::on_nameInput_returnPressed()
{
    ui->label_5->setText(ui->nameInput->text());
}

//updates the user score label and...
void BlackJackTable::on_hitButton_clicked()
{
    ui->userHandScoreLabel->setVisible(true);
    userHandScore += 1;
    //Card * card1 = new Card("2", "clubs");
    ui->userHandScoreLabel->setText("Current hand: " + QString::number(userHandScore));

}
//sets the actions associated with hitting the stay button
void BlackJackTable::on_stayButton_clicked()
{

}

void BlackJackTable::on_doubleDownButton_clicked()
{

}

void BlackJackTable::on_NextRoundButton_clicked()
{
    ui->hitButton->setVisible(false);
    ui->stayButton->setVisible(false);
    ui->BetLabel->setVisible(true);
    ui->BetLineEdit->setVisible(true);
    ui->doubleDownButton->setVisible(false);
    ui->NextRoundButton->setVisible(false);
    ui->userHandScoreLabel->setVisible(false);

}

void BlackJackTable::on_BetLineEdit_returnPressed()
{
    ui->hitButton->setVisible(true);
    ui->stayButton->setVisible(true);
    ui->BetLabel->setVisible(false);
    ui->BetLineEdit->setVisible(false);
    ui->doubleDownButton->setVisible(true);
    ui->NextRoundButton->setVisible(true);
    ui->userHandScoreLabel->setVisible(true);
    ui->ExitGameButton->setVisible(true);
    //ui->moneyLabel->setText()
}

void BlackJackTable::on_buyInLineEdit_returnPressed()
{
    ui->moneyLabel->setText("Money: " + ui->buyInLineEdit->text());
    game->setAmountMoney(std::stoi(ui->buyInLineEdit->text().toStdString()));
}


void BlackJackTable::on_deckCountSpinBox_valueChanged(int arg1)
{
    game->setNumDecks(ui->deckCountSpinBox->value());
}

void BlackJackTable::on_minBetLineEdit_returnPressed()
{
    game->setTableBuyIn(std::stoi(ui->minBetLineEdit->text().toStdString()));
}
