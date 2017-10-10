#include "gui_jugador.h"
#include "ui_gui_jugador.h"
#include "conexion.h"
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <jugador_model.h>
#include <QDesktopWidget>
#include <custommensaje.h>


/**  Implementacion del Constructor de gui_jugador,
 * Se pasa como parametro al constructor un puntero a objeto widget
 * COmo parametro del constructor de la superclase el objeto widget
 * Se inicializa la variable ui de gui_jugador
 * */


gui_jugador::gui_jugador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_jugador)
{
    // EL metodo setupUI crea los componentes y otros objetos de la interfaz visual
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
}

// Funcion Destructor
gui_jugador::~gui_jugador()
{
    delete ui;
}





int gui_jugador::guardarJugador(){


    QString s_nom= ui->t_nom->text();
    QString s_ape= ui->t_ape->text();
    QString s_login= ui->t_login->text();
    QString s_pass= ui->t_clave->text();
 jugador.setNombre(  s_nom);jugador.setApellido( s_ape);
 jugador.setUsuario( s_login); jugador.setClave( s_pass);
int res= jugador.crear();
if( res >0 )
    (void)(new custommensaje("correcto.png","Jugador creado!",  true, this));
 else
     (void)(new custommensaje("alert.png","No se pudo crear el jugador", true, this) );
    return res;
}



void gui_jugador::on_grbr_jugador_clicked()
{
    this->guardarJugador();
}
