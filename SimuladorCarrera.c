#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PAISES 10
#define MAX_EQUIPOS 10
#define MAX_PILOTOS 22
#define MAX_PUNTOS 10

typedef struct {
    char id[10];
    char nombre[50];
} Pais;

typedef struct {
    char id[10];
    char nombre[50];
    char id_pais[10];
} Equipo;

typedef struct {
    char id[10];
    char nombre[50];
    int numero;
    char id_equipo[10];
    char id_pais[10];
    int posicion_inicial;  // Posición de inicio en la carrera
    int posicion_final;    // Posición final en la carrera
    int puntos;            // Puntos acumulados
    int vuelta_rapida;     // 1 si hizo vuelta rápida, 0 de otro modo
} Piloto;

// Declaración de funciones
void mostrarMenu();
void menuCatalogos(int *contador_paises, Pais *paises, int *contador_equipos, Equipo *equipos, int *contador_pilotos, Piloto *pilotos);
void menuPaises(Pais *paises, int *contador_paises);
void menuEquipos(Equipo *equipos, int *contador_equipos, Pais *paises, int contador_paises);
void menuPilotos(Piloto *pilotos, int *contador_pilotos, Equipo *equipos, int contador_equipos, Pais *paises, int contador_paises);

void agregarPais(Pais *paises, int *contador_paises);
void modificarPais(Pais *paises, int contador_paises);
void mostrarPaises(Pais *paises, int contador_paises);
void eliminarPais(Pais *paises, int *contador_paises);

void agregarEquipo(Equipo *equipos, int *contador_equipos, Pais *paises, int total_paises);
void modificarEquipo(Equipo *equipos, int contador_equipos, Pais *paises, int total_paises);
void mostrarEquipos(Equipo *equipos, int contador_equipos, Pais *paises, int total_paises);
void eliminarEquipo(Equipo *equipos, int *contador_equipos, Pais *paises, int total_paises);

void agregarPiloto(Piloto *pilotos, int *contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises);
void modificarPiloto(Piloto *pilotos, int contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises);
void mostrarPilotos(Piloto *pilotos, int contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises);
void eliminarPiloto(Piloto *pilotos, int *contador_pilotos);
void simularCarrera(Piloto *pilotos, int total_pilotos);
void simularCarrera(Piloto *pilotos, int total_pilotos);



void generarId(char *prefijo, int numero, char *resultado);

// Definiciones de las funciones
int main() {
    Pais paises[MAX_PAISES];
    Equipo equipos[MAX_EQUIPOS];
    Piloto pilotos[MAX_PILOTOS];
    int contador_paises = 0, contador_equipos = 0, contador_pilotos = 0;
    int opcion;

    srand(time(NULL)); // Inicializa la semilla para números aleatorios

    while (1) {
        mostrarMenu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
    case 1:
        menuCatalogos(&contador_paises, paises, &contador_equipos, equipos, &contador_pilotos, pilotos);
        break;
    case 2:
        simularCarrera(pilotos, contador_pilotos);
        break;
    case 3:
        printf("Funcionalidad de resultados de carreras pendiente.\n");
        break;
    case 4:
        printf("Saliendo del programa.\n");
        exit(0);
    default:
        printf("Opción no válida.\n");
}

    }
    return 0;
}

void mostrarMenu() {
    printf("\nMenú Principal\n");
    printf("1) Catálogos\n");
    printf("2) Simulador de carrera\n");
    printf("3) Resultados de la carrera\n");
    printf("4) Salir\n");
}

void menuCatalogos(int *contador_paises, Pais *paises, int *contador_equipos, Equipo *equipos, int *contador_pilotos, Piloto *pilotos) {
    int opcion;

    while (1) {
        printf("\nCatálogos:\n");
        printf("1) Paises\n");
        printf("2) Equipos\n");
        printf("3) Pilotos\n");
        printf("4) Regresar al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menuPaises(paises, contador_paises);
                break;
            case 2:
                menuEquipos(equipos, contador_equipos, paises, *contador_paises);
                break;
            case 3:
                menuPilotos(pilotos, contador_pilotos, equipos, *contador_equipos, paises, *contador_paises);
                break;
            case 4:
                return; // Salir al menú principal
            default:
                printf("Opción no válida.\n");
        }
    }
}


void menuPaises(Pais *paises, int *contador_paises) {
    int opcion;

    while (1) {
        printf("\nGestión de Países:\n");
        printf("1) Agregar país\n");
        printf("2) Modificar país\n");
        printf("3) Mostrar países\n");
        printf("4) Eliminar país\n");
        printf("5) Regresar al menú Catálogos\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarPais(paises, contador_paises);
                break;
            case 2:
                modificarPais(paises, *contador_paises);
                break;
            case 3:
                mostrarPaises(paises, *contador_paises);
                break;
            case 4:
                eliminarPais(paises, contador_paises);
                break;
            case 5:
                return;
            default:
                printf("Opción no válida.\n");
        }
    }
}

void agregarPais(Pais *paises, int *contador_paises) {
    if (*contador_paises >= MAX_PAISES) {
        printf("No se pueden agregar más países.\n");
        return;
    }
    generarId("PA", *contador_paises + 1, paises[*contador_paises].id);
    printf("Ingrese el nombre del país: ");
    scanf("%s", paises[*contador_paises].nombre);
    (*contador_paises)++;
    printf("País agregado con éxito.\n");
}

void modificarPais(Pais *paises, int contador_paises) {
    if (contador_paises == 0) {
        printf("No hay países registrados para modificar.\n");
        return;
    }
    mostrarPaises(paises, contador_paises);
    char id[10];
    printf("Ingrese el ID del país que desea modificar: ");
    scanf("%s", id);

    for (int i = 0; i < contador_paises; i++) {
        if (strcmp(paises[i].id, id) == 0) {
            printf("Ingrese el nuevo nombre para el país %s: ", paises[i].id);
            scanf("%s", paises[i].nombre);
            printf("Modificación realizada con éxito.\n");
            return;
        }
    }
    printf("No se encontró el país con el ID especificado.\n");
}

void mostrarPaises(Pais *paises, int contador_paises) {
    if (contador_paises == 0) {
        printf("No hay países registrados.\n");
        return;
    }
    printf("\nID_País\tNombre_País\n");
    printf("-------------------------\n");
    for (int i = 0; i < contador_paises; i++) {
        printf("%s\t%s\n", paises[i].id, paises[i].nombre);
    }
}

void eliminarPais(Pais *paises, int *contador_paises) {
    if (*contador_paises == 0) {
        printf("No hay países registrados para eliminar.\n");
        return;
    }
    mostrarPaises(paises, *contador_paises);
    char id[10];
    printf("Ingrese el ID del país que desea eliminar: ");
    scanf("%s", id);

    for (int i = 0; i < *contador_paises; i++) {
        if (strcmp(paises[i].id, id) == 0) {
            for (int j = i; j < *contador_paises - 1; j++) {
                paises[j] = paises[j + 1];
            }
            (*contador_paises)--;
            printf("País eliminado con éxito.\n");
            mostrarPaises(paises, *contador_paises);
            return;
        }
    }
    printf("No se encontró el país con el ID especificado.\n");
}

void menuEquipos(Equipo *equipos, int *contador_equipos, Pais *paises, int contador_paises) {
    int opcion;

    while (1) {
        printf("\nGestión de Equipos:\n");
        printf("1) Agregar equipo\n");
        printf("2) Modificar equipo\n");
        printf("3) Mostrar equipos\n");
        printf("4) Eliminar equipo\n");
        printf("5) Regresar al menú Catálogos\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarEquipo(equipos, contador_equipos, paises, contador_paises);
                break;
            case 2:
                modificarEquipo(equipos, *contador_equipos, paises, contador_paises);
                break;
            case 3:
                mostrarEquipos(equipos, *contador_equipos, paises, contador_paises);
                break;
            case 4:
                eliminarEquipo(equipos, contador_equipos, paises, contador_paises);
                break;
            case 5:
                return;
            default:
                printf("Opción no válida.\n");
        }
    }
}

void agregarEquipo(Equipo *equipos, int *contador_equipos, Pais *paises, int total_paises) {
    if (*contador_equipos >= MAX_EQUIPOS) {
        printf("No se pueden agregar más equipos.\n");
        return;
    }

    generarId("EQ", *contador_equipos + 1, equipos[*contador_equipos].id);
    printf("Ingrese el nombre del equipo: ");
    scanf("%s", equipos[*contador_equipos].nombre);

    printf("Seleccione el ID del país asociado al equipo:\n");
    mostrarPaises(paises, total_paises);
    printf("ID del país: ");
    scanf("%s", equipos[*contador_equipos].id_pais);

    (*contador_equipos)++;
    printf("Equipo agregado con éxito.\n");
}

void modificarEquipo(Equipo *equipos, int contador_equipos, Pais *paises, int total_paises) {
    if (contador_equipos == 0) {
        printf("No hay equipos registrados para modificar.\n");
        return;
    }
    mostrarEquipos(equipos, contador_equipos, paises, total_paises);
    char id[10];
    printf("Ingrese el ID del equipo que desea modificar: ");
    scanf("%s", id);

    for (int i = 0; i < contador_equipos; i++) {
        if (strcmp(equipos[i].id, id) == 0) {
            printf("Ingrese el nuevo nombre para el equipo %s: ", equipos[i].id);
            scanf("%s", equipos[i].nombre);
            printf("Seleccione el nuevo país asociado:\n");
            mostrarPaises(paises, total_paises);
            printf("ID del país: ");
            scanf("%s", equipos[i].id_pais);
            printf("Modificación realizada con éxito.\n");
            return;
        }
    }
    printf("No se encontró el equipo con el ID especificado.\n");
}

void mostrarEquipos(Equipo *equipos, int contador_equipos, Pais *paises, int total_paises) {
    if (contador_equipos == 0) {
        printf("No hay equipos registrados.\n");
        return;
    }

    printf("\nID_Equipo\tNombre_Equipo\tPaís\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < contador_equipos; i++) {
        char pais_nombre[50] = "Desconocido";
        for (int j = 0; j < total_paises; j++) {
            if (strcmp(equipos[i].id_pais, paises[j].id) == 0) {
                strcpy(pais_nombre, paises[j].nombre);
                break;
            }
        }
        printf("%s\t\t%s\t\t%s\n", equipos[i].id, equipos[i].nombre, pais_nombre);
    }
}

void eliminarEquipo(Equipo *equipos, int *contador_equipos, Pais *paises, int total_paises) {
    if (*contador_equipos == 0) {
        printf("No hay equipos registrados para eliminar.\n");
        return;
    }
    mostrarEquipos(equipos, *contador_equipos, paises, total_paises);
    char id[10];
    printf("Ingrese el ID del equipo que desea eliminar: ");
    scanf("%s", id);

    for (int i = 0; i < *contador_equipos; i++) {
        if (strcmp(equipos[i].id, id) == 0) {
            for (int j = i; j < *contador_equipos - 1; j++) {
                equipos[j] = equipos[j + 1];
            }
            (*contador_equipos)--;
            printf("Equipo eliminado con éxito.\n");
            mostrarEquipos(equipos, *contador_equipos, paises, total_paises);
            return;
        }
    }
    printf("No se encontró el equipo con el ID especificado.\n");
}

void menuPilotos(Piloto *pilotos, int *contador_pilotos, Equipo *equipos, int contador_equipos, Pais *paises, int contador_paises) {
    int opcion;

    while (1) {
        printf("\nGestión de Pilotos:\n");
        printf("1) Agregar piloto\n");
        printf("2) Modificar piloto\n");
        printf("3) Mostrar pilotos\n");
        printf("4) Eliminar piloto\n");
        printf("5) Regresar al menú Catálogos\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarPiloto(pilotos, contador_pilotos, equipos, contador_equipos, paises, contador_paises);
                break;
            case 2:
                modificarPiloto(pilotos, *contador_pilotos, equipos, contador_equipos, paises, contador_paises);
                break;
            case 3:
                mostrarPilotos(pilotos, *contador_pilotos, equipos, contador_equipos, paises, contador_paises);
                break;
            case 4:
                eliminarPiloto(pilotos, contador_pilotos);
                break;
            case 5:
                return;
            default:
                printf("Opción no válida.\n");
        }
    }
}

void agregarPiloto(Piloto *pilotos, int *contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises) {
    if (*contador_pilotos >= MAX_PILOTOS) {
        printf("No se pueden agregar más pilotos.\n");
        return;
    }

    generarId("PI", *contador_pilotos + 1, pilotos[*contador_pilotos].id);
    printf("Ingrese el nombre del piloto: ");
    scanf("%s", pilotos[*contador_pilotos].nombre);
    pilotos[*contador_pilotos].numero = rand() % 99 + 1; // Número aleatorio entre 1 y 99.

    printf("Seleccione el equipo del piloto:\n");
    mostrarEquipos(equipos, total_equipos, paises, total_paises);
    scanf("%s", pilotos[*contador_pilotos].id_equipo);

    printf("Seleccione el país del piloto:\n");
    mostrarPaises(paises, total_paises);
    scanf("%s", pilotos[*contador_pilotos].id_pais);

    (*contador_pilotos)++;
    printf("Piloto agregado con éxito.\n");
}

void modificarPiloto(Piloto *pilotos, int contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises) {
    if (contador_pilotos == 0) {
        printf("No hay pilotos registrados para modificar.\n");
        return;
    }

    mostrarPilotos(pilotos, contador_pilotos, equipos, total_equipos, paises, total_paises);
    char id[10];
    printf("Ingrese el ID del piloto que desea modificar: ");
    scanf("%s", id);

    for (int i = 0; i < contador_pilotos; i++) {
        if (strcmp(pilotos[i].id, id) == 0) {
            printf("Ingrese el nuevo nombre del piloto: ");
            scanf("%s", pilotos[i].nombre);

            printf("Seleccione el nuevo equipo del piloto:\n");
            mostrarEquipos(equipos, total_equipos, paises, total_paises);
            printf("ID del equipo: ");
            scanf("%s", pilotos[i].id_equipo);

            printf("Seleccione el nuevo país del piloto:\n");
            mostrarPaises(paises, total_paises);
            printf("ID del país: ");
            scanf("%s", pilotos[i].id_pais);

            printf("Modificación realizada con éxito.\n");
            return;
        }
    }
    printf("Piloto no encontrado.\n");
}

void mostrarPilotos(Piloto *pilotos, int contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises) {
    if (contador_pilotos == 0) {
        printf("No hay pilotos registrados.\n");
        return;
    }

    printf("\nID_Piloto\tNombre\tNúmero\tEquipo\tPaís\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < contador_pilotos; i++) {
        char equipo_nombre[50] = "Desconocido";
        char pais_nombre[50] = "Desconocido";

        // Buscar el equipo correspondiente.
        for (int j = 0; j < total_equipos; j++) {
            if (strcmp(pilotos[i].id_equipo, equipos[j].id) == 0) {
                strcpy(equipo_nombre, equipos[j].nombre);
                break;
            }
        }

        // Buscar el país correspondiente.
        for (int k = 0; k < total_paises; k++) {
            if (strcmp(pilotos[i].id_pais, paises[k].id) == 0) {
                strcpy(pais_nombre, paises[k].nombre);
                break;
            }
        }

        printf("%s\t%s\t%d\t%s\t%s\n", pilotos[i].id, pilotos[i].nombre, pilotos[i].numero, equipo_nombre, pais_nombre);
    }
}

void eliminarPiloto(Piloto *pilotos, int *contador_pilotos) {
    if (*contador_pilotos == 0) {
        printf("No hay pilotos registrados para eliminar.\n");
        return;
    }

    mostrarPilotos(pilotos, *contador_pilotos, NULL, 0, NULL, 0);
    char id[10];
    printf("Ingrese el ID del piloto que desea eliminar: ");
    scanf("%s", id);

    for (int i = 0; i < *contador_pilotos; i++) {
        if (strcmp(pilotos[i].id, id) == 0) {
            for (int j = i; j < *contador_pilotos - 1; j++) {
                pilotos[j] = pilotos[j + 1];
            }
            (*contador_pilotos)--;
            printf("Piloto eliminado con éxito.\n");
            return;
        }
    }
    printf("Piloto no encontrado.\n");
}

void simularCarrera(Piloto *pilotos, int total_pilotos) {
    if (total_pilotos != MAX_PILOTOS) {
        printf("Debe haber exactamente %d pilotos registrados para simular una carrera.\n", MAX_PILOTOS);
        return;
    }

    // Declaración de variables
    int polePositionIndex = rand() % total_pilotos; // Índice aleatorio para pole position
    int vueltaRapidaIndex = rand() % total_pilotos; // Índice aleatorio para vuelta rápida
    int puntos[MAX_PUNTOS] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1}; // Tabla de puntos

    Piloto *clasificados[MAX_PILOTOS];
    Piloto *finalistas[MAX_PILOTOS];
    int descalificadosIndices[9];

    // Asignar la pole position
    clasificados[polePositionIndex] = &pilotos[polePositionIndex];
    clasificados[polePositionIndex]->posicion_inicial = 1;
    clasificados[polePositionIndex]->puntos += 3;

    // Asignar la vuelta rápida en clasificación
    clasificados[vueltaRapidaIndex] = &pilotos[vueltaRapidaIndex];
    clasificados[vueltaRapidaIndex]->vuelta_rapida = 1;
    clasificados[vueltaRapidaIndex]->puntos += 1;

    // Mezclar pilotos restantes para asignar posiciones iniciales
    int pos = 2;
    for (int i = 0; i < total_pilotos; i++) {
        if (i != polePositionIndex && i != vueltaRapidaIndex) {
            clasificados[i] = &pilotos[i];
            clasificados[i]->posicion_inicial = pos++;
        }
    }

    // Mostrar posiciones iniciales
    printf("\nPosiciones iniciales:\n");
    printf("Posición\tID\tNombre\tNúmero\n");
    for (int i = 0; i < total_pilotos; i++) {
        printf("%d\t\t%s\t%s\t%d\n", clasificados[i]->posicion_inicial, clasificados[i]->id, clasificados[i]->nombre, clasificados[i]->numero);
    }

    // Simular descalificaciones
    int descalificados = (rand() % 9) + 1; // Número aleatorio entre 1 y 9
    printf("\nPilotos descalificados: %d\n", descalificados);
    for (int i = 0; i < descalificados; i++) {
        descalificadosIndices[i] = rand() % total_pilotos;
        pilotos[descalificadosIndices[i]].posicion_final = -1; // Marcados como descalificados
    }

    // Asignar posiciones finales
    int finalistasCount = 0;
    for (int i = 0; i < total_pilotos; i++) {
        int descalificado = 0;
        for (int j = 0; j < descalificados; j++) {
            if (descalificadosIndices[j] == i) {
                descalificado = 1;
                break;
            }
        }
        if (!descalificado) {
            finalistas[finalistasCount++] = &pilotos[i];
        }
    }

    // Asignar posiciones finales y puntos
    for (int i = 0; i < finalistasCount; i++) {
        finalistas[i]->posicion_final = i + 1;
        if (i < MAX_PUNTOS) {
            finalistas[i]->puntos += puntos[i];
        }
    }

    // Asignar vuelta rápida en carrera
    int vueltaRapidaCarreraIndex = rand() % MAX_PUNTOS;
    finalistas[vueltaRapidaCarreraIndex]->puntos += 1;

    // Mostrar resultados finales
    printf("\nResultados finales:\n");
    printf("Posición\tID\tNombre\tNúmero\tPuntos\n");
    for (int i = 0; i < finalistasCount; i++) {
        printf("%d\t\t%s\t%s\t%d\t%d\n", finalistas[i]->posicion_final, finalistas[i]->id, finalistas[i]->nombre, finalistas[i]->numero, finalistas[i]->puntos);
    }

    printf("\nSimulación realizada con éxito. Podrá verificar los resultados en la sección de resultados de la carrera.\n");
}


void generarId(char *prefijo, int numero, char *resultado) {
    sprintf(resultado, "%s%03d", prefijo, numero);
}
