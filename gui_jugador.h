#ifndef GUI_JUGADOR_H
#define GUI_JUGADOR_H

#include <QMainWindow>
#include <jugador_model.h>

namespace Ui {
class gui_jugador;
}




class gui_jugador : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui_jugador(QWidget *parent = 0);
    ~gui_jugador();

private slots:
    void on_grbr_jugador_clicked();

private:
    Ui::gui_jugador *ui;// Puntero que permite acceder a los objetos de la UI
    jugador_model jugador;
 int guardarJugador();

};

#endif // GUI_JUGADOR_H
