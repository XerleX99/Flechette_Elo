#pragma once
#include <QMainWindow>
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

private:
    Ui::NewParty *ui;
};