#ifndef RESULT_H
#define RESULT_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "Mainwnd.h"

/*Cette class correspond à la fenetre de résultat, il y a le résultat(gagné ou perdu) qui est affiché ici,
il y a aussi deux butons à choisir: Rejouer ou quitter le jeu*/

class Mainwnd::resultWindow : public QFrame
{
public:
    QLabel *resultat;
    QPushButton *btnRejouer;
    QPushButton *btnSortir;
public:
    resultWindow(QWidget* pparent=0, Qt::WindowFlags flags=0);
    void setResultat(string );
};

#endif
