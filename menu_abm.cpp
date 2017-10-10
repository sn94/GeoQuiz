#include "menu_abm.h"
#include "ui_menu_abm.h"

menu_abm::menu_abm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu_abm)
{
    ui->setupUi(this);
}

menu_abm::~menu_abm()
{
    delete ui;
}
