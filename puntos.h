#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

struct Puntos{
    int puntosPregunta;
    int puntosPartida;
    int puntosTotales;
    int diferencia;
};

typedef struct Puntos * PuntosPtr;

PuntosPtr iniciarPuntosEnCero();
void puntosPorResponder(PuntosPtr p,int tiempo);
void puntosFinalPartida(PuntosPtr p);



#endif // PUNTOS_H_INCLUDED
