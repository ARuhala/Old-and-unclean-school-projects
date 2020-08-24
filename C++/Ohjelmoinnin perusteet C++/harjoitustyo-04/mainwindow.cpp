#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QString>
#include <string>
#include <iomanip>
#include <sstream>
#include <QActionGroup>

// --------------------------------------------------
// Tekijä: Antti Ruhala
// antti.ruhala@student.tut.fi
// osana Ohjelmoinnin peruskurssia TIE-02200
// --------------------------------------------------


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Lopetanapin toiminnallisuus
    connect(ui->Lopeta, SIGNAL(triggered(bool)), this, SLOT(close()));
    // Alkutilanapin toiminnallisuus
    connect(ui->Alkutila, SIGNAL(triggered(bool)), this, SLOT(nollaa_kaikki_arvot()));

    // BMI laskentatuloksen asettaminen aina arvojen muuttuessa
    connect(ui->cmslider, SIGNAL(valueChanged(int)), this, SLOT(laskeBMI()));
    connect(ui->kgslider, SIGNAL(valueChanged(int)), this, SLOT(laskeBMI()));

    // BMI tulkinnan muuttaminen BMI muuttuessa

    connect(ui->cmslider, SIGNAL(valueChanged(int)), this, SLOT(tulkinta()));
    connect(ui->kgslider, SIGNAL(valueChanged(int)), this, SLOT(tulkinta()));

    // Sukupuolivalikon toiminnallisuus
    connect(ui->Nainen, SIGNAL(triggered(bool)), this, SLOT(naissukupuoli()));
    connect(ui->Mies, SIGNAL(triggered(bool)), this, SLOT(miessukupuoli()));

    // alustetaan sukupuolivalikon checked osoittamaan naiseen
    ui->Nainen->setChecked(true);


    


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nollaa_kaikki_arvot()
{
    // Alkutilanapin toiminnallisuusfunktio
    // tämä funktio nollaa sliderien arvot

    ui->kgslider->setValue(0);
    ui->cmslider->setValue(0);

    ui->painoindeksi->setText( QString::fromStdString("-") );
    ui->tulkinta->setText(  QString::fromStdString("-") );

    // nollataan sukupuoliasetus oletusasetukseksi
    naissukupuoli();
}



void MainWindow::laskeBMI()
{
    // Tämä funktio laskee painoideksin BMI ja asettaa sen painoindeksin dataksi

    // jos yksikin slidereista on arvossa nolla, asetetaan BMI " - ", eikä ruveta tekemään mitään nollallajakamisia
    if (( ui->kgslider->value() == 0 ) or ( ui->cmslider->value() == 0 )) {
        ui->painoindeksi->setText(  QString::fromStdString("-")  );
        ui->tulkinta->setText(  QString::fromStdString("-") );
    }

    // muussa tapauksessa voidaan laskea ja asettaa painoideksi BMI
    else {
        double paino = ui->kgslider->value();
        double syotepituus =ui->cmslider->value();
        double pituus = syotepituus / 100;

        double bmi = paino / ( pituus * pituus );

        stringstream stream;
        stream <<  setprecision(6) << bmi;
        string bmiteksti = stream.str();

        ui->painoindeksi->setText( QString::fromStdString(bmiteksti) );

    }

}

void MainWindow::tulkinta()
{
    // tämä funktio kirjoittaa sanallisen tulkinnan BMI:stä, sukupuolesta riippuen

    // otetaan BMI arvo talteen, jos se ei ole "-"
    if (ui->painoindeksi->text() != "-") {
        double BMI = stod( ui->painoindeksi->text().toStdString() );

        // sukupuoli 0 tarkoittaa naista
       if (sukupuoli_ == 0) {


           if (BMI <= 19.1) {
               ui->tulkinta->setText(  QString::fromStdString("alipainoa")  );

           }

           else if (BMI > 19.1 and BMI <=25.8) {
               ui->tulkinta->setText(  QString::fromStdString("normaali")  );
           }

           else if (BMI > 25.8 and BMI <=27.3) {
               ui->tulkinta->setText(  QString::fromStdString("lievää ylipainoa")  );
           }
           else if (BMI > 27.3 and BMI <=32.2) {
               ui->tulkinta->setText(  QString::fromStdString("ylipainoa")  );
           }
           else if (BMI > 32.2) {
               ui->tulkinta->setText(  QString::fromStdString("paljon ylipainoa")  );

           }

       }

       // sukupuoli 1, tarkoittaa miestä, nyt lähinnä nollasta poikkeava
       else {


           if (BMI <= 20.7) {
               ui->tulkinta->setText(  QString::fromStdString("alipainoa")  );

           }

           else if (BMI > 20.7 and BMI <=26.4) {
               ui->tulkinta->setText(  QString::fromStdString("normaali")  );
           }

           else if (BMI > 26.4 and BMI <=27.8) {
               ui->tulkinta->setText(  QString::fromStdString("lievää ylipainoa")  );
           }
           else if (BMI > 27.8 and BMI <=31.1) {
               ui->tulkinta->setText(  QString::fromStdString("ylipainoa")  );
           }
           else if (BMI > 31.1) {
               ui->tulkinta->setText(  QString::fromStdString("paljon ylipainoa")  );

           }


    }



   }
    // muutetaan tulkinta takaisin "-", siltä varalta, että se ei sitä ole, vaikka painoindeksi on "-"
    else {
        ui->tulkinta->setText(   QString::fromStdString("-")  );
    }
}

void MainWindow::miessukupuoli()
{
    // tämä funktio asettaa miessukupuoleen liittyviä arvoja, ja pyöräyttää BMI tulkinnan läpi varmuuden vuoksi
    // jos satutaan olemaan sellaisella alueella, jossa arvo muuttuisi
    sukupuoli_ = 1;
    ui->Sukupuolidata->setText( QString::fromStdString("Mies") );
    ui->Mies->setChecked(true);
    ui->Nainen->setChecked(false);
    tulkinta();



}

void MainWindow::naissukupuoli()
{
    // tämä funktio asettaa naissukupuoleen liittyviä arvoja, ja pyöräyttää BMI tulkinnan läpi varmuuden vuoksi
    // jos satutaan olemaan sellaisella alueella, jossa arvo muuttuisi
    sukupuoli_ = 0;
    ui->Sukupuolidata->setText( QString::fromStdString("Nainen") );
    ui->Nainen->setChecked(true);
    ui->Mies->setChecked(false);
    tulkinta();
}




