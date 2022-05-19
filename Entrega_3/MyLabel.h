#include <QLabel>

class MyLabel:public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent);
    int cont = 0;
    int total = 0;
    
public slots:
    void bolaRebuda();
    void SeleccionaChild();
    void bolaRebudaArrel();
    void reset();
    void Counter();
    void Total();
    void ResetArrel();
    void resetCont();
    void resetContTotal();
signals:
    void Child1();
    void Child2();
    void resetall();
};
    
