#ifndef RESULT_H
#define RESULT_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "Mainwnd.h"

/*Cette class correspond � la fenetre de r�sultat, il y a le r�sultat(gagn� ou perdu) qui est affich� ici,
il y a aussi deux butons � choisir: Rejouer ou quitter le jeu*/

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
