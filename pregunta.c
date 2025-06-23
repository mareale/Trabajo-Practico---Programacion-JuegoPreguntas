#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pregunta.h"
#include "lista.h"


PreguntaPtr crearPreguntaVacia(){
    PreguntaPtr p = (PreguntaPtr)malloc(sizeof(struct Pregunta));
    char aux[70]=" ";
    strcpy(p->pregunta,aux);
    p->numPregunta = -1;
    return p;
}


void mostrarPregunta(PreguntaPtr p){
    printf("\n-%s\n", p->pregunta);
    mostrarArrayRespuestas(p->respuestas,4);
}
void mostrarListaPregunta(Lista lista){

    for ( int i = 0; i < obtenerTamanio(lista); ++i) {

        PreguntaPtr p = *( (PreguntaPtr*) obtenerDato(lista, i) );

		mostrarPregunta(p);
    }
    printf("\n");
};

PreguntaPtr preguntaRandom(Lista lista){

    int random = rand()% obtenerTamanio(lista);
    PreguntaPtr p = *( (PreguntaPtr*) obtenerDato(lista, random) );
    remover(lista,random,&p);
    return p;
}

PreguntaPtr transformarTextoAPregunta(char c[], int t){
    //El formato es numero;pregunta
    int pos = -1;

    char auxNum[3]=" ";
    char auxPregunta[60]=" ";

    PreguntaPtr p = (PreguntaPtr) malloc(sizeof(struct Pregunta));

    for (int i = 0; i<t; i++){
        if(c[i]==';'){
            pos = i;
            i = t;
        }
    }
    for ( int i = 0; i<pos; i++){
        auxNum[i]= c[i];
    }
    for ( int i = pos+1; i<t; i++){
        auxPregunta[i-pos-1]= c[i];
    }
    p->numPregunta= atoi(auxNum);
    strcpy(p->pregunta,auxPregunta);

    return p;
};

void cargarPreguntaAListaDesdeTxt(Lista listaP, Lista listaR){

    FILE * archivo = fopen("preguntas.txt", "r");

    while(!feof(archivo)){

        char aux[70] = " ";

        fgets(aux, 70, archivo);

        int tam = strlen(aux);

        PreguntaPtr p = transformarTextoAPregunta(aux,tam+5);

        iniciarRespuestasVacias(p->respuestas,4);

        cargarRespuestasAPregunta(p,listaR);

        insertarFinal(listaP,&p);
    }
    fclose(archivo);
};

void cargarRespuestasAPregunta(PreguntaPtr p, Lista listaR){
    int contador = 0;
    for(int i = 0; i<obtenerTamanio(listaR);i++){
        RespuestaPtr r = *( (RespuestaPtr*) obtenerDato(listaR, i) );
        if (p->numPregunta == r->numRelacion){
            p->respuestas[r->numRespuesta-1] = r;
            contador++;
        }
        if (contador == 4){
            i = obtenerTamanio(listaR);
        }
    }
    RandomRespuestas(p->respuestas,4);
}

int preguntaEmpate(){
    int a,b,c;
    int resultado;

    a = rand()%900+100;
    b = rand()%90+10;
    c = rand()%19+1;

    resultado = a+b*c;
    printf("\nLa operacion matematica es la siguiente...\n\n\t%d + %d * %d\n\n", a, b, c);

    return resultado;
}
