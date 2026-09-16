#pragma once
#include <QMainWindow>
#include "../ui/ui_ScoreBoardParty.h"

class ScoreBoardParty : public QMainWindow {
    Q_OBJECT
public:
    explicit ScoreBoardParty(QWidget *parent = nullptr);

private slots:
    void onNouvellePartie();
    void onInscrireJoueur();

private:
    Ui::ScoreBoardFlechettes *ui;
};