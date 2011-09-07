#ifndef EDYTUJCENY_H
#define EDYTUJCENY_H

#include <QDialog>

namespace Ui {
    class edytujCeny;
}

class edytujCeny : public QDialog
{
    Q_OBJECT

public:
    explicit edytujCeny(QWidget *parent = 0);
    ~edytujCeny();

    float cenaPaspartu;
    float cenaKlejenia;
    float cenaSzkloFloat;
    float cenaAntyrefleks;
    float cenaPodporki;
    float cenaDodatkowa;
    float cenaLustra;

private:
    Ui::edytujCeny *ui;

private slots:
    void on_przyciski_accepted();

signals:
    void zapisanoCeny();
};

#endif // EDYTUJCENY_H
