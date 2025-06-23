#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "respuesta.h"
#include "lista.h"

RespuestaPtr crearRespuestaVacia(){
    RespuestaPtr r=(RespuestaPtr)malloc(sizeof (struct Respuesta));
    char aux[25]=" ";
    strcpy(r->respuesta,aux);
    r->numRespuesta = -1;
    r->numRelacion = -1;
    r->correcta = -1;
    return r;
}

void iniciarRespuestasVacias(RespuestaPtr rs[], int t){
    RespuestaPtr v = crearRespuestaVacia();
    for(int i = 0; i<t; i++){
        rs[t]=v;
    }
}

RespuestaPtr transformarTextoARespuestas(char c[], int t){
    //El formato es numeroRelacion;respuesta;correcto
    int pos1 = -1;
    int pos2 = -1;
    int pos3 = -1;

    char auxNumRelacion[4]=" ";
    char auxRespuesta[25]=" ";
    char auxCorrecta[3]=" ";
    char auxNumRespuesta[3]=" ";


    RespuestaPtr r =(RespuestaPtr)malloc(sizeof (struct Respuesta));

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
    for (int i = pos2+1; i<t; i++){
        if(c[i]==';'){
            pos3 = i;
            i = t;
        }
    }
    for ( int i = 0; i<pos1; i++){
        auxNumRelacion[i]= c[i];
    }
    for ( int i = pos1+1; i<pos2; i++){
        auxRespuesta[i-pos1-1]= c[i];
    }
    for ( int i = pos2+1; i<pos3; i++){
        auxCorrecta[i-pos2-1]= c[i];
    }
    for ( int i = pos3+1; i<t; i++){
        auxNumRespuesta[i-pos3-1]= c[i];
    }


    r->numRelacion = atoi (auxNumRelacion);
    strcpy(r->respuesta,auxRespuesta);
    r->correcta = atoi (auxCorrecta);
    r->numRespuesta = atoi (auxNumRespuesta);

    return r;
};

void cargarRespuestaAListaDesdeTxt(Lista lista){

    FILE * archivo = fopen("respuestas.txt", "r");

    while(!feof(archivo)){

        char aux[30] = " ";

        fgets(aux, 30, archivo);

        int tam = strlen(aux);

        RespuestaPtr r = transformarTextoARespuestas(aux,tam);

        insertarFinal(lista,&r);
    }
    fclose(archivo);
};

void mostrarRespuesta(RespuestaPtr r){

    printf ("(%d) %s\n", r->numRespuesta, r->respuesta);
}

void mostrarListaRespuesta(Lista lista){

    for ( int i = 0; i < obtenerTamanio(lista); ++i) {

        RespuestaPtr r = *( (RespuestaPtr*) obtenerDato(lista, i) );

		mostrarRespuesta(r);
    }
    printf("\n");
};
void mostrarArrayRespuestas(RespuestaPtr rs[], int t){

    for(int i = 0; i<t;i++){
        mostrarRespuesta(rs[i]);
    }
    printf("\n");
}

void RandomRespuestas(RespuestaPtr rs[], int t){

    for (int i = 0; i<t;i++){
        rs[i]->numRespuesta = rand()% 1000 + 1;
    }
    ordenarArrayRespuestas(rs,t);
    for (int i = 0; i<t;i++){
        rs[i]->numRespuesta = i+1;
    }
}

void ordenarArrayRespuestas(RespuestaPtr rs[], int t){
    RespuestaPtr aux = crearRespuestaVacia();
    int min;
    for (int i=0; i<t; i++){
        min = i;
        for (int j=i+1;j<t;j++){
            if (rs[min]->numRespuesta > rs[j]->numRespuesta){
                min = j;
            }
        }
        aux = rs[min];
        rs[min]= rs[i];
        rs[i]= aux;
    }
}
int buscarRespuestaCorrecta(RespuestaPtr rs[], int t){

    int numeroOpcionCorrecta = -1;
    int busco = 1; // la respuesta que tiene 1 es la correcta

    for (int i = 0; i<t; i++){
        if (rs[i]->correcta==busco){
            numeroOpcionCorrecta = rs[i]->numRespuesta;
        }
    }
    return numeroOpcionCorrecta;
}
