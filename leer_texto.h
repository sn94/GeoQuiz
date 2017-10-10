#ifndef LEER_TEXTO_H
#define LEER_TEXTO_H
#include <QFile>
#include <QTextStream>
#include <QStringList>


namespace utilidades {
class leer_texto;

}

class leer_texto
{


 QFile archivo;

public:
  explicit  leer_texto( QString nomfile );// parametro es nombre del archivo
QString nom_file;
  QFile file_for_reading;
void leer();
void cerrar_archivo();
};

#endif // LEER_TEXTO_H
