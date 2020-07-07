#include <iostream>
#include "Mainwnd.h"
#include "bienvenuewindow.h"
#include "pacmanwindow.h"
#include "joueurwindow.h"
#include "result.h"

using namespace std;

Mainwnd::Mainwnd(QWidget* pparent) : QMainWindow(pparent){
    //initilisation les variables privées
    timerId = 0;
    inGame = false;
    init_bienvenueWnd();
    setCentralWidget(bienvenueWnd); //laisse la fénêtre de bienvenue apparaitre lorsde lancer le jeu

    //mettre le nom et l'icon pour la fenetre
    setWindowTitle(tr("PACMAN: REVENGE"));
    QIcon mainIcon("./data/icon.png");
    setWindowIcon(mainIcon);

    //des icons pour des options dans la pricipale fenetre
    QPixmap newpix("./data/newGame.png");
    QPixmap openpix("./data/result.png");
    QPixmap quitpix("./data/quit.png");

    //des options à choisir dans la principale fenetre
    QAction *nouveauJeu = new QAction(newpix, "&Nouveau Jeu", this);
    QAction *resultt = new QAction(openpix, "&Meilleur Resultat", this);
    QAction *fermer = new QAction(quitpix, "&Fermer", this);
    fermer->setShortcut(tr("CTRL+Q"));

    //ajouter des options dans un menu
    QMenu *file;
    file = menuBar()->addMenu("&Option");
    file->addAction(nouveauJeu);
    file->addAction(resultt);
    file->addSeparator();
    file->addAction(fermer);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    //conecter des slots correspondent aux certains options
    connect(nouveauJeu, &QAction::triggered, this, handleNouveauJeu);
    connect(resultt, &QAction::triggered, this, handleMeuilleurNote);
    connect(fermer, &QAction::triggered, this, close);

    resize(850, 525);
}

void Mainwnd::keyPressEvent(QKeyEvent *e){
    if (inGame)
        pacmanWnd->keyPressEvent(e);
}

void Mainwnd::init_bienvenueWnd(){

    bienvenueWnd = new bienvenuewindow();

    //les signaux et les slots pour bienvenueWnd
    connect(bienvenueWnd->btnUnJoueur,QPushButton::clicked, this, handleUnJoueur);
    connect(bienvenueWnd->btnDeuxJoueur,QPushButton::clicked, this, handleDeuxJoueur);
    connect(bienvenueWnd->btnMarque,QPushButton::clicked, this, handleMeuilleurNote);
    connect(bienvenueWnd->btnSortie,QPushButton::clicked, this, close);

    //afficher le status du jeu
    statusBar()->showMessage(tr("Realise par Quang Quoc Bao LE et Quang Linh LE"));

}

void Mainwnd::init_caractWnd(int nombreJoueur){

    caractWnd = new joueurWindow();
    caractWnd->setNombre(nombreJoueur);
    caractWnd->configurer();

    //les signaux et les slots pour caractWnd
    connect(caractWnd->btnCommence,QPushButton::clicked, this, handleCommence);
    connect(caractWnd->btnRetourne,QPushButton::clicked, this, handleNouveauJeu);

    //afficher le status du jeu
    statusBar()->showMessage(tr("Regler les parametre comme vous voulez !"));

}

void Mainwnd::init_pacmanWnd(string name1, string name2, int nJoueur, int nFantome, int vit, int mode){
    pacmanWnd = new PacmanWindow();
    pacmanWnd->configurer(name1,name2,nJoueur,nFantome,vit,mode);
    pacmanWnd->startJeu();
    inGame = true;

    //afficher le status du jeu
    statusBar()->showMessage(tr("Vous etes en jeu!"));

}

void Mainwnd::init_resultWnd(string resultat){
    resultWnd = new resultWindow();
    resultWnd->setResultat(resultat);

    //les slots corespondent aux certains butons lorsde apparation de la fenêtre de résultat
    connect(resultWnd->btnRejouer,QPushButton::clicked, this, handleNouveauJeu);
    connect(resultWnd->btnSortir,QPushButton::clicked, this, close);
    statusBar()->showMessage(tr("Essayez encore une fois pour vaincre le champion"));
}

void Mainwnd::handleUnJoueur(){
    init_caractWnd(1);
    setCentralWidget(caractWnd); // laisse la fenetre de configuration du jeu apparaitre
}

void Mainwnd::handleDeuxJoueur(){
    init_caractWnd(2);
    setCentralWidget(caractWnd);
}

void Mainwnd::handleCommence(){
    init_pacmanWnd(caractWnd->getName1(),caractWnd->getName2(),caractWnd->getNombre(),caractWnd->getNombreFantomes(),caractWnd->getVitesse(),caractWnd->getNumMode());
    setCentralWidget(pacmanWnd); // laisse la fenetre de jeu apparatre
    timerId = startTimer(caractWnd->getVitesse()); //si le jeu commence, mettre le timer de MainWnd en commence pour synchroniser avec le timer de PacmanWindow
}

void Mainwnd::handleNouveauJeu(){
    init_bienvenueWnd();
    setCentralWidget(bienvenueWnd); // laisse la fénêtre de bienvenue apparaitre

    //si on n'est pas en jeu, reset les varibles privées
    inGame = false;
    killTimer(timerId);
    timerId = 0;
}

void Mainwnd::handleResultat(){
    init_resultWnd(pacmanWnd->resultat);
    setCentralWidget(resultWnd); //laisse la fenetre de résulat apparaitre
}

void Mainwnd::handleMeuilleurNote(){
    //lire les meilleur notes en le fichier
    readfile();

    //afficher le résultat sous la forme d'un QMessageBox
    QMessageBox msg;
    msg.resize(500, 500);
    msg.setFont(QFont("Arial", 10));
    string str = "";
    str += "Joueur1 - nFantome - Vitesse - Temps - Etat\n" ;
    for (int i=0; i < 2;i++){
        for (int j=0;j < 5;j++)
                if (j != 4)
                    str += result[i][j]+" - ";
                else str += result[i][j];
        if(i==0)
            str += "\n\Joueur1 - Joueur2 - nFantome - Vitesse - QuiGagne\n" ;
    }
    msg.setText(QString::fromStdString(str));
    msg.exec();
}

void Mainwnd::compareResultat(PacmanWindow &Wnd){
    //Pour le meilleur note, nous supposons que pour mode un joueur la vitesse soit priori, apres c'est le nombre de fantome et dernieremet, le temps pris à gagner
    //pour deux joueurs, nous allons prendre le nouveau.
    int vit = (result[0][2] != "")? stoi(result[0][2]):0;
    int fan = (result[0][1] != "")? stoi(result[0][1]):0;
    int temp = (result[0][3] != "")? stoi(result[0][3]):0;
    if (Wnd.jeu.getNombreJoueur() == 1){
        if (vit > Wnd.jeu.getVitesse() ){
            result[0][0] = Wnd.jeu.pacmanA.getName();
            result[0][1] = to_string(Wnd.jeu.getNombreFantome());
            result[0][2] = to_string(Wnd.jeu.getVitesse());
            result[0][3] = to_string(30 - Wnd.countdown.second());
            result[0][4] = "Champion";
        } else if (vit == Wnd.jeu.getVitesse()){
            if (fan < Wnd.jeu.getNombreFantome()){
                result[0][0] = Wnd.jeu.pacmanA.getName();
                result[0][1] = to_string(Wnd.jeu.getNombreFantome());
                result[0][2] = to_string(Wnd.jeu.getVitesse());
                result[0][3] = to_string(30 - Wnd.countdown.second());
                result[0][4] = "Champion";
            } else if (fan  == Wnd.jeu.getVitesse()){
                if (temp > (30 - Wnd.countdown.second())){
                    result[0][0] = Wnd.jeu.pacmanA.getName();
                    result[0][1] = to_string(Wnd.jeu.getNombreFantome());
                    result[0][2] = to_string(Wnd.jeu.getVitesse());
                    result[0][3] = to_string(30 - Wnd.countdown.second());
                    result[0][4] = "Champion";
                }
            }
        } else if (vit == 0){
            result[0][0] = Wnd.jeu.pacmanA.getName();
            result[0][1] = to_string(Wnd.jeu.getNombreFantome());
            result[0][2] = to_string(Wnd.jeu.getVitesse());
            result[0][3] = to_string(30 - Wnd.countdown.second());
            result[0][4] = "Champion";
        }
    } else
    {
        result[1][0] = Wnd.jeu.pacmanA.getName();
        result[1][1] = Wnd.jeu.pacmanB.getName();
        result[1][2] = to_string(Wnd.jeu.getNombreFantome());
        result[1][3] = to_string(Wnd.jeu.getVitesse());
        result[1][4] = Wnd.resultat;
    }
}

void Mainwnd::readfile(){
    ifstream resultat;
    //string str;
    resultat.open("./resultat.txt");
    for (int i=0; i<2;i++)
        for (int j=0;j<5;j++)
            getline(resultat,result[i][j]);
    resultat.close();
}

void Mainwnd::writefile(){
    ofstream resultat;
    //string str;
    resultat.open("./resultat.txt",ios_base::trunc);
    for (int i=0; i<2;i++)
        for (int j=0;j<5;j++){
            resultat<<result[i][j]<<endl;
        }
    resultat.close();
}

void Mainwnd::timerEvent(QTimerEvent * e){
    if (pacmanWnd->gameFini){
        killTimer(timerId);
        timerId = 0;
        if(pacmanWnd->gameGagne){
            readfile();
            compareResultat(*pacmanWnd);
            writefile();
        }
        handleResultat();
        inGame = false;
    }
}

