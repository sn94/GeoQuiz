#ifndef REG_PAISAJES_H
#define REG_PAISAJES_H
#include <pais_model.h>
#include <QPixmap>

class reg_paisajes
{
public:
    reg_paisajes();
   void lectura();

private:
    QString nombre, bin_img, pista;
    QPixmap imagen;
      pais_model nation;
    QString generarCod();
     void grabar();
    QString convertirImagen(QString filenam);

};

#endif // REG_PAISAJES_H
