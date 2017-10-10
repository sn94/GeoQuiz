#include "juego_1.h"
#include "ui_juego_1.h"
#include  <conexion.h>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>
#include <time.h>
#include <gui_pais.h>
#include <imagenes_model.h>
#include <QMessageBox>
#include <QDesktopWidget>
#include <menu.h>
#include <custommensaje.h>



juego_1::juego_1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::juego_1)
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

  /**Aplicar estilos  **/
  QString stiloradio="QRadioButton::indicator::unchecked {image: url(:/no_radio.png);} QRadioButton::indicator::checked { image: url(:/sel_radio.png);}";

  ui->opc_1->setStyleSheet( stiloradio);
   ui->opc_2->setStyleSheet( stiloradio);
    ui->opc_3->setStyleSheet( stiloradio);
    lanzar_preg();
}

juego_1::juego_1(QString user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::juego_1)
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
  /**Aplicar estilos  **/
  QString stiloradio="QRadioButton::indicator::unchecked {image: url(:/no_radio.png);} QRadioButton::indicator::checked { image: url(:/sel_radio.png);}";

  ui->opc_1->setStyleSheet( stiloradio);
   ui->opc_2->setStyleSheet( stiloradio);
    ui->opc_3->setStyleSheet( stiloradio);
 /********/
ui->l_user->setText( user );
this->Player.setModo('C');
this->Player.setUsuario(user); this->Player.buscar();
ui->l_score->setText( QString::number(this->Player.getPuntaje())  );
ui->l_level->setText(QString::number( this->Player.getNivel() ));
lanzar_preg();
}


juego_1::~juego_1()
{
    delete ui;
}





void juego_1::iconoContinente(QString ar){
    QString arr= ar.trimmed();

QString recurso= ":/continentes/";
 if( arr.toLower() == "américa")  recurso+= "america.png";
 if( arr.toLower() == "europa")  recurso+= "europa.png";
  if( arr.toLower() == "asia")  recurso+= "asia.png";
   if( arr.toLower() == "áfrica")  recurso+= "africa.png";
    if( arr.toLower() == "oceanía")  recurso+= "oceania.png";

 ui->imagen->setStyleSheet("image: url("+recurso+"); ");
 qDebug() <<  recurso << "R E CURSO " << "conti "<< ar;

}


void juego_1::Desordenar(){
    generador_random changeorder; changeorder.setMin(0); changeorder.setMax(2);
 bool usado[3]= {false, false, false};

     for(int i=0; i< 3; i++){
         int rando;
         do{ rando= changeorder.generar();
             if( this->ids_opc[rando]== this->ids_opc[i]){ usado[rando]=true;}
         else{ usado[rando]= false; }
         }while( usado[rando] );

         usado[rando]=true;
          int cambio= this->ids_opc[rando];
         this->ids_opc[rando]= this->ids_opc[i];
         this->ids_opc[i]= cambio;
          qDebug()<<" Intercambio " << cambio <<" y "<< this->ids_opc[rando];
     }
    /* **Ahora desordenado ***/
     qDebug()<< this->ids_opc[0]<< "-" << this->ids_opc[1]<<" -"<< this->ids_opc[2];

    this->pais_m.setCodigo( QString::number(ids_opc.at(0) )  ); this->pais_m.buscar();
     ui->opc_1->setText( this->pais_m.getCapital());
     this->pais_m.setCodigo( QString::number(ids_opc.at(1)) ); this->pais_m.buscar();
      ui->opc_2->setText(    this->pais_m.getCapital() );
     this->pais_m.setCodigo(QString::number(ids_opc.at(2))  );this->pais_m.buscar();
       ui->opc_3->setText(  this->pais_m.getCapital());
}




void juego_1::formularOpciones(){
   this->ids_opc.clear();
    int id_gen, total_opc=1,  pruebas_pasadas=0;
    while(   total_opc<=3){//MIentras el numero de ids sea menor o igual a 3
        if(total_opc==1){//SI se trata del primer id se guardara el id de pais que se obtuvo anteriormente
            this->ids_opc.append(this->id_pais.toInt());
            this->respuesta= this->respuesta;
            qDebug()<< "1ro "<<this->respuesta<<" id: "<< this->id_pais;
            total_opc++; // Se incrementa en 1 el total de opciones
        }
        else{//Si se trata del 2do o tercer id
            id_gen= this->gen_random.generar();
            int nro_veri= this->ids_opc.length();//numero de elementos en la lista

            int id_saved;// Otra variable que almacena ids generados pero
            //que se usara para comparar con id_gen

            //Se itera la coleccion de ids que ya se cargaron y se verifica la existencia
            //de un mismo valor que almacena id_gen
            while(pruebas_pasadas< nro_veri){

                foreach (int var, this->ids_opc) {

                    id_saved= var;
                    if( id_gen == id_saved){ while(  id_gen == id_saved ){  id_gen= this->gen_random.generar(); }  }
                    else{  pruebas_pasadas++;}

                }/** end foreach **/

            }

            this->ids_opc.append(id_gen);

             qDebug()<< total_opc<<" id_gen "<< id_gen;
              total_opc++;
        }/** ** ** ** **/
       }
    /** Desordenar opciones **/
this->Desordenar();
}









void juego_1::lanzar_preg(){
int nivelJ= this->Player.getNivel();

 this->pais_m.setModo( nivelJ);
 QVector<int> canti= this->pais_m.getMinMax();
lanzar_preg( canti );

}



void juego_1::lanzar_preg( QVector<int> canti){

int min= canti[0] ,  max= canti[1];
this->gen_random.setMin( min);   this->gen_random.setMax(max);

int cod_R= this->gen_random.generar();
this->pais_m.setCodigo(QString::number(cod_R )); this->pais_m.buscar();

 QString s_nom= this->pais_m.getNombre();
 qDebug()<<" id "<< this->pais_m.getCodigo()<<"  "<<this->pais_m.getCapital();
this->id_pais= this->pais_m.getCodigo();
this->respuesta= this->pais_m.getCapital();
ui->l_variante->setText(  s_nom );
ui->l_continente->setText( this->pais_m.getContinente());
this->iconoContinente( this->pais_m.getContinente()  );
formularOpciones();
    }




void juego_1::lanzar_preg_america(){
  this->pais_m.setModo('1');

  lanzar_preg( this->pais_m.getMinMax() );

}








void juego_1::subirNivel(){
       ui->l_level->setText( QString::number( this->Player.getNivel() )  );

}


void juego_1::on_btn_juego1_clicked()
{
        int idselc=0;

    if( ui->opc_1->isChecked())  idselc= this->ids_opc[0];
      if( ui->opc_2->isChecked())  idselc= this->ids_opc[1];
        if( ui->opc_3->isChecked())  idselc= this->ids_opc[2];

        qDebug()<< "  comparacion " <<idselc<<"   ==  "<<  this->id_pais;
        if(  idselc== this->id_pais.toInt() ){

    (void)( new custommensaje("correcto.png","Genial! La respuesta es correcta ", true, this));
                //SUmar puntaje
                this->Player.sumarPuntaje();
                ui->l_score->setText( QString::number(this->Player.getPuntaje()));
                this->subirNivel();
           this->lanzar_preg();

        }else{
    (void)( new custommensaje("incorrecto.png","La capital de "+this->pais_m.getNombre()+" es ->"+ this->respuesta, true, this));  this->lanzar_preg();
        }


}

void juego_1::on_pushButton_clicked()
{
    this->close();
   menu *m= new menu(0, ui->l_user->text());
   m->show();
}
