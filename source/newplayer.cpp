#include "../include/newplayer.h"
#include "../include/elo_utils.h"

NewPlayer::NewPlayer(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &NewPlayer::onAjouterJoueur);
}

void NewPlayer::onAjouterJoueur()
{
    const std::string nom = ui->lineEdit->text().trimmed().toStdString();
    addNewPlayer(nom);
}
