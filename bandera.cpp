#include "bandera.h"
#include <QSqlQuery>
#include <QDir>
#include <QStringList>
#include <QMessageBox>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QDebug>




bandera::bandera()
{





}

QString bandera::generarcod(){
    QString cons= "select coalesce(max(band_cod), 0)+1 from banderas";
    QSqlQuery query; query.exec( cons );
    if( query.next()){
        return query.value(0).toString();
    }else{  return ""; }
}



void bandera::convertirImagen(QString ruta){
 QFile *f_img= new QFile(ruta);
 qDebug() <<" RUTA DE LA "<< ruta;
 if( !f_img->open( QIODevice::ReadOnly)){  qDebug()<< "Error al abrir la imagen "+ f_img->errorString();}
 else{   qDebug()<< "Correcto ";
 QByteArray streamimg( f_img->readAll());
this->bin_bandera= QString( streamimg.toBase64()); //convertir a base 64 gracias al metodo de qbytearray
 }
}



void bandera::grabar(){
    QSqlQuery query;
    query.prepare("insert into banderas(band_cod, band_imagen, band_nombre, pais_cod) values(:cod, :img, :nom, :pais)");
    query.bindValue(":cod",  generarcod() );
    query.bindValue(":img",  this->bin_bandera    );
    query.bindValue(":nom",  this->Pais.getNombre() );
    query.bindValue(":pais", this->Pais.getCodigo());
    query.exec();
    if( query.numRowsAffected() > 0){
 qDebug() <<"ok";
    }else{

 qDebug() << "NO se grabo datos de bandera ";
 qDebug()<< query.lastQuery();
    }

}

void bandera::registrar(){
QDir dirs("FlagsPNG");
QStringList lisdir= dirs.entryList(); //Recibe una lista de cadenas nombre de directorios o archivos


QSqlQuery query;
QFile *f_img;


foreach ( QString ar, lisdir ) {

    //QFileInfo es objeto de informacion del archivo
 QString aux= QFileInfo(ar).fileName().split(".")[1];
QString nombrepuro= QFileInfo(ar).fileName().split(".")[0];
    // Se verifica si es de extension png
    if( aux == "png"){

    QString nombre= ar;
    //Abrir archivo si es una imagen png
    f_img= new QFile( "FlagsPNG/"+nombre);

    if( !f_img->open( QIODevice::ReadOnly)){  qDebug()<< "Error al abrir la imagen "+ f_img->errorString();}
    else{   qDebug()<< "Correcto "; }
     //

    // Se Lee todo el archivo como qbytearrays, esto es parametro para un constructor de otro qbytearray
    QByteArray streamimg( f_img->readAll());
        //int tamano_ori= streamimg.length();//tamano de la imagen

        QString img64= QString( streamimg.toBase64()); //convertir a base 64 gracias al metodo de qbytearray

        //int tamano_64= img64.size();

        qDebug() << img64;

    query.prepare("insert into banderas(band_cod, band_imagen, band_nombre) values(:cod, :img, :nom)");
    query.bindValue(":cod",  generarcod() );
    query.bindValue(":img",  img64    );
    query.bindValue(":nom",  nombrepuro );
    query.exec();

    qDebug() << "Sql   "   << query.lastQuery();
   if( query.numRowsAffected() > 0){
qDebug() << f_img->fileName();
   }else{
qDebug() << "NO se grabo datos de bandera ";
   }
} }    }





void bandera::reg_banderas(){
 QString dirban="FlagsPNG";
QDir dirs( dirban );
QStringList lisdir= dirs.entryList(); //Recibe una lista de cadenas nombre de directorios o archivos


foreach ( QString ar, lisdir ) {

  if(  ar != "." &&  ar!= ".." && ar !=""){

      //Verificar si es directorio
    bool EsDirectorio=  QFileInfo( dirban+"/"+ar ).isDir();
    if( EsDirectorio){

              QDir SUBdirs(dirban+"/"+ar);  QStringList lisdir2= SUBdirs.entryList(); //Dirs de los continentes
              foreach (QString arch, lisdir2) {
                  //Verificar si es directorio
                bool EsDirectorio=  QFileInfo( dirban+"/"+ar+"/"+arch ).isDir();
                 if(   arch != "." &&  arch != ".." && arch !=""){
                if( !EsDirectorio){

                    qDebug()<< dirban+"/"+ar+"/"+arch ;

                    QString paisBandera= arch.split(".")[0];
                  qDebug()<<"cod "<< this->Pais.getCodigo(paisBandera );
                   qDebug() <<" nombre "<< this->Pais.getNombre();
                   this->convertirImagen( dirban+"/"+ar+"/"+arch );
                 this->grabar();
                }    }  } }}
 }


}




 QPixmap bandera::mostrar_imagen(){
QVariant encode64;

     QString cons= "select band_imagen from banderas where band_cod="+ this->id_bandera;
     QSqlQuery query; query.exec( cons );

     if( query.next()){
    encode64= query.value(0);
     }

     // LO que se recupera de la base de datos
     qDebug() << encode64.toString();

     //Se convierte el qvariant a qbytearray
     QByteArray img_dat= encode64.toByteArray();
     //Se realiza la decodificacion de base 64
     QByteArray img_dec= QByteArray::fromBase64( img_dat) ;
     // Se crea un objeto qpixmap, se llama a su metodo loadFromData ( qbytearray decodificado, tipo de imagen)
     QPixmap qx; qx.loadFromData( img_dec ,"PNG");

     return qx;
 }




 void bandera::consultar(){
     QString sq="select b.band_nombre, b.pais_cod from banderas b, paises p where b.pais_cod=p.pais_cod and b.band_cod="+this->id_bandera;
    QSqlQuery query( sq );  qDebug()<< "consultar clase bandera "<< sq;
    if( query.isActive()){
        if(query.next()){
            this->nombre=  query.value(0).toString();
              this->Pais.setCodigo( query.value(1).toString() ); this->Pais.buscar();

        }
    }
 }

 void bandera::setId(QString ar) {
     this->id_bandera= ar;
 }

 QString bandera::getNombre(){
     return this->nombre;
 }


 pais_model bandera::getPais(){
    return  this->Pais;
 }



