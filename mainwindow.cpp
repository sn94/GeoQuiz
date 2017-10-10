#include "mainwindow.h"
#include "pieceslist.h"
#include "puzzlewidget.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <imagenes_model.h>
#include <QDesktopWidget>
#include <custommensaje.h>
#include <menu.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenus();
    setupPregunta();
   setupWidgets();
   setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
      setWindowTitle(tr("Puzzle"));

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


     // this->loadImage();
}

MainWindow::MainWindow(QString user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenus();
    setupPregunta();
   setupWidgets();
   setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
      setWindowTitle(tr("Puzzle"));

      /** Centrar **/
   QRect geo_ori= this->geometry();
   int ancho= geo_ori.width();
   int alto= geo_ori.height();

   QDesktopWidget *deskw= QApplication::desktop();
   QRect rectas= deskw->screenGeometry();
   int px  = (rectas.width()/2) - (ancho/2);
    int py = (rectas.height()/2) - ( alto/2);
  // this->move( QPoint(px, py )  );
   this->setGeometry(px, py, ancho+(ancho/2), alto- (alto/5) );
  /** **/


      /**MOstrar nombre de usu **/
    this->l_usu_name->setText(  user);
      this->Player.setModo('P');
      this->Player.setUsuario(user); this->Player.buscar(); qDebug()<< "mirame  "<<this->Player.getPuntaje();
      this->l_puntaje->setText( QString::number(this->Player.getPuntaje()));
     // this->loadImage();


}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::openImage()
{
    const QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open Image"), QString(),
                                     tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
        loadImage(fileName);
}

void MainWindow::loadImage(){
  this->genCodigoPaisaje();
    /**generar las opciones a marcar **/
    this->generarOpcionesMarcar();
    imagenes_model *imgtest= new imagenes_model;
    imgtest->setModoBuscar('P'); imgtest->setFormato("JPG");
    imgtest->setId( this->id_paisaje);
    QPixmap pixx= imgtest->imagen_paisaje();
    this->loadImage(  pixx );
}



void MainWindow::loadImage(QPixmap arg)
{
 puzzleImage = arg;
    setupPuzzle();
 qDebug()<< " end metodo load image";

}

void MainWindow::loadImage(const QString &fileName)
{
    QPixmap newImage;
    if (!newImage.load(fileName)) {
        QMessageBox::warning(this, tr("Open Image"),
                             tr("The image file could not be loaded."),
                             QMessageBox::Close);
        return;
    }
    puzzleImage = newImage;
    setupPuzzle();
}


void MainWindow::habilitarOpciones(){
    this->siguiente->setEnabled( true );
}

void MainWindow::setCompleted()
{
    QMessageBox::information(this, tr("Puzzle completado"),
                             tr("Genial! Haz terminado de ordenar el puzzle\n"
                                "Ahora elige tu respuesta."),
                             QMessageBox::Ok);

    // setupPuzzle();
    // Habilitar opciones de solucion
    this->habilitarOpciones();
}





void MainWindow::setupPuzzle()
{


    int size = qMin(puzzleImage.width(), puzzleImage.height());

/**QPIXMAP     Metodo Copy
 *  x   y   width  height
 *
 *   QRectangle**/

// Metodo scaled
    /** scaled(const QSize &size,
     * Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio,
     *  Qt::TransformationMode transformMode = Qt::FastTransformation) const
     * **/

    /** scaled(int width,
     * int height,
     * Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio,
     *  Qt::TransformationMode transformMode = Qt::FastTransformation) const
     * */

    /*************************/
int X1=  (puzzleImage.width() - size)/2,  Y1= (puzzleImage.height() - size)/2 ;
int Width1= size;  int Height1=  size;
/*********** EScale *************/
int Width2=   puzzleWidget->width();  int Height2=    puzzleWidget->height();
  puzzleImage = puzzleImage.copy( X1,   Y1,   Width1,   Height1 ).
          scaled(
               Width2,                      Height2   ,
              Qt::IgnoreAspectRatio,    Qt::SmoothTransformation);

  // Derivado de QListWIdget , clear elimina todos los elementos de la lista
    piecesList->clear();


    /** ES un puzzle de 5x5   */
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            // puzzle widget es un derivado de qwidget
            int pieceSize = puzzleWidget->pieceSize();
            /** Seria como recortar cuadros de la imagen  **/
            QPixmap pieceImage = puzzleImage.copy(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            /** Se agrega un elemento a la lista de piezas ***/
            piecesList->addPiece(pieceImage, QPoint(x, y));
        }
    }


    /** Ahora se insertan las piezas aleatoriamente  **/
    /** void 	insertItem(int row, QListWidgetItem * item)
void 	insertItem(int row, const QString & label)**/

    int  qcursr= QCursor::pos().x() ^ QCursor::pos().y();
    qsrand(  qcursr );

    /** Una vez que se hayan listado se desordena  **/

    for (int i = 0; i < piecesList->count(); ++i) {

        if (int(2.0*qrand()/(RAND_MAX+1.0)) == 1) {
            QListWidgetItem *item = piecesList->takeItem(i);
            piecesList->insertItem(0, item);
        }
    }

    puzzleWidget->clear();
}







void MainWindow::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MainWindow::openImage);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));

    gameMenu->addAction(tr("&Restart"), this, &MainWindow::setupPuzzle);
}

void MainWindow::genCodigoPaisaje(){

    int generado= this->gen_random.generar();
   // qDebug() << "ALEATORIO min "<<this->gen_random.getMin() <<" max "<< this->gen_random.getMax()<<" "<<generado;
    this->id_paisaje=  QString::number(generado);

}

void MainWindow::setupPregunta(){
 this->l_puntaje= new QLabel("Puntaje:");
    this->l_usu_name= new QLabel("Usuario:");
  this->l_pista= new QPushButton("Dame una pista");
  connect(this->l_pista, SIGNAL(clicked()), this, SLOT(lanzar_pista()));
QString stiloradio="QRadioButton::indicator::unchecked {image: url(:/no_radio.png);} QRadioButton::indicator::checked { image: url(:/sel_radio.png);}";

 this->l_pregunta= new QLabel("Este lugar es ");
 this->opc1= new QRadioButton(" La torre de Pisa ");
 this->opc2= new QRadioButton(" La torre Eiffel");
 this->opc3= new QRadioButton(" Las ruinas jesuticas");
  this->opc1->setChecked(true);

this->opc1->setStyleSheet( stiloradio);
this->opc2->setStyleSheet( stiloradio);
this->opc3->setStyleSheet( stiloradio);

 this->siguiente= new QPushButton("Siguiente"); //this->siguiente->setEnabled( false );
  connect(this->siguiente, SIGNAL(clicked()), this, SLOT(evaluar_respuesta()));
this->siguiente->setStyleSheet("QPushButton{border-color: rgba(193, 125, 17, 0.6); border-style:solid; border-width:2px; border-top-left-radius: 25px;border-top-right-radius: 0px;border-bottom-right-radius:25px;border-bottom-left-radius: 0px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(245, 121, 0, 255), stop:1 rgba(255, 255, 255, 255)); max-height: 32px; min-height: 32px; font-size: 20px; color: rgb(40, 40, 40);  } QPushButton:hover{  border-color: rgb(233, 185, 110); border-style:solid; border-width: 3px; font-size: 14px;font-weight: bolder; font-size:24px; height: 64px; background-image:url(:/background_3.jpg);  color:  rgb(143, 89, 2); } ");

    /** setup generador random **/
     imagenes_model imgs; imgs.setModoBuscar('P');
    this->gen_random.setMin(  imgs.getMinCod() );
    this->gen_random.setMax( imgs.getMaxCod());
    this->id_paisaje= this->gen_random.generar(); imgs.setId( this->id_paisaje);
    this->respuesta= imgs.getNombre();

}


void  MainWindow::generarpregunta(){
 imagenes_model imgs; imgs.setModoBuscar('P');
    this->ids_opc.clear(); int id_gen, total_opc=1,  pruebas_pasadas=0;
    while(   total_opc<=3){
        if(total_opc==1){
            this->ids_opc.append(this->id_paisaje.toInt());imgs.setId( this->id_paisaje);
            this->respuesta= imgs.getNombre();
            qDebug()<< "1ro "<<this->respuesta<<" id: "<< this->id_paisaje;
            total_opc++; // Se incrementa en 1 el total de opciones
        }
        else{
            id_gen= this->gen_random.generar();
            int nro_veri= this->ids_opc.length();
            int id_saved;
            while(pruebas_pasadas< nro_veri){

                foreach (int var, this->ids_opc) {
id_saved= var;
if( id_gen == id_saved){ while(  id_gen == id_saved ){  id_gen= this->gen_random.generar(); }  }
 else{  pruebas_pasadas++;} }  }
  this->ids_opc.append(id_gen);  total_opc++;}}
}




void MainWindow::generarOpcionesMarcar(){
imagenes_model imgs; imgs.setModoBuscar('P');
//qDebug()<<" Antes de preguntar ";
this->generarpregunta();
//limpiar vector de ids
   /*this->ids_opc.clear();
  imagenes_model imgs; imgs.setModoBuscar('P');
  int id_gen, total_opc=1;

while(   total_opc<=3){
    if(total_opc==1){
this->ids_opc.append(this->id_paisaje.toInt()); imgs.setId( this->id_paisaje);
this->respuesta= imgs.getNombre(); qDebug()<< "1ro "<<this->respuesta<<" id: "<< this->id_paisaje;   total_opc++;}
 else{
        int id_saved; bool repetido= false;

        do{
        foreach (int var, this->ids_opc) {
            id_saved= var;
            id_gen= this->gen_random.generar();

            if(id_saved == id_gen){  repetido= true; break; }
            else{  repetido= false; }

        }
         }while(  repetido );

        this->ids_opc.append(id_gen);
        total_opc++;
         qDebug()<< total_opc<<" id_gen "<< id_gen;;
    }
   }*/
/** Desordenar opciones **/
/** ** ** * ** *** *** *** *** *** *** *** ** **/
generador_random changeorder; changeorder.setMin(0); changeorder.setMax(2);

for(int i=0; i< 3; i++){
    int rando= changeorder.generar();
    int cambio= this->ids_opc[rando];
    this->ids_opc[rando]= this->ids_opc[i]; this->ids_opc[i]= cambio;
}
/**Ahora desordenado **/
qDebug()<< this->ids_opc[0]<< "-" << this->ids_opc[1]<<" -"<< this->ids_opc[2];

imgs.setId( QString::number(ids_opc.at(0)) );
this->opc1->setText( imgs.getNombre());
 imgs.setId( QString::number(ids_opc.at(1)) );
this->opc2->setText( imgs.getNombre());
 imgs.setId( QString::number(ids_opc.at(2))  );
 this->opc3->setText( imgs.getNombre());

}



void MainWindow::setupWidgets()
{
    QFrame *frame = new QFrame;
    /** Layout principal **/

/** Primer layout  PUNTAJE      **/
    QVBoxLayout *principal= new QVBoxLayout(frame);// Layout principal
/** ** ** *** ** ** *** ***/

    /** PANEL DATOS DE JUEGO **/
    QHBoxLayout *datos_juego= new QHBoxLayout;
    QLabel *lus=new QLabel("Usuario:");QLabel *lpu=new QLabel("Puntaje:");
    lus->setStyleSheet("font: 57 16pt 'Arial'; color: rgb(40,40,40); ");  lpu->setStyleSheet("font: 57 16pt 'Arial'; color: rgb(40,40,40); ");

    this->l_usu_name->setStyleSheet("font: 57 16pt 'Arial';  color:  black; ");    this->l_puntaje->setStyleSheet("font: 57 16pt 'Arial';  color:  black; ");

  datos_juego->addWidget(lus); datos_juego->addWidget(this->l_usu_name);
  datos_juego->addWidget(lpu);   datos_juego->addWidget( this->l_puntaje);

    QWidget *w_datos_juego= new QWidget; w_datos_juego->setLayout( datos_juego);
   w_datos_juego->setStyleSheet("background-color: rgb(206, 92, 0);  border-color: rgba(193, 125, 17, 0.6); border-style:solid; border-width:2px; border-top-left-radius: 25px; border-top-right-radius: 0px; border-bottom-right-radius:25px; border-bottom-left-radius: 0px;   min-height: 70px; max-height:70px;");
    /** ** ** ** ** ** **/

    QHBoxLayout *frameLayout = new QHBoxLayout;
    /** AQui se agregara la pregunta y las opciones a marcar **/
    puzzleWidget = new PuzzleWidget(400);/** Panel donde se colocaran**/
    piecesList = new PiecesList(puzzleWidget->pieceSize(), this);
    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted,
            this, &MainWindow::setCompleted, Qt::QueuedConnection);

    /***SECCION IZQUIERDA **/
    frameLayout->addWidget(piecesList);/** AGrega un qlistwidget  **/
    /** ** *** ***  *** ***/
  //  frameLayout->addWidget(puzzleWidget); /**  Agrega un qwidget  **/
    /** ** ** ** SECCION DERECHA** ** ** **/
    QWidget *pregunta= new QWidget;
    QVBoxLayout *pre_layout= new QVBoxLayout;
    pre_layout->addWidget( puzzleWidget);
    pre_layout->addWidget( this->l_pregunta);
    pre_layout->addWidget(  this->opc1);
    pre_layout->addWidget( this->opc2);
    pre_layout->addWidget( this->opc3);
    pre_layout->addWidget( this->siguiente);
    pregunta->setLayout( pre_layout);


/** ** ** ** *** ** ** ** ** ** **/
frameLayout->addWidget( pregunta);
QWidget * sec_central= new QWidget; sec_central->setLayout( frameLayout);

principal->addWidget( w_datos_juego); //Panel superior
/** **/
QString stilobtn= "QPushButton{   border-color: rgba(193, 125, 17, 0.6); border-style:solid; border-width:2px;   border-top-left-radius: 25px; border-top-right-radius: 0px; border-bottom-right-radius:25px;  border-bottom-left-radius: 0px;   background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(245, 121, 0, 255), stop:1 rgba(255, 255, 255, 255)); max-height: 32px;  min-height: 32px;  font-size: 20px;  color: rgb(40, 40, 40);  } QPushButton:hover{ border-color: rgb(233, 185, 110); border-style:solid; border-width: 3px; font-size: 14px;font-weight: bolder; font-size:24px; height: 64px; background-image:url(:/background_3.jpg); color:  rgb(143, 89, 2);   } ";

QPushButton *btnmenu= new QPushButton("Menu");
btnmenu->setStyleSheet( stilobtn);
this->l_pista->setStyleSheet( stilobtn);

connect( btnmenu, SIGNAL(clicked()), this, SLOT(ir_menu()));

QHBoxLayout *panel_pista= new QHBoxLayout;
panel_pista->addWidget( this->l_pista); panel_pista->addWidget( btnmenu);
QWidget *wpista= new QWidget; wpista->setLayout( panel_pista);
 /** **/
principal->addWidget( wpista);//Texto pista

principal->addWidget(sec_central);//Panel central
frame->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 178, 102, 255), stop:0.55 rgba(235, 148, 61, 255), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));");
    setCentralWidget(frame);/** Metodo de qwindow **/

}



void MainWindow::ir_menu(){
    this->close();
   menu *m= new menu(0, this->l_usu_name->text());
   m->show();
}

void MainWindow::lanzar_pista(){
imagenes_model im; im.setModoBuscar('P'); im.setId( this->id_paisaje);
QString pista= im.getPista();
(void)(new custommensaje(pista, this));
}



void MainWindow::evaluar_respuesta(){
    imagenes_model imgx; imgx.setModoBuscar('P');
bool r1= this->opc1->isChecked(); bool r2= this->opc2->isChecked();
bool acerto= false;

if( r1){
    imgx.setId( QString::number(this->ids_opc[0])); acerto= imgx.getNombre()== this->respuesta;
}
else{ if(r2){  imgx.setId( QString::number(this->ids_opc[1])); acerto= imgx.getNombre()== this->respuesta;

    }else{  imgx.setId( QString::number(this->ids_opc[2])); acerto= imgx.getNombre()== this->respuesta;}
}/** ** **/
if(acerto){
 (void)( new custommensaje("correcto.png","Genial! La respuesta es correcta ", true, this));
    //Sumar puntaje
    this->Player.sumarPuntaje();
    this->l_puntaje->setText( QString::number(this->Player.getPuntaje()) );
    this->loadImage();
}else{

 (void)( new custommensaje("incorrecto.png","Esa no es! La respuesta es "+respuesta, true, this)); this->loadImage();

}
}
