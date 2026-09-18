#include "../include/newparty.h"
#include "../include/newplayer.h"
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QStyle>
#include <QVBoxLayout>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <QMessageBox>

NewParty::NewParty(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewParty)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);

    auto *centralLayout = new QVBoxLayout(ui->centralwidget);
    centralLayout->setContentsMargins(10, 10, 10, 10);
    centralLayout->setSizeConstraint(QLayout::SetFixedSize);
    centralLayout->addWidget(ui->gridLayoutWidget_2);
    load_players(ui); // Charge les joueurs dans les comboBox au démarrage

    connect(ui->AjoutJoueur, &QPushButton::clicked, this, &NewParty::onAjouterJoueur);
    connect(ui->AddNewPlayer, &QPushButton::clicked, this, &NewParty::onInscrireJoueur);
    connect(ui->ValidateParty, &QPushButton::clicked, this, &NewParty::onValiderPartie);
    connect(ui->Cancel, &QPushButton::clicked, this, &NewParty::Close);

    
    ui->lineEdit->setPlaceholderText("Score");
    ui->lineEdit_2->setPlaceholderText("Score");
    ui->lineEdit_3->setPlaceholderText("Score");

    playerComboBoxes = {ui->comboBox, ui->comboBox_2, ui->comboBox_3};
    playerPositions = {ui->lineEdit, ui->lineEdit_2, ui->lineEdit_3};
}

void NewParty::onAjouterJoueur()
{
    QGridLayout *layout = ui->gridLayout_2;
    const auto elos = load_elos();

    auto *comboBox = new QComboBox(this);
    auto *scoreEdit = new QLineEdit(this);
    auto *deleteButton = new QPushButton(this);
    comboBox->addItem("Sélectionner un joueur");
    comboBox->setMinimumWidth(200);
    scoreEdit->setMinimumWidth(200);
    scoreEdit->setPlaceholderText("Score");
    deleteButton->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    deleteButton->setToolTip("Supprimer ce joueur");

    for (const auto& [name, elo] : elos) {
        comboBox->addItem(QString::fromStdString(name));
    }

    layout->removeWidget(ui->AjoutJoueur);
    layout->removeWidget(ui->AddNewPlayer);
    layout->removeWidget(ui->ValidateParty);
    layout->removeWidget(ui->Cancel);

    layout->addWidget(comboBox, playerRow, 0);
    layout->addWidget(scoreEdit, playerRow, 1);
    layout->addWidget(deleteButton, playerRow, 2);
    ++playerRow;

    layout->addWidget(ui->AjoutJoueur, playerRow, 0);
    layout->addWidget(ui->AddNewPlayer, playerRow, 1);
    layout->addWidget(ui->ValidateParty, playerRow + 1, 0);
    layout->addWidget(ui->Cancel, playerRow + 1, 1);

    layout->activate();
    ui->centralwidget->layout()->activate();
    adjustSize();

    playerComboBoxes.push_back(comboBox);
    playerPositions.push_back(scoreEdit);

    connect(deleteButton, &QPushButton::clicked, this, [this, comboBox, scoreEdit, deleteButton]() {
        const auto comboIt = std::find(playerComboBoxes.begin(), playerComboBoxes.end(), comboBox);
        if (comboIt != playerComboBoxes.end()) {
            playerComboBoxes.erase(comboIt);
        }

        const auto positionIt = std::find(playerPositions.begin(), playerPositions.end(), scoreEdit);
        if (positionIt != playerPositions.end()) {
            playerPositions.erase(positionIt);
        }

        ui->gridLayout_2->removeWidget(comboBox);
        ui->gridLayout_2->removeWidget(scoreEdit);
        ui->gridLayout_2->removeWidget(deleteButton);
        comboBox->deleteLater();
        scoreEdit->deleteLater();
        deleteButton->deleteLater();
        ui->gridLayout_2->activate();
        ui->centralwidget->layout()->activate();
        adjustSize();
    });
}

void NewParty::onInscrireJoueur()
{
    NewPlayer *fenetre = new NewPlayer();
    fenetre->show();
}

void NewParty::onValiderPartie()
{
    std::vector<PlayerResult> results;
    std::set<std::string> names;

    for (std::size_t index = 0; index < playerComboBoxes.size(); ++index) {
        if (playerComboBoxes[index]->currentText().isEmpty()) {
            continue; // Ignore les joueurs non sélectionnés
        }
        const std::string name = playerComboBoxes[index]->currentText().trimmed().toStdString();
        bool positionOk = false;
        const int position = playerPositions[index]->text().toInt(&positionOk);

        if (name.empty() || !positionOk || position < 1 ) {
            QMessageBox::warning(this, "Partie invalide",
                                 "Chaque joueur doit avoir une position numerique positive.");
            return;
        }

        if (name == "Sélectionner un joueur") {
            QMessageBox::warning(this, "Partie invalide",
                                 "Veuillez sélectionner un joueur valide.");
            return;
        }

        if (!names.insert(name).second) {
            QMessageBox::warning(this, "Partie invalide",
                                 "Un joueur ne peut pas participer deux fois a la meme partie.");
            return;
        }

        results.push_back({name, position, 0, 0.0F});
    }

    if (results.size() < 2) {
        QMessageBox::warning(this, "Partie invalide",
                             "Une partie doit contenir au moins deux joueurs.");
        return;
    }

    auto elos = load_elos();
    auto playerStats = load_player_stats();
    for (const auto& result : results) {
        if (elos.find(result.name) == elos.end()) {
            QMessageBox::warning(this, "Partie invalide",
                                 "Un joueur selectionne est absent de elos.csv.");
            return;
        }
    }

    auto updatedElos = update_multiplayer_elo(elos, results);
    const auto previousParties = load_parties();
    std::map<std::string, float> currentGains;

    for (auto& result : results) {
        const int nextGamesPlayed = playerStats[result.name].games_played + 1;
        if (nextGamesPlayed % 5 == 0) {
            updatedElos[result.name] += 5;
        }

        std::vector<float> recentGains;
        for (const auto& party : previousParties) {
            for (const auto& previousResult : party) {
                if (previousResult.name == result.name) {
                    recentGains.push_back(previousResult.GainMoyenne);
                }
            }
        }

        const auto currentElo = elos.at(result.name);
        const std::size_t firstGain = recentGains.size() > 3 ? recentGains.size() - 3 : 0;
        float gainTotal = 0.0F;
        for (std::size_t gainIndex = firstGain; gainIndex < recentGains.size(); ++gainIndex) {
            gainTotal += recentGains[gainIndex];
        }

        const float previousAverage = recentGains.empty()
            ? 0.0F
            : gainTotal / static_cast<float>(recentGains.size() - firstGain);
        float currentGain = static_cast<float>(updatedElos.at(result.name) - currentElo);
        if (previousAverage > 0.0F) {
            currentGain += previousAverage / 5.0F;
            updatedElos[result.name] = static_cast<int>(std::round(currentElo + currentGain));
            currentGain = static_cast<float>(updatedElos.at(result.name) - currentElo);
        }

        currentGains[result.name] = currentGain;
        recentGains.push_back(currentGain);
        const std::size_t updatedFirstGain = recentGains.size() > 3 ? recentGains.size() - 3 : 0;
        gainTotal = 0.0F;
        for (std::size_t gainIndex = updatedFirstGain; gainIndex < recentGains.size(); ++gainIndex) {
            gainTotal += recentGains[gainIndex];
        }

        result.games_played = nextGamesPlayed;
        result.GainMoyenne = gainTotal / static_cast<float>(recentGains.size() - updatedFirstGain);
        playerStats[result.name] = result;
    }

    std::ofstream partyFile("../Parties.csv", std::ios::app);
    if (!partyFile) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir Parties.csv.");
        return;
    }

    for (const auto& result : results) {
        const auto gain = currentGains.at(result.name);
        partyFile << result.name << "," << result.rank << "," << gain << "\n";
    }
    partyFile << "\n";
    partyFile.close();

    save_player_stats(playerStats, updatedElos);
    close();
}

void NewParty::load_players(Ui::NewParty *ui){
    const auto elos = load_elos();
    ui->comboBox->addItem("Sélectionner un joueur");
    ui->comboBox_2->addItem("Sélectionner un joueur");
    ui->comboBox_3->addItem("Sélectionner un joueur");
    for (const auto& [name, elo] : elos) {
        const QString playerName = QString::fromStdString(name);
        ui->comboBox->addItem(playerName);
        ui->comboBox_2->addItem(playerName);
        ui->comboBox_3->addItem(playerName);
    }
}

void NewParty::Close() {
    close();
}

