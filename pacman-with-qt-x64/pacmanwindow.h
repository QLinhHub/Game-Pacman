#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"
#include "Mainwnd.h"

/*Cette class correspond à la fenetre de jeu, il y a un ou deux pacman à ridiger, des fantomes et les autres objets de comestiques*/

class Mainwnd::PacmanWindow : public QFrame
{

  public:
    Jeu jeu;

    QPixmap pixmapPacmanDefaut, pixmapPacman1, pixmapPacman2, pixmapPacman3, pixmapPacman4;
    QPixmap pixmapMur1, pixmapMur2, pixmapMur3, pixmapGrass;
    QPixmap pixmapGod, pixmapFantome1, pixmapFantome2, pixmapFantome3;
  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);

    void loadImage(); //charger des images
    void setupLabel(); // initialisation des labels pour 1 ou 2 joueur

  public:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void handleTimer();
    void handleCountdown(); //manipulation pour compter à rebours

    void configurer(string, string, int ,int ,int, int); // configuration des choses nécessaires dans le jeu
    void startJeu(); //lancer le jeu
    void pauseJeu(); //faire un pause
    void stopJeu(); //stopper le jeu, lorsde perdu
    void gagneJeu(int ); // modifier le message du résultat lorsde gagné
    void checkCollision(Pacman &); // vérifier si il y a une collision entre pacman et fantomes
    void handleCollision(); // manipulation de la collision

  public:
    QLabel* label_countdown;
    QLabel* label_marqueA;
    QLabel* label_marqueB;
    QTime countdown;
    QTimer *vitesseJeu;
    QTimer *countTime;

  public:
    //int timeId;
    bool gameFini;
    bool paused;
    bool gameGagne;
    string resultat;
    int countGod;
};
#endif
