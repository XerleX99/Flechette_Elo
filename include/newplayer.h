#pragma once
#include <QWidget>
#include "../ui/ui_NewPlayer.h"

class NewPlayer : public QWidget {
    Q_OBJECT
public:
    explicit NewPlayer(QWidget *parent = nullptr);

private slots:
    void onAjouterJoueur();

private:
    Ui::Form *ui;
};