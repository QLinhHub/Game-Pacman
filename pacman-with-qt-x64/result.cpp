#include <iostream>
#include "result.h"

using namespace std;

Mainwnd::resultWindow::resultWindow(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);

    resultat = new QLabel(this);
    resultat->setAlignment(Qt::AlignCenter);
    resultat->setFont(QFont("Arial", 50));

    btnRejouer = new QPushButton("Rejouer", this);
    btnRejouer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnSortir = new QPushButton("Sortir", this);
    btnSortir->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vbox->addWidget(resultat);
    vbox->addWidget(btnRejouer);
    vbox->addWidget(btnSortir);

    setLayout(vbox);
}

void Mainwnd::resultWindow::setResultat(string result){
    resultat->setText(QString::fromStdString(result));
}

