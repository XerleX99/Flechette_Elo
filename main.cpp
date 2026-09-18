#include <QApplication>
#include <QMessageBox>
#include <exception>
#include "include/scoreboardparty.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    try {
        ScoreBoardParty fenetre;
        fenetre.show();
        return app.exec();
    } catch (const std::exception& error) {
        QMessageBox::critical(nullptr, "Erreur", QString::fromLocal8Bit(error.what()));
    } catch (...) {
        QMessageBox::critical(nullptr, "Erreur", "Une erreur inconnue est survenue.");
    }

    return 1;
}