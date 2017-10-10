#ifndef IMAGENES_MODEL_H
#define IMAGENES_MODEL_H
#include <QPixmap>

class imagenes_model
{
public:
    imagenes_model();
    imagenes_model(QString id);
    void setModoBuscar(char);
    void setFormato(QString );
    void setId( QString  );
    QPixmap imagen_bandera();
    QPixmap imagen_paisaje();
    int getMinCod();
    int getMaxCod();
    QVector<int> getCodMinMax();
    QString getCodigoPais();
void setNivelJugador(int);
    QString getNombre();
    QString getPista();
private:
    QString id;
    int nivelJugador=0;
    char  modo;
    QPixmap pix_img;
    QString codigo_pais;
    int min, max;
    QString formato="PNG";
    QString nombre_foto, pista;
};

#endif // IMAGENES_MODEL_H
