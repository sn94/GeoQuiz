#ifndef PAIS_MODEL_H
#define PAIS_MODEL_H
#include <QString>
#include <QVariant>


class pais_model
{
public:
    pais_model();
    pais_model(QString);

    void setModo(int);
    void setCodigo(QString);
    void setNombre(QString);
    void setContinente(QString);
    void setCapital(QString);

    QString getCodigo();
int getTotalPaises();
    int getMin();
    int getMax();
    QString getCodigo( QString pattern_name);
    QString getNombre();
    QString getContinente();
    QString getCapital();
    QVector<int> getMinMax();
 void buscar();
    void crear();
    void editar();

 private:
    QString codigo, nombre, continente, capital, nombre_pattern="";
     int min, max;  int modo= 0;
      QString getSearchWord();


};

#endif // PAIS_MODEL_H
