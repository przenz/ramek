#ifndef PODGLAD_H
#define PODGLAD_H

#include <QWidget>

class podglad : public QWidget
{
    Q_OBJECT
public:
    explicit podglad(QWidget *parent = 0);

private:
    float obrazWys,obrazSzer,paspartu,ramka;
    int rozmiar,skala,szklo;

protected:
   void paintEvent(QPaintEvent *);

signals:

public slots:
   void ustawWymiary(float oWys, float oSzer, float pas, float ramk, int szk);

};

#endif // PODGLAD_H
