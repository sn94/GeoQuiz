#include "generador_random.h"
#include <time.h>
#include <QTime>

generador_random::generador_random()
{
    this->semilla= time(NULL);
      srand(  this->semilla);
}


generador_random::generador_random(int min, int max)
{
this->semilla= time(NULL);
  srand(  this->semilla);
this->minimo= min;
this->maximo= max;
}


void generador_random::setMin(int a){
    this->minimo= a;
}


void generador_random::setMax(int a){
    this->maximo= a;
}



int generador_random::getMin(){
    return this->minimo;
}



int generador_random::getMax(){
    return this->maximo;
}
int generador_random::generar(){
    //  numeros entre 0 y  50  int num=  rand()% 51;
    //  numeros entre 1 y 100 int num= 1+rand()%(101-1);
    //numero entre 250 y 420  int num= 250+rand()%(421-250)
    //general
    //var=  lim_inferior  + rand() % ( lim_superior + 1 - lim_inferior)
//start_required + ( generator_output *  range_required)/generator_maximum

// Numero Semilla - seed
  //  int crm= this->semilla;
    //srand(  crm);

 int num=   this->minimo + rand()  % ( this->maximo +1  - this->minimo );
    return  num;
}
