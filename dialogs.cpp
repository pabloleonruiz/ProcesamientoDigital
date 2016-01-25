#include "dialogs.h"

/***********************************************/
/***  INICIO CLASE DIALOGO NORMALIZAR        ***/
/***********************************************/

Dialogo_Normalizar::Dialogo_Normalizar(QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);

    text = new QLabel(tr("Seleccione valor para normalizar:"));
    valor = new QSpinBox;
    valor->setRange(0, 255);
    valor->setValue(0);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Normalizar"));
}


Dialogo_Normalizar::~Dialogo_Normalizar()
{

}

void Dialogo_Normalizar::okPulsado()
{
    operador = valor->value();
    close();
}


int Dialogo_Normalizar::resultado()
{
    return operador;
}

/*!
DETECTORES
*/

/***********************************************/
/***  INICIO CLASE DIALOGO DETECTOR LEE COK  ***/
/***********************************************/

Dialogo_Lee_Cok::Dialogo_Lee_Cok(QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);


    text = new QLabel(tr("Seleccione operador básico:"));
    valor = new QSpinBox;
    valor->setRange(1, 3);
    valor->setValue(1);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Lee Cok"));
}


Dialogo_Lee_Cok::~Dialogo_Lee_Cok()
{

}

void Dialogo_Lee_Cok::okPulsado()
{
    operador = valor->value();
    close();
}


int Dialogo_Lee_Cok::resultado()
{
    return operador;
}




/****************************************************/
/***   INICIO CLASE DIALOGO DETECTOR DIRECCIONAL  ***/
/****************************************************/

Dialogo_Direccional::Dialogo_Direccional(QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);


    text = new QLabel(tr("Seleccione una opción:"));
    valor = new QSpinBox;
    valor->setRange(1, 3);
    valor->setValue(1);
    text->setBuddy(valor);

    textDesc = new QLabel(tr("\nDESCRIPCIÓN DE LOS CASOS\n"
                             "Caso 1 -> tamaño de ventana = 3x3\n"
                             "Caso 2 -> tamaño de ventana = 5x5\n"
                             "Caso 3 -> tamaño de ventana = 7x7"));

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addWidget(textDesc);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Direccional"));
}


Dialogo_Direccional::~Dialogo_Direccional()
{

}

void Dialogo_Direccional::okPulsado()
{

    operador = valor->value();
    close();

}




int Dialogo_Direccional::resultado()
{
    return operador;
}




/*****************************************************/
/***   INICIO CLASE DIALOGO DETECTOR DV y DV-HV    ***/
/*****************************************************/

Dialogo_Dv::Dialogo_Dv(QString &titulo, int *d, float a, QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);

    opc = FALSE;
    datos[0] = d[0];
    datos[1] = d[1];
    datos[2] = d[2];
    alfa = a;

    text = new QLabel(tr("Seleccione el tamaño de ventana:"));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(1, 2);
    valor->setValue(1);
    text->setBuddy(valor);
    textDesc = new QLabel(tr("\nDESCRIPCIÓN DE LOS CASOS\n"
                             "Caso 1 -> tamaño de ventana = 5x5\n"
                             "Caso 2 -> tamaño de ventana = 3x3"));
    textDesc->setFont(QFont("Ubuntu", 11, QFont::Normal));

    text1 = new QLabel(tr("Seleccione el tipo de filtro:"));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(1, 3);
    valor1->setValue(1);
    text1->setBuddy(valor1);
    textDesc1 = new QLabel(tr("\nDESCRIPCIÓN DE LOS CASOS\n"
                              "Caso 1 -> filtro de la media aritmética\n"
                              "Caso 2 -> filtro del vector mediana\n"
                              "Caso 3 -> filtro de la media 'alfa ajustada'"));
    textDesc1->setFont(QFont("Ubuntu", 11, QFont::Normal));

    text2 = new QLabel(tr("Seleccione el valor de alfa:"));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QDoubleSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(0.00, 0.50);
    valor2->setValue(0);
    text2->setBuddy(valor2);
    textDesc2 = new QLabel(tr("\nDESCRIPCIÓN\n"
                              "Parámetro para el filtro de la media\n"
                              "alfa ajustada (valores entre 0 y 0.5)\n"));
    textDesc2->setFont(QFont("Ubuntu", 11, QFont::Normal));

    text3 = new QLabel(tr("Seleccione el tipo de distancia:"));
    text3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3 = new QSpinBox;
    valor3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3->setRange(1, 3);
    valor3->setValue(1);
    text3->setBuddy(valor3);
    textDesc3 = new QLabel(tr("\nDESCRIPCIÓN DE LOS CASOS\n"
                              "Caso 1 -> distancia euclídea\n"
                              "Caso 2 -> distancia absoluta\n"
                              "Caso 3 -> distancia de ajedrez"));
    textDesc3->setFont(QFont("Ubuntu", 11, QFont::Normal));


    ok = new QPushButton(tr("Aceptar"));


    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));


    ventana = new QGroupBox(tr("Ventana"));
    ventana->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato1 = new QHBoxLayout;
    dato1->addWidget(text);
    dato1->addStretch();
    dato1->addWidget(valor);

    dato2 = new QVBoxLayout;
    dato2->addLayout(dato1);
    dato2->addWidget(textDesc);
    ventana->setLayout(dato2);


    filtro = new QGroupBox(tr("Filtro"));
    filtro->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato3 = new QHBoxLayout;
    dato3->addWidget(text1);
    dato3->addStretch();
    dato3->addWidget(valor1);

    dato4 = new QVBoxLayout;
    dato4->addLayout(dato3);
    dato4->addWidget(textDesc1);
    filtro->setLayout(dato4);


    alfaDialog = new QGroupBox(tr("Alfa"));
    alfaDialog->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato5 = new QHBoxLayout;
    dato5->addWidget(text2);
    dato5->addStretch();
    dato5->addWidget(valor2);

    dato6 = new QVBoxLayout;
    dato6->addLayout(dato5);
    dato6->addWidget(textDesc2);
    alfaDialog->setLayout(dato6);


    distancia = new QGroupBox(tr("Distancia"));
    distancia->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato7 = new QHBoxLayout;
    dato7->addWidget(text3);
    dato7->addStretch();
    dato7->addWidget(valor3);

    dato8 = new QVBoxLayout;
    dato8->addLayout(dato7);
    dato8->addWidget(textDesc3);
    distancia->setLayout(dato8);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    grid = new QGridLayout;
    grid->addWidget(ventana, 1, 1);
    grid->addWidget(filtro, 1, 2);
    grid->addWidget(alfaDialog, 2, 1);
    grid->addWidget(distancia, 2, 2);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(grid);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(titulo);
}


Dialogo_Dv::~Dialogo_Dv()
{

}


void Dialogo_Dv::okPulsado()
{
    datos[0] = valor->value();
    datos[1] = valor1->value();
    alfa = valor2->value();
    datos[2] = valor3->value();
    close();
}


int* Dialogo_Dv::resultado_datos()
{
    return datos;
}


float Dialogo_Dv::resultado_alfa()
{
    return alfa;
}




/********************************************************/
/***CLASE DIALOGO DETECTOR MVD (PARA LAS DOS VERSIONES***/
/********************************************************/

Dialogo_Mvd::Dialogo_Mvd(QString &titulo, int *d, QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);

    datos[0] = d[0];
    datos[1] = d[1];
    datos[2] = d[2];
    datos[3] = d[3];

    text = new QLabel(tr("Seleccione el tamaño de ventana:"));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(1, 3);
    valor->setValue(1);
    text->setBuddy(valor);
    textDesc = new QLabel(tr("\nDESCRIPCIÓN DE LOS CASOS\n"
                             "Caso 1 -> tamaño de ventana = 3x3\n"
                             "Caso 2 -> tamaño de ventana = 5x5\n"
                             "Caso 3 -> tamaño de ventana = 7x7"));
    textDesc->setFont(QFont("Ubuntu", 11, QFont::Normal));

    text1 = new QLabel(tr("Seleccione el tipo de distancia:"));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(1, 3);
    valor1->setValue(1);
    text1->setBuddy(valor1);
    textDesc1 = new QLabel(tr("\nDESCRIPCIÓN DE LOS CASOS\n"
                              "Caso 1 -> distancia euclídea\n"
                              "Caso 2 -> distancia absoluta\n"
                              "Caso 3 -> distancia de ajedrez"));
    textDesc1->setFont(QFont("Ubuntu", 11, QFont::Normal));

    text2 = new QLabel(tr("Seleccione el número de vector 'l':"));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(1, 3);
    valor2->setValue(1);
    text2->setBuddy(valor2);
    textDesc2 = new QLabel(tr("\nDESCRIPCIÓN\n"
                              "Se calcula el vector mediana\n"
                              "como la media de los 'l' primeros\n"
                              "vectores ordenados crecientemente"));
    textDesc2->setFont(QFont("Ubuntu", 11, QFont::Normal));


    text3 = new QLabel(tr("Seleccione el número de elemento 'k':"));
    text3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3 = new QSpinBox;
    valor3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3->setRange(1, 3);
    valor3->setValue(1);
    text3->setBuddy(valor3);
    textDesc3 = new QLabel(tr("\nDESCRIPCIÓN\n"
                              "Se calcula el valor del borde detectado como la\n"
                              "distancia mínima entre los últimos 'k' elementos\n"
                              "según el orden establecido y el vector mediana"));
    textDesc3->setFont(QFont("Ubuntu", 11, QFont::Normal));


    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));


    ventana = new QGroupBox(tr("Ventana"));
    ventana->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato1 = new QHBoxLayout;
    dato1->addWidget(text);
    dato1->addStretch();
    dato1->addWidget(valor);

    dato2 = new QVBoxLayout;
    dato2->addLayout(dato1);
    dato2->addWidget(textDesc);
    ventana->setLayout(dato2);


    distancia = new QGroupBox(tr("Distancia"));
    distancia->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato3 = new QHBoxLayout;
    dato3->addWidget(text1);
    dato3->addStretch();
    dato3->addWidget(valor1);

    dato4 = new QVBoxLayout;
    dato4->addLayout(dato3);
    dato4->addWidget(textDesc1);
    distancia->setLayout(dato4);


    mediana = new QGroupBox(tr("Mediana"));
    mediana->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato5 = new QHBoxLayout;
    dato5->addWidget(text2);
    dato5->addStretch();
    dato5->addWidget(valor2);

    dato6 = new QVBoxLayout;
    dato6->addLayout(dato5);
    dato6->addWidget(textDesc2);
    mediana->setLayout(dato6);


    borde = new QGroupBox(tr("Borde"));
    borde->setFont(QFont("Ubuntu", 11, QFont::Bold));
    dato7 = new QHBoxLayout;
    dato7->addWidget(text3);
    dato7->addStretch();
    dato7->addWidget(valor3);

    dato8 = new QVBoxLayout;
    dato8->addLayout(dato7);
    dato8->addWidget(textDesc3);
    borde->setLayout(dato8);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    grid = new QGridLayout;
    grid->addWidget(ventana, 1, 1);
    grid->addWidget(distancia, 1, 2);
    grid->addWidget(mediana, 2, 1);
    grid->addWidget(borde, 2, 2);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(grid);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(titulo);
}


Dialogo_Mvd::~Dialogo_Mvd()
{

}


void Dialogo_Mvd::okPulsado()
{
    datos[0] = valor->value();
    datos[1] = valor1->value();
    datos[2] = valor2->value();
    datos[3] = valor3->value();
    close();
}


int* Dialogo_Mvd::resultado_datos()
{
    return datos;
}





/*!
UMBRALIZADORES
*/

/********************************************/
/***  INICIO CLASE DIALOGO UMBR. MANUAL   ***/
/********************************************/

Dialogo_Umbr_Manual::Dialogo_Umbr_Manual(QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);

    text = new QLabel(tr("Seleccione umbral:    "));
    valor = new QDoubleSpinBox;
    valor->setRange(0.00, 255.00);
    valor->setValue(0);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Umbralización manual"));
}


Dialogo_Umbr_Manual::~Dialogo_Umbr_Manual()
{

}

void Dialogo_Umbr_Manual::okPulsado()
{
    operador = valor->value();
    close();
}



float Dialogo_Umbr_Manual::resultado()
{
    return operador;
}





/**************************************************/
/***   INICIO CLASE DIALOGO UMBR. PORCENTUAL    ***/
/**************************************************/

Dialogo_Umbr_Porcentual::Dialogo_Umbr_Porcentual(QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);

    text = new QLabel(tr("Seleccione porcentaje:    "));
    valor = new QDoubleSpinBox;
    valor->setRange(0.00, 100.00);
    valor->setValue(0);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Umbralización porcentual"));
}


Dialogo_Umbr_Porcentual::~Dialogo_Umbr_Porcentual()
{

}

void Dialogo_Umbr_Porcentual::okPulsado()
{
    operador = valor->value();
    close();
}


float Dialogo_Umbr_Porcentual::resultado()
{
    return operador;
}




/*******************************************/
/***   INICIO CLASE DIALOGO HISTERESIS   ***/
/*******************************************/

Dialogo_Histeresis::Dialogo_Histeresis(QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);

    aux_mayor = 255;
    aux_menor = 0;

    text = new QLabel(tr("Seleccione umbral mayor:    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QDoubleSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(0.00, 255.00);
    valor->setValue(aux_mayor);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Seleccione umbral menor:    "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QDoubleSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0.00, 255.00);
    valor1->setValue(aux_menor);
    text1->setBuddy(valor1);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    mayorGrupo = new QGroupBox(tr("Umbral mayor"));
    mayorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    mayorGrupo->setLayout(datos);

    menorGrupo = new QGroupBox(tr("Umbral menor"));
    menorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    menorGrupo->setLayout(datos1);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(mayorGrupo);
    total->addSpacing(10);
    total->addWidget(menorGrupo);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Histéresis"));
}


Dialogo_Histeresis::~Dialogo_Histeresis()
{

}

void Dialogo_Histeresis::okPulsado()
{
    if (valor->value() < valor1->value())
    {
      valor->setValue(aux_mayor);
      valor1->setValue(aux_menor);
      QString texto = "Recuerde que el umbral mayor debe ser mayor que el umbral menor";
      QString titulo = "Aviso";
      Dialogo_General *dialogo8 = new Dialogo_General(texto, titulo);
      dialogo8->exec();
    }
    else
    {
        mayor = valor->value();
        menor = valor1->value();
        close();
    }
}




float Dialogo_Histeresis::resultado_mayor()
{
    return mayor;
}

float Dialogo_Histeresis::resultado_menor()
{
    return menor;
}

/*!
INICIO CLASE DIALOGO GENERAL
*/

Dialogo_General::Dialogo_General(QString &umbral, QString &umbral1, QWidget *parent)
 : QDialog(parent)
{
    text = new QLabel(umbral);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));


    texto = new QHBoxLayout;
    texto->addWidget(text);

    boton = new QHBoxLayout;
    boton->addStretch();
    boton->addWidget(ok);


    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(texto);
    total->addSpacing(15);
    total->addLayout(boton);
    setLayout(total);

    setWindowTitle(umbral1);
}


Dialogo_General::~Dialogo_General()
{

}

void Dialogo_General::okPulsado()
{
    close();
}


/*******************************************/
/***   INICIO CLASE DIALOGO LINEAR       ***/
/*******************************************/

Dialogo_Linear::Dialogo_Linear(QWidget *parent)
 : QDialog(parent)
{
    aux_mayor = 255;
    aux_menor = 0;
    inicio = 0;
    pendiente = 1.2;

    text = new QLabel(tr("Seleccione final:    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(32, 255);
    valor->setValue(aux_mayor);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Seleccione comienzo:    "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0, 255);
    valor1->setValue(aux_menor);
    text1->setBuddy(valor1);

    text2 = new QLabel(tr("Valor inicial:    "));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(0, 128);
    valor2->setValue(inicio);
    text2->setBuddy(valor2);

    text3 = new QLabel(tr("Slope:    "));
    text3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3 = new QDoubleSpinBox;
    valor3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3->setRange(-4.00, 4.00);
    valor3->setValue(pendiente);
    text3->setBuddy(valor3);

    recortar= new QCheckBox(tr("Poner a valor 0 los que queda fuera del rango "));
    recortar->setLayoutDirection(Qt::RightToLeft);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    mayorGrupo = new QGroupBox(tr("Final"));
    mayorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    mayorGrupo->setLayout(datos);

    menorGrupo = new QGroupBox(tr("Comienzo"));
    menorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    menorGrupo->setLayout(datos1);

    inicioGrupo = new QGroupBox(tr("Inicio"));
    inicioGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos2 = new QHBoxLayout;
    datos2->addWidget(text2);
    datos2->addWidget(valor2);
    inicioGrupo->setLayout(datos2);

    pendienteGrupo = new QGroupBox(tr("Slope"));
    pendienteGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos3 = new QHBoxLayout;
    datos3->addWidget(text3);
    datos3->addWidget(valor3);
    pendienteGrupo->setLayout(datos3);


    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(menorGrupo);
    total->addSpacing(10);
    total->addWidget(mayorGrupo);
    total->addSpacing(15);
    total->addWidget(inicioGrupo);
    total->addSpacing(20);
    total->addWidget(pendienteGrupo);
    total->addSpacing(25);
    total->addWidget(recortar);
    total->addSpacing(30);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Linear"));
}


Dialogo_Linear::~Dialogo_Linear()
{

}

void Dialogo_Linear::okPulsado()
{
    if (valor->value() < valor1->value())
    {
      valor->setValue(aux_mayor);
      valor1->setValue(aux_menor);
      QString texto = "Recuerde que el final debe ser mayor que el inicio";
      QString titulo = "Aviso";
      Dialogo_General *dialogo8 = new Dialogo_General(texto, titulo);
      dialogo8->exec();
    }
    else
    {
        Qt::CheckState state1;
        state1 = recortar->checkState();

        mayor = valor->value();
        menor = valor1->value();
        inicial = valor2->value();
        pend = valor3->value();
        if(state1==Qt::Checked)
            rec=FALSE;
        else
            rec=TRUE;
        close();
    }
}



double Dialogo_Linear::resultado_mayor()
{
    return mayor;
}

double Dialogo_Linear::resultado_menor()
{
    return menor;
}

double Dialogo_Linear::resultado_inicial()
{
    return inicial;
}

float Dialogo_Linear::resultado_pendiente()
{
    return pend;
}

bool Dialogo_Linear::resultado_recortar()
{
    return rec;
}

/***********************************************/
/***  INICIO CLASE DIALOGO HISTOGRAM SLIDE   ***/
/***********************************************/

Dialogo_Slide::Dialogo_Slide(QWidget *parent)
 : QDialog(parent)
{

    text = new QLabel(tr("Seleccione slide:"));
    valor = new QSpinBox;
    valor->setRange(-100, 100);
    valor->setValue(0);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Histogram Slide"));
}


Dialogo_Slide::~Dialogo_Slide()
{

}

void Dialogo_Slide::okPulsado()
{
    operador = valor->value();
    close();
}


int Dialogo_Slide::resultado()
{
    return operador;
}

/*******************************************/
/***   INICIO CLASE DIALOGO SHRINK      ***/
/*******************************************/

Dialogo_Shrink::Dialogo_Shrink(QWidget *parent)
 : QDialog(parent)
{
    aux_mayor = 255;
    aux_menor = 0;

    text = new QLabel(tr("Seleccione limite superior:    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QDoubleSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(0.00, 255.00);
    valor->setValue(aux_mayor);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Seleccione limite inferior:    "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QDoubleSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0.00, 255.00);
    valor1->setValue(aux_menor);
    text1->setBuddy(valor1);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    mayorGrupo = new QGroupBox(tr("Limite superior"));
    mayorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    mayorGrupo->setLayout(datos);

    menorGrupo = new QGroupBox(tr("Limite inferior"));
    menorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    menorGrupo->setLayout(datos1);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(mayorGrupo);
    total->addSpacing(10);
    total->addWidget(menorGrupo);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Histogram Shrink"));
}


Dialogo_Shrink::~Dialogo_Shrink()
{

}

void Dialogo_Shrink::okPulsado()
{

        mayor = valor->value();
        menor = valor1->value();
        close();
}


float Dialogo_Shrink::resultado_mayor()
{
    return mayor;
}

float Dialogo_Shrink::resultado_menor()
{
    return menor;
}


/*******************************************/
/***   INICIO CLASE DIALOGO STRETCH      ***/
/*******************************************/

Dialogo_Stretch::Dialogo_Stretch(QWidget *parent)
 : QDialog(parent)
{
    aux_mayor = 255;
    aux_menor = 0;
    low_clip=0;
    high_clip=0;

    text = new QLabel(tr("Seleccione limite superior:    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QDoubleSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(0.00, 255.00);
    valor->setValue(aux_mayor);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Seleccione limite inferior:    "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QDoubleSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0.00, 255.00);
    valor1->setValue(aux_menor);
    text1->setBuddy(valor1);

    text2 = new QLabel(tr("Seleccione el porcentaje de valores inferior para recortar:    "));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QDoubleSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(0.00, 1.00);
    valor2->setValue(low_clip);
    text2->setBuddy(valor2);

    text3 = new QLabel(tr("Seleccione el porcentaje de valores superior para recortar:    "));
    text3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3 = new QDoubleSpinBox;
    valor3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3->setRange(0.00, 1.00);
    valor3->setValue(high_clip);
    text3->setBuddy(valor3);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    mayorGrupo = new QGroupBox(tr("Limite inferior"));
    mayorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    mayorGrupo->setLayout(datos);

    menorGrupo = new QGroupBox(tr("Limite superior"));
    menorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    menorGrupo->setLayout(datos1);

    menorClip = new QGroupBox(tr("Porcentaje inferior para recortar"));
    menorClip->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos2 = new QHBoxLayout;
    datos2->addWidget(text2);
    datos2->addWidget(valor2);
    menorClip->setLayout(datos2);

    mayorClip = new QGroupBox(tr("Porcentaje superior para recortar"));
    mayorClip->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos3 = new QHBoxLayout;
    datos3->addWidget(text3);
    datos3->addWidget(valor3);
    mayorClip->setLayout(datos3);


    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(mayorGrupo);
    total->addSpacing(10);
    total->addWidget(menorGrupo);
    total->addSpacing(15);
    total->addWidget(mayorClip);
    total->addSpacing(20);
    total->addWidget(menorClip);
    total->addSpacing(25);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Histogram Stretch"));
}


Dialogo_Stretch::~Dialogo_Stretch()
{

}

void Dialogo_Stretch::okPulsado()
{

        mayor = valor->value();
        menor = valor1->value();
        bajo = valor2->value();
        alto = valor3->value();
        close();
}


float Dialogo_Stretch::resultado_mayor()
{
    return mayor;
}

float Dialogo_Stretch::resultado_menor()
{
    return menor;
}

float Dialogo_Stretch::resultado_bajo()
{
    return bajo;
}

float Dialogo_Stretch::resultado_alto()
{
    return alto;
}

/*******************************************/
/***   INICIO CLASE DIALOGO ADAPTATIVE   ***/
/*******************************************/

Dialogo_Adaptative::Dialogo_Adaptative(QWidget *parent)
 : QDialog(parent)
{
    text = new QLabel(tr("Seleccione k1 (local gain factor multiplier):    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QDoubleSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(0.0, 1.0);
    valor->setValue(0.5);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Seleccione k2 (local mean multiplier):    "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QDoubleSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0.0, 1.0);
    valor1->setValue(1);
    text1->setBuddy(valor1);

    text2 = new QLabel(tr("Seleccione el tamaño del la ventana local:    "));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(1,30);
    valor2->setValue(11);
    text2->setBuddy(valor2);

    text3 = new QLabel(tr("Seleccione el valor minimo de ganacia local:    "));
    text3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3 = new QDoubleSpinBox;
    valor3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3->setRange(0, 20);
    valor3->setValue(0.5);
    text3->setBuddy(valor3);

    text4 = new QLabel(tr("Seleccione el valor maximo de ganacia local:    "));
    text4->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor4 = new QDoubleSpinBox;
    valor4->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor4->setRange(0, 100);
    valor4->setValue(10);
    text4->setBuddy(valor4);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    k1Grupo = new QGroupBox(tr("k1"));
    k1Grupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    k1Grupo->setLayout(datos);

    k2Grupo = new QGroupBox(tr("k2"));
    k2Grupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    k2Grupo->setLayout(datos1);

    sizeGrupo = new QGroupBox(tr("Tamaño de la ventana local"));
    sizeGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos2 = new QHBoxLayout;
    datos2->addWidget(text2);
    datos2->addWidget(valor2);
    sizeGrupo->setLayout(datos2);

    minGrupo = new QGroupBox(tr("Minimo ganancia local"));
    minGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos3 = new QHBoxLayout;
    datos3->addWidget(text3);
    datos3->addWidget(valor3);
    minGrupo->setLayout(datos3);

    maxGrupo = new QGroupBox(tr("Maximo ganancia local"));
    maxGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos4 = new QHBoxLayout;
    datos4->addWidget(text4);
    datos4->addWidget(valor4);
    maxGrupo->setLayout(datos4);


    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(k1Grupo);
    total->addSpacing(10);
    total->addWidget(k2Grupo);
    total->addSpacing(15);
    total->addWidget(sizeGrupo);
    total->addSpacing(20);
    total->addWidget(minGrupo);
    total->addSpacing(25);
    total->addWidget(maxGrupo);
    total->addSpacing(30);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Histogram Stretch"));
}


Dialogo_Adaptative::~Dialogo_Adaptative()
{

}

void Dialogo_Adaptative::okPulsado()
{

        k1 = valor->value();
        k2 = valor1->value();
        if(valor2->value()%2==0)
            size = valor2->value()+1;
        else
            size = valor2->value();
        min = valor3->value();
        max= valor4->value();
        close();
}


float Dialogo_Adaptative::resultado_k1()
{
    return k1;
}

float Dialogo_Adaptative::resultado_k2()
{
    return k2;
}

float Dialogo_Adaptative::resultado_size()
{
    return size;
}

float Dialogo_Adaptative::resultado_min()
{
    return min;
}
float Dialogo_Adaptative::resultado_max()
{
    return max;
}


/******************************************/
/***   INICIO CLASE DIALOGO COLORMAP    ***/
/******************************************/

Dialogo_ColorMap::Dialogo_ColorMap(QWidget *parent)
 : QDialog(parent)
{
    QWidget::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowMinMaxButtonsHint);


    text = new QLabel(tr("Seleccione un colormap:"));
    valor = new QSpinBox;
    valor->setRange(0, 11);
    valor->setValue(0);
    text->setBuddy(valor);

    textDesc = new QLabel(tr("Colormap 0 -> Autumn\n"
                             "Colormap 1 -> Bone\n"
                             "Colormap 2 -> Jet\n"
                             "Colormap 3 -> Winter\n"
                             "Colormap 4 -> Rainbow\n"
                             "Colormap 5 -> Ocean\n"
                             "Colormap 6 -> Summer\n"
                             "Colormap 7 -> Spring\n"
                             "Colormap 8 -> Cool\n"
                             "Colormap 9 -> Hsv\n"
                             "Colormap 10 -> Pink\n"
                             "Colormap 11 -> Hot"
                             ));

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addWidget(textDesc);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("ColorMap"));
}


Dialogo_ColorMap::~Dialogo_ColorMap()
{

}

void Dialogo_ColorMap::okPulsado()
{

    operador = valor->value();
    close();

}


int Dialogo_ColorMap::resultado()
{
    return operador;
}



/****************************************************/
/***   INICIO CLASE HIGH FREQUENCY EMPHASIS       ***/
/****************************************************/

Dialogo_High::Dialogo_High(QWidget *parent)
 : QDialog(parent)
{

    text = new QLabel(tr("Seleccione tamaño de bloque:    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(0, 100);
    valor->setValue(0);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Frecuencia de corte (cutoff):    "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0, 100);
    valor1->setValue(0);
    text1->setBuddy(valor1);

    text2 = new QLabel(tr("Orden de filtrado:    "));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(1, 8);
    valor2->setValue(1);
    text2->setBuddy(valor2);

    text3 = new QLabel(tr("Constante alfa:    "));
    text3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3 = new QDoubleSpinBox;
    valor3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3->setRange(1.0, 2.0);
    valor3->setValue(1.0);
    text3->setBuddy(valor3);

    recortar= new QCheckBox(tr("Mantener DC"));
    recortar->setLayoutDirection(Qt::RightToLeft);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    sizeGrupo = new QGroupBox(tr("Tamaño del bloque"));
    sizeGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    sizeGrupo->setLayout(datos);

    cutoffGrupo = new QGroupBox(tr("Cutoff"));
    cutoffGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    cutoffGrupo->setLayout(datos1);

    orderGrupo = new QGroupBox(tr("Orden de filtrado"));
    orderGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos2 = new QHBoxLayout;
    datos2->addWidget(text2);
    datos2->addWidget(valor2);
    orderGrupo->setLayout(datos2);

    alfaGrupo = new QGroupBox(tr("Alfa"));
    alfaGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos3 = new QHBoxLayout;
    datos3->addWidget(text3);
    datos3->addWidget(valor3);
    alfaGrupo->setLayout(datos3);


    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(sizeGrupo);
    total->addSpacing(10);
    total->addWidget(cutoffGrupo);
    total->addSpacing(15);
    total->addWidget(alfaGrupo);
    total->addSpacing(20);
    total->addWidget(orderGrupo);
    total->addSpacing(25);
    total->addWidget(recortar);
    total->addSpacing(30);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("High frequency filter"));
}


Dialogo_High::~Dialogo_High()
{

}

void Dialogo_High::okPulsado()
{

        Qt::CheckState state1;
        state1 = recortar->checkState();

        size = valor->value();
        cutoff = valor1->value();
        order = valor2->value();
        alfa = valor3->value();
        if(state1==Qt::Checked)
            dc=TRUE;
        else
            dc=FALSE;
        close();

}

int Dialogo_High::resultado_size()
{
    return size;
}

int Dialogo_High::resultado_cutoff()
{
    return cutoff;
}

int Dialogo_High::resultado_order()
{
    return order;
}

float Dialogo_High::resultado_alfa()
{
    return alfa;
}

bool Dialogo_High::resultado_dc()
{
    return dc;
}

/***********************************************/
/***  INICIO CLASE DIALOGO HISTOGRAM SLIDE   ***/
/***********************************************/

Dialogo_Moravec::Dialogo_Moravec(QWidget *parent)
 : QDialog(parent)
{

    text = new QLabel(tr("Seleccione umbral:"));
    valor = new QDoubleSpinBox;
    valor->setRange(0.0, 100.0);
    valor->setValue(0);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Moravec Filter"));
}


Dialogo_Moravec::~Dialogo_Moravec()
{

}

void Dialogo_Moravec::okPulsado()
{
    operador = valor->value();
    close();
}


float Dialogo_Moravec::resultado()
{
    return operador;
}

/**************************************/
/***  INICIO CLASE DIALOGO SMOOTH   ***/
/**************************************/

Dialogo_Smooth::Dialogo_Smooth(QWidget *parent)
 : QDialog(parent)
{

    text = new QLabel(tr("Seleccione kernel:"));
    valor = new QSpinBox;
    valor->setRange(1, 99);
    valor->setValue(1);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Smooth Filter"));
}


Dialogo_Smooth::~Dialogo_Smooth()
{

}

void Dialogo_Smooth::okPulsado()
{
    if(valor->value()%2==0)
        operador = valor->value()+1;
    else
        operador = valor->value();
    close();
}


int Dialogo_Smooth::resultado()
{
    return operador;
}

/**************************************/
/***  INICIO CLASE DIALOGO SMOOTH   ***/
/**************************************/

Dialogo_Kuwahara::Dialogo_Kuwahara(QWidget *parent)
 : QDialog(parent)
{

    text = new QLabel(tr("Seleccione tamaño de la ventana de filtrado:"));
    valor = new QSpinBox;
    valor->setRange(1, 99);
    valor->setValue(1);
    text->setBuddy(valor);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);

    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addLayout(datos);
    total->addSpacing(15);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Kuwahara Filter"));
}


Dialogo_Kuwahara::~Dialogo_Kuwahara()
{

}

void Dialogo_Kuwahara::okPulsado()
{
   operador = valor->value();
    close();
}


int Dialogo_Kuwahara::resultado()
{
    return operador;
}

/*******************************************/
/***   INICIO CLASE DIALOGO HOMOMORPHIC  ***/
/*******************************************/

Dialogo_Homomorphic::Dialogo_Homomorphic(QWidget *parent)
 : QDialog(parent)
{

    text = new QLabel(tr("Seleccione la mayor frecuencia de ganancia (Higher Frequency Gain):    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QDoubleSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(1.10, 3.00);
    valor->setValue(1.10);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Seleccione la menor frecuencia de ganancia (Lower Frequency Gain):     "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QDoubleSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0.10, 0.95);
    valor1->setValue(0.10);
    text1->setBuddy(valor1);

    text2 = new QLabel(tr("Seleccione la frecuencia de corte (cutoff):    "));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(1, 100);
    valor2->setValue(1);
    text2->setBuddy(valor2);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    upperGrupo = new QGroupBox(tr("Higher Frequency Gain"));
    upperGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    upperGrupo->setLayout(datos);

    lowerGrupo = new QGroupBox(tr("Lower Frequency Gain"));
    lowerGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    lowerGrupo->setLayout(datos1);

    cutoffGrupo = new QGroupBox(tr("Cutoff"));
    cutoffGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos2 = new QHBoxLayout;
    datos2->addWidget(text2);
    datos2->addWidget(valor2);
    cutoffGrupo->setLayout(datos2);



    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(upperGrupo);
    total->addSpacing(10);
    total->addWidget(lowerGrupo);
    total->addSpacing(15);
    total->addWidget(cutoffGrupo);
    total->addSpacing(20);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Homomorphic Filter"));
}


Dialogo_Homomorphic::~Dialogo_Homomorphic()
{

}

void Dialogo_Homomorphic::okPulsado()
{

        upper = valor->value();
        lower = valor1->value();
        cutoff = valor2->value();
        close();
}


float Dialogo_Homomorphic::resultado_upper()
{
    return upper;
}

float Dialogo_Homomorphic::resultado_lower()
{
    return lower;
}

int Dialogo_Homomorphic::resultado_cutoff()
{
    return cutoff;
}


/*******************************************/
/***   INICIO CLASE DIALOGO UNSHARP      ***/
/*******************************************/

Dialogo_Unsharp::Dialogo_Unsharp(QWidget *parent)
 : QDialog(parent)
{
    text = new QLabel(tr("Seleccione limite superior (histogram shrink):    "));
    text->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor = new QSpinBox;
    valor->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor->setRange(1, 255);
    valor->setValue(255);
    text->setBuddy(valor);


    text1 = new QLabel(tr("Seleccione limite inferior (histogram shrink):    "));
    text1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1 = new QSpinBox;
    valor1->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor1->setRange(0, 254);
    valor1->setValue(0);
    text1->setBuddy(valor1);

    text2 = new QLabel(tr("Seleccione el porcentaje de valores inferior para recortar:    "));
    text2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2 = new QDoubleSpinBox;
    valor2->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor2->setRange(0.00, 1.00);
    valor2->setValue(0.00);
    text2->setBuddy(valor2);

    text3 = new QLabel(tr("Seleccione el porcentaje de valores superior para recortar:    "));
    text3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3 = new QDoubleSpinBox;
    valor3->setFont(QFont("Ubuntu", 11, QFont::Normal));
    valor3->setRange(0.00, 1.00);
    valor3->setValue(0.00);
    text3->setBuddy(valor3);

    ok = new QPushButton(tr("Aceptar"));

    connect(ok, SIGNAL(clicked()), this, SLOT(okPulsado()));

    mayorGrupo = new QGroupBox(tr("Limite superior"));
    mayorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos = new QHBoxLayout;
    datos->addWidget(text);
    datos->addWidget(valor);
    mayorGrupo->setLayout(datos);

    menorGrupo = new QGroupBox(tr("Limite inferior"));
    menorGrupo->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos1 = new QHBoxLayout;
    datos1->addWidget(text1);
    datos1->addWidget(valor1);
    menorGrupo->setLayout(datos1);

    menorClip = new QGroupBox(tr("Porcentaje inferior para recortar"));
    menorClip->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos2 = new QHBoxLayout;
    datos2->addWidget(text2);
    datos2->addWidget(valor2);
    menorClip->setLayout(datos2);

    mayorClip = new QGroupBox(tr("Porcentaje superior para recortar"));
    mayorClip->setFont(QFont("Ubuntu", 11, QFont::Bold));
    datos3 = new QHBoxLayout;
    datos3->addWidget(text3);
    datos3->addWidget(valor3);
    mayorClip->setLayout(datos3);


    botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(ok);

    total = new QVBoxLayout;
    total->addSpacing(5);
    total->addWidget(mayorGrupo);
    total->addSpacing(10);
    total->addWidget(menorGrupo);
    total->addSpacing(15);
    total->addWidget(mayorClip);
    total->addSpacing(20);
    total->addWidget(menorClip);
    total->addSpacing(25);
    total->addLayout(botones);
    setLayout(total);

    setWindowTitle(tr("Unsharp Filter"));
}


Dialogo_Unsharp::~Dialogo_Unsharp()
{

}

void Dialogo_Unsharp::okPulsado()
{

        mayor = valor->value();
        menor = valor1->value();
        bajo = valor2->value();
        alto = valor3->value();
        close();
}


int Dialogo_Unsharp::resultado_mayor()
{
    return mayor;
}

int Dialogo_Unsharp::resultado_menor()
{
    return menor;
}

float Dialogo_Unsharp::resultado_bajo()
{
    return bajo;
}

float Dialogo_Unsharp::resultado_alto()
{
    return alto;
}
