#include "reg_paisajes.h"
#include <QDir>
#include <QStringList>
#include <QFileInfo>
#include <QSqlQuery>
#include <QDebug>
#include <QByteArray>


reg_paisajes::reg_paisajes()
{

}


QString reg_paisajes::generarCod(){
    QString cons= "select coalesce(max(paisaje_cod), 0)+1 from paisajes";
    QSqlQuery query; query.exec( cons );
    if( query.next()){ return query.value(0).toString();
    }else{  return ""; }
}


QString reg_paisajes::convertirImagen(QString fn){
    QFile f_img( fn);
    if( !f_img.open( QIODevice::ReadOnly)){  qDebug()<< "Error al abrir la imagen "+ f_img.errorString();}
    else{   qDebug()<< "Correcto "; }
    // Se Lee todo el archivo como qbytearrays, esto es parametro para un constructor de otro qbytearray
    QByteArray streamimg( f_img.readAll());
    QString img64= QString( streamimg.toBase64()); //convertir a base 64 gracias al metodo de qbytearray
    this->bin_img= img64; return img64;
}

void reg_paisajes::lectura(){
    QDir dir_paisajes("Paisajes");
    QStringList lista_fotos= dir_paisajes.entryList();

    QString pais_nombre="";
    foreach (QString it, lista_fotos) {
     QString filen= QFileInfo(it).fileName(); qDebug() << "Lectura primera "<< filen;
     filen= QFileInfo( filen ).fileName();
     pais_nombre= (filen.split("."))[0];
     /** GUardar los primeros datos **/
     this->nation.getCodigo( pais_nombre);/** Codigo de pais **/
     qDebug() << "COdigo "<< this->nation.getCodigo();

     if( QFileInfo("Paisajes/"+it).isDir() && filen!="" &&  filen !="." &&  filen!=".."   ){

         QDir subdir("Paisajes/"+it); qDebug() << "SUb path "<< "Paisajes/" <<it;
         QStringList sub_lista=  subdir.entryList();

         foreach (QString imag,  sub_lista) {
             /** *** *****/

             filen= QFileInfo("Paisajes/"+it+"/"+imag).fileName();
             if( filen !="" &&  filen !="." &&  filen!=".." ){
                 this->nombre= (filen.split("."))[0];
                  qDebug()<< this->nombre << " -- NOmbre de la foto ";
                  this->convertirImagen( "Paisajes/"+it+"/"+filen);
                  /** **** *** ***/
                 this->grabar();
             }

         }/** for each 2**/

     }/**SI fuera directorio **/
     else{}/**Si fuera archivo ****/
     }
}



void reg_paisajes::grabar(){

    qDebug()<<"nombre "<< this->nombre;

    qDebug()<<"pais cod "<< this->nation.getCodigo();

QSqlQuery query; query.prepare("insert into paisajes(paisaje_cod, paisaje_nom, paisaje_ruta, pais_cod, pista) values(:cod, :nom, :img, :pais, :pista)");
query.bindValue(":cod", this->generarCod());
query.bindValue(":nom", this->nombre);
query.bindValue(":img", this->bin_img);
query.bindValue(":pais", this->nation.getCodigo());
query.bindValue(":pista", "");   query.exec();
if( query.numRowsAffected() >0) qDebug()<< "Paisaje registrado ";
else "ALgo ocurrio al intentar registrar el paisaje";

}
