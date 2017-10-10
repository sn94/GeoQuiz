#-------------------------------------------------
#
# Project created by QtCreator 2017-08-04T21:49:54
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GeoQuiz
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        menu.cpp \
    gui_jugador.cpp \
    conexion.cpp \
    gui_edit_jugador.cpp \
    menu_abm.cpp \
    login.cpp \
    gui_pais.cpp \
    leer_texto.cpp \
    bandera.cpp \
    juego_1.cpp \
    mainwindow.cpp \
    pieceslist.cpp \
    puzzlewidget.cpp \
    jugador_model.cpp \
    pais_model.cpp \
    imagenes_model.cpp \
    juego_2.cpp \
    generador_random.cpp \
    reg_paisajes.cpp \
    custommensaje.cpp \
    cargador.cpp \
    test.cpp

HEADERS += \
        menu.h \
    gui_jugador.h \
    conexion.h \
    gui_edit_jugador.h \
    menu_abm.h \
    login.h \
    gui_pais.h \
    leer_texto.h \
    bandera.h \
    juego_1.h \
    mainwindow.h \
    pieceslist.h \
    puzzlewidget.h \
    jugador_model.h \
    pais_model.h \
    imagenes_model.h \
    juego_2.h \
    generador_random.h \
    reg_paisajes.h \
    custommensaje.h \
    cargador.h \
    test.h

FORMS += \
        menu.ui \
    gui_jugador.ui \
    gui_edit_jugador.ui \
    menu_abm.ui \
    login.ui \
    juego_1.ui \
    mainwindow.ui \
    juego_2.ui \
    cargador.ui \
    test.ui

DISTFILES +=

RESOURCES += \
    assets/imagenes.qrc
