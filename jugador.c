#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jugador.h"
#include "puntos.h"
#include "lista.h"
#include "pregunta.h"
#include "juego.h"

JugadorPtr cargarJugadorPorTeclado(Lista listaGlobal){
    //Parametro lista global para garantizar si ya ingreso al juego anteriormente

    JugadorPtr j = (JugadorPtr) malloc(sizeof(struct Jugador));
    int cambiarUsuario;
    char aux[25]=" ";

    printf("\nDNI: ");
    scanf("%d", &j->dni);

    int busco = buscarJugadorDni(listaGlobal,j->dni); //Si la pos es -1, no lo encontro
    if (busco != -1){
        JugadorPtr encontrado = *( (JugadorPtr*) obtenerDato(listaGlobal, busco) );
        printf("\nYa habias jugado este juego, tu usuario es: %s", encontrado->usuario);
        printf("\nDeseas continuar con este usuario?\n\n");
        printf("0) Continuar con usuario actual\n");
        printf("1) Cambiar mi usuario\n\nOpcion: ");
        scanf("%d",&cambiarUsuario);
        if(cambiarUsuario==0){
            strcpy(j->usuario,encontrado->usuario);
        }else{
            printf("\nNuevo Usuario: ");
            fflush(stdin);
            gets(aux);
            strcpy(j->usuario, aux);
        }
    }else{

        printf("\nUsuario: ");
        fflush(stdin);
        gets(aux);
        strcpy(j->usuario, aux);
    }
    j->p = iniciarPuntosEnCero();

    presioneEnterParaContinuar();

    return j;
}

int buscarJugadorDni(Lista lista, int dniBusco){
    int pos = -1;

    for (int i = 0; i<obtenerTamanio(lista); i++){
        JugadorPtr j = *( (JugadorPtr*) obtenerDato(lista, i) );
        if (j->dni==dniBusco){
            pos = i;
        }
    }
    return pos;
}

void cargarJugadoresAListaPorTeclado(Lista listaPartida, Lista listaGlobal, int cantJugadores){//P=Partida - G=Global
    for(int i = 0; i<cantJugadores; i++){
        printf("\nComplete los datos del jugador %d\n",i+1);
        JugadorPtr j = cargarJugadorPorTeclado(listaGlobal);
        insertarFinal(listaPartida,&j);
    }
}

void mostrarJugador(JugadorPtr j){
    if(j->p->puntosTotales == -1){
    //Despues de terminar la partida los puntos totales estaran en -1
    //Luego de mostar la lista de la partida se cargaran en listaGlobal los puntos totales
        printf("\n%s\t%d\t%d", j->usuario, j->dni, j->p->puntosPartida);
    }else{
        printf("\n%s\t%d\t%d", j->usuario, j->dni, j->p->puntosTotales);
    }
};

void mostrarListaJugadores(Lista lista){

    if (estaVacia(lista)==TRUE){
        printf("\nLa lista de jugadores esta vacia...\n");

    }else{
        printf("\nUSUARIO \t  DNI   \tPUNTOS\n");
        for ( int i = 0; i < obtenerTamanio(lista); ++i) {

            JugadorPtr j = *( (JugadorPtr*) obtenerDato(lista, i) );

            mostrarJugador(j);
        }
    }
    printf("\n");
};


JugadorPtr transformarTextoAJugador(char c[], int t){
    //El formato es nombre;dni;puntos
    int pos1 = -1;
    int pos2 = -1;

    char auxUsuario[20]=" ";
    char auxDni[20]=" ";
    char auxPuntos[20]=" ";

    JugadorPtr j = (JugadorPtr) malloc(sizeof(struct Jugador));
    PuntosPtr aux = (PuntosPtr) malloc(sizeof(struct Puntos));

    for (int i = 0; i<t; i++){
        if(c[i]==';'){
            pos1 = i;
            i = t;
        }
    }
    for (int i = pos1+1; i<t; i++){
        if(c[i]==';'){
            pos2 = i;
            i = t;
        }
    }
    for ( int i = 0; i<pos1; i++){
        auxUsuario[i]= c[i];
    }
    for ( int i = pos1+1; i<pos2; i++){
        auxDni[i-pos1-1]= c[i];
    }
    for ( int i = pos2+1; i<t; i++){
        auxPuntos[i-pos2-1]= c[i];
    }
    strcpy(j->usuario,auxUsuario);
    j->dni = atoi(auxDni);
    aux->puntosTotales = atoi(auxPuntos);
    j->p = aux;

    return j;
};
void cargarJugadoresAListaDesdeTxt(Lista lista){

    FILE * archivo = fopen("listadejugadores.txt", "r");

    while(!feof(archivo)){

        char aux[30] = " ";

        fgets(aux, 30, archivo);

        JugadorPtr j = transformarTextoAJugador(aux,30);
        if(j->dni!=0){
            insertarFinal(lista,&j);
        }
    }
    fclose(archivo);
};

void guardarJugadoresATxtDesdeLista(Lista lista){

    FILE * archivo = fopen("listadejugadores.txt", "w");
    int primero = 1;

    for (int i = 0; i<obtenerTamanio(lista); i++){
            if(primero==0){
                fprintf(archivo, "\n");
            }

        JugadorPtr j = *( (JugadorPtr*) obtenerDato(lista, i) );
        fprintf(archivo, "%s;%d;%d", j->usuario, j->dni, j->p->puntosTotales);
        primero=0;

    }
    fclose(archivo);
};

void actualizarListaJugadores(Lista listaPartida,Lista listaGlobal){
    int busco;

    for(int i = 0; i<obtenerTamanio(listaPartida); i++){
        JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaPartida, i) );
        busco = buscarJugadorDni(listaGlobal,j->dni);
        puntosFinalPartida(j->p);

        if (busco != -1){
            JugadorPtr encontrado = *( (JugadorPtr*) obtenerDato(listaGlobal, busco) );
            strcpy(encontrado->usuario,j->usuario);

            if(j->p->puntosTotales > encontrado->p->puntosTotales){
                encontrado->p->puntosTotales = j->p->puntosTotales;
            }
        }else{
            insertarFinal(listaGlobal,&j);
        }
    }
}


int jugadorRespondePregunta(JugadorPtr j,Lista listaPreguntas){

    int retornar; //esta variable va a ser retornada para saber si contesto correctamente o no
    int opcionDelJugador;

    PreguntaPtr p = preguntaRandom(listaPreguntas);
    mostrarPregunta(p);
    int opcionCorrecta = buscarRespuestaCorrecta(p->respuestas,4);

    printf("\nOpcion: ");
    clock_t inicio = clock(); // Marcar el inicio del tiempo
    scanf("%d", &opcionDelJugador);
    clock_t fin = clock(); // Marcar el final del tiempo

    double tiempoTranscurrido = (double)(fin - inicio) / CLOCKS_PER_SEC;

    if (tiempoTranscurrido <= 15){

        if (opcionDelJugador==opcionCorrecta){
            puntosPorResponder(j->p,tiempoTranscurrido);
            retornar = 1;
        }else{
            printf("\nINCORRECTO!\n");
            printf("Sumaste en total %d Puntos\n", j->p->puntosPartida);
            retornar = 0;
        }
    }else{
        printf("\nTiempo agotado! No respondiste en 15 segundos.\n");
        retornar = 0;
    }

    presioneEnterParaContinuar();

    return retornar;

}
void jugadoresRespondenPreguntas(Lista listaJ, Lista listaP){

    for(int i = 0; i<obtenerTamanio(listaJ);i++){
        int correcta=1;
        JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaJ, i) );
        printf("\nTurno del jugador %d   -->  %s\n", i+1, j->usuario);
        printf("\nAl presionar continuar, aparecera la primer pregunta... Atento!");
        printf("\nRecuerda, tienes 15 segundos para responder.\n");
        presioneEnterParaContinuar();
        while(correcta==1){
            correcta = jugadorRespondePregunta(j,listaP);
        }

    }
}
void buscarGanador(Lista listaPartida){

    int maxPuntos = -1;
    int empataron;
    int posGanador;

        for(int i = 0; i<obtenerTamanio(listaPartida); i++){
            JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaPartida, i) );
            if(j->p->puntosPartida > maxPuntos){
                maxPuntos = j->p->puntosPartida;
                posGanador = i;

            }
        }
        empataron = chequearSiHayEmpate(maxPuntos, listaPartida);
        if(empataron>=2){
            printf("\nHay empate!!!\n");
            printf("\nEl jugador que mas se acerque al resultado de la siguiente operacion\nmatematica se llevara 10 punto para desempatar\n\n");
            presioneEnterParaContinuar();
            posGanador = desempate(listaPartida,maxPuntos);
        }
    JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaPartida, posGanador) );
    printf("\n!!! F E L I C I T A C I O N E S !!!\nEl ganador es: %s \n", j->usuario);
}

int chequearSiHayEmpate(int maxPuntos, Lista listaPartida){
    int chequeo = 0;//Esta variable va a contar cuantos jugadores tienen los mismos puntos
    for(int i = 0; i<obtenerTamanio(listaPartida); i++){
        JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaPartida, i) );

        if(j->p->puntosPartida==maxPuntos){
            chequeo++;
        }
    }
    return chequeo;
}

int desempate(Lista listaPartida, int maxPuntos){

    int resultado;
    int respuestaJugador;
    int menorDiferencia;
    int posGanador;
    int first = 0;
    int empataron;

    do{
        resultado = preguntaEmpate();
        for(int i = 0; i<obtenerTamanio(listaPartida); i++){
            JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaPartida, i) );

            //chequeo para saber QUIENES empataron y asi seleccionarlos para responder solo ellos
            if (j->p->puntosPartida==maxPuntos){
                printf("\nRespuesta de %s: ",j->usuario);
                scanf("%d", &respuestaJugador);

                //con el siguiente condicional me aseguro que la diferencia sea siempre positiva
                if(respuestaJugador>=resultado){
                    j->p->diferencia = respuestaJugador-resultado;
                }else{
                    j->p->diferencia = resultado-respuestaJugador;
                }
                if(first==0){//Guardo la primera diferencia como la menor
                    menorDiferencia = j->p->diferencia;
                    posGanador = i;
                    first=1;
                }
                if (j->p->diferencia < menorDiferencia){
                    menorDiferencia = j->p->diferencia;
                    posGanador = i;
                }
            }
        }
        printf("\nResultado: %d\n", resultado);
        empataron = chequearSiHayEmpateDelEmpate(menorDiferencia,listaPartida);
        if(empataron>=2){
            printf("\nEMPATARON OTRA VEZ!!!\n\n");
            presioneEnterParaContinuar();
        }
    }while(empataron>=2);

    JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaPartida, posGanador) );
    j->p->puntosPartida = j->p->puntosPartida + 10;

    return posGanador;
}

int chequearSiHayEmpateDelEmpate(int menorDiferencia, Lista listaPartida){
    int chequeo = 0;//Esta variable va a contar cuantos jugadores tienen la misma diferencia
    for(int i = 0; i<obtenerTamanio(listaPartida); i++){
        JugadorPtr j = *( (JugadorPtr*) obtenerDato(listaPartida, i) );

        if(j->p->diferencia==menorDiferencia){
            chequeo++;
        }
    }
    return chequeo;
}
