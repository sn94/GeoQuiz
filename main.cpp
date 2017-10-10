#include "login.h"
#include <QApplication>
#include <conexion.h>
#include <mainwindow.h>
#include <cargador.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Recibe los argumentos de la funcion main

    conexion *conn= new conexion;// Puntero a objeto

    if( !conn->ConexionExitosa()){ //SI no fue exitosa la conexion
        return 1;
    }

//reg_paisajes regp; regp.lectura();
   /* imagenes_model *imgtest= new imagenes_model;
    imgtest->setModoBuscar('P'); imgtest->setFormato("JPG");
    imgtest->setId("12");
    QPixmap pixx= imgtest->imagen_paisaje();*/

  /*  MainWindow window;
    window.loadImage();// window.loadImage(QStringLiteral(":/mapamundi.jpg"));
    window.show();
*/
Cargador cargador; cargador.show();
    //login j;// instancia de formulario jugador

    //j.show();// Hacer visible el formulario
//bandera b; b.reg_banderas();
    return a.exec(); //ejecutar la aplicacion
}
