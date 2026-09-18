#pragma once
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <vector>
#include "../ui/ui_NewParty.h"
#include "elo_utils.h"


class NewParty : public QMainWindow {
    Q_OBJECT
public:
    explicit NewParty(QWidget *parent = nullptr);
    void load_players(Ui::NewParty *ui);

private slots:
    void onAjouterJoueur();
    void onInscrireJoueur();
    void onValiderPartie();
    void Close();

private:
    Ui::NewParty *ui;
    int playerRow = 3;
    std::vector<QComboBox*> playerComboBoxes;
    std::vector<QLineEdit*> playerPositions;
};