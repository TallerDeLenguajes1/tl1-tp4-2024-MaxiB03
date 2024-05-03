#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define tama 100

struct Tarea{
    int TareaID; //Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}typedef Nodo;

//Funciones
Nodo* crearListaVacia();
Nodo* crearNodo(int id, char descrip[], int duracion);
Nodo* QuitarNodo(Nodo **start);
void eliminarNodo(Nodo **cabecera, int id);
void InsertarNodo(Nodo **start, Nodo *nuevoNodo);
void mostrarLista(Nodo *lista);
void mostrarTarea(Tarea t);
void buscarxPalabra(Nodo *listaP, Nodo *listaR, char clave[]);
void buscarxId(Nodo *listaP, Nodo *listaR, int id);
Nodo* buscarTareaId(Nodo *listaP, Nodo *listaR, int id);
void eliminarLista(Nodo **lista);

int main()
{
    int id=1000, duracion, resp, cont=1, idBuscado;
    char buff[tama], buff2[tama], *clave;

    Nodo *ListaPendientes;
    Nodo *ListaRealizadas;

    ListaPendientes=crearListaVacia();
    ListaRealizadas=crearListaVacia();

    do
    {
        printf("\n--------CARGAR TAREA[%d]--------\n", cont++);

        fflush(stdin);
        printf("Ingrese Descripcion de la tarea: ");
        gets(buff);

        printf("Ingrese Duracion: ");
        scanf("%d", &duracion);

        id++;

        //Creo el Nodo con los datos y lo inserto en la lista de pendientes
        Nodo *nuevoNodo=crearNodo(id, buff, duracion);
        InsertarNodo(&ListaPendientes, nuevoNodo);

        printf("Finalizar Carga de Tareas (Si=1), (No=0): ");
        scanf("%d", &resp);

    } while (resp!=1);

    Nodo *nodoAux, *nodoquitado, *nodoAnterior=NULL;
    nodoAux=ListaPendientes;

    printf("\n-------Lista de Tareas Pendientes-------\n");

    while (nodoAux!=NULL)
    {
        do
        {
            mostrarTarea(nodoAux->T);
            fflush(stdin);
            printf("Realizo la Tarea? (Si=1), (No=0): ");
            scanf("%d", &resp);

        } while (resp!=1 && resp!=0);

        if(resp==1)
        {
            
            nodoquitado=crearNodo(nodoAux->T.TareaID, nodoAux->T.Descripcion, nodoAux->T.Duracion);
            InsertarNodo(&ListaRealizadas, nodoquitado);
            nodoAnterior=nodoAux;
            nodoAux=nodoAux->Siguiente;
            eliminarNodo(&ListaPendientes, nodoAnterior->T.TareaID);
            
        }else
            {
                nodoAux=nodoAux->Siguiente;
            }
    }
    
    printf("\n-------Lista de Tareas Realizadas-------\n");
    mostrarLista(ListaRealizadas);
    printf("\n-------Lista de Tareas Pendientes-------\n");
    mostrarLista(ListaPendientes);

    fflush(stdin);
    printf("Ingrese ID para buscar una Tarea: ");
    scanf("%d", &idBuscado);

    buscarxId(ListaPendientes, ListaRealizadas, idBuscado);

    fflush(stdin);
    printf("\nBuscar Tarea, Ingrese palabra clave: ");
    gets(buff2);
    clave=malloc(sizeof(char)* (strlen(buff2)+1) );
    strcpy(clave,buff2);

    buscarxPalabra(ListaPendientes, ListaRealizadas, clave);

    //Libero la memoria luego de finalizar el programa
    eliminarLista(&ListaPendientes);
    eliminarLista(&ListaRealizadas);

    printf("\n---------- LISTAS ELIMINADAS ----------\n");
    printf("\n-------Lista de Tareas Realizadas-------\n");
    mostrarLista(ListaRealizadas);
    printf("\n-------Lista de Tareas Pendientes-------\n");
    mostrarLista(ListaPendientes);

    return 0;
}

Nodo* crearListaVacia()
{
    return NULL;
}

Nodo* crearNodo(int id, char descrip[], int duracion)
{
    Nodo *nuevoNodo=malloc(sizeof(Nodo));

    nuevoNodo->T.TareaID=id;
    nuevoNodo->T.Duracion=duracion;
    nuevoNodo->T.Descripcion=malloc((strlen(descrip)+1)*sizeof(char));
    strcpy(nuevoNodo->T.Descripcion, descrip);

    nuevoNodo->Siguiente=NULL;

    return nuevoNodo;
}

Nodo* QuitarNodo(Nodo **start)
{
    Nodo *aux;
    aux=*start;
    
    *start=(*start)->Siguiente;
    aux->Siguiente=NULL;
    
    return aux;
}

void eliminarLista(Nodo **lista)
{
    Nodo *aux;

    while(*lista!=NULL)
    {
        aux=*lista;
        *lista=aux->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}

void eliminarNodo(Nodo **cabecera, int id){

    Nodo *aux=*cabecera;
    Nodo *auxAnterior=NULL;

    while(aux!=NULL && aux->T.TareaID!=id){

        auxAnterior=aux;
        aux=aux->Siguiente;
    }

    if(aux==NULL){ //Significa que no se encontro el nodo con ese dato o la lista esta vacia

        if(*cabecera==NULL){
            printf("\nLa Lista esta Vacia");
        }else{
            printf("\nNo se encontro el elemento");
        }

    }else{

        if(*cabecera==aux){  //Significa que quiero borrar el primer elemento
            *cabecera=aux->Siguiente;
        }else{
            auxAnterior->Siguiente=aux->Siguiente;
            free(aux->T.Descripcion);
            free(aux);
        }
    }
}

void buscarxId(Nodo *listaP, Nodo *listaR, int id)
{
    Nodo *aux=listaP;

    while(aux && aux->T.TareaID!=id)
    {
        aux=aux->Siguiente;
    }
    if(aux==NULL){

        aux=listaR;
        while(aux && aux->T.TareaID!=id)
        {
            aux=aux->Siguiente;
        }

        if(aux==NULL)
        {
            printf("\n--------- Tarea No Encontrada ---------\n");
        }else{
            printf("\n--------- Tarea Encontrada (Realizada) ---------\n");
            mostrarTarea(aux->T);
        }
    }else{
        printf("\n--------- Tarea Encontrada (Pendiente) ---------\n");
        mostrarTarea(aux->T);
    }
}

void buscarxPalabra(Nodo *listaP, Nodo *listaR, char clave[])
{
    Nodo *aux=listaP;

    while (aux && strstr(aux->T.Descripcion, clave) == NULL)
    {
        aux =aux->Siguiente;
    }
    if (aux == NULL)
    {
        aux = listaR;
        while (aux && strstr(aux->T.Descripcion, clave) == NULL)
        {
            aux =aux->Siguiente;
        }
        if(aux==NULL)
        {
            printf("\n--------- Tarea No Encontrada ---------\n");
        }else{
            printf("\n--------- Tarea Encontrada (Realizada) ---------\n");
            mostrarTarea(aux->T);
        }

    }else{
        printf("\n--------- Tarea Encontrada (Pendiente) ---------\n");
        mostrarTarea(aux->T);
    }
}

void InsertarNodo(Nodo **start, Nodo *nuevoNodo)
{
    nuevoNodo->Siguiente=*start;
    *start=nuevoNodo;
}


void mostrarTarea(Tarea t)
{
    printf("\n-------- TAREA --------\n");
    printf("ID tarea: %d\n", t.TareaID);
    printf("Descripcion: %s\n", t.Descripcion);
    printf("Duracion: %d\n", t.Duracion);
}

void mostrarLista(Nodo *lista)
{
    while (lista != NULL)
    {
        printf("\n-------- TAREA --------\n");
        printf("ID tarea: %d\n", lista->T.TareaID);
        printf("Descripcion: %s\n", lista->T.Descripcion);
        printf("Duracion: %d\n", lista->T.Duracion);

        lista=lista->Siguiente;
    }
}