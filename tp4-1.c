#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

void cargarTarea(Tarea **listado, int id);

int main() {
    srand(time(NULL));
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
        TareasRealizadas[i] = (Tarea *) malloc(sizeof(Tarea));
    }

    // Carga de tareas
    for (int i = 0; i < cantTareas; i++) {
        printf("-- Tarea %d --\n", i + 1);
        cargarTarea(&TareasPendientes[i], i + 1);
    }

    // Listar tareas y preguntar si estan completadas o no
    printf("\n====== Listado de tareas ======\n");
    int tRealizadas = 0; // Contador para indice de TareasRealizadas (para indice del arreglo y para ciclo for de mostrar tareas realizadas)
    for (int i = 0; i < cantTareas; i++) {
        printf("--- Tarea [%d] ---\n", i + 1);
        printf("ID de tarea: %d\n", TareasPendientes[i]->TareaID);
        printf("Descripcion: %s\n", TareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n\n", TareasPendientes[i]->Duracion);

        printf("\nLa tarea fue completada?\n1) SI\n2) NO\n");
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

    // liberacion de memoria
    for (int i = 0; i < cantTareas; i++) {
        free(TareasPendientes[i]);
        free(TareasRealizadas[i]);
    }
    return 0;
}

void cargarTarea(Tarea **listado, int id) {
    printf("Descripcion de la tarea: ");
    char *buffer;
    buffer = (char *) malloc(sizeof(char) * 100);
    gets(buffer);
    (*listado)->Descripcion = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy((*listado)->Descripcion, buffer);
    (*listado)->Duracion = rand() % 91 + 10;
    (*listado)->TareaID = id;
    free(buffer);
}