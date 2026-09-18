#pragma once
#include <QMainWindow>
#include <QStandardItemModel>
#include <map>
#include <string>
#include "../ui/ui_ScoreBoardParty.h"

class ScoreBoardParty : public QMainWindow {
    Q_OBJECT
public:
    explicit ScoreBoardParty(QWidget *parent = nullptr);

private slots:
    void onNouvellePartie();
    void onInscrireJoueur();
    void load_elos_from_file();
    void load_parties_from_file();

private:
    Ui::ScoreBoardFlechettes *ui;
    std::map<std::string, int> database_elos;  // Stocke les élos chargés
    QStandardItemModel *eloModel;
};