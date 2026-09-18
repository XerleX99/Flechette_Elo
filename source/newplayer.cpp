#include "../include/newplayer.h"
#include "../include/elo_utils.h"
#include <QMessageBox>

NewPlayer::NewPlayer(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->pushButton, &QPushButton::clicked, this, &NewPlayer::onAjouterJoueur);
}

void NewPlayer::onAjouterJoueur()
{
    const std::string nom = ui->lineEdit->text().trimmed().toStdString();
    if (nom.empty()) {
        QMessageBox::warning(this, "Nom invalide", "Le nom du joueur ne peut pas être vide.");
        return;
    }
    const auto elos = load_elos();
    if (elos.find(nom) != elos.end()) {
        QMessageBox::warning(this, "Nom invalide", "Ce joueur existe déjà.");
        return;
    }
    addNewPlayer(nom);
    close();
}
