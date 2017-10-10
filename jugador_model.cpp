#include "jugador_model.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <pais_model.h>


jugador_model::jugador_model()
{



}

jugador_model::jugador_model(QString codigo)
{

this->id= codigo;
 this->buscar();
}


void jugador_model::setModo(char arg){
    this->modo= arg;
}

void jugador_model::setCodigo(QString arg){
this->id= arg;
}

void jugador_model::setNombre(QString a){
    this->nombre=  a;
}

void jugador_model::setApellido( QString a){
    this->apellido= a;
}

void jugador_model::setUsuario(QString ar){
    this->usuario= ar;
}


void jugador_model::setClave(QString a){
    this->clave= a;
}

void jugador_model::setPuntajeCapitales(int a){
    this->p_capitales= a;
}
void jugador_model::setPuntajePaisajes(int a){
    this->p_paisajes= a;
}

void jugador_model::setPuntajeBanderas(int a){
    this->p_banderas= a;
}

QString jugador_model::getCodigo(){
    return this->id;
}

QString jugador_model::getNombre(){
    return this->nombre;
}
QString jugador_model::getApellido(){
    return this->apellido;
}
QString jugador_model::getUsuario(){
    return this->usuario;
}
QString jugador_model::getClave(){
    return this->clave;
}
int jugador_model::getPuntaje(){
    if(this->modo=='C')
    return this->p_capitales;
    else{
        if(this->modo=='P') return this->p_paisajes;
        else return this->p_banderas;
    }
}


int jugador_model::getNivel(){

    //determina el total de paises para
    //cada continente  tc1 tc2 tc3 tc4 tc5
    pais_model pais; pais.setModo( 1 );
    int america= pais.getTotalPaises();
    pais.setModo( 2  );
    int europa= pais.getTotalPaises();
    pais.setModo( 3 );
    int asia= pais.getTotalPaises();
    pais.setModo(  4  );
    int africa= pais.getTotalPaises();
    pais.setModo(  5 );
    int oceania= pais.getTotalPaises();


int puntaj= this->getPuntaje();
int level= 1;
if( puntaj <= america){
 level=1;
}
else{
if(puntaj <= (europa+america) ) level= 2;
else{
    if( puntaj <= (asia+europa+america) ) level = 3;
    else{
    if(puntaj <=  (africa+asia+europa+america)  ) level= 4;
    else{
    if( puntaj < (oceania+africa+asia+europa+america)  ) level= 5;
    else if( puntaj == (oceania+africa+asia+europa+america)  ){ level= 6;}/** *** ***/
    }
    }
}/** ** ** **/

}
this->nivel= QString::number(level);
    //si el puntaje acumulado es menor a tc1 sigue en nivel 1 sino, pasa al 2. Si supera tc5 gana el juego
    return this->nivel.toInt(); }



QString jugador_model::gencod(){
    QString cons= "select coalesce(max(jug_cod), 0)+1 from jugadores";
    QSqlQuery query; query.exec( cons );
    if( query.next()){   return query.value(0).toString();
    }else{  return ""; }
}
QString jugador_model::gencod2(){
    QString cons= "select coalesce(max(id), 0)+1 from puntaje";
    QSqlQuery query; query.exec( cons );
    if( query.next()){   return query.value(0).toString();
    }else{  return ""; }
}


void jugador_model::buscar(){
    QString condicion1=" j.jug_login like '%"+this->getUsuario()+"%'";
    QString condicion2= " j.jug_cod="+ this->id;
    QString condicion= this->id.isEmpty()? condicion1: condicion2;
 QString str= "select j.jug_cod, j.jug_name, j.jug_ape, j.jug_login, j.jug_pass, p.juego_capi as p1, p.juego_paisaje as p2,p.juego_band as p3  from jugadores j, puntaje p    where  j.jug_cod = p.jug_cod and "+ condicion;

    QSqlQuery query(str);
    if(query.isActive()){
        if(  query.next()){
       this->setCodigo( query.value(0).toString() );
     this->setNombre( query.value(1).toString());
     this->setApellido( query.value(2).toString());
     this->setUsuario( query.value(3).toString() );
     this->setClave( query.value(4).toString() );
            this->p_capitales= query.value(5).toInt();
            this->p_paisajes= query.value(6).toInt();
            this->p_banderas= query.value(7).toInt();
       }
    }/** ES ACTIVO **/
 else{  qDebug()<< "No activo";}/** no activo **/
}

int jugador_model::crear(){
 QSqlQuery q; q.prepare("insert into jugadores(jug_cod, jug_name, jug_ape, jug_login, jug_pass) "
                        "values(:id, :nom, :ape, :log, :pass )"); QString gc= this->gencod();
 q.bindValue(":id", gc);
 q.bindValue(":nom", this->getNombre());
 q.bindValue(":ape", this->getApellido());
 q.bindValue(":log",this->getUsuario());
 q.bindValue(":pass", this->getClave());
 q.exec();
 if( q.numRowsAffected() > 0  && this->crear_puntaje( gc)){
return q.numRowsAffected();
 }else{  return -1; }

}


int jugador_model::editar(){
 QSqlQuery q; q.prepare("update jugadores set jug_name= :nom , jug_ape= :ape , jug_login= :log, jug_pass= :pass  where  jug_cod= :id");

 q.bindValue(":id", this->getCodigo() );
 q.bindValue(":nom", this->getNombre());
 q.bindValue(":ape", this->getApellido());
 q.bindValue(":log",this->getUsuario());
 q.bindValue(":pass", this->getClave());
 q.exec();

 if( q.numRowsAffected() > 0){   return 1;
 }else{   return -1; }

}


bool jugador_model::crear_puntaje( QString newid){
    //Crear tabla de puntaje
    QString sq="insert into puntaje(id,juego_capi, juego_paisaje,juego_band,jug_cod) values(:cod,:p1,:p2,:p3,:jugador)";

    QSqlQuery q1; q1.prepare(sq);
    q1.bindValue(":cod", this->gencod2());
    q1.bindValue(":p1",0);  q1.bindValue(":p2",0);  q1.bindValue(":p3",0);
      q1.bindValue(":jugador", newid);
    q1.exec();
    return q1.numRowsAffected()>0;
}



bool jugador_model::sumarPuntaje(){
    //Crear tabla de puntaje
    QString nom_juego= this->modo=='C'?"juego_capi": this->modo=='P'?"juego_paisaje":"juego_band";
    if( this->getNivel()!= 6 ){
    QSqlQuery q1("update puntaje set "+nom_juego+"="+nom_juego+"+1  where jug_cod="+this->getCodigo());

    if(q1.numRowsAffected()>0) {
        if(this->modo=='C' && this->getNivel()!=6 ) ++this->p_capitales;
        if(this->modo=='P') ++this->p_paisajes;
         if(this->modo=='B'  && this->getNivel()!=6)   ++this->p_banderas;  return true;}
        return false;
} return false;}
