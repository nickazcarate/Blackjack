#include "blackjacktable.h"
#include "ui_blackjacktable.h"
#include <string>
#include <QMediaPlayer>
#include <QDebug>
#include "card.h"
#include "game.h"
#include "deckstack.h"
#include "player.h"
#include <array>




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
		ui->scoreLabel->setText("My score is: ");
		ui->playerCounter->setVisible(false);
		ui->playerLabel->setVisible(false);
		ui->statsButton->setVisible(false);
		ui->userButton->setVisible(false);
		ui->scoreLabel->setVisible(false);
		ui->playerConfirmationButton->setVisible(false);
		//ui->statsProgress->setVisible(false);
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
		ui->instructionsTextBrowser->setVisible(false);
		ui->winsLabel1->setVisible(false);
		ui->winPercentageLabel1->setVisible(false);
		ui->lossesLabel1->setVisible(false);
		ui->tiesLabel1->setVisible(false);
		ui->totalMoneyLabel1->setVisible(false);
		ui->winsLabel2->setVisible(false);
		ui->winPercentageLabel2->setVisible(false);
		ui->lossesLabel2->setVisible(false);
		ui->tiesLabel2->setVisible(false);
		ui->totalMoneyLabel2->setVisible(false);
		ui->winsLabel3->setVisible(false);
		ui->winPercentageLabel3->setVisible(false);
		ui->lossesLabel3->setVisible(false);
		ui->tiesLabel3->setVisible(false);
		ui->totalMoneyLabel3->setVisible(false);
		ui->winsLabel4->setVisible(false);
		ui->winPercentageLabel4->setVisible(false);
		ui->lossesLabel4->setVisible(false);
		ui->tiesLabel4->setVisible(false);
		ui->totalMoneyLabel4->setVisible(false);
		ui->winsLabel5->setVisible(false);
		ui->winPercentageLabel5->setVisible(false);
		ui->lossesLabel5->setVisible(false);
		ui->tiesLabel5->setVisible(false);
		ui->totalMoneyLabel5->setVisible(false);
		ui->ExitInstrButton->setVisible(false);
		




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

		//Starts the music
		musicPlayer->setMedia(QUrl::fromLocalFile("C:/Users/dc_wa/Desktop/COP3503ProjectGUI/music.mp3"));
		musicPlayer->setVolume(50);
		musicPlayer->play();
		qDebug() << musicPlayer->errorString();
		qDebug() << musicPlayer->isAudioAvailable();
		qDebug() << musicPlayer->state();

		ui->playerLabel->setVisible(true);
		ui->nameLabel->setVisible(true);
		ui->nameInput->setVisible(true);
		ui->playerCounter->setVisible(true);
		ui->playerConfirmationButton->setVisible(true);
		ui->buyInLabel->setVisible(true);
		ui->buyInLineEdit->setVisible(true);
		ui->minBetLabel->setVisible(true);
		ui->minBetLineEdit->setVisible(true);
		ui->deckCountSpinBox->setVisible(true);
		ui->DeckLabel->setVisible(true);
		ui->moneyLabel->setVisible(true);


	}




	//sets the actions associated with clicking the user mode button
	void BlackJackTable::on_userButton_clicked()
	{
		
		game->startGame();
		
		

		ui->statsButton->deleteLater();
		ui->userButton->deleteLater();
		


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
		
		
		ui->userButton->setVisible(true);
		ui->statsButton->setVisible(true);


		//ui->BetLabel->setVisible(true);
		//ui->BetLineEdit->setVisible(true);
		//game->runPlayingMode();
		
		//ui->card1Label->setPixmap(card->getPix());
		//ui->card2Label->setPixmap(card->getPix());
	}

	//sets the actions associated with clicking stats mode
	void BlackJackTable::on_statsButton_clicked()
	{
		//creates control array for total money label
		QLabel * labelArray[5];
		labelArray[0] = ui->totalMoneyLabel1;
		labelArray[1] = ui->totalMoneyLabel2;
		labelArray[2] = ui->totalMoneyLabel3;
		labelArray[3] = ui->totalMoneyLabel4;
		labelArray[4] = ui->totalMoneyLabel5;

		//creates control array for win label
		QLabel * winLabelArray[5];
		winLabelArray[0] = ui->winsLabel1;
		winLabelArray[1] = ui->winsLabel2;
		winLabelArray[2] = ui->winsLabel3;
		winLabelArray[3] = ui->winsLabel4;
		winLabelArray[4] = ui->winsLabel5;

		//creates control array for loss label array
		QLabel * lossLabelArray[5];
		lossLabelArray[0] = ui->lossesLabel1;
		lossLabelArray[1] = ui->lossesLabel2;
		lossLabelArray[2] = ui->lossesLabel3;
		lossLabelArray[3] = ui->lossesLabel4;
		lossLabelArray[4] = ui->lossesLabel5;

		//creates control array for tie label array
		QLabel * tieLabelArray[5];
		tieLabelArray[0] = ui->tiesLabel1;
		tieLabelArray[1] = ui->tiesLabel2;
		tieLabelArray[2] = ui->tiesLabel3;
		tieLabelArray[3] = ui->tiesLabel4;
		tieLabelArray[4] = ui->tiesLabel5;

		//creates control array for win percentage label array
		QLabel * winPercentLabelArray[5];
		winPercentLabelArray[0] = ui->winPercentageLabel1;
		winPercentLabelArray[1] = ui->winPercentageLabel2;
		winPercentLabelArray[2] = ui->winPercentageLabel3;
		winPercentLabelArray[3] = ui->winPercentageLabel4;
		winPercentLabelArray[4] = ui->winPercentageLabel5;


		//names of bots
		//vector<string> names = { "You", "RandomBot", "SuperCounterBot", "ModerateCounterBot", "BasicStrategyBot1", "BasicStrategyBot2" };

		ui->userButton->deleteLater();
		ui->statsButton->deleteLater();
		//ui->statsProgress->setVisible(true);
		ui->runningLabel->setVisible(true);
		game->runSimulationMode();
		ui->winsLabel1->setVisible(true);
		ui->winPercentageLabel1->setVisible(true);
		ui->lossesLabel1->setVisible(true);
		ui->tiesLabel1->setVisible(true);
		ui->totalMoneyLabel1->setVisible(true);
		ui->winsLabel2->setVisible(true);
		ui->winPercentageLabel2->setVisible(true);
		ui->lossesLabel2->setVisible(true);
		ui->tiesLabel2->setVisible(true);
		ui->totalMoneyLabel2->setVisible(true);
		ui->winsLabel3->setVisible(true);
		ui->winPercentageLabel3->setVisible(true);
		ui->lossesLabel3->setVisible(true);
		ui->tiesLabel3->setVisible(true);
		ui->totalMoneyLabel3->setVisible(true);
		ui->winsLabel4->setVisible(true);
		ui->winPercentageLabel4->setVisible(true);
		ui->lossesLabel4->setVisible(true);
		ui->tiesLabel4->setVisible(true);
		ui->totalMoneyLabel4->setVisible(true);
		ui->winsLabel5->setVisible(true);
		ui->winPercentageLabel5->setVisible(true);
		ui->lossesLabel5->setVisible(true);
		ui->tiesLabel5->setVisible(true);
		ui->totalMoneyLabel5->setVisible(true);
		for (int i = 1; i < game->getNumPlayers(); i++) {
			Player * p = game->findPlayer(i);
			int j = i;
			switch (j) 
			{
			case 1:
				ui->label->setText(QString::fromStdString(p->getPlayerName()));
				break;
			case 2:
				ui->label_2->setText(QString::fromStdString(p->getPlayerName()));
				break;
			case 3:
				ui->label_3->setText(QString::fromStdString(p->getPlayerName()));
				break;
			case 4:
				ui->label_4->setText(QString::fromStdString(p->getPlayerName()));
				break;
			case 5:
				ui->label_6->setText(QString::fromStdString(p->getPlayerName()));
				break;
			
			}
			labelArray[i-1]->setText("Total Money: " + QString::number(p->getMoney()));
			winLabelArray[i-1]->setText("Wins: " + QString::number(p->getWins()));
			lossLabelArray[i-1]->setText("Losses: " + QString::number(p->getLosses()));
			tieLabelArray[i-1]->setText("Ties: " + QString::number(p->getTies()));
			if (p->getLosses() != 0 || p->getWins() != 0) {// prevents divide by zero error
				winPercentLabelArray[i-1]->setText("Win Percentage: " + QString::number(p->getWins() * 100 / (p->getLosses() + p->getWins()))+ "%");
			}
		}
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
		//game.doubleDown();
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


	void BlackJackTable::on_seeRulesButton_clicked()
	{
		ui->instructionsTextBrowser->setVisible(true);
		ui->ExitInstrButton->setVisible(true);
	}

	void BlackJackTable::on_ExitInstrButton_clicked()
	{
		ui->instructionsTextBrowser->setVisible(false);
		ui->ExitInstrButton->setVisible(false);
	}
	