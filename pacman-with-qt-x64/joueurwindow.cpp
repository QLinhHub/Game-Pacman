#include <iostream>
#include <string>
#include "joueurwindow.h"

using namespace std;

Mainwnd::joueurWindow::joueurWindow(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags){

    labelNF = new QLabel("10", this);
    labelVT = new QLabel("25", this);
    labelMO = new QLabel("1",this);
    btnCommence = new QPushButton(this);
    btnCommence->setText("Commmencer");
    btnRetourne = new QPushButton(this);
    btnRetourne->setText("Retourner");
}

void Mainwnd::joueurWindow::configurer()
{
    QFormLayout *formLayout = new QFormLayout;
    formLayout->setSpacing(20);

    if (nombreJoueur == 1)
    {
        name1.setPlaceholderText("Bao");
        formLayout->addRow("Name:", &name1);
    }
    else
    {
        name1.setPlaceholderText("Bao");
        name2.setPlaceholderText("Linh");
        formLayout->addRow("Name1:", &name1);
        formLayout->addRow("Name2:", &name2);
    }


    QSlider* s_numFantomes = new QSlider(Qt::Horizontal , this);
    s_numFantomes->setMinimum(10);
    s_numFantomes->setMaximum(50);
    QSlider* s_vitesse = new QSlider(Qt::Horizontal , this);
    s_vitesse->setMinimum(25);
    s_vitesse->setMaximum(500);
    QSpinBox * s_mode = new QSpinBox(this);
    s_mode->setMinimum(1);
    s_mode->setMaximum(7);

    formLayout->addRow("Nombre de Fantomes: ", labelNF);
    formLayout->addRow("", s_numFantomes);
    formLayout->addRow("Vitesse:", labelVT);
    formLayout->addRow("", s_vitesse);

    formLayout->addRow("Mode", labelMO);
    formLayout->addRow("",s_mode);
    formLayout->addRow(btnRetourne,btnCommence);

    connect(s_numFantomes, &QSlider::valueChanged, labelNF, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(s_vitesse, &QSlider::valueChanged, labelVT, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(s_mode, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),labelMO, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    setLayout(formLayout);
}


