#ifndef BANDERA_H
#define BANDERA_H
#include <QMainWindow>
#include <pais_model.h>


class bandera
{

public:
    bandera();
 void registrar();
 void reg_banderas();
void setId(QString);
 QString getNombre();
 QPixmap mostrar_imagen( );
 void consultar();
pais_model getPais();
private:
 QString id_bandera, nombre;
 pais_model Pais;
 QString  bin_bandera;
  QString generarcod();
 void convertirImagen(QString);
 void grabar();


};

#endif // BANDERA_H
