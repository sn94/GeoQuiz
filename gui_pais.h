#ifndef GUI_PAIS_H
#define GUI_PAIS_H
#include <QMainWindow>

namespace Ui {
class gui_pais;
}

class gui_pais {


public:
    explicit gui_pais();
    ~gui_pais();
    QVector<int>  max_paises();
    QVector<int>  paises_america();
    QVector<int>  paises_europa();
    QVector<int>  paises_asia();
    QVector<int>  paises_africa();
    QVector<int>  paises_oceania();

    void registrar();
     QString generarcod();
     QVector<QString>  datos(QString cod);

private:
    void registrar_(QString conti, QString pais, QString capital);
};

#endif // GUI_PAIS_H
