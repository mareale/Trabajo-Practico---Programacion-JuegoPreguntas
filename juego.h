#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "lista.h"

void inicio();
void iniciarJuego(Lista listaJugadoresGlobal, Lista listaPartida, Lista listaPreguntas, Lista listaRespuestas);
void presioneEnterParaContinuar();

void jugar(Lista listaJugadoresGlobal, Lista listaPartida, Lista listaPreguntas);
void ayuda();

#endif // JUEGO_H_INCLUDED
