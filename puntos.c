#include <stdio.h>
#include <stdlib.h>
#include "puntos.h"
#include "jugador.h"


PuntosPtr iniciarPuntosEnCero(){
    PuntosPtr p = (PuntosPtr)malloc(sizeof(struct Puntos));

    p->puntosPregunta = 0;
    p->puntosPartida = 0;
    p->puntosTotales = -1;
    p->diferencia=0;
    return p;
}

void puntosPorResponder(PuntosPtr p, int tiempo){
    if(tiempo>=10){
        p->puntosPregunta = 10;
    }
    if(tiempo<10 && tiempo >=5){
        p->puntosPregunta = 15;
    }
    if(tiempo<5){
        p->puntosPregunta = 20;
    }
    p->puntosPartida = p->puntosPartida + p->puntosPregunta;
    printf("\nCORRECTO!\nTiempo en contestar: %ds\nSUMASTE %d PUNTOS\n", tiempo, p->puntosPregunta);
    p->puntosPregunta = 0;
}

void puntosFinalPartida(PuntosPtr p){
    p->puntosTotales = p->puntosPartida;
}
