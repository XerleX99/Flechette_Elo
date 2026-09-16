#include "../include/newplayer.h"

NewPlayer::NewPlayer(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &NewPlayer::onAjouterJoueur);
}

void NewPlayer::onAjouterJoueur()
{
    QString nom = ui->lineEdit->text();
    // ajoute "nom" à ta base de joueurs (ta map C++, puis save_elos())
}