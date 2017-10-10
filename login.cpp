#include "login.h"
#include "ui_login.h"
#include <gui_jugador.h>
#include <QSqlQuery>
#include <QMessageBox>
#include <menu.h>
#include <QSqlError>
#include <QDebug>
#include <leer_texto.h>
#include <gui_pais.h>
#include <QPixmap>
#include <juego_1.h>
#include <imagenes_model.h>
#include <custommensaje.h>

#include <QDesktopWidget>
#include <QRect>
#include <QPoint>


login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
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


 QRect qr1= ui->widget->geometry();
 int px1  = (ancho/2) - (qr1.width()/2);
  int py1 = (ancho/2) - ( qr1.height()/2);
 ui->widget->setGeometry(px1, py1, ui->widget->size().width(), alto);

}

login::~login()
{
    delete ui;
}


void login::crearJugador(){
    gui_jugador *j= new gui_jugador;
    j->show();
}


void login::loguear(){
//juego_1 ju; qDebug() << ju.GetRandomNumber(10,20);
 //gui_pais gp; gp.registrar();

QSqlQuery log;
log.exec("select jug_pass from jugadores where jug_login= '"+  ui->txt_usu->text()  +"'");


if( log.next()){
QString pass= ui->txt_clave->text();
QString pas= log.value(0).toString();

if( pass == pas ){  this->close();  menu *men= new menu( 0, ui->txt_usu->text()); men->show(); }
else{
  (void)(new custommensaje( "incorrecto.png",  "Clave incorrecta" , true, this ) );
}

}else{
(void)(new custommensaje( "unknown.png",  "El jugador -->"+ ui->txt_usu->text() + "<-- no existe"+log.lastError().text()  , true, this ) );

}

}
