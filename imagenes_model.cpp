#include "imagenes_model.h"
#include <QSqlQuery>
#include <QVariant>
#include <QByteArray>
#include <QDebug>

imagenes_model::imagenes_model()
{

}


imagenes_model::imagenes_model( QString id)
{
this->id= id;
}


void imagenes_model::setId(QString a){
    this->id= a;
}

void imagenes_model::setNivelJugador(int ar){
    this->nivelJugador=   ar;
}

void imagenes_model::setModoBuscar(char a){
 this->modo= a;
 this->getCodMinMax();
}
void imagenes_model::setFormato(QString arg){
    this->formato= arg;
}

int imagenes_model::getMinCod(){
    return this->min;
}
int imagenes_model::getMaxCod(){
    return this->max;
}

QPixmap imagenes_model::imagen_bandera(){
    QSqlQuery q; q.exec("select band_imagen from banderas where band_cod="+this->id);
    QPixmap px;
    if( q.next()){
       QByteArray b= q.value(0).toByteArray();
       QByteArray c= QByteArray::fromBase64(  b );
       if(this->formato == "PNG"){

       px.loadFromData( c,"PNG");
       }else        px.loadFromData( c,"JPG");

    }  return px;
}

QPixmap imagenes_model::imagen_paisaje(){
    QSqlQuery q; q.exec("select paisaje_ruta from paisajes where paisaje_cod="+this->id);
    QPixmap px;
    if( q.next()){
       QByteArray b= q.value(0).toByteArray();
       QByteArray c= QByteArray::fromBase64(  b );
       if(this->formato == "PNG")
       px.loadFromData( c,"PNG");
       else        px.loadFromData( c,"JPG");

    }  return px;
}




QVector<int> imagenes_model::getCodMinMax(){
    int jugnivel=  this->nivelJugador;
    QString r="";
    if(jugnivel== 0) r="";
    if( jugnivel ==1) r=" lower(p.pais_continente) like  '%am_rica%'";
    if(jugnivel == 2) r="  lower(p.pais_continente) like  'europa%'";
    if( jugnivel== 3) r="  lower(p.pais_continente) like  'asia%'";
    if(  jugnivel ==  4) r="  lower(p.pais_continente) like  '_frica%'";
    if( jugnivel==  5) r= "  lower(p.pais_continente) like  'ocean_a%'";


    QString sc="";
    if( this->modo== 'P')
        sc= "select min(paisaje_cod),max(paisaje_cod) from paisajes";
    else
        sc="select min(b.band_cod),max(b.band_cod) from banderas b,paises p where b.pais_cod=p.pais_cod   "+(r==""?"":" and "+r);
QSqlQuery query; query.exec(  sc );
QString ini="",  fin="";
QVector<int> vec(2, 0);

if( query.isActive()){
    if(query.next()){
        ini=  query.value(0).toString();
          fin= query.value(1).toString();
     vec[0]= ini.toInt(); vec[1]= fin.toInt();
     this->min= vec[0];  this->max= vec[1];
    }

}
return vec;
}


QString imagenes_model::getNombre(){
    QString sc="";
    if( this->modo== 'P')
        sc= "select paisaje_nom from paisajes where paisaje_cod="+this->id;
    else
        sc="select band_nombre from banderas where band_cod="+this->id;
QSqlQuery query; query.exec(  sc ); QString ini= "";
if( query.isActive()){
    if(query.next()){   ini=  query.value(0).toString();  }}
return ini;
}




QString imagenes_model::getPista(){
    QString sc="";
    if( this->modo== 'P')
        sc= "select pista from paisajes where paisaje_cod="+this->id;
    else
        sc="select band_pista from banderas where band_cod="+this->id;
QSqlQuery query; query.exec(  sc ); QString ini= "";
if( query.isActive()){
    if(query.next()){   ini=  query.value(0).toString();  }}
return ini;
}
