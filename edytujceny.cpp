#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "edytujceny.h"
#include "ui_edytujceny.h"

edytujCeny::edytujCeny(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edytujCeny)
{
    ui->setupUi(this);
    show();

    //wczytujemy pliczek
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
                ui->editSzkloFloat->setText(line);
            } else if( line.contains("#SZKLO ANTYREFLEKS") ){
                line = strim.readLine();
                cenaAntyrefleks=line.toFloat();
                ui->editSzkloAnty->setText(line);
            } else if ( line.contains("#PASPARTU") ){
                line = strim.readLine();
                cenaPaspartu=line.toFloat();
                ui->editPaspartu->setText(line);
            } else if ( line.contains("#LUSTRO") ){
                line = strim.readLine();
                cenaLustra=line.toFloat();
                ui->editLustro->setText(line);
            } else if ( line.contains("#KLEJENIE") ){
                line = strim.readLine();
                cenaKlejenia=line.toFloat();
                ui->editKlejenie->setText(line);
            } else if ( line.contains("#PODPORKA") ){
                line = strim.readLine();
                cenaPodporki=line.toFloat();
                ui->editPodporka->setText(line);
            } else if ( line.contains("#DODATKOWO") ){
                line = strim.readLine();
                cenaDodatkowa=line.toFloat();
                ui->editDodatkowo->setText(line);
            }
        }
        file.close();
    } else {
        setDisabled(true);
        QMessageBox::critical(this, tr("Blad!"),tr("Nie odnaleziono pliku z cenami (ceny.txt)!"));
    }
}

edytujCeny::~edytujCeny()
{
    delete ui;
}

void edytujCeny::on_przyciski_accepted()
{
    //zapisujemy plik
    QString fileName = "ceny.txt";
    QFile file(fileName);
    if ( file.open(QIODevice::WriteOnly) ) {
        QTextStream strim( &file );
        strim << "#PLIK ZAWIERAJACY CENY, PROSZE NIE EDYTOWAC!" << endl;
        strim << "#SZKLO FLOAT" << endl;
        strim << ui->editSzkloFloat->text() << endl;
        strim << "#SZKLO ANTYREFLEKS" << endl;
        strim << ui->editSzkloAnty->text() << endl;
        strim << "#LUSTRO" << endl;
        strim << ui->editLustro->text() << endl;
        strim << "#PASPARTU" << endl;
        strim << ui->editPaspartu->text() << endl;
        strim << "#KLEJENIE" << endl;
        strim << ui->editKlejenie->text() << endl;
        strim << "#PODPORKA" << endl;
        strim << ui->editPodporka->text() << endl;
        strim << "#DODATKOWO" << endl;
        strim << ui->editDodatkowo->text() << endl;
        file.close();
        emit zapisanoCeny();
    } else {
        QMessageBox::critical(this, tr("Blad!"),tr("Nie odnaleziono pliku z cenami (ceny.txt)!"));
    }
}
