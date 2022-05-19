#include "MyLabel.h"

MyLabel::MyLabel(QWidget *parent=0):QLabel(parent)
{
}

void MyLabel::bolaRebuda() {
        setText("o");
        SeleccionaChild();  
}

void MyLabel::bolaRebudaArrel() {
    emit resetall();
    setText("o");
    SeleccionaChild();
}

void MyLabel::ResetArrel() {
    emit resetall();
    setText("-");
}

void MyLabel::reset() {
    setText("-");
}

void MyLabel::resetCont() {
    cont = 0;
    setText("0");
}

void MyLabel::resetContTotal() {
    total = 0;  
    setText("Boles Llençades : 0");
}

void MyLabel::SeleccionaChild() {
    int c = rand() %10 +1;
    if (c >5) emit Child1();
    else emit Child2();
}

void MyLabel::Counter() {
    setText(QString("%1").arg(++cont));
}

void MyLabel::Total() {
    setText(QString("Boles Llençades : %1").arg(++total));
}