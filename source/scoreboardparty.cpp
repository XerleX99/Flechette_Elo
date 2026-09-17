#include "../include/scoreboardparty.h"
#include "../include/newparty.h"
#include "../include/newplayer.h"
#include "../include/elo_utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>


ScoreBoardParty::ScoreBoardParty(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ScoreBoardFlechettes)
{
    ui->setupUi(this);

    // Charger les élos au démarrage
    database_elos = load_elos();

    connect(ui->pushButton, &QPushButton::clicked, this, &ScoreBoardParty::onNouvellePartie);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &ScoreBoardParty::onInscrireJoueur);
}

void ScoreBoardParty::onNouvellePartie()
{
    NewParty *fenetre = new NewParty();
    fenetre->show();
}

void ScoreBoardParty::onInscrireJoueur()
{
    NewPlayer *fenetre = new NewPlayer();
    fenetre->show();
}
