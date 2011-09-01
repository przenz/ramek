#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::obliczCene(){
    float cena=0;
    float powierzchnia=0;
    float cenaMetra=0;
    float cenaOpcje=0;
    float cenaRamki=0;

    float obrazWysokosc=0;
    float obrazSzerokosc=0;
    float paspartu=0;
    float ramkaSzer=0;

    float cenaPaspartu = 100;
    float cenaKlejenia = 30;
    float cenaSzkloFloat = 58;
    float cenaAntyrefleks = 78;
    float cenaPodporki = 5;

    if( ui->editPaspartu->text().isEmpty() ){
        //jesli NIE mamy paspartu
        if( !ui->editObrazSzer->text().isEmpty() && !ui->editObrazWys->text().isEmpty() ){
            obrazWysokosc = ui->editObrazWys->text().toFloat()/100;
            obrazSzerokosc = ui->editObrazSzer->text().toFloat()/100;
            powierzchnia = (obrazSzerokosc) * (obrazWysokosc);
        }
    } else {
        //jesli mamy paspartu
        if( !ui->editObrazSzer->text().isEmpty() && !ui->editObrazWys->text().isEmpty() ){
            obrazWysokosc = ui->editObrazWys->text().toFloat()/100;
            obrazSzerokosc = ui->editObrazSzer->text().toFloat()/100;
            paspartu = ui->editPaspartu->text().toFloat()/100;
            powierzchnia = ((obrazSzerokosc+(2*paspartu)))*((obrazWysokosc+(2*paspartu)));
            cenaMetra+=cenaPaspartu;
        }
    }

    //szklo
    int switchSzklo=0;
    if( ui->radioSzkloFloat->isChecked() ) {
        cenaMetra+=cenaSzkloFloat;
        switchSzklo=1;
    } else if( ui->radioSzkloAnty->isChecked() ){
        cenaMetra+=cenaAntyrefleks;
        switchSzklo=2;
    } else {
        switchSzklo=0;
    }

    //ramka
    if( !ui->editRamkaSzer->text().isEmpty() && !ui->editRamkaCena->text().isEmpty() ){
        ramkaSzer=ui->editRamkaSzer->text().toFloat();
        float calaSzerokosc = obrazSzerokosc+(paspartu*2)+(2*ramkaSzer/100);
        float calaWysokosc = obrazWysokosc+(paspartu*2)+(2*ramkaSzer/100);

        cenaRamki=2*(calaSzerokosc+calaWysokosc)*ui->editRamkaCena->text().toFloat();
    }

    //klejenie 30zl za metr^2
    if( ui->checkKlejenie->isChecked() ) cenaMetra+=cenaKlejenia;

    //podporka 5z³
    if( ui->checkPodporka->isChecked() ) cenaOpcje+=cenaPodporki;

    //obliczanie ceny
    cena = (powierzchnia*cenaMetra)+cenaRamki+cenaOpcje;

    ui->textCena->setText(QString::number(cena, 'g', 4)+tr(" zl"));

    ui->wizualizacja->ustawWymiary(obrazWysokosc,obrazSzerokosc,paspartu,ramkaSzer,switchSzklo);
}

void MainWindow::on_actionZako_triggered()
{
    qApp->exit(0);
}

void MainWindow::on_actionOprogramie_triggered()
{
    QMessageBox::information(this, tr("O programie"),tr("Program dedykuje mojej Kochanej Esterce :) \n - Mateusz"));
}
