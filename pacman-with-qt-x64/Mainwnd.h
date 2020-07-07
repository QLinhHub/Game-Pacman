#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <string>
#include <fstream>
using namespace std;

/*La principal fenêtre qui héritie QMainWindow, des widgets vont apparitre ici avec QMenubar et QStatusbar */

class Mainwnd : public QMainWindow {

private:
    //quatre classes imbriquées de la classe Mainwnd
    class bienvenuewindow; // contient des widgets nécessaires pour la fenetre de bienvenue
    class joueurWindow; // contient des widgets nécessaires pour la fenetre de configuration le jeu
    class PacmanWindow; // contient des widgets de la fenetre du jeu
    class resultWindow; // contient des widgets de la fenetre de résultat

    string result[2][5] = {}; //tableau contient le resultat du jeu

public:
    Mainwnd(QWidget *parent = 0);
    ~Mainwnd(){};

public:
    bienvenuewindow * bienvenueWnd;
    joueurWindow *caractWnd;
    PacmanWindow *pacmanWnd;
    resultWindow *resultWnd;


public:
//Initlisation les QFrames
    void init_bienvenueWnd(); // initialisation la fenêtre de bienvenue
    void init_caractWnd(int ); // initalisation la fenêtre de configuration de jeu
    void init_pacmanWnd(string, string, int, int, int, int); // initialisation la fenêtre de jeu
    void init_resultWnd(string); // initialisaion la fenêtre de résultat

//Les slots pour bienvenueWnd
    void handleUnJoueur(); // manipulation pour un joueur
    void handleDeuxJoueur(); // manipulation pour deux joueur
//Les slots pour caractWnd

    void handleCommence(); // manipulation pour commencer le jeu et afficher l'écran à jouer
    void handleNouveauJeu(); // manipulation pour rẹjouer et afficher l'écran à choisir la facon de jouer
    void handleResultat(); // manipulation pour afficher l'écran du résultat
    void handleMeuilleurNote(); // manipulation pour afficher le meilleur joueur

//Les actions pour le résultat
    void compareResultat(PacmanWindow &); // vérifier si le résultat est le meilleur
    void readfile(); // lire le fichier .txt qui contient les meilleurs marks et le sauvegarder en tableau resultat
    void writefile(); // écrire le meilleurs marks à un fichier .txt

////Redéfinition méthode QMainWindow
    void keyPressEvent(QKeyEvent *); // permettant à PacmanWindow  de prendre les événements de MainWnd
    void timerEvent(QTimerEvent *); // si le jeu a fini, il permet de faire des actions pour le résultat

private:
    int timerId; //permettant de synchroniser timer de Mainwnd et de Pacmanwindow
    bool inGame; // pour savoir que vous êtes en jeu ou pas
};




#endif // MAINWINDOW_H_INCLUDED
