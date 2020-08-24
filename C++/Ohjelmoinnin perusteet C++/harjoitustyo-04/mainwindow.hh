#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

// --------------------------------------------------
// Tekijä: Antti Ruhala
// antti.ruhala@student.tut.fi
// osana Ohjelmoinnin peruskurssia TIE-02200
// --------------------------------------------------


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void nollaa_kaikki_arvot();

    void laskeBMI();

    void tulkinta();

    void miessukupuoli();

    void naissukupuoli();

private:
    Ui::MainWindow *ui;

    int sukupuoli_ = 0;

};

#endif // MAINWINDOW_HH
