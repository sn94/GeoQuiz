#ifndef GENERADOR_RANDOM_H
#define GENERADOR_RANDOM_H


class generador_random
{
public:
    generador_random();
    generador_random(int min, int max);
    void setMin( int );
    void setMax(int );
    int getMin();
    int getMax();
    int generar();
private:
        int minimo, maximo, semilla;
};

#endif // GENERADOR_RANDOM_H
