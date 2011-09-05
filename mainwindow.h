#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "edytujceny.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    float cenaPaspartu;
    float cenaKlejenia;
    float cenaSzkloFloat;
    float cenaAntyrefleks;
    float cenaPodporki;
    float cenaDodatkowa;
    float cenaLustra;

private:
    Ui::MainWindow *ui;
    edytujCeny *cenyDialog;

private slots:
    void on_actionEdytuj_ceny_triggered();
    void on_wyczyscButton_clicked();
    void on_actionOprogramie_triggered();
    void on_actionZako_triggered();
    void obliczCene();
    void wczytajCeny();
    void wczytajEdytowaneCeny();
};

#endif // MAINWINDOW_H
