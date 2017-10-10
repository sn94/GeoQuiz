#include "juego_2.h"
#include "ui_juego_2.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <menu.h>
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>
#include <custommensaje.h>


juego_2::juego_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::juego_2)
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

ui->r_ban1->setStyleSheet( stiloradio);
ui->r_ban2->setStyleSheet( stiloradio);
ui->r_ban3->setStyleSheet( stiloradio);

    this->iniciarPregunta();
}

juego_2::juego_2( QString user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::juego_2)
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

  /**Aplicar estilos  **/
  QString stiloradio="QRadioButton::indicator::unchecked {image: url(:/no_radio.png);} QRadioButton::indicator::checked { image: url(:/sel_radio.png);}";

ui->r_ban1->setStyleSheet( stiloradio);
ui->r_ban2->setStyleSheet( stiloradio);
ui->r_ban3->setStyleSheet( stiloradio);
/***************/
  ui->centralwidget->setGeometry(0,100, ancho, alto-20);

    ui->l_user_name->setText( user );
    this->Player.setUsuario( user );
    this->Player.setModo('B');
    this->Player.buscar();
    ui->l_score->setText( QString::number( this->Player.getPuntaje())   );
    ui->l_level->setText( QString::number( this->Player.getNivel()) );
    this->img_gest.setModoBuscar('B');
    this->img_gest.setFormato("PNG");

    this->iniciarPregunta();
}


juego_2::~juego_2()
{
    delete ui;
}




void juego_2::iconoContinente(QString ar){
    QString arr= ar.trimmed();

QString recurso= ":/continentes/";
 if( arr.toLower() == "américa")  recurso+= "america.png";
 if( arr.toLower() == "europa")  recurso+= "europa.png";
  if( arr.toLower() == "asia")  recurso+= "asia.png";
   if( arr.toLower() == "áfrica")  recurso+= "africa.png";
    if( arr.toLower() == "oceanía")  recurso+= "oceania.png";

 ui->imagen->setStyleSheet("image: url("+recurso+"); ");
}


void juego_2:: iniciarPregunta(){
this->img_gest.setNivelJugador(  this->Player.getNivel());
QVector<int> mm= this->img_gest.getCodMinMax();
this->gen_ran.setMin(  mm[0] );   this->gen_ran.setMax( mm[1]);
this->id_bandera=  QString::number( this->gen_ran.generar());

this->img_gest.setId( this->id_bandera ); qDebug()<<" QUIZ id bandera es "<< this->id_bandera;
ui->l_pais->setText( this->img_gest.getNombre() ); qDebug()<< "NOmbre pais de bandera es "<< this->img_gest.getNombre();

bandera band;band.setId( this->id_bandera); band.consultar();
ui->l_continente->setText( band.getPais().getContinente()  ) ;
this->iconoContinente( ui->l_continente->text());
this->solucion= this->img_gest.imagen_bandera();
this->mostrarBanderas();
}




void  juego_2:: mostrarBanderas(){
     this->ids_opc.clear();
     int id_gen, total_opc=1,  pruebas_pasadas=0;
   while(   total_opc<=3){//MIentras el numero de ids sea menor o igual a 3
        if(total_opc==1){//SI se trata del primer id se guardara el id de pais que se obtuvo anteriormente
            this->ids_opc.append(this->id_bandera.toInt());
 total_opc++; // Se incrementa en 1 el total de opciones
        }
        else{//Si se trata del 2do o tercer id
            id_gen= this->gen_ran.generar();
            int nro_veri= this->ids_opc.length();//numero de elementos en la lista
            int id_saved;
            while(pruebas_pasadas< nro_veri){

                foreach (int var, this->ids_opc) {

                    id_saved= var;
                    if( id_gen == id_saved){ while(  id_gen == id_saved ){  id_gen= this->gen_ran.generar(); }  }
                    else{  pruebas_pasadas++;}

                }/** end foreach **/

            }

            this->ids_opc.append(id_gen);

              total_opc++;
        }/** ** ** ** **/
       }
    /** Desordenar opciones **/
   this->Desordenar();
}



void juego_2::Desordenar(){
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

     }
    /* **Ahora desordenado ***/
     this->img_gest.setId( QString::number(this->ids_opc.at(0) )  );
      ui->img1->setPixmap( this->img_gest.imagen_bandera());


      this->img_gest.setId( QString::number( this->ids_opc.at(1) )  );
       ui->img2->setPixmap( this->img_gest.imagen_bandera());

       this->img_gest.setId( QString::number( this->ids_opc.at(2) )  );
        ui->img3->setPixmap( this->img_gest.imagen_bandera());

}


void juego_2::subirNivel(){
       ui->l_level->setText( QString::number( this->Player.getNivel() )  );

}
void juego_2::on_btnsiguiente_clicked()
{
    int idselc=0;

if( ui->r_ban1->isChecked())  idselc= this->ids_opc[0];
  if( ui->r_ban2->isChecked())  idselc= this->ids_opc[1];
    if( ui->r_ban3->isChecked())  idselc= this->ids_opc[2];

    if(  idselc== this->id_bandera.toInt() ){
 (void)( new custommensaje("correcto.png","Genial! La respuesta es correcta ", true, this));
 //SUmar puntaje
 this->Player.sumarPuntaje();
 ui->l_score->setText( QString::number(this->Player.getPuntaje()));
 this->subirNivel();
this->iniciarPregunta();
    }else{

 (void)(new custommensaje( this->id_bandera,"LA BANDERA CORRECTA ES:\n", false, this ));

    }

}


void juego_2::on_pushButton_clicked()
{
  this->close();
   menu *m= new menu(0, ui->l_user_name->text());
   m->show();
}
