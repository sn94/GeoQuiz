#ifndef CARGADOR_H
#define CARGADOR_H

#include <QMainWindow>

namespace Ui {
class Cargador;
}

class Cargador : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cargador(QWidget *parent = 0);
    ~Cargador();

private:
    Ui::Cargador *ui;
     QTimer *timer;
    void crono();
    int contador= 0;

  private slots:
    void updateCaption();
};

#endif // CARGADOR_H
