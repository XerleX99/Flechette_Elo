#include "../include/newparty.h"
#include "../include/newplayer.h"

NewParty::NewParty(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewParty)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &NewParty::onAjouterJoueur);
    connect(ui->pushButton, &QPushButton::clicked, this, &NewParty::onInscrireJoueur);
}

void NewParty::onAjouterJoueur()
{
    // Récupère la valeur d'un comboBox, ajoute une ligne, etc.
    // ex: QString nom = ui->comboBox->currentText();
}

void NewParty::onInscrireJoueur()
{
    NewPlayer *fenetre = new NewPlayer();
    fenetre->show();
}