#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    show();
    wczytajCeny();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wczytajCeny(){
    //wczytujemy ceny
    QString fileName = "ceny.txt";
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly) ){
        QString line;
        QTextStream strim( &file );
        while( !strim.atEnd() ){
            line = strim.readLine();
            if( line.contains("#SZKLO FLOAT") ){
                line = strim.readLine();
                cenaSzkloFloat=line.toFloat();
            } else if( line.contains("#SZKLO ANTYREFLEKS") ){
                line = strim.readLine();
                cenaAntyrefleks=line.toFloat();
            } else if ( line.contains("#PASPARTU") ){
                line = strim.readLine();
                cenaPaspartu=line.toFloat();
            } else if ( line.contains("#LUSTRO") ){
                line = strim.readLine();
                cenaLustra=line.toFloat();
            } else if ( line.contains("#KLEJENIE") ){
                line = strim.readLine();
                cenaKlejenia=line.toFloat();
            } else if ( line.contains("#PODPORKA") ){
                line = strim.readLine();
                cenaPodporki=line.toFloat();
            } else if ( line.contains("#DODATKOWO") ){
                line = strim.readLine();
                cenaDodatkowa=line.toFloat();
            }
        }
        file.close();
        obliczCene();
    } else {
        setDisabled(true);
        QMessageBox::critical(this, tr("Blad!"),tr("Nie odnaleziono pliku z cenami (ceny.txt)!"));
    }
}

void MainWindow::wczytajEdytowaneCeny(){
    cenaAntyrefleks = cenyDialog->cenaAntyrefleks;
    cenaDodatkowa = cenyDialog->cenaDodatkowa;
    cenaKlejenia = cenyDialog->cenaKlejenia;
    cenaLustra = cenyDialog->cenaLustra;
    cenaPaspartu = cenyDialog->cenaPaspartu;
    cenaPodporki = cenyDialog->cenaPodporki;
    cenaSzkloFloat = cenyDialog->cenaSzkloFloat;
    obliczCene();
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

    /*
    cenaPaspartu = 100;
    cenaKlejenia = 30;
    cenaSzkloFloat = 58;
    cenaAntyrefleks = 78;
    cenaPodporki = 5;
    cenaDodatkowa = 0;
    */

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
    } else if( ui->radioLustro->isChecked() ){
        cenaMetra+=cenaLustra;
        switchSzklo=3;
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

    //klejenie za metr^2
    if( ui->checkKlejenie->isChecked() ) cenaMetra+=cenaKlejenia;

    //podporka
    if( ui->checkPodporka->isChecked() ) cenaOpcje+=cenaPodporki;

    //obliczanie ceny
    cena = (powierzchnia*cenaMetra)+cenaRamki+cenaOpcje+cenaDodatkowa;

    ui->textCena->setText(QString::number(cena, 'g', 4));

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

void MainWindow::on_actionEdytuj_ceny_triggered()
{
    cenyDialog = new edytujCeny(this);
    connect(cenyDialog,SIGNAL(zapisanoCeny()),this,SLOT(wczytajCeny()));
}

void MainWindow::on_wyczyscButton_clicked()
{
    ui->checkKlejenie->setChecked(false);
    ui->checkPodporka->setChecked(false);
    ui->radioSzkloFloat->setChecked(true);
    ui->editRamkaCena->clear();
    ui->editRamkaSzer->clear();
    ui->editPaspartu->clear();
    ui->editObrazWys->clear();
    ui->editObrazSzer->clear();

    ui->editObrazWys->setFocus();

    obliczCene();
}


