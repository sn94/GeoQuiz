#include "leer_texto.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <conexion.h>
#include <QSqlQuery>
#include <QDebug>


leer_texto::leer_texto( QString nombr)
{
    this->nom_file= nombr;
/*
    QFile archivo("lista_paises.txt");
    archivo.open( QIODevice::WriteOnly   |  QIODevice::Truncate ); // bool  openmode flags
    QTextStream txtstream( &archivo );

     txtstream << text; // Se envia el texto a salida
   //cierre del archivo
   archivo.close();
   // vaciar el texto que se grabo
   text.clear();
*/

   //LA lectura
}


void leer_texto::leer(){

    QString text="";
    // Abrir el archivo para lectura y configurar el stream de texto a leer, del archivo


     QFile file_for_reading( this->nom_file );
    file_for_reading.open(QIODevice::ReadOnly); // Modo de apertura solo lectura

   QTextStream  text_stream_for_reading(&file_for_reading);// Parametro por referencia
    //Reset the position on the file
      text_stream_for_reading.seek(0);


        //read a line
      while( !text_stream_for_reading.atEnd()){
     text= text_stream_for_reading.readLine();

      }


 qDebug() << text;

       //close the file
      file_for_reading.close();


}








void leer_texto::cerrar_archivo(){

  file_for_reading.close();
}


