#ifndef BIENVENUEWINDOW_H
#define BIENVENUEWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "Mainwnd.h"

/*Cette class correspond à la fenêtre de bienvenue, il y a des butons à choisir comme: Un joueur, Deux joueur
meilleur mark et quiter le jeu*/

class Mainwnd::bienvenuewindow: public QFrame
{
public:
    bienvenuewindow(QWidget* pparent=0, Qt::WindowFlags flags=0);

public:
    QVBoxLayout *vbox;

    QPushButton *btnUnJoueur;
    QPushButton *btnDeuxJoueur;
    QPushButton *btnMarque;
    QPushButton *btnSortie;
};


#endif
