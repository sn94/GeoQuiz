#include "cargador.h"
#include "ui_cargador.h"
#include <QTimer>
#include <login.h>
#include <QDesktopWidget>


Cargador::Cargador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cargador)
{
    ui->setupUi(this);
    /** Centrar **/
 QRect geo_ori= this->geometry();
 int ancho= geo_ori.width();
 int alto= geo_ori.height();

 QDesktopWidget *deskw= QApplication::desktop();
 QRect rectas= deskw->screenGeometry();
 int px  = (rectas.width()/2) - (ancho/2);
  int py = (rectas.height()/2) - ( alto/2);
 this->move( QPoint(px, py )  );
/** **/


    ui->progressBar->setRange(0, 5);
    ui->progressBar->setValue( 0);
    this->crono();
}

Cargador::~Cargador()
{
    delete ui;
}


void Cargador::crono(){
 timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    timer->start(1000);
}

void  Cargador::updateCaption(){
if( this->contador <= 5  )    {
        this->contador ++;
        ui->progressBar->setValue( this->contador );
    }
    else
    {
        timer->stop();
        delete timer;
         ui->progressBar->setValue( this->contador );
         this->close();
         login *lo= new login;  lo->show();

    }

}
