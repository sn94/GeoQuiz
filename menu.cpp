#include "menu.h"
#include "ui_menu.h"
#include <gui_edit_jugador.h>
#include <menu_abm.h>
#include <juego_1.h>
#include <juego_2.h>
#include <mainwindow.h>
#include <QDebug>

#include <QDesktopWidget>
#include <QRect>
#include <QPoint>

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
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
}


menu::menu(QWidget *parent, QString log):QMainWindow(parent), ui(new Ui::menu){

    ui->setupUi(this);
    ui->l_nom_usu->setText( log );
    /** Centrar **/
 QRect geo_ori= this->geometry();
 int ancho= geo_ori.width();
 int alto= geo_ori.height();
 QDesktopWidget *deskw= QApplication::desktop();
 QRect rectas= deskw->screenGeometry();
 int px  = (rectas.width()/2) - (ancho/2);
  int py = (rectas.height()/2) - ( alto/2);
 this->move( QPoint(px, py )  );
}



menu::~menu()
{
    delete ui;
}





void menu::jugar_capitales(){
    this->close();
juego_1 *ju1= new  juego_1( ui->l_nom_usu->text());  ju1->show();
}

void menu::jugar_paisajes(){
    this->close();

    MainWindow *window= new MainWindow( ui->l_nom_usu->text());
    window->loadImage();
    window->show();
}

void menu::abm(){
menu_abm *ma= new menu_abm;
ma->show();
}

/*

void menu::on_btn_juego3_clicked()
{
    MainWindow window;
    window.loadImage(QStringLiteral(":/mapamundi.jpg"));
    window.show();
}

*/




void menu::jugar_banderas()
{
    this->close();
      juego_2 *jue2= new juego_2(ui->l_nom_usu->text()); jue2->show();
}

void menu::on_btn_juego2_clicked()
{
    this->jugar_capitales();
}

void menu::on_btn_banderas_2_clicked()
{
    this->jugar_banderas();
}

void menu::on_btn_juego3_clicked()
{
    this->jugar_paisajes();
}

void menu::on_btn_editar_jug_clicked()
{

    gui_edit_jugador *ge= new gui_edit_jugador(ui->l_nom_usu->text());
    ge->show();
}
