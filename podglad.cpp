#include "podglad.h"

#include <QPainter>

podglad::podglad(QWidget *parent) :
    QWidget(parent)
{
    rozmiar=390;//390
    obrazSzer=0,obrazWys=0,paspartu=0,ramka=0;
    skala=1;
    szklo=1;
}

void podglad::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    QPen pen(QColor(0,0,0,100),2);
    painter.setPen(pen);

    int srodek=390/2;
    if( ramka>0 ){
        painter.fillRect(srodek-(obrazSzer/2+paspartu+ramka),srodek-(obrazWys/2+paspartu+ramka)
                         ,obrazSzer+2*paspartu+2*ramka,obrazWys+2*paspartu+2*ramka,QColor(130,51,0));
        painter.drawRect(srodek-(obrazSzer/2+paspartu+ramka),srodek-(obrazWys/2+paspartu+ramka)
                         ,obrazSzer+2*paspartu+2*ramka,obrazWys+2*paspartu+2*ramka);
    }
    if( paspartu>0 ){
        painter.fillRect(srodek-(obrazSzer/2+paspartu),srodek-(obrazWys/2+paspartu)
                         ,obrazSzer+2*paspartu,obrazWys+2*paspartu,QColor(255,205,170));
        painter.drawRect(srodek-(obrazSzer/2+paspartu),srodek-(obrazWys/2+paspartu)
                         ,obrazSzer+2*paspartu,obrazWys+2*paspartu);
    }
    if( obrazSzer>0 && obrazWys>0 ){
        //painter.fillRect(srodek-obrazSzer/2,srodek-obrazWys/2,obrazSzer,obrazWys,QColor(120,255,120));
        painter.fillRect(srodek-obrazSzer/2,srodek-obrazWys/2,obrazSzer,obrazWys,QColor(255,255,255));
        painter.drawRect(srodek-obrazSzer/2,srodek-obrazWys/2,obrazSzer,obrazWys);
    }
    if( szklo>0 ){
        if( paspartu>0 ){
            QRect myQRect(srodek-(obrazSzer/2+paspartu),srodek-(obrazWys/2+paspartu)
                          ,obrazSzer+2*paspartu,obrazWys+2*paspartu);
            QLinearGradient gradient(myQRect.topLeft(), myQRect.bottomRight()); // diagonal gradient from top-left to bottom-right
            if(szklo==1){
                gradient.setColorAt(0, QColor(100,100,255,100));
                gradient.setColorAt(0.3, QColor(255,255,255,150));
                gradient.setColorAt(0.4, QColor(255,255,255,250));
                gradient.setColorAt(0.5, QColor(255,255,255,150));
                gradient.setColorAt(1, QColor(100,100,255,100));
            } else {
                gradient.setColorAt(0, QColor(255,255,255,150));
                gradient.setColorAt(1, QColor(100,100,255,150));
            }
            painter.fillRect(myQRect, gradient);
            //jesli antyrefleks
            if( szklo==2 ){
                QBrush brusz(QColor(0,0,0,30),Qt::Dense5Pattern);
                painter.setBrush(brusz);
                painter.setPen(Qt::NoPen);
                painter.drawRect(myQRect);
            }
        } else if( obrazSzer>0 && obrazWys>0 ){
            QRect myQRect(srodek-obrazSzer/2,srodek-obrazWys/2,obrazSzer,obrazWys);
            QLinearGradient gradient(myQRect.topLeft(), myQRect.bottomRight()); // diagonal gradient from top-left to bottom-right
            if(szklo==1){
                gradient.setColorAt(0, QColor(100,100,255,100));
                gradient.setColorAt(0.3, QColor(255,255,255,150));
                gradient.setColorAt(0.4, QColor(255,255,255,250));
                gradient.setColorAt(0.5, QColor(255,255,255,150));
                gradient.setColorAt(1, QColor(100,100,255,100));
            } else {
                gradient.setColorAt(0, QColor(255,255,255,150));
                gradient.setColorAt(1, QColor(100,100,255,150));
            }
            painter.fillRect(myQRect, gradient);
            //jesli antyrefleks
            if( szklo==2 ){
                QBrush brusz(QColor(0,0,0,30),Qt::Dense5Pattern);
                painter.setBrush(brusz);
                painter.setPen(Qt::NoPen);
                painter.drawRect(myQRect);
            }
            //painter.fillRect(srodek-obrazSzer/2,srodek-obrazWys/2,obrazSzer,obrazWys,QColor(120,255,120));
        }
    }


}

void podglad::ustawWymiary(float oWys, float oSzer, float pas, float ramk, int szk){
    if(oWys>oSzer){
        skala = (rozmiar)/(oWys*100+2*pas*100+2*ramk);
    } else {
        skala = (rozmiar)/(oSzer*100+2*pas*100+2*ramk);
    }
    obrazWys=oWys*100*skala;
    obrazSzer=oSzer*100*skala;
    paspartu=pas*100*skala;
    ramka=ramk*skala;
    szklo=szk;
    repaint();
}
