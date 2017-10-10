#include "gui_pais.h"
#include "ui_gui_pais.h"
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QSqlError>


gui_pais::gui_pais(){

}

gui_pais::~gui_pais()
{
    delete this;
}


QVector<int> gui_pais:: max_paises(){
QSqlQuery query; query.exec("select min(pais_cod),max(pais_cod) from paises");
QString ini="",  fin="";
QVector<int> vec(2, 0);

if( query.isActive()){
    if(query.next()){
        ini=  query.value(0).toString();
          fin= query.value(1).toString();
     vec[0]= ini.toInt(); vec[1]= fin.toInt(); qDebug()<< vec[0] <<"  "<< vec[1];
    }

}
return vec;
}



QVector<int> gui_pais:: paises_america(){
    QSqlQuery query; query.exec("select min(pais_cod),max(pais_cod)  from paises where lower(pais_continente) like '%am_rica%'");
    QString ini="",  fin="";
    QVector<int> vec(2, 0);

    if( query.isActive()){
        ini=  query.value(0).toString();
          fin= query.value(1).toString();
     vec[0]= ini.toInt(); vec[1]= fin.toInt(); qDebug()<< vec[0] <<"  "<< vec[1];
    }
    return vec;

}

QVector<int> gui_pais:: paises_europa(){
    QSqlQuery query; query.exec("select min(pais_cod),max(pais_cod)  from paises where lower(pais_continente) like 'europa%'");
    QString ini="",  fin="";
    QVector<int> vec(2, 0);

    if( query.isActive()){
        ini=  query.value(0).toString();
          fin= query.value(1).toString();
     vec[0]= ini.toInt(); vec[1]= fin.toInt(); qDebug()<< vec[0] <<"  "<< vec[1];
    }
    return vec;

}

QVector<int> gui_pais:: paises_asia(){
    QSqlQuery query; query.exec("select min(pais_cod),max(pais_cod)  from paises where lower(pais_continente) like 'asia%'");
    QString ini="",  fin="";
    QVector<int> vec(2, 0);

    if( query.isActive()){
        ini=  query.value(0).toString();
          fin= query.value(1).toString();
     vec[0]= ini.toInt(); vec[1]= fin.toInt(); qDebug()<< vec[0] <<"  "<< vec[1];
    }
    return vec;

}

QVector<int> gui_pais:: paises_africa(){
    QSqlQuery query; query.exec("select min(pais_cod),max(pais_cod)  from paises where lower(pais_continente) like '_frica%'");
    QString ini="",  fin="";
    QVector<int> vec(2, 0);

    if( query.isActive()){
        ini=  query.value(0).toString();
          fin= query.value(1).toString();
     vec[0]= ini.toInt(); vec[1]= fin.toInt(); qDebug()<< vec[0] <<"  "<< vec[1];
    }
    return vec;

}
QVector<int> gui_pais:: paises_oceania(){
    QSqlQuery query; query.exec("select min(pais_cod),max(pais_cod)  from paises where lower(pais_continente) like 'ocean_a%'");
    QString ini="",  fin="";
    QVector<int> vec(2, 0);

    if( query.isActive()){
        ini=  query.value(0).toString();
          fin= query.value(1).toString();
     vec[0]= ini.toInt(); vec[1]= fin.toInt(); qDebug()<< vec[0] <<"  "<< vec[1];
    }
    return vec;

}




QString gui_pais::generarcod(){
    QString cons= "select coalesce(max(pais_cod), 0)+1 from paises";
    QSqlQuery query; query.exec( cons );
    if( query.next()){
        qDebug() <<  "HEY ";
        return query.value(0).toString();
    }else{  return ""; }
}


void gui_pais::registrar_(QString conti, QString pais, QString capital){

    QSqlQuery  query;
    query.prepare("insert into paises(pais_cod, pais_name, pais_capital,pais_continente) values(:COD, :NOM, :CAPITAL, :CONTINENTE)");
    query.bindValue(":COD", generarcod() );
    query.bindValue(":NOM", pais);
    query.bindValue(":CAPITAL",  capital);
    query.bindValue(":CONTINENTE", conti);
    query.exec();
    if(  query.numRowsAffected() >0){
        qDebug() << "Grabado ";
    }else{  qDebug() << "NO grabado " + query.lastError().text();}
}





QVector<QString>  gui_pais::datos(QString cod){
      QVector <QString> dats(3, "");
    QSqlQuery  query("select pais_name,pais_capital, pais_continente from paises where pais_cod="+ cod );
    if( query.next()){

      dats[0]= query.value(0).toString();
       dats[1]= query.value(1).toString();
        dats[2]= query.value(2).toString();
    return dats;
    }else{
        return dats;
    }
}





void  gui_pais::registrar(){
    QFile file_for_reading( "lista_paises.txt" );
   file_for_reading.open(QIODevice::ReadOnly); // Modo de apertura solo lectura
QTextStream lect_str( &file_for_reading);

//Reset the position on the file
lect_str.seek(0);

 QString s_Continente="", s_Pais="", s_Capital= "";

while( ! lect_str.atEnd()){

    QString linea= lect_str.readLine();

    QStringList linea_d= linea.split('\t');

    s_Continente= linea_d[0]; s_Pais=  linea_d[1];  s_Capital=  linea_d[2];

    qDebug() << s_Continente;
    qDebug() << s_Pais;
     qDebug() << s_Capital;

     registrar_(s_Continente, s_Pais, s_Capital);
} file_for_reading.close();
}



