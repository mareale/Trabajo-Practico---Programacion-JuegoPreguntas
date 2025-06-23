#ifndef RESPUESTA_H_INCLUDED
#define RESPUESTA_H_INCLUDED
#include "lista.h"


struct Respuesta{
    char respuesta[25];
    int numRespuesta;
    int numRelacion;
    int correcta;//0 o 1
};

typedef struct Respuesta * RespuestaPtr;

RespuestaPtr crearRespuestaVacia();
void iniciarRespuestasVacias(RespuestaPtr rs[], int t);

RespuestaPtr transformarTextoARespuestaa(char c[], int t);
void cargarRespuestaAListaDesdeTxt(Lista lista);

void mostrarRespuesta(RespuestaPtr r);
void mostrarListaRespuesta(Lista lista);
void mostrarArrayRespuestas(RespuestaPtr rs[], int t);

void RandomRespuestas(RespuestaPtr rs[], int t);
void ordenarArrayRespuestas(RespuestaPtr rs[], int t);
int buscarRespuestaCorrecta(RespuestaPtr rs[], int t);

#endif // RESPUESTA_H_INCLUDED
