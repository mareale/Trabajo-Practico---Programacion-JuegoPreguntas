#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "juego.h"
#include "lista.h"
#include "jugador.h"
#include "puntos.h"
#include "pregunta.h"
#include "respuesta.h"

int main()
{
    srand(time(0));

    Lista listaGlobal = crearLista(sizeof(JugadorPtr));
    Lista listaPartida = crearLista(sizeof(JugadorPtr));
    Lista listaPreguntas = crearLista(sizeof(PreguntaPtr));
    Lista listaRespuestas = crearLista(sizeof(RespuestaPtr));

    iniciarJuego(listaGlobal,listaPartida,listaPreguntas,listaRespuestas);

    return 0;
}
