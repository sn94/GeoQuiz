#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QMainWindow>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <generador_random.h>
#include <jugador_model.h>

class PiecesList;
class PuzzleWidget;
class QListWidgetItem;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QString, QWidget *parent=0);
    ~MainWindow();
    void loadImage();
    void loadImage(const QString &path);
    void loadImage(QPixmap);

   public slots:
       void openImage();
       void setupPuzzle();

   private slots:
       void setCompleted();
       void ir_menu();
       void lanzar_pista();
       void evaluar_respuesta();

   private:

    Ui::MainWindow *ui;
    void setupMenus();
    void habilitarOpciones();
   void genCodigoPaisaje();
    void setupPregunta();
    void generarpregunta();
    void generarOpcionesMarcar();
    void setupWidgets();
     QString id_paisaje, respuesta;
generador_random gen_random;

    QPixmap puzzleImage;
    PiecesList *piecesList;
    PuzzleWidget *puzzleWidget;


   QLabel *l_puntaje, *l_usu_name;
    QPushButton *l_pista;
    QLabel *l_pregunta;
    QRadioButton *opc1, *opc2, *opc3;
QPushButton *siguiente;
QVector<int> ids_opc;
jugador_model Player;

};

#endif // MAINWINDOW_H
