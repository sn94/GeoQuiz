#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    explicit menu(QWidget *parent=0, QString usu_log="");
    ~menu();

private:
    Ui::menu *ui;
   void jugar_capitales();
   void jugar_paisajes();
   void jugar_banderas();

private slots:
    void abm();

    void on_btn_juego2_clicked();
    void on_btn_banderas_2_clicked();
    void on_btn_juego3_clicked();
    void on_btn_editar_jug_clicked();
};

#endif // MENU_H
