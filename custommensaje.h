#ifndef CUSTOMMENSAJE_H
#define CUSTOMMENSAJE_H

#include <QDialog>




class custommensaje: QDialog{


 public:
    explicit custommensaje(QString , QString, bool, QWidget *parent);
    explicit custommensaje(QString,  QWidget *parent);
private:
    void centrar(QWidget *parent);
    int ancho=0, alto=0;






};


#endif // CUSTOMMENSAJE_H
