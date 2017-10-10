#include "conexion.h"
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QtSql/QSqlError>




conexion::conexion()
{

    // Paso 1  crear el objeto QSqlDatabase e indicar el driver a usar

      QSqlDatabase  obj_bd= QSqlDatabase::addDatabase("QPSQL");
    // Paso 2 Indicar parametros  de conexion

    obj_bd.setHostName("localhost");
    obj_bd.setDatabaseName("quiz");
    obj_bd.setPort( 5434);
    obj_bd.setUserName("postgres");
    obj_bd.setPassword("94");

    if( ! obj_bd.open()){

        /**** MENSAJE **/
     QMessageBox::critical( 0, QObject::tr( "Error"), obj_bd.lastError().text() );
       exito= false;
    }
    exito= true;

}


bool     conexion::ConexionExitosa(){

  return exito;
}
