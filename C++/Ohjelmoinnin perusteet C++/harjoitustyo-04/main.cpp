#include "mainwindow.hh"
#include <QApplication>

// --------------------------------------------------
// Tekijä: Antti Ruhala
// antti.ruhala@student.tut.fi
// osana Ohjelmoinnin peruskurssia TIE-02200
// --------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
