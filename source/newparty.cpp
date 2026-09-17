#include "../include/newparty.h"
#include "../include/newplayer.h"
#include <QComboBox>
#include <QLineEdit>
#include <iostream>

NewParty::NewParty(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewParty)
{
    ui->setupUi(this);
    setMinimumSize(650, 260);
    resize(650, 260);

    load_players(ui); // Charge les joueurs dans les comboBox au démarrage

    connect(ui->pushButton_2, &QPushButton::clicked, this, &NewParty::onAjouterJoueur);
    connect(ui->pushButton, &QPushButton::clicked, this, &NewParty::onInscrireJoueur);
}

void NewParty::onAjouterJoueur()
{
    QGridLayout *layout = ui->gridLayout_2;
    const auto elos = load_elos();

    auto *comboBox = new QComboBox(this);
    auto *scoreEdit = new QLineEdit(this);
    comboBox->setMinimumWidth(200);
    scoreEdit->setMinimumWidth(200);
    scoreEdit->setPlaceholderText("Score");

    for (const auto& [name, elo] : elos) {
        comboBox->addItem(QString::fromStdString(name));
    }

    layout->removeWidget(ui->pushButton_2);
    layout->removeWidget(ui->pushButton);
    layout->removeWidget(ui->pushButton_3);
    layout->removeWidget(ui->pushButton_4);

    layout->addWidget(comboBox, playerRow, 0);
    layout->addWidget(scoreEdit, playerRow, 1);
    ++playerRow;

    layout->addWidget(ui->pushButton_2, playerRow, 0);
    layout->addWidget(ui->pushButton, playerRow, 1);
    layout->addWidget(ui->pushButton_3, playerRow + 1, 0);
    layout->addWidget(ui->pushButton_4, playerRow + 1, 1);


}

void NewParty::onInscrireJoueur()
{
    NewPlayer *fenetre = new NewPlayer();
    fenetre->show();
}

void NewParty::load_players(Ui::NewParty *ui){
    const auto elos = load_elos();
    for (const auto& [name, elo] : elos) {
        const QString playerName = QString::fromStdString(name);
        ui->comboBox->addItem(playerName);
        ui->comboBox_2->addItem(playerName);
        ui->comboBox_3->addItem(playerName);
    }
}


// int calcule_de_l_elo() {
//     // Base de données des joueurs et leurs Élos actuels
//     std::map<std::string, int> database_elos = load_elos();

//     std::cout << "--- Élos avant la partie (5 joueurs) ---" << std::endl;
//     for (const auto& player : game_results) {
//         std::cout << player.name << " : " << database_elos[player.name] << std::endl;
//     }

//     // Calcul de la mise à jour (K_base fixé à 32)
//     std::map<std::string, int> updated_elos = update_multiplayer_elo(database_elos, game_results, 32.0);

//     std::cout << "\n--- Nouveaux Élos après calcul (K adaptatif + Bonus Vainqueur) ---" << std::endl;
//     for (const auto& player : game_results) {
//         int ancien = database_elos[player.name];
//         int nouveau = updated_elos[player.name];
//         int variation = nouveau - ancien;

//         std::cout << player.name << " (Rang " << player.rank << ") : " 
//                   << nouveau << " (" << (variation >= 0 ? "+" : "") << variation << ")" << std::endl;
//     }

//     save_elos(updated_elos); // Sauvegarde des nouveaux Élos dans un fichier CSV

//     return 0;
// }
