#ifndef JUGADOR_MODEL_H
#define JUGADOR_MODEL_H
#include <QString>
#include <QVariant>

class jugador_model
{
public:

    jugador_model();
    jugador_model(QString codigo);

void setModo( char );
    void setCodigo(QString);
    void setNombre(QString);
    void setApellido(QString);
    void setUsuario(QString);
    void setClave(QString);
    void setPuntajeCapitales(int);
    void setPuntajePaisajes(int);
    void setPuntajeBanderas(int );

     QString getCodigo();
    QString getNombre();
    QString getApellido();
    QString getUsuario();
    QString getClave();
    int getPuntaje();
    int getNivel();
   bool sumarPuntaje();
   void buscar();

    int crear();
   int editar();

private:    QString id="", nombre, apellido, usuario, clave, puntaje, nivel;
            int p_capitales=0 , p_paisajes=0 , p_banderas=0;

            bool crear_puntaje( QString newid);
            QString gencod();
            QString gencod2();
           char modo;
};

#endif // JUGADOR_MODEL_H
