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
#include <unistd.h>

void inicio(){
    char mensaje[] = "...\n";

    for(int j=0; j<5;j++){
        printf("\n\tINICIANDO");
    for (int i = 0; mensaje[i] != '\0'; i++) {
        putchar(mensaje[i]);
        fflush(stdout);
        usleep(300000);

    }
    system("cls");
    }
    printf("\n\t=================");
    printf("\n\t  M A R E A L E  \n");
    printf("\t=================\n");
}

void iniciarJuego(Lista listaJugadoresGlobal, Lista listaPartida, Lista listaPreguntas, Lista listaRespuestas){

    int opcion;

    cargarJugadoresAListaDesdeTxt(listaJugadoresGlobal);
    cargarRespuestaAListaDesdeTxt(listaRespuestas);
    cargarPreguntaAListaDesdeTxt(listaPreguntas, listaRespuestas);

    inicio();

    presioneEnterParaContinuar();

    do{

        printf("\nPresione el numero de la opcion que desea utilizar...\n\n");
        printf("\n1 --> Jugar\n");
        printf("\n2 --> Lista de jugadores\n");
        printf("\n3 --> Como jugar?\n");
        printf("\n4 --> Cerrar\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        system("cls");

        switch (opcion){
        case 1: printf("\nJ U G A R\n");
                jugar(listaJugadoresGlobal,listaPartida,listaPreguntas);
                guardarJugadoresATxtDesdeLista(listaJugadoresGlobal);
            break;
        case 2: printf("\nL I S T A  D E  J U G A D O R E S\n");
                mostrarListaJugadores(listaJugadoresGlobal);
            break;
        case 3: printf("\nC O M O  J U G A R ?\n");
                ayuda();
            break;
        case 4:
            break;
        default: printf("ERROR!!! La opcion que intentas ingresar no existe...");
            break;
        }
        if(opcion != 4 ){
            presioneEnterParaContinuar();
        }

    }while(opcion != 4);
}

void presioneEnterParaContinuar(){

    char continuar[10] = " ";
    printf("\nPresione - ENTER - para continuar");
    fflush(stdin);
    gets(continuar);
    system("cls");
}

void jugar(Lista listaJugadoresGlobal, Lista listaPartida, Lista listaPreguntas){
    int opcion;
    do{
        printf("\nSeleccione cuantos jugadores quieren jugar - (2 a 4)\n\nOpcion: ");
        scanf("%d", &opcion);
        if(opcion != 2 && opcion != 3 && opcion != 4){
            printf("\nERROR! No es posible esa cantidad de jugadores\n");

        }
        presioneEnterParaContinuar();
    }while(opcion != 2 && opcion != 3 && opcion != 4);
    cargarJugadoresAListaPorTeclado(listaPartida, listaJugadoresGlobal, opcion);
    jugadoresRespondenPreguntas(listaPartida,listaPreguntas);

    mostrarListaJugadores(listaPartida);
    buscarGanador(listaPartida);

    actualizarListaJugadores(listaPartida,listaJugadoresGlobal);

    liberarlista(listaPartida);//remover toda la lista de partida
}

void ayuda(){
    printf("\nEn este emocionante juego de preguntas y respuestas, pondras a prueba tus\n");
    printf("conocimientos y competiras contra tus amigos. El juego admite de 2 a 4.\n");
    printf("El objetivo es simple: responder preguntas correctamente y mantener tu racha.\n");
    printf("\nComenzara la partida el jugador 1  y respondera una pregunta. Si la respuesta\n");
    printf("es correcta, continua su turno y enfrenta la proxima pregunta. La clave esta en\n");
    printf("no cometer errores, ya que cuando te equivoques, el turno pasara al siguiente \n");
    printf("jugador.\n");
    printf("\nAclaracion, solo tendran 15 segundos para contestar correctamente. Si contesta\n");
    printf("en los primeros 5 segundos se llevara 20 puntos, despues de los 5 pero antes de\n");
    printf("los 10, se llevara 15, y en los ultimos 5 segundos se llevara solo 10 puntos.\n");
    printf("Si pasan los 15 segundos la respuesta sera anulada y no ganara puntos.\n");
    printf("\nLa competencia sigue su curso asi con cada jugador, tratando de acumular la\n");
    printf("mayor cantidad de respuestas correctas. Eso es todo lo que debes saber...\n");
    printf("\nQue comience el juego y que el mas astuto se corone como el campeon!\n");
}
