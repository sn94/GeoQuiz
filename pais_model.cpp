#include "pais_model.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>


pais_model::pais_model()
{

}



pais_model::pais_model(QString ar)
{
this->codigo= ar;
this->buscar();
}


void pais_model::setModo(int arg){
    this->modo= arg;
}

void pais_model::setCodigo(QString ar){
    this->codigo= ar;
}

void pais_model::setNombre(QString ar){
    this->nombre= ar;
}
void pais_model::setContinente(QString ar){
    this->continente= ar;
}
void pais_model::setCapital(QString ar){
    this->capital= ar;
}

QString pais_model::getCodigo(){
    return this->codigo;
}
QString pais_model::getCodigo(QString str){
    this->nombre_pattern= str; this->buscar();
    return this->codigo;
}

int pais_model::getMin(){  this->getMinMax();return this->min;}
int pais_model::getMax(){  this->getMinMax(); return this->max;}







QString pais_model::getNombre(){
    return this->nombre;
}
QString pais_model::getContinente(){
    return this->continente;
}
QString pais_model::getCapital(){
    return this->capital;
}


QVector<int> pais_model::getMinMax(){
QSqlQuery query; query.exec("select min(pais_cod),max(pais_cod) from paises "+this->getSearchWord());
QString ini="",  fin="";
QVector<int> vec(2, 0);

if( query.isActive()){
    if(query.next()){
        ini=  query.value(0).toString(); this->min= ini.toInt();
          fin= query.value(1).toString();this->max= fin.toInt();
     vec[0]= ini.toInt(); vec[1]= fin.toInt(); qDebug()<< vec[0] <<"  "<< vec[1];
    }

}
return vec;
}


int pais_model::getTotalPaises(){
QSqlQuery query("select count(pais_cod) from paises "+this->getSearchWord());
int re= -1;
if( query.isActive()){
    if(query.next()){  re= query.value(0).toInt();  qDebug()<<" Total de paises "<< re;}
}
    return re;
}

QString pais_model::getSearchWord(){
   QString r="";
   if(this->modo== 0 ) r="";
   if( this->modo==1) r=" where lower(pais_continente) like  '%am_rica%'";
   if(this->modo== 2) r=" where lower(pais_continente) like  'europa%'";
   if(this->modo== 3) r=" where lower(pais_continente) like  'asia%'";
   if(this->modo==  4) r=" where lower(pais_continente) like  '_frica%'";
   if(this->modo==  5) r= " where lower(pais_continente) like  'ocean_a%'";

   return r;
}

void pais_model::buscar(){
QString condicion="";
if( this->nombre_pattern != ""){
 condicion=" where  trim(lower(pais_name)) like '"+ this->nombre_pattern.toLower() +"%'";
}else{
condicion=" where pais_cod="+this->codigo;
}
    QSqlQuery query;
    query.exec("select pais_cod, pais_name, pais_continente, pais_capital from paises "+ condicion);
    if(  query.next()){
      this->setCodigo( query.value(0).toString() );
            this->setNombre( query.value(1).toString() );
             this->setContinente( query.value(2).toString() );
              this->setCapital( query.value(3).toString() );
    }else{   qDebug()<< "No encontrado en paises"; }
}


void pais_model::crear(){
    QSqlQuery query;
    query.prepare("insert into paises( pais_cod, pais_name, pais_continente, pais_capital) values ("
                  ":cod, :nom, :conti, :capi )");
    query.bindValue(":cod", this->getCodigo());
    query.bindValue(":nom", this->getNombre());
    query.bindValue(":conti", this->getContinente());
    query.bindValue(":capi", this->getCapital());
    query.exec();
    if( query.numRowsAffected() > 0){
      //  QMessageBox::critical(0, "", "Pais creado!");
        qDebug() << "Pais creado ";
    }else{
       // QMessageBox::critical(0, "", "No se pudo crear el pais!");
          qDebug() << "No se pudo registrar el pais ";
    }
}



void pais_model::editar(){
    QSqlQuery query;
query.prepare("update paises set pais_name= :nom , pais_continente= :conti, pais_capital= :capi) where pais_cod= :cod");

    query.bindValue(":cod", this->getCodigo());
    query.bindValue(":nom", this->getNombre());
    query.bindValue(":conti", this->getContinente());
    query.bindValue(":capi", this->getCapital());
    query.exec();
    if( query.numRowsAffected() > 0){
      //  QMessageBox::critical(0, "", "Pais actualizado!");
          qDebug() << "Pais editado ";
    }else{
      //  QMessageBox::critical(0, "", "No se pudo crear el jugador!");
          qDebug() << "No se pudo editar pais ";
    }
}

