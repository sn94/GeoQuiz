#ifndef GUI_EDIT_JUGADOR_H
#define GUI_EDIT_JUGADOR_H

#include <QMainWindow>
#include <jugador_model.h>

namespace Ui {
class gui_edit_jugador;
}

class gui_edit_jugador : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui_edit_jugador(QWidget *parent = 0);
      explicit gui_edit_jugador(   QString, QWidget *parent = 0);
    ~gui_edit_jugador();

private:
    Ui::gui_edit_jugador *ui;
    jugador_model jugador;

private slots:
    int editar();
    int borrarJugador();


    void on_btn_editar_clicked();
};

#endif // GUI_EDIT_JUGADOR_H
