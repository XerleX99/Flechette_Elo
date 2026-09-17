#include <QApplication>
#include "include/scoreboardparty.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ScoreBoardParty fenetre;
    fenetre.show();
    return app.exec();
}