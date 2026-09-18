#include "../include/scoreboardparty.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include "../include/newparty.h"
#include "../include/newplayer.h"
#include "../include/elo_utils.h"
#include <QIcon>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>


ScoreBoardParty::ScoreBoardParty(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ScoreBoardFlechettes), eloModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon.png"));
    // Charger les élos au démarrage
    database_elos = load_elos();

    connect(ui->pushButton, &QPushButton::clicked, this, &ScoreBoardParty::onNouvellePartie);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &ScoreBoardParty::onInscrireJoueur);
    load_elos_from_file();
    load_parties_from_file();
}

void ScoreBoardParty::onNouvellePartie()
{
    NewParty *fenetre = new NewParty();
    fenetre->setAttribute(Qt::WA_DeleteOnClose);
    connect(fenetre, &QObject::destroyed, this, [this]() {
        load_elos_from_file();
        load_parties_from_file();
    });
    fenetre->show();
}

void ScoreBoardParty::onInscrireJoueur()
{
    NewPlayer *fenetre = new NewPlayer();
    connect(fenetre, &QObject::destroyed, this, [this]() {
        load_elos_from_file();
        load_parties_from_file();
    });
    fenetre->setAttribute(Qt::WA_DeleteOnClose);
    fenetre->show();
}

void ScoreBoardParty::load_elos_from_file() {
    database_elos = load_elos();
    const auto playerStats = load_player_stats();
    ui->eloTableView->setModel(eloModel);
    eloModel->clear();
    eloModel->setColumnCount(4);
    eloModel->setHorizontalHeaderLabels({
        "Joueur", "ELO", "Parties Jouées", "Gain Moyen (3)"
    });
    eloModel->setHeaderData(1, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
    eloModel->setHeaderData(2, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
    eloModel->setHeaderData(3, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);

    std::vector<std::pair<std::string, int>> ranking(database_elos.begin(), database_elos.end());
    std::sort(ranking.begin(), ranking.end(), [](const auto& left, const auto& right) {
        if (left.second != right.second) {
            return left.second > right.second;
        }
        return left.first < right.first;
    });

    for (std::size_t index = 0; index < ranking.size(); ++index) {
        const auto& [name, elo] = ranking[index];
        const auto statsIt = playerStats.find(name);
        const int gamesPlayed = statsIt == playerStats.end()
            ? 0
            : statsIt->second.games_played;
        const float gainAverage = statsIt == playerStats.end()
            ? 0.0F
            : statsIt->second.GainMoyenne;
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::fromStdString(name)));
        auto *eloItem = new QStandardItem(QString::number(elo));
        auto *gamesItem = new QStandardItem(QString::number(gamesPlayed));
        auto *averageItem = new QStandardItem(QString::number(gainAverage, 'f', 2));
        eloItem->setTextAlignment(Qt::AlignCenter);
        gamesItem->setTextAlignment(Qt::AlignCenter);
        averageItem->setTextAlignment(Qt::AlignCenter);
        row.append(eloItem);
        row.append(gamesItem);
        row.append(averageItem);
        eloModel->appendRow(row);
    }

    ui->eloTableView->setAlternatingRowColors(true);
    ui->eloTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->eloTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->eloTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->eloTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->eloTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->eloTableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->eloTableView->setColumnWidth(1, 70);
    ui->eloTableView->setColumnWidth(2, 100);
    ui->eloTableView->setColumnWidth(3, 110);
    
}

void ScoreBoardParty::load_parties_from_file()
{
    ui->listWidget->clear();
    const auto parties = load_parties();

    for (std::size_t index = 0; index < parties.size(); ++index) {
        const auto& party = parties[index];
        QString partyText = QString("Partie %1")
                                .arg(static_cast<int>(index) + 1);

        for (const auto& player : party) {
            partyText += QString(" | %1. %2")
                             .arg(player.rank)
                             .arg(QString::fromStdString(player.name));
        }

        auto *partyItem = new QListWidgetItem(partyText, ui->listWidget);
        partyItem->setData(Qt::UserRole, static_cast<int>(index));
    }

    ui->listWidget->setAlternatingRowColors(true);
}