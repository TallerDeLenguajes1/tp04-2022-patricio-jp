#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

typedef struct Nodo {
    Tarea Tarea;
    struct Nodo *Siguiente;
} Nodo;

void cargarNodo(Nodo **Lista, Tarea tarea);
void cargarTareas(Nodo **lista, int cantTareas);
void mostrarTareas(Nodo *lista, int cantTareas);
void mostrarTareasYConsultar(Nodo **tareasPendientes, int cantTareas, Nodo **tareasRealizadas);
void moverTareas(Nodo **lista1, Nodo **nodo1, Nodo **lista2);
Tarea * BuscarTareaPorPalabra(Tarea **listado, char *palabra, int cantTareas);
Tarea * BuscarTareaPorID(Tarea **listado, int id, int cantTareas);

int main() {
    srand(time(NULL));
    char *buffer = (char *) malloc(sizeof(char) * 100);
    int cantTareas = 0, respuesta = 0;
    // Tarea **TareasRealizadas, **TareasPendientes;
    Nodo *TareasPendientes, *TareasRealizadas;

    printf("=== Tareas ===\n");
    printf("Ingrese la cantidad de tareas que desea cargar: ");
    scanf("%d", &cantTareas);
    fflush(stdin);

    // Creación de listas
    TareasPendientes = NULL;
    TareasRealizadas = NULL;


    cargarTareas(&TareasPendientes, cantTareas);

    // Listar tareas y preguntar si estan completadas o no
    printf("\n====== Listado de tareas ======\n");
    int tRealizadas = 0; // Contador para indice de TareasRealizadas (para indice del arreglo y para ciclo for de mostrar tareas realizadas)
    mostrarTareasYConsultar(&TareasPendientes, cantTareas, &TareasRealizadas);
    

    // Listar tareas realizadas y tareas pendientes
    printf("\nTareas realizadas\n");
    mostrarTareas(TareasRealizadas, cantTareas);

    printf("\nTareas pendientes\n");
    mostrarTareas(TareasPendientes, cantTareas);

    // Prueba funcion BuscarTarea
    /*Tarea * tareaAux;
    printf("\nBuscarTarea con Palabra en TareasPendientes: ");
    fflush(stdin);
    gets(buffer);
    char *palabra = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(palabra, buffer);

    tareaAux = BuscarTareaPorPalabra(TareasPendientes, palabra, cantTareas);
    mostrarTareas(tareaAux);

    printf("\nBuscarTarea con Palabra en TareasRealizadas: \n");
    tareaAux = BuscarTareaPorPalabra(TareasRealizadas, palabra, cantTareas);
    mostrarTareas(tareaAux);

    printf("\nBuscarTarea con ID 3 en TareasPendientes: \n");
    tareaAux = BuscarTareaPorID(TareasPendientes, 3, cantTareas);
    mostrarTareas(tareaAux);

    printf("\nBuscarTarea con ID 3 en TareasRealizadas: \n");
    tareaAux = BuscarTareaPorID(TareasRealizadas, 3, cantTareas);
    mostrarTareas(tareaAux);

    // Probando funcion BuscarTarea con un ID que no existe en ninguna lista
    printf("\nBuscarTarea con ID %d en TareasPendientes: \n", cantTareas + 3);
    tareaAux = BuscarTareaPorID(TareasPendientes, cantTareas + 3, cantTareas);
    mostrarTareas(tareaAux);

    printf("\nBuscarTarea con ID %d en TareasRealizadas: \n", cantTareas + 3);
    tareaAux = BuscarTareaPorID(TareasRealizadas, cantTareas + 3, cantTareas);
    mostrarTareas(tareaAux);
    
    // liberacion de memoria
    for (int i = 0; i < cantTareas; i++) {
        free(TareasPendientes[i]);
        free(TareasRealizadas[i]);
    }*/
    free(buffer);
    return 0;
}

void cargarNodo(Nodo **Lista, Tarea tarea) {
    Nodo *nuevoNodo = (Nodo *) malloc(sizeof(Nodo));

    nuevoNodo->Tarea.TareaID = tarea.TareaID;
    nuevoNodo->Tarea.Duracion = tarea.Duracion;
    nuevoNodo->Tarea.Descripcion = (char *) malloc(sizeof(char) * (strlen(tarea.Descripcion) + 1));
    strcpy(nuevoNodo->Tarea.Descripcion, tarea.Descripcion);

    nuevoNodo->Siguiente = *Lista;
    *Lista = nuevoNodo;
}

void cargarTareas(Nodo **lista, int cantTareas) {
    printf("====== Carga de tareas ======\n");
    char *buffer;
    buffer = (char *) malloc(sizeof(char) * 100);

    for (int i = 0; i < cantTareas; i++) {
        Tarea *tareaAux = (Tarea *) malloc(sizeof(Tarea));
        printf("-- Tarea %d --\n", i + 1);
        tareaAux->TareaID = i + 1;
        printf("Descripcion de la tarea: ");
        gets(buffer);
        tareaAux->Descripcion = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(tareaAux->Descripcion, buffer);
        tareaAux->Duracion = rand() % 91 + 10;
        cargarNodo(lista, *tareaAux);
        free(tareaAux);
    }

    free(buffer);
}

void mostrarTareas(Nodo *lista, int cantTareas) {
    int i = 1; // Indice auxiliar para enumerar las tareas
    while (lista != NULL && i <= cantTareas) {
        printf("--- Tarea [%d] ---\n", i);
        printf("* ID de tarea: %d\n", lista->Tarea.TareaID);
        printf("* Descripcion: %s\n", lista->Tarea.Descripcion);
        printf("* Duracion: %d\n", lista->Tarea.Duracion);
        i++;
        lista = lista->Siguiente;
    }
}

void mostrarTareasYConsultar(Nodo **tareasPendientes, int cantTareas, Nodo **tareasRealizadas) {
    int i = 1; // Indice auxiliar para enumerar las tareas
    int respuesta = 0;
    Nodo *cabecera = *tareasPendientes; // Auxiliar para cabecera de tareasPendientes
    while (cabecera != NULL && i <= cantTareas) {
        printf("--- Tarea [%d] ---\n", i);
        printf("* ID de tarea: %d\n", cabecera->Tarea.TareaID);
        printf("* Descripcion: %s\n", cabecera->Tarea.Descripcion);
        printf("* Duracion: %d\n", cabecera->Tarea.Duracion);
        i++;
        printf("\nLa tarea fue completada?\n1) SI\n2) NO\n");
        printf("Ingrese su respuesta: ");
        scanf("%d", &respuesta);
        while (respuesta != 1 && respuesta != 2) {
            printf("\nOpcion invalida. Ingrese nuevamente: ");
            scanf("%d", &respuesta);
        }
        if (respuesta == 1) {
            Nodo *siguienteAux = cabecera->Siguiente;
            // Auxiliar siguiente para no perder referencia del nodo que seguiría después de mover la tarea a la otra lista
            moverTareas(tareasPendientes, &cabecera, tareasRealizadas);
            cabecera = siguienteAux;
        } else {
            cabecera = cabecera->Siguiente;
        }
    }
}

void moverTareas(Nodo **lista1, Nodo **nodo1, Nodo **lista2) {
    Nodo *lista1Aux = *lista1; // Auxiliar para salvar la cabecera de la lista1
    if ((*lista1) != *nodo1) {
        // Si el nodo a mover no es el del comienzo
        while ((*lista1)->Siguiente != *nodo1) {
            // Avanzar cabecera de lista1 hasta el nodo anterior que debe ser movido
            (*lista1) = (*lista1)->Siguiente;
        }
    } else {
        // Se mueve el primer nodo, por lo tanto hay que salvar la posición del siguiente, más no el comienzo
        lista1Aux = lista1Aux->Siguiente;
    }

    (*lista1)->Siguiente = (*nodo1)->Siguiente; // Saltear nodo que se moverá

    (*nodo1)->Siguiente = *lista2; // Apuntar el nodo que se moverá a la cabecera de la lista2
    (*lista2) = *nodo1; // Apuntar cabecera de lista2 al nodo que se moverá, vinculándolo así a lista2

    *lista1 = lista1Aux; // Apuntar lista1 nuevamente al comienzo
}

Tarea * BuscarTareaPorPalabra(Tarea **listado, char *palabra, int cantTareas) {
    Tarea *tareaBuscada;
    tareaBuscada = (Tarea *) malloc(sizeof(Tarea));
    // Inicializacion de tareaBuscada para, en caso de no encontrar la buscada, devuelva una indefinida
    tareaBuscada->TareaID = 0;
    tareaBuscada->Duracion = 0;
    tareaBuscada->Descripcion = (char *) malloc(sizeof(char) * 100);
    strcpy(tareaBuscada->Descripcion, "Undefined");

    for (int i = 0; i < cantTareas; i++) {
        if (listado[i]) {
            if (strcmp(palabra, listado[i]->Descripcion) == 0) {
                tareaBuscada->TareaID = listado[i]->TareaID;
                tareaBuscada->Duracion = listado[i]->Duracion;
                strcpy(tareaBuscada->Descripcion, listado[i]->Descripcion);
                break;
            }
        }
    }
    return tareaBuscada;
}

Tarea * BuscarTareaPorID(Tarea **listado, int id, int cantTareas) {
    Tarea *tareaBuscada;
    tareaBuscada = (Tarea *) malloc(sizeof(Tarea));
    // Inicializacion de tareaBuscada para, en caso de no encontrar la buscada, devuelva una indefinida
    tareaBuscada->TareaID = 0;
    tareaBuscada->Duracion = 0;
    tareaBuscada->Descripcion = (char *) malloc(sizeof(char) * 100);
    strcpy(tareaBuscada->Descripcion, "Undefined");

    for (int i = 0; i < cantTareas; i++) {
        if (listado[i] && listado[i]->TareaID == id) {
            tareaBuscada->TareaID = listado[i]->TareaID;
            tareaBuscada->Duracion = listado[i]->Duracion;
            strcpy(tareaBuscada->Descripcion, listado[i]->Descripcion);
            break;
        }
    }
    return tareaBuscada;
}
