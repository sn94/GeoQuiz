#ifndef JUEGO_1_H
#define JUEGO_1_H

#include <QMainWindow>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <gui_pais.h>
#include <pais_model.h>
#include <generador_random.h>
#include <jugador_model.h>


namespace Ui {
class juego_1;
}

class juego_1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit juego_1(QWidget *parent = 0);
    explicit juego_1(QString user, QWidget *parent=0);
    ~juego_1();
void lanzar_preg();/** Preguntas sobre capitales (todo continente) **/
void lanzar_preg(QVector<int> rango);
void lanzar_preg_america();/** Exclusivamente sobre America **/


int GetRandomNumber( int semilla, const int min, const int max);
private slots:
void on_btn_juego1_clicked();

void on_pushButton_clicked();

private:
    Ui::juego_1 *ui;
    pais_model pais_m;
    generador_random gen_random;
    QString id_pais,  respuesta;
    QVector<int> ids_opc;
    jugador_model Player;
    QVector<int> Desordenar( QVector<int>);
    void iconoContinente(QString);
    void Desordenar();
    void formularOpciones( );
    void subirNivel();

};

#endif // JUEGO_1_H
