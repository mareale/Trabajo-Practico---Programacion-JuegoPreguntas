#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED
#include "respuesta.h"
#include "lista.h"


struct Pregunta{
    int numPregunta;
    char pregunta[70];
    RespuestaPtr respuestas[4];
};

typedef struct Pregunta * PreguntaPtr;


PreguntaPtr crearPreguntaVacia();

void mostrarPregunta(PreguntaPtr p);
void mostrarListaPregunta(Lista lista);
PreguntaPtr preguntaRandom(Lista lista);

PreguntaPtr transformarTextoAPregunta(char c[], int t);
void cargarPreguntaAListaDesdeTxt(Lista listaP, Lista listaR);
void cargarRespuestasAPregunta(PreguntaPtr p, Lista listaR);

int preguntaEmpate();

#endif // PREGUNTA_H_INCLUDED
