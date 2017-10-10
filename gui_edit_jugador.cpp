#include "gui_edit_jugador.h"
#include "ui_gui_edit_jugador.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDesktopWidget>
#include <custommensaje.h>

gui_edit_jugador::gui_edit_jugador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_edit_jugador)
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

}


gui_edit_jugador::gui_edit_jugador(  QString usu, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_edit_jugador)
{
    ui->setupUi(this);
    jugador.setUsuario( usu );
    jugador.buscar();
    ui->t_nick->setText( usu );

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


gui_edit_jugador::~gui_edit_jugador()
{
    delete ui;
}


int gui_edit_jugador::editar(){

    QString s_login= ui->t_nick->text();
    QString s_nlogin= ui->t_nnick->text();
    QString s_pass= ui->t_pass->text();

    jugador.setUsuario(   s_nlogin); jugador.setClave(  s_pass );
    int numr=jugador.editar();
    if( numr>0){
 (void) (new custommensaje( "update.png","Usuario actualizado", true, this ));

   return 1;}
    else{   (void) (new custommensaje( "alert.png","Error al actualizar!", true, this)  );
        return 0; }
}



int gui_edit_jugador::borrarJugador(){
    return 1;
}


void gui_edit_jugador::on_btn_editar_clicked()
{
    this->editar();
}
