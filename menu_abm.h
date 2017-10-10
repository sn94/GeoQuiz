#ifndef MENU_ABM_H
#define MENU_ABM_H

#include <QMainWindow>

namespace Ui {
class menu_abm;
}

class menu_abm : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu_abm(QWidget *parent = 0);
    ~menu_abm();

private:
    Ui::menu_abm *ui;
};

#endif // MENU_ABM_H
