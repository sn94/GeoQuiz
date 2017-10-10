#include <custommensaje.h>

#include <QLabel>
#include <imagenes_model.h>
#include <QPixmap>
#include <QVBoxLayout>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>


custommensaje::custommensaje(QString idimg, QString descr, bool recurso, QWidget *parent)  : QDialog(parent){
QLabel *et= new QLabel(  descr );

    QLabel *img= new QLabel; img->setStyleSheet("background-position: center;");

    et->setStyleSheet(" color: rgb(40, 40, 40);    font-size: 20px; text-align: center;");
    if( ! recurso){
    imagenes_model im; im.setId( idimg );
    im.setModoBuscar('B');
    img->setPixmap(     im.imagen_bandera()   );
}else{
        QPixmap pi; pi.load(":/"+idimg,"PNG");
        img->setPixmap( pi );
    }

    setStyleSheet("background-color: rgb(226, 112, 20);");
     QPushButton *cerrar= new QPushButton("OK");
    connect( cerrar, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *lay= new QVBoxLayout;
    lay->addWidget(   et  );
    lay->addWidget(   img );
   lay->addWidget( cerrar );

    setLayout(  lay );

  this->centrar( parent);
    show();
}





custommensaje::custommensaje(QString descr, QWidget *parent)  : QDialog(parent){
QTextEdit *et= new QTextEdit( descr);

  et->setStyleSheet(" color: rgb(40, 40, 40);    font-size: 14px; text-align: justify; min-width: 300px; max-width: 300px; min-height: 200px; max-height: 200px;background-color:  rgb(233, 185, 110); border-color:  rgb(233, 185, 110);");



    QVBoxLayout *lay= new QVBoxLayout;
    lay->addWidget(   et  );
    setLayout(  lay );

    this->ancho= 330; this->alto= 200;
  this->centrar( parent);
    show();
}


void custommensaje::centrar(QWidget *parent){
    /** Centrar **/
 QRect geo_ori= this->geometry();
 int ancho= this->ancho >0 ? this->ancho : (geo_ori.width()*3);
 int alto=  this->alto >0 ? this->alto : (geo_ori.height()*5);

 QDesktopWidget *deskw= QApplication::desktop();
 QRect rectas= deskw->screenGeometry();
 int px  = (rectas.width()/2) - (ancho/2);
  int py = (rectas.height()/2) - ( alto/2);
 //move( QPoint(px, py )  );

/** **/
    setGeometry( px, py , ancho, alto);
}
