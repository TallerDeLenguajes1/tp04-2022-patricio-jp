#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

void cargarTareas(Tarea **listado, int cantTareas);
void mostrarTarea(Tarea *tarea);
Tarea * BuscarTarea(Tarea **listado, char *palabra, int cantTareas);

int main() {
    srand(time(NULL));
    char *buffer = (char *) malloc(sizeof(char) * 100);
    int cantTareas = 0, respuesta = 0;
    Tarea **TareasRealizadas, **TareasPendientes;

    printf("=== Tareas ===\n");
    printf("Ingrese la cantidad de tareas que desea cargar: ");
    scanf("%d", &cantTareas);
    fflush(stdin);

    // Reserva de memoria
    TareasPendientes = (Tarea **) malloc(sizeof(Tarea *) * cantTareas);
    TareasRealizadas = (Tarea **) malloc(sizeof(Tarea *) * cantTareas);

    for (int i = 0; i < cantTareas; i++) {
        TareasPendientes[i] = (Tarea *) malloc(sizeof(Tarea));
        TareasRealizadas[i] = NULL; // Inicializo en NULL cada posicion del arreglo para no tener basura
    }

    cargarTareas(TareasPendientes, cantTareas);

    // Listar tareas y preguntar si estan completadas o no
    printf("\n====== Listado de tareas ======\n");
    int tRealizadas = 0; // Contador para indice de TareasRealizadas (para indice del arreglo y para ciclo for de mostrar tareas realizadas)
    for (int i = 0; i < cantTareas; i++) {
        printf("--- Tarea [%d] ---\n", i + 1);
        mostrarTarea(TareasPendientes[i]);

        printf("\nLa tarea fue completada?\n1) SI\n2) NO\n");
        printf("Ingrese su respuesta: ");
        scanf("%d", &respuesta);
        while (respuesta != 1 && respuesta != 2) {
            printf("\nOpcion invalida. Ingrese nuevamente: ");
            scanf("%d", &respuesta);
        }
        if (respuesta == 1) {
            TareasRealizadas[tRealizadas] = TareasPendientes[i];
            tRealizadas++;
            TareasPendientes[i] = NULL;
        }
        printf("\n");
    }

    // Listar tareas realizadas y tareas pendientes
    printf("\nTareas realizadas\n");
    for (int i = 0; i < tRealizadas; i++) {
        printf("-- Tarea %d --\n", i + 1);
        printf("ID de tarea: %d\n", TareasRealizadas[i]->TareaID);
        printf("Descripcion: %s\n", TareasRealizadas[i]->Descripcion);
        printf("Duracion: %d\n\n", TareasRealizadas[i]->Duracion);
    }
    printf("\nTareas pendientes\n");
    int j = 1; // Auxiliar para numerar las tareas
    for (int i = 0; i < cantTareas; i++) {
        if (TareasPendientes[i]) {
            printf("-- Tarea %d --\n", j);
            printf("ID de tarea: %d\n", TareasPendientes[i]->TareaID);
            printf("Descripcion: %s\n", TareasPendientes[i]->Descripcion);
            printf("Duracion: %d\n\n", TareasPendientes[i]->Duracion);
            j++;
        }
    }

    // Prueba funcion BuscarTarea
    Tarea * tareaAux;
    printf("\nBuscar tarea en TareasPendientes por palabra: ");
    fflush(stdin);
    gets(buffer);
    char *palabra = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(palabra, buffer);

    tareaAux = BuscarTarea(TareasPendientes, palabra, cantTareas);
    mostrarTarea(tareaAux);

    printf("\nBuscarTarea en TareasRealizadas: \n");
    tareaAux = BuscarTarea(TareasRealizadas, palabra, cantTareas);
    mostrarTarea(tareaAux);

    // liberacion de memoria
    for (int i = 0; i < cantTareas; i++) {
        free(TareasPendientes[i]);
        free(TareasRealizadas[i]);
    }
    free(buffer);
    return 0;
}

void cargarTareas(Tarea **listado, int cantTareas) {
    printf("====== Carga de tareas ======\n");
    char *buffer;
    buffer = (char *) malloc(sizeof(char) * 100);

    for (int i = 0; i < cantTareas; i++) {
        printf("-- Tarea %d --\n", i + 1);
        listado[i]->TareaID = i;
        printf("Descripcion de la tarea: ");
        gets(buffer);
        listado[i]->Descripcion = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(listado[i]->Descripcion, buffer);
        listado[i]->Duracion = rand() % 91 + 10;
    }

    free(buffer);
}

void mostrarTarea(Tarea *tarea) {
    printf("* ID de tarea: %d\n", tarea->TareaID);
    printf("* Descripcion: %s\n", tarea->Descripcion);
    printf("* Duracion: %d\n", tarea->Duracion);
}

Tarea * BuscarTarea(Tarea **listado, char *palabra, int cantTareas) {
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
