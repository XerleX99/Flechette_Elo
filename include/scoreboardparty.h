#pragma once
#include <QMainWindow>
#include <map>
#include <string>
#include "ui_ScoreBoardParty.h"

class ScoreBoardParty : public QMainWindow {
    Q_OBJECT
public:
    explicit ScoreBoardParty(QWidget *parent = nullptr);

private slots:
    void onNouvellePartie();
    void onInscrireJoueur();

private:
    Ui::ScoreBoardFlechettes *ui;
    std::map<std::string, int> database_elos;  // Stocke les élos chargés
};