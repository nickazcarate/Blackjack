#ifndef BLACKJACKTABLE_H
#define BLACKJACKTABLE_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "card.h"

namespace Ui {
class BlackJackTable;
}

#include <string>

class BlackJackTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit BlackJackTable(QWidget *parent = 0);
    ~BlackJackTable();
    void assignCard1Image(Card card);
    void assignCard2Image(Card card);
    void assignCard3Image(Card card);
    void assignCard4Image(Card card);
	


private slots:
    void on_PlayGameButton_clicked();

    void on_playerCounter_valueChanged(int arg1);

    void on_userButton_clicked();

    void on_playerConfirmationButton_clicked();

    void on_statsButton_clicked();

    void on_nameInput_returnPressed();

    void on_hitButton_clicked();

    void on_stayButton_clicked();

    void on_doubleDownButton_clicked();

    void on_NextRoundButton_clicked();

    void on_BetLineEdit_returnPressed();

    void on_buyInLineEdit_returnPressed();

    void on_deckCountSpinBox_valueChanged(int arg1);

    void on_minBetLineEdit_returnPressed();

    void on_seeRulesButton_clicked();

	void on_ExitInstrButton_clicked();

private:
    Ui::BlackJackTable *ui;
    QMediaPlayer * musicPlayer;
    int userHandScore = 0;
    std::string userScore;
};

#endif // BLACKJACKTABLE_H
