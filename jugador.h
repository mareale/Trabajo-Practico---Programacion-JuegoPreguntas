#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "lista.h"
#include "puntos.h"

struct Jugador{
    char usuario[25];
    int dni;
    PuntosPtr p;
};

typedef struct Jugador * JugadorPtr;

JugadorPtr cargarJugadorPorTeclado(Lista listaGlobal);
void cargarJugadoresAListaPorTeclado(Lista listaPartida, Lista listaGlobal, int cantJugadores);

void mostrarJugador(JugadorPtr j);
void mostrarListaJugadores(Lista lista);

JugadorPtr transformarTextoAJugador(char c[], int t);
void cargarJugadoresAListaDesdeTxt(Lista lista);
void guardarJugadoresATxtDesdeLista(Lista lista);
void actualizarListaJugadores(Lista listaPartida,Lista listaGlobal);

int buscarJugadorDni(Lista lista, int dniBusco);

int jugadorRespondePregunta(JugadorPtr j,Lista listaP);
void jugadoresRespondenPreguntas(Lista listaJ, Lista listaP);

void buscarGanador(Lista listaPartida);
int chequearSiHayEmpate(int maxPuntos, Lista listaPartida);
int desempate(Lista listaPartida, int maxPuntos);
int chequearSiHayEmpateDelEmpate(int menorDiferencia, Lista listaPartida);

#endif // JUGADOR_H_INCLUDED
