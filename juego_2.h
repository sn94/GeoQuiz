#ifndef JUEGO_2_H
#define JUEGO_2_H

#include <QMainWindow>
#include <imagenes_model.h>
#include <generador_random.h>
#include <jugador_model.h>
#include <bandera.h>



namespace Ui {
class juego_2;
}

class juego_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit juego_2(QWidget *parent = 0);
    explicit juego_2(QString user, QWidget *parent=0);
    ~juego_2();

private slots:
    void on_btnsiguiente_clicked();

    void on_pushButton_clicked();

private:
    Ui::juego_2 *ui;

    QVector<int> ids_opc;
    QString id_bandera;
    imagenes_model img_gest;
    generador_random gen_ran;
    void iconoContinente(QString );
    void iniciarPregunta();
    void mostrarBanderas();
    void Desordenar();
    jugador_model Player;
    QPixmap solucion;
    void subirNivel();
};

#endif // JUEGO_2_H
