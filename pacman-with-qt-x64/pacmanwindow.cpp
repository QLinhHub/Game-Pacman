#include <iostream>
#include "pacmanwindow.h"

using namespace std;

Mainwnd::PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    gameFini = false;
    paused = false;
    gameGagne = false;
    countGod = 0;
    loadImage();

    vitesseJeu = new QTimer(this);
    connect(vitesseJeu, QTimer::timeout, this, PacmanWindow::handleTimer);
    countTime = new QTimer(this);
    connect(countTime, &QTimer::timeout, this, &PacmanWindow::handleCountdown);

}

void Mainwnd::PacmanWindow::loadImage()
{

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    // Charqer les pixmaps pour le pacman
    if (pixmapPacman1.load("./data/pacman1.png")==false)
    {
        cout<<"Impossible d'ouvrir pacman1.png"<<endl;
        exit(-1);
    }
    if (pixmapPacman2.load("./data/pacman2.png")==false)
    {
        cout<<"Impossible d'ouvrir pacman2.png"<<endl;
        exit(-1);
    }
    if (pixmapPacman3.load("./data/pacman3.png")==false)
    {
        cout<<"Impossible d'ouvrir pacman3.png"<<endl;
        exit(-1);
    }
    if (pixmapPacman4.load("./data/pacman4.png")==false)
    {
        cout<<"Impossible d'ouvrir pacman4.png"<<endl;
        exit(-1);
    }
    pixmapPacmanDefaut = pixmapPacman4;

    // Charqer les pixmaps pour le fantome
    if (pixmapFantome1.load("./data/fantome1.png")==false)
    {
        cout<<"Impossible d'ouvrir fantome.png"<<endl;
        exit(-1);
    }
    if (pixmapFantome2.load("./data/fantome2.png")==false)
    {
        cout<<"Impossible d'ouvrir fantome.png"<<endl;
        exit(-1);
    }
    if (pixmapFantome3.load("./data/fantome3.png")==false)
    {
        cout<<"Impossible d'ouvrir fantome.png"<<endl;
        exit(-1);
    }

    // Charqer les pixmaps pour le godFantome
    if (pixmapGod.load("./data/godFantome.png")==false)
    {
        cout<<"Impossible d'ouvrir god fantome.bmp"<<endl;
        exit(-1);
    }

    // Charqer les pixmaps pour le mur
    if (pixmapMur1.load("./data/mur1.png")==false)
    {
        cout<<"Impossible d'ouvrir mur1.png"<<endl;
        exit(-1);
    }
    if (pixmapMur2.load("./data/mur2.png")==false)
    {
        cout<<"Impossible d'ouvrir mur2.png"<<endl;
        exit(-1);
    }
    if (pixmapMur3.load("./data/mur3.png")==false)
    {
        cout<<"Impossible d'ouvrir mur3.png"<<endl;
        exit(-1);
    }
    if (pixmapGrass.load("./data/grass.png")==false)
    {
        cout<<"Impossible d'ouvrir grass.png"<<endl;
        exit(-1);
    }
    //PacmanButton *a = new PacmanButton(this);

    largeurCase = pixmapMur1.width();
    hauteurCase = pixmapMur1.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase);
}

void Mainwnd::PacmanWindow::setupLabel()
{

    if(jeu.getNombreJoueur() == 1)
    {
        countdown.setHMS(0,0,30,0);
        label_countdown = new QLabel("0:30", this);
        label_countdown->setGeometry(QRect(QPoint(700, 45), QSize(130, 50)));
        label_countdown->setFont(QFont("Arial", 30));

        QLabel* labelA = new QLabel( QString::fromStdString(jeu.pacmanA.getName()), this);
        labelA->setGeometry(QRect(QPoint(650, 90), QSize(300, 100)));
        labelA->setFont(QFont("Arial", 30));

        QLabel* labelA1 = new QLabel("Mark: ", this);
        labelA1->setGeometry(QRect(QPoint(675, 135), QSize(300, 100)));
        labelA1->setFont(QFont("Arial", 30));

        label_marqueA = new QLabel(this);
        label_marqueA->setGeometry(QRect(QPoint(700, 180), QSize(200, 100)));
        label_marqueA->setFont(QFont("Arial", 30));
        label_marqueA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.getMarque())));
    }
    else
    {
        QLabel* labelA = new QLabel(QString::fromStdString(jeu.pacmanA.getName()), this);
        labelA->setGeometry(QRect(QPoint(650, 90), QSize(300, 100)));
        labelA->setFont(QFont("Arial", 30));

        QLabel* labelB = new QLabel(QString::fromStdString(jeu.pacmanB.getName()), this);
        labelB->setGeometry(QRect(QPoint(650, 180), QSize(300, 100)));
        labelB->setFont(QFont("Arial", 30));

        label_marqueA = new QLabel(this);
        label_marqueA->setGeometry(QRect(QPoint(700, 135), QSize(200, 100)));
        label_marqueA->setFont(QFont("Arial", 30));
        label_marqueA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.getMarque())));

        label_marqueB = new QLabel(this);
        label_marqueB->setGeometry(QRect(QPoint(700, 225), QSize(200, 100)));
        label_marqueB->setFont(QFont("Arial", 30));
        label_marqueB->setText(QString::fromStdString(std::to_string(jeu.pacmanB.getMarque())));
    }
}

void Mainwnd::PacmanWindow::configurer(string name1, string name2, int nJoueur, int nFantome, int vit, int mode)
{
    jeu.setInfoJeu(name1, name2, nJoueur,nFantome,vit, mode);
    jeu.init();
}

void Mainwnd::PacmanWindow::startJeu()
{
    setupLabel();
    vitesseJeu->start(jeu.getVitesse());
    countTime->start(1000);
}

void Mainwnd::PacmanWindow::pauseJeu()
{
  if (paused) {
    vitesseJeu->start(jeu.getVitesse());
    countTime->start(1000);
    paused = false;
  } else {
    vitesseJeu->stop();
    countTime->stop();
    paused = true;
  }
}

void Mainwnd::PacmanWindow::stopJeu()
{
    vitesseJeu->stop();
    countTime->stop();
    gameFini = true;
    resultat = jeu.pacmanA.getName() +" est perdu!!!";
}

void Mainwnd::PacmanWindow::gagneJeu(int codeResult)
{
    vitesseJeu->stop();
    countTime->stop();
    gameFini = true;
    gameGagne = true;
    switch (codeResult){
        case -1:
            resultat = jeu.pacmanA.getName() +" est gagnant!!!";
            break;
        case 0:
            resultat = jeu.pacmanA.getName() + "&" + jeu.pacmanA.getName() + " sont égaux!";
            break;
        case 1:
            resultat = jeu.pacmanA.getName() +" gagne " + jeu.pacmanB.getName();
            break;
        case 2:
            resultat = jeu.pacmanB.getName() +" gagne " + jeu.pacmanA.getName();
            break;
    }
}

void Mainwnd::PacmanWindow::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    list<GodFantome>::const_iterator itGod;
    int x, y;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur1.width();
    hauteurCase = pixmapMur1.height();

    // Dessine les cases
    for (y=0;y<jeu.getNbCasesY();y++)
        for (x=0;x<jeu.getNbCasesX();x++)
			if (jeu.getCase(x,y)==MUR1)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapMur1);
            else if (jeu.getCase(x,y)==MUR2)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapMur2);
            else if (jeu.getCase(x,y)==MUR3)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapMur3);
            else
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapGrass);


    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        if (itFantome->getCode() == 1)
            painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome1);
        else if (itFantome->getCode() == 2)
            painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome2);
        else if (itFantome->getCode() == 3)
            painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome3);

    // Dessine les gods
    if (countGod <= 3)
        for (itGod=jeu.godFantomes.begin(); itGod!=jeu.godFantomes.end(); itGod++)
            painter.drawPixmap(itGod->getPosX()*largeurCase, itGod->getPosY()*hauteurCase, pixmapGod);

	// Dessine Pacman
	if (jeu.getNombreJoueur() == 1)
        painter.drawPixmap(jeu.pacmanA.getPosX()*largeurCase, jeu.pacmanA.getPosY()*hauteurCase, pixmapPacmanDefaut);
    else{
        painter.drawPixmap(jeu.pacmanA.getPosX()*largeurCase, jeu.pacmanA.getPosY()*hauteurCase, pixmapPacman1);
        painter.drawPixmap(jeu.pacmanB.getPosX()*largeurCase, jeu.pacmanB.getPosY()*hauteurCase, pixmapPacman2);
    }

}

void Mainwnd::PacmanWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (!paused)
    {
        if (key == Qt::Key_Left)
            jeu.deplacePacman(jeu.pacmanA,GAUCHE);
        else if (key == Qt::Key_Right)
            jeu.deplacePacman(jeu.pacmanA,DROITE);
        else if (key == Qt::Key_Up)
            jeu.deplacePacman(jeu.pacmanA,HAUT);
        else if (key == Qt::Key_Down)
            jeu.deplacePacman(jeu.pacmanA,BAS);

        if (jeu.getNombreJoueur() == 2){
            if (key == Qt::Key_Q)
                jeu.deplacePacman(jeu.pacmanB,GAUCHE);
            else if (key == Qt::Key_D)
                jeu.deplacePacman(jeu.pacmanB,DROITE);
            else if (key == Qt::Key_Z)
                jeu.deplacePacman(jeu.pacmanB,HAUT);
            else if (key == Qt::Key_S)
                jeu.deplacePacman(jeu.pacmanB,BAS);
        }
    }

    if (key == Qt::Key_Space)
        pauseJeu();

    handleCollision();
    update();
}

void Mainwnd::PacmanWindow::handleTimer()
{
    jeu.evolue();
    handleCollision();
    repaint();
}

void Mainwnd::PacmanWindow::handleCountdown()
{
    if (jeu.getNombreJoueur()==1){
        if (countdown.second() != 0)
            countdown = countdown.addSecs(-1); ////correspond à 1000ms(1s)
        else
            stopJeu();
        label_countdown->setText(countdown.toString("m:ss"));
    }
    //Pour faire clignoter les 3 godfantomes, de 0->3: il apparaitre, de 4->6: il disparaitre, lorsde countGod = 6, on le remet à 0
    if (countGod != 6)
        countGod++;
    else
        countGod = 0;
}

void Mainwnd::PacmanWindow::checkCollision(Pacman & pac)
{
    for(auto it = jeu.fantomes.begin(); it != jeu.fantomes.end(); it++){
        if(it->getPosX() == pac.getPosX() && it->getPosY() == pac.getPosY()){
            pac.increaseMarque(1); // plus 1 mark
            jeu.fantomes.erase(it); // supprimer ce fantome
        }
    }
    for(auto it = jeu.godFantomes.begin(); it != jeu.godFantomes.end(); it++){
        if(it->getPosX() == pac.getPosX() && it->getPosY() == pac.getPosY()){
            if (jeu.getNombreJoueur() == 1){
                countdown = countdown.addSecs(3); // plus 3 secondes dans le cas 1 joueurs
                //changer le apercu du pacman
                switch (jeu.godFantomes.size()){
                case 3:
                    pixmapPacmanDefaut = pixmapPacman3;
                    break;
                case 2:
                    pixmapPacmanDefaut = pixmapPacman2;
                    break;
                case 1:
                    pixmapPacmanDefaut = pixmapPacman1;
                    break;
                default:
                    pixmapPacmanDefaut =pixmapPacman4;
                };
            }
            else
                pac.increaseMarque(3); // plus 3 marks si dans le cas 2 joueurs
            jeu.godFantomes.erase(it); //supprimer
        }
    }
}

void Mainwnd::PacmanWindow::handleCollision()
{
    if (jeu.getNombreJoueur() == 1)
    {
        if (jeu.fantomes.empty())
            gagneJeu(-1);
        checkCollision(jeu.pacmanA);
        label_marqueA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.getMarque())));
    }
    else
    {
        if (jeu.fantomes.empty() && jeu.godFantomes.empty()){
            if (jeu.pacmanA.getMarque() > jeu.pacmanB.getMarque())
                gagneJeu(1);
            else if (jeu.pacmanA.getMarque() < jeu.pacmanB.getMarque())
                gagneJeu(2);
            else
                gagneJeu(0);
        }
        checkCollision(jeu.pacmanA);
        checkCollision(jeu.pacmanB);
        label_marqueA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.getMarque())));
        label_marqueB->setText(QString::fromStdString(std::to_string(jeu.pacmanB.getMarque())));
    }
}
