#ifndef ONEPLAYERWINDOW_H
#define ONEPLAYERWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <string>
#include "Mainwnd.h"

using namespace std;

/*Cette class correspond à la fenêtre de configuration du jeu, ça veut dire qu'il faut tapper le nom,
choisir la vitesse, le nombre de fantome, le mode à jouer(il y a 7 mode à choisir qui correcpends aux 7 terrains différences) */

class Mainwnd::joueurWindow : public QFrame{

  public:
    joueurWindow(QWidget* pparent=0, Qt::WindowFlags flags=0);

    void configurer(); //configuration des widgets

    int getVitesse()
    {
        return (labelVT->text()).toInt();
    }

    int getNombreFantomes()
    {
        return (labelNF->text()).toInt();
    }

    string getName1()
    {
        if ((name1.text()).toStdString()=="")
            return (name1.placeholderText()).toStdString();
        else
            return (name1.text()).toStdString();
    }

    string getName2()
    {
        if ((name2.text()).toStdString()=="")
            return (name2.placeholderText()).toStdString();
        else
            return (name2.text()).toStdString();
    }

    void setNombre(int a){
        nombreJoueur = a;
    }

    int getNombre(){
        return nombreJoueur;
    }


    int getNumMode(){
        return (labelMO->text()).toInt();
    }

    public:
    QLineEdit name1;
    QLineEdit name2;
    QLabel *labelNF;
    QLabel *labelVT;
    QLabel *labelMO;
    int numeroMode;
    int nombreJoueur;
    QPushButton *btnCommence;
    QPushButton *btnRetourne;

};


#endif
