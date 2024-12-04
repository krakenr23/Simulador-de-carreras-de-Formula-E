/*
@file simuladorFormulaE.c
@brief Simulador de Carreras de Fórmula E.
@details Programa que simula el comportamiento de una Carrera de Fórmula E.
@author Desarrollado por Daniel Loyo, Andrés Muñoz, Héctor Murillo & Carlos Ríos.
@date Fecha de creacion: 25 de noviembre del 2024.
 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h> // Para funciones de manipulación de caracteres (tolower)


#define MAX_PAISES 40
#define MAX_EQUIPOS 25
#define MAX_PILOTOS 22
#define MAX_PUNTOS 400
#define BAR_LENGTH 30 
#define TOTAL_TIME 3000000 

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
    char id_pais[20];
    int posicion_inicial;
    int posicion_final;
    int puntos;
    int vuelta_rapida;
} Piloto;

typedef struct {
    char id[10];
    char nombre[50];
    int numero; 
    char id_pais[10];
    char fecha_hora[30]; 
    int resultados[MAX_PILOTOS][3];
    int simulada;
} Carrera;

void mostrarMenu();
void menuCatalogos(int *contador_paises, Pais *paises, int *contador_equipos, Equipo *equipos, int *contador_pilotos, Piloto *pilotos, int *contador_carreras, Carrera *carreras);
void menuPaises(Pais *paises, int *contador_paises);
void menuEquipos(Equipo *equipos, int *contador_equipos, Pais *paises, int contador_paises);
void menuPilotos(Piloto *pilotos, int *contador_pilotos, Equipo *equipos, int contador_equipos, Pais *paises, int contador_paises);
void mostrarResultadosCarrera(Carrera *carreras, int total_carreras, Piloto *pilotos, int total_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises);

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
void simularCarrera(Piloto *pilotos, int total_pilotos, Carrera *carreras, int total_carreras);

void menuCarreras(Carrera *carreras, int *contador_carreras, Pais *paises, int total_paises);
void agregarCarrera(Carrera *carreras, int *contador_carreras, Pais *paises, int total_paises);
void modificarCarrera(Carrera *carreras, int contador_carreras, Pais *paises, int total_paises);
void eliminarCarrera(Carrera *carreras, int *contador_carreras);
void mostrarCarreras(Carrera *carreras, int total_carreras);

void generarId(char *prefijo, int numero, char *resultado);

int main() {
    Pais paises[MAX_PAISES];
    Equipo equipos[MAX_EQUIPOS];
    Piloto pilotos[MAX_PILOTOS];
    int contador_paises = 0, contador_equipos = 0, contador_pilotos = 0;
    Carrera carreras[MAX_PAISES]; 
    int contador_carreras = 0, opcion;

    srand(time(NULL)); 

    while (1) {
        mostrarMenu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
    case 1:
        menuCatalogos(&contador_paises, paises, &contador_equipos, equipos, &contador_pilotos, pilotos, &contador_carreras, carreras);
        break;
    case 2:
        simularCarrera(pilotos, contador_pilotos, carreras, contador_carreras);
        break;
    case 3:
        mostrarResultadosCarrera(carreras, contador_carreras, pilotos, contador_pilotos, equipos, contador_equipos, paises, contador_paises);
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

/*
@fn Función que muestra el menú principal.
*/
void mostrarMenu(void) {
    printf("\nMenú Principal\n");
    printf("1) Catálogos\n");
    printf("2) Simulador de carrera\n");
    printf("3) Resultados de la carrera\n");
    printf("4) Salir\n");
}

/*
@fn Función que muestra el menú de la opción Catálogos.
@param Apuntador entero: contador_paises, paises, contador_Equipos, equipos, contador_pilotos, pilotos, contador_carreras, carreras.
*/
void menuCatalogos(int *contador_paises, Pais *paises, int *contador_equipos, Equipo *equipos, int *contador_pilotos, Piloto *pilotos, int *contador_carreras, Carrera *carreras) {
    int opcion;

    while (1) {
        system("clear");
        printf("\nCatálogos:\n");
        printf("1) Paises\n");
        printf("2) Equipos\n");
        printf("3) Pilotos\n");
        printf("4) Carreras\n");
        printf("5) Regresar al menú principal\n");
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
                menuCarreras(carreras, contador_carreras, paises, *contador_paises);
                break;
            case 5:
                return;
            default:
                printf("Opción no válida.\n");
        }
    }
}

/*
@fn Función que muestra el menú de Países.
@param Apuntador: contador_paises, paises.
*/
void menuPaises(Pais *paises, int *contador_paises) {
    int opcion;

    while (1) {
        system("clear");
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
                system("clear");
                mostrarPaises(paises, *contador_paises);
                printf("\nPresione Enter para regresar al menú...\n");
                getchar();
                getchar();
                break;
            case 4:
                eliminarPais(paises, contador_paises);
                break;
            case 5:
                return;
            default:
                printf("Opción no válida.\n");
                getchar();
        }
    }
}

/*
@fn Función que agrega un país a los registros.
@param Apuntador: contador_paises, paises.
*/
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
    int i;

    if (contador_paises == 0) {
        printf("No hay países registrados para modificar.\n");
        return;
    }

    while (1) {
        system("clear");
        printf("=== Países Registrados ===\n\n");
        printf("   ID_País       Nombre_País   \n");
        printf("-------------------------------\n");

        for (i = 0; i < contador_paises; i++) {
            // Calcular espacios para centrar
            int id_padding_left = (14 - strlen(paises[i].id)) / 2;
            int id_padding_right = 9 - strlen(paises[i].id) - id_padding_left;

            int nombre_padding_left = (28 - strlen(paises[i].nombre)) / 2;
            int nombre_padding_right = 24 - strlen(paises[i].nombre) - nombre_padding_left;

            // Imprimir valores centrados
            printf("%*s%s%*s", id_padding_left, "", paises[i].id, id_padding_right, "");
            printf("%*s%s%*s\n", nombre_padding_left, "", paises[i].nombre, nombre_padding_right, "");
        }

        char opcion;
        printf("\n¿Desea realizar alguna modificación? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return;
        } else if (opcion == 's' || opcion == 'S') {
            char id[20];
            printf("\nIngrese el ID del país que desea modificar: ");
            scanf("%s", id);

            int encontrado = 0;
            for (i = 0; i < contador_paises; i++) {
                if (strcmp(paises[i].id, id) == 0) {
                    encontrado = 1;

                    char nuevo_nombre[50];
                    printf("Ingrese el nuevo nombre para el país '%s': ", paises[i].nombre);
                    scanf("%s", nuevo_nombre);

                    // Verificar duplicidad
                    int nombre_duplicado = 0;
                    for (int j = 0; j < contador_paises; j++) {
                        if (strcasecmp(paises[j].nombre, nuevo_nombre) == 0) {
                            nombre_duplicado = 1;
                            printf("\033[33m(Ya existe el país '%s' registrado)\033[0m\n", paises[j].nombre);
                            printf("\nPresione Enter para continuar...\n");
                            getchar(); // Captura el salto de línea residual
                            getchar(); // Espera a que el usuario presione Enter
                            break;
                        }
                    }

                    if (nombre_duplicado) {
                        printf("Modificación cancelada debido a duplicidad de nombres.\n");
                        break;
                    }

                    // Confirmar la modificación
                    char confirmacion;
                    printf("\n¿Desea guardar los cambios realizados al país '%s'? (s/n): ", paises[i].nombre);
                    scanf(" %c", &confirmacion);

                    if (confirmacion == 's' || confirmacion == 'S') {
                        strcpy(paises[i].nombre, nuevo_nombre);
                        printf("Modificación realizada con éxito.\n");
                    } else {
                        printf("Modificación cancelada. No se realizaron cambios.\n");
                    }

                    break;
                }
            }

            if (!encontrado) {
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
                printf("\nPresione Enter para continuar...\n");
                getchar(); // Captura el salto de línea residual
                getchar(); // Espera a que el usuario presione Enter
            }
        } else {
            printf("Opción no válida. Intente de nuevo.\n");
        }
    }
}



/*
@fn Función que muestra países previemente registrados.
@param Apuntador: contador_paises, paises.
*/
void mostrarPaises(Pais *paises, int contador_paises) {
    int i;
    system("clear");
    if (contador_paises == 0) {
        printf("No hay países registrados.\n");
    } else {
        printf("\n=== Países Registrados ===\n\n");
        printf("   ID_País       Nombre_País   \n");
        printf("-------------------------------\n");
        for (i = 0; i < contador_paises; i++) {
            // Calcular espacios para centrar
            int id_padding_left = (14 - strlen(paises[i].id)) / 2;
            int id_padding_right = 9 - strlen(paises[i].id) - id_padding_left;

            int nombre_padding_left = (28 - strlen(paises[i].nombre)) / 2;
            int nombre_padding_right = 24 - strlen(paises[i].nombre) - nombre_padding_left;

            // Imprimir valores centrados
            printf("%*s%s%*s", id_padding_left, "", paises[i].id, id_padding_right, "");
            printf("%*s%s%*s\n", nombre_padding_left, "", paises[i].nombre, nombre_padding_right, "");
        }
    }
}

void eliminarPais(Pais *paises, int *contador_paises) {
    if (*contador_paises == 0) {
        printf("No hay países registrados para eliminar.\n");
        printf("\nPresione Enter para regresar al menú...\n");
        getchar(); // Captura el salto de línea residual
        getchar(); // Espera a que el usuario presione Enter
        return;
    }

    while (1) {
        system("clear"); // Limpia la pantalla

        // Mostrar la lista de países registrados
        printf("=== Países Registrados ===\n\n");
        printf("   ID_País       Nombre_País   \n");
        printf("-------------------------------\n");
        for (int i = 0; i < *contador_paises; i++) {
            int id_padding_left = (14 - strlen(paises[i].id)) / 2;
            int id_padding_right = 9 - strlen(paises[i].id) - id_padding_left;

            int nombre_padding_left = (28 - strlen(paises[i].nombre)) / 2;
            int nombre_padding_right = 24 - strlen(paises[i].nombre) - nombre_padding_left;

            printf("%*s%s%*s", id_padding_left, "", paises[i].id, id_padding_right, "");
            printf("%*s%s%*s\n", nombre_padding_left, "", paises[i].nombre, nombre_padding_right, "");
        }

        // Preguntar si desea eliminar un país
        char opcion;
        printf("\n¿Desea eliminar algún país? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return; // Regresa al menú
        } else if (opcion == 's' || opcion == 'S') {
            char id[10];
            printf("\nIngrese el ID del país que desea eliminar: ");
            scanf("%s", id);

            // Buscar el país por ID
            int encontrado = -1;
            for (int i = 0; i < *contador_paises; i++) {
                if (strcmp(paises[i].id, id) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                // Confirmar eliminación
                char confirmacion;
                printf("\n¿Está seguro de que desea eliminar el país '%s'? (s/n): ", paises[encontrado].nombre);
                scanf(" %c", &confirmacion);

                if (confirmacion == 's' || confirmacion == 'S') {
                    // Eliminar el país desplazando los registros
                    for (int j = encontrado; j < *contador_paises - 1; j++) {
                        paises[j] = paises[j + 1];
                    }
                    (*contador_paises)--; // Disminuir el contador
                    printf("\nPaís eliminado con éxito.\n");
                    printf("\nPresione Enter para continuar...\n");
                    getchar(); // Captura el salto de línea residual
                    getchar(); // Espera a que el usuario presione Enter
                } else {
                    printf("\nEl país no se eliminó.\n");
                    printf("\nPresione Enter para continuar...\n");
                    getchar(); // Captura el salto de línea residual
                    getchar(); // Espera a que el usuario presione Enter
                }
            } else {
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
                printf("\nPresione Enter para continuar...\n");
                getchar(); // Captura el salto de línea residual
                getchar(); // Espera a que el usuario presione Enter
            }
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
            printf("\nPresione Enter para continuar...\n");
            getchar(); // Captura el salto de línea residual
            getchar(); // Espera a que el usuario presione Enter
        }
    }
}




/*
@fn Función que muestra el menú de Equipos.
@param Apuntador: equipos, contador_equipos, paises. Entero: contador_paises.
*/
void menuEquipos(Equipo *equipos, int *contador_equipos, Pais *paises, int contador_paises) {
    int opcion;

    while (1) {
        system("clear");
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
                system("clear");
                mostrarEquipos(equipos, *contador_equipos, paises, contador_paises);
                printf("\nPresione Enter para regresar al menú...\n");
                getchar();
                getchar();
                break;
            case 4:
                eliminarEquipo(equipos, contador_equipos, paises, contador_paises);
                break;
            case 5:
                return;
            default:
                printf("Opción no válida.\n");
                getchar();
        }
    }
}

/*
@fn Función que agrega un país a los registros.
@param Apuntador: equipos, contador_equipos, paises. Entero: total_paises.
*/
void agregarEquipo(Equipo *equipos, int *contador_equipos, Pais *paises, int total_paises) {
    int indice_aleatorio;
    
    if (*contador_equipos >= MAX_EQUIPOS) {
        printf("No se pueden agregar más equipos.\n");
        return;
    }

    generarId("EQ", *contador_equipos + 1, equipos[*contador_equipos].id);
    printf("Ingrese el nombre del equipo: ");
    scanf("%s", equipos[*contador_equipos].nombre);

    if (total_paises > 0) {
        indice_aleatorio = rand() % total_paises;
        strcpy(equipos[*contador_equipos].id_pais, paises[indice_aleatorio].id);
    } else {
        printf("No hay países registrados para asignar.\n");
        strcpy(equipos[*contador_equipos].id_pais, "");
    }

    (*contador_equipos)++;
    printf("Equipo agregado con éxito. País asignado automáticamente.\n");
}

void modificarEquipo(Equipo *equipos, int contador_equipos, Pais *paises, int total_paises) {
    char opcion, id[10];
    int i, j, encontrado = -1;

    if (contador_equipos == 0) {
        printf("No hay equipos registrados para modificar.\n");
        printf("\nPresione Enter para regresar al menú...\n");
        getchar(); // Captura el salto de línea residual
        getchar(); // Espera la entrada del usuario
        return;
    }

    while (1) {
        system("clear"); // Limpia la pantalla

        // Mostrar la tabla de equipos registrados
        printf("=== Equipos Registrados ===\n\n");
        printf("   ID_Equipo           Nombre_Equipo            País\n");
        printf("---------------------------------------------------------------\n");

        for (i = 0; i < contador_equipos; i++) {
            char pais_nombre[50] = "Desconocido";

            // Buscar el nombre del país asociado al equipo
            for (j = 0; j < total_paises; j++) {
                if (strcmp(equipos[i].id_pais, paises[j].id) == 0) {
                    strcpy(pais_nombre, paises[j].nombre);
                    break;
                }
            }

            // Calcular espacios para centrar
            int id_padding_left = (10 - strlen(equipos[i].id)) / 2;
            int id_padding_right = 14 - strlen(equipos[i].id) - id_padding_left;

            int equipo_padding_left = (24 - strlen(equipos[i].nombre)) / 2;
            int equipo_padding_right = 24 - strlen(equipos[i].nombre) - equipo_padding_left;

            int pais_padding_left = (18 - strlen(pais_nombre)) / 2;
            int pais_padding_right = 28 - strlen(pais_nombre) - pais_padding_left;

            // Imprimir valores centrados
            printf("   %*s%s%*s", id_padding_left, "", equipos[i].id, id_padding_right, "");
            printf("%*s%s%*s", equipo_padding_left, "", equipos[i].nombre, equipo_padding_right, "");
            printf("%*s%s%*s\n", pais_padding_left, "", pais_nombre, pais_padding_right, "");
        }

        // Preguntar si desea realizar alguna modificación
        printf("\n¿Desea realizar alguna modificación? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return; // Salir del bucle y regresar al menú principal
        } else if (opcion == 's' || opcion == 'S') {
            // Pedir el ID del equipo a modificar
            printf("\nIngrese el ID del equipo que desea modificar: ");
            scanf("%s", id);

            encontrado = -1;
            for (i = 0; i < contador_equipos; i++) {
                if (strcmp(equipos[i].id, id) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                Equipo equipo_backup = equipos[encontrado]; // Respaldar datos originales

                // Pedir el nuevo nombre del equipo
                printf("\nIngrese el nuevo nombre del equipo '%s': ", equipos[encontrado].nombre);
                scanf("%s", equipos[encontrado].nombre);

                // Mostrar los países disponibles y pedir el nuevo país asociado
                printf("Seleccione el nuevo país asociado al equipo:\n");
                for (j = 0; j < total_paises; j++) {
                    printf("%s: %s\n", paises[j].id, paises[j].nombre);
                }
                printf("ID del país: ");
                scanf("%s", equipos[encontrado].id_pais);

                // Confirmar cambios
                char confirmacion;
                printf("\n¿Desea guardar los cambios realizados al equipo '%s'? (s/n): ", equipo_backup.nombre);
                scanf(" %c", &confirmacion);

                if (confirmacion == 's' || confirmacion == 'S') {
                    printf("\nModificación realizada con éxito.\n");
                } else {
                    equipos[encontrado] = equipo_backup; // Revertir cambios
                    printf("\nModificación cancelada. No se realizaron cambios.\n");
                }
            } else {
                // Si el ID no es válido, mostrar mensaje de error y esperar Enter para continuar
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
                printf("\nPresione Enter para continuar...\n");
                getchar(); // Captura el salto de línea residual
                getchar(); // Espera la entrada del usuario
            }
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
            printf("\nPresione Enter para continuar...\n");
            getchar(); // Captura el salto de línea residual
            getchar(); // Espera la entrada del usuario
        }
    }
}



/*
@fn Función que muestra equipos previemente registrados.
@param Apuntador: equipos, contador_equipos, paises. Entero: contador_equipos, total_paises.
*/
void mostrarEquipos(Equipo *equipos, int contador_equipos, Pais *paises, int total_paises) {
    if (contador_equipos == 0) {
        printf("No hay equipos registrados.\n");
        return;
    }

    printf("=== Equipos Registrados ===\n\n");
    printf("   ID_Equipo           Nombre_Equipo            País\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < contador_equipos; i++) {
        char pais_nombre[50] = "Desconocido";

        // Buscar el país asociado al equipo
        for (int j = 0; j < total_paises; j++) {
            if (strcmp(equipos[i].id_pais, paises[j].id) == 0) {
                strcpy(pais_nombre, paises[j].nombre);
                break;
            }
        }

        // Calcular espacios para centrar
        int id_padding_left = (10 - strlen(equipos[i].id)) / 2;
        int id_padding_right = 14 - strlen(equipos[i].id) - id_padding_left;

        int equipo_padding_left = (24 - strlen(equipos[i].nombre)) / 2;
        int equipo_padding_right = 24 - strlen(equipos[i].nombre) - equipo_padding_left;

        int pais_padding_left = (18 - strlen(pais_nombre)) / 2;
        int pais_padding_right = 24 - strlen(pais_nombre) - pais_padding_left;

        // Imprimir valores centrados
        printf("   %*s%s%*s", id_padding_left, "", equipos[i].id, id_padding_right, "");
        printf("%*s%s%*s", equipo_padding_left, "", equipos[i].nombre, equipo_padding_right, "");
        printf("%*s%s%*s\n", pais_padding_left, "", pais_nombre, pais_padding_right, "");
    }
    printf("---------------------------------------------------------------\n");
}


void eliminarEquipo(Equipo *equipos, int *contador_equipos, Pais *paises, int total_paises) {
    if (*contador_equipos == 0) {
        printf("No hay equipos registrados para eliminar.\n");
        printf("\nPresione Enter para regresar al menú...\n");
        getchar(); // Captura el salto de línea residual
        getchar(); // Espera a que el usuario presione Enter
        return;
    }

    while (1) {
        system("clear"); // Limpia la pantalla

        // Mostrar la tabla de equipos registrados
        printf("=== Equipos Registrados ===\n\n");
        printf("   ID_Equipo           Nombre_Equipo            País\n");
        printf("---------------------------------------------------------------\n");

        for (int i = 0; i < *contador_equipos; i++) {
            char pais_nombre[50] = "Desconocido";

            // Buscar el país asociado al equipo
            for (int j = 0; j < total_paises; j++) {
                if (strcmp(equipos[i].id_pais, paises[j].id) == 0) {
                    strcpy(pais_nombre, paises[j].nombre);
                    break;
                }
            }

            printf("   %-10s           %-20s           %-20s\n",
                   equipos[i].id, equipos[i].nombre, pais_nombre);
        }
        printf("---------------------------------------------------------------\n");

        // Preguntar si desea eliminar un equipo
        char opcion;
        printf("\n¿Desea eliminar algún equipo? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return; // Regresa directamente al menú principal
        } else if (opcion == 's' || opcion == 'S') {
            char id[10];
            printf("\nIngrese el ID del equipo que desea eliminar: ");
            scanf("%s", id);

            // Buscar el equipo por ID
            int encontrado = -1;
            for (int i = 0; i < *contador_equipos; i++) {
                if (strcmp(equipos[i].id, id) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                // Confirmar eliminación
                char confirmacion;
                printf("\n¿Está seguro de que desea eliminar el equipo '%s'? (s/n): ", equipos[encontrado].nombre);
                scanf(" %c", &confirmacion);

                if (confirmacion == 's' || confirmacion == 'S') {
                    // Eliminar el equipo desplazando los registros
                    for (int j = encontrado; j < *contador_equipos - 1; j++) {
                        equipos[j] = equipos[j + 1];
                    }
                    (*contador_equipos)--; // Disminuir el contador
                    printf("\nEquipo eliminado con éxito.\n");
                    printf("\nPresione Enter para continuar...\n");
                    getchar(); // Captura el salto de línea residual
                    getchar(); // Espera a que el usuario presione Enter
                } else {
                    printf("\nEl equipo no se eliminó.\n");
                    printf("\nPresione Enter para continuar...\n");
                    getchar(); // Captura el salto de línea residual
                    getchar(); // Espera a que el usuario presione Enter
                }
            } else {
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
                printf("\nPresione Enter para continuar...\n");
                getchar(); // Captura el salto de línea residual
                getchar(); // Espera a que el usuario presione Enter
            }
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
            printf("\nPresione Enter para continuar...\n");
            getchar(); // Captura el salto de línea residual
            getchar(); // Espera a que el usuario presione Enter
        }
    }
}

/*
@fn Función que muestra el menú de Pilotos.
@param Apuntador: pilotos, contador_pilotos, equipos, contador_equipos, paises. Entero: contador_equipos, contador_paises.
*/
void menuPilotos(Piloto *pilotos, int *contador_pilotos, Equipo *equipos, int contador_equipos, Pais *paises, int contador_paises) {
    int opcion;

    while (1) {
        system("clear"); // Limpia la pantalla antes de mostrar el menú
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
                system("clear"); // Limpia la pantalla antes de mostrar pilotos
                mostrarPilotos(pilotos, *contador_pilotos, equipos, contador_equipos, paises, contador_paises);
                printf("\nPresione Enter para regresar al menú...\n");
                getchar();
                getchar(); // Pausa para permitir al usuario ver los resultados
                break;
            case 4:
                eliminarPiloto(pilotos, contador_pilotos);
                break;
            case 5:
                return; // Regresa al menú Catálogos
            default:
                printf("Opción no válida.\n");
                getchar(); // Captura el salto de línea residual
                getchar(); // Pausa antes de volver al menú
        }
    }
}


/*
@fn Función que agrega un piloto a los registros.
@param Apuntador: pilotos, contador_pilotos, equipos, contador_equipos, paises. Entero: total_paises.
*/
void agregarPiloto(Piloto *pilotos, int *contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises) {
    if (*contador_pilotos >= MAX_PILOTOS) {
        printf("No se pueden agregar más pilotos. Se alcanzó el máximo permitido (%d).\n", MAX_PILOTOS);
        return;
    }

    generarId("PI", *contador_pilotos + 1, pilotos[*contador_pilotos].id);

    printf("Ingrese el nombre del piloto: ");
    scanf("%s", pilotos[*contador_pilotos].nombre);
    pilotos[*contador_pilotos].numero = rand() % 99 + 1;

    // Contar pilotos por equipo
    int conteo_equipos[MAX_EQUIPOS] = {0};
    for (int i = 0; i < *contador_pilotos; i++) {
        for (int j = 0; j < total_equipos; j++) {
            if (strcmp(pilotos[i].id_equipo, equipos[j].id) == 0) {
                conteo_equipos[j]++;
                break;
            }
        }
    }

    // Buscar un equipo disponible
    int equipo_asignado = -1;
    for (int i = 0; i < total_equipos; i++) {
        if (conteo_equipos[i] < 2) {
            equipo_asignado = i;
            break;
        }
    }

    if (equipo_asignado == -1) {
        printf("No hay equipos disponibles con capacidad para más pilotos.\n");
        return;
    }

    strcpy(pilotos[*contador_pilotos].id_equipo, equipos[equipo_asignado].id);

    // Asignar país
    if (total_paises > 0) {
        int indice_pais = rand() % total_paises;
        strcpy(pilotos[*contador_pilotos].id_pais, paises[indice_pais].id);
    } else {
        printf("No hay países registrados para asignar.\n");
        strcpy(pilotos[*contador_pilotos].id_pais, "");
    }

    (*contador_pilotos)++;

    printf("Piloto agregado con éxito.\n");
    printf("Nombre: %s\n", pilotos[*contador_pilotos - 1].nombre);
    printf("Número: %d\n", pilotos[*contador_pilotos - 1].numero);
    printf("Equipo asignado: %s\n", equipos[equipo_asignado].nombre);
    printf("País asignado: %s\n", pilotos[*contador_pilotos - 1].id_pais);
}


/*
@fn Función que modifica un piloto previamente ingresado.
@param Apuntador: pilotos, contador_pilotos, equipos, contador_equipos, paises. Entero: total_paises.
*/
void modificarPiloto(Piloto *pilotos, int contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises) {
    if (contador_pilotos == 0) {
        printf("No hay pilotos registrados para modificar.\n");
        printf("Presione Enter para regresar al menú...\n");
        getchar(); // Captura el salto de línea residual
        getchar(); // Espera a que el usuario presione Enter
        return;
    }

    while (1) {
        system("clear"); // Limpia la pantalla

        // Mostrar pilotos registrados
        printf("=== Pilotos Registrados ===\n\n");
        printf("ID_Piloto\tNombre\t\tNúmero\tEquipo\t\tPaís\n");
        printf("-----------------------------------------------------------\n");
        for (int i = 0; i < contador_pilotos; i++) {
            char equipo_nombre[50] = "Desconocido", pais_nombre[50] = "Desconocido";

            // Buscar el nombre del equipo asociado al piloto
            for (int j = 0; j < total_equipos; j++) {
                if (strcmp(pilotos[i].id_equipo, equipos[j].id) == 0) {
                    strcpy(equipo_nombre, equipos[j].nombre);
                    break;
                }
            }

            // Buscar el nombre del país asociado al piloto
            for (int k = 0; k < total_paises; k++) {
                if (strcmp(pilotos[i].id_pais, paises[k].id) == 0) {
                    strcpy(pais_nombre, paises[k].nombre);
                    break;
                }
            }

            printf("%s\t\t%s\t%d\t%s\t\t%s\n", pilotos[i].id, pilotos[i].nombre, pilotos[i].numero, equipo_nombre, pais_nombre);
        }

        // Preguntar si desea realizar alguna modificación
        char opcion;
        printf("\n¿Desea modificar algún piloto? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return; // Regresa al menú principal
        } else if (opcion == 's' || opcion == 'S') {
            char id[10];
            printf("\nIngrese el ID del piloto que desea modificar: ");
            scanf("%s", id);

            int encontrado = -1;
            for (int i = 0; i < contador_pilotos; i++) {
                if (strcmp(pilotos[i].id, id) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                Piloto piloto_backup = pilotos[encontrado]; // Respaldar datos originales

                printf("\nIngrese el nuevo nombre del piloto: ");
                scanf("%s", pilotos[encontrado].nombre);

                printf("Seleccione el nuevo equipo para el piloto:\n");
                mostrarEquipos(equipos, total_equipos, paises, total_paises);
                printf("ID del equipo: ");
                scanf("%s", pilotos[encontrado].id_equipo);

                printf("Seleccione el nuevo país para el piloto:\n");
                mostrarPaises(paises, total_paises);
                printf("ID del país: ");
                scanf("%s", pilotos[encontrado].id_pais);

                // Confirmar la modificación
                char confirmacion;
                printf("\n¿Desea guardar los cambios realizados al piloto '%s'? (s/n): ", piloto_backup.nombre);
                scanf(" %c", &confirmacion);

                if (confirmacion == 's' || confirmacion == 'S') {
                    printf("Modificación realizada con éxito.\n");
                } else {
                    pilotos[encontrado] = piloto_backup; // Revertir cambios
                    printf("Modificación cancelada. No se realizaron cambios.\n");
                }
            } else {
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
            }

            printf("\nPresione cualquier tecla para continuar...\n");
            getchar(); // Captura el salto de línea residual
            getchar(); // Pausa antes de volver a la tabla
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
            getchar(); // Captura el salto de línea residual
            getchar(); // Pausa antes de volver a la tabla
        }
    }
}

/*
@fn Función que muestra pilotos previamente registrados.
@param Apuntador: pilotos, contador_pilotos, equipos, contador_equipos, paises. Entero: total_paises.
*/
void mostrarPilotos(Piloto *pilotos, int contador_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises) {
    if (contador_pilotos == 0) {
        printf("No hay pilotos registrados.\n");
        return;
    }

    printf("\nID_Piloto\tNombre\t\tNúmero\t\tEquipo\t\tPaís\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < contador_pilotos; i++) {
        char equipo_nombre[50] = "Desconocido", pais_nombre[50] = "Desconocido";

        for (int j = 0; j < total_equipos; j++) {
            if (strcmp(pilotos[i].id_equipo, equipos[j].id) == 0) {
                strcpy(equipo_nombre, equipos[j].nombre);
                break;
            }
        }

        for (int k = 0; k < total_paises; k++) {
            if (strcmp(pilotos[i].id_pais, paises[k].id) == 0) {
                strcpy(pais_nombre, paises[k].nombre);
                break;
            }
        }

        printf("%s\t\t%s\t\t%d\t\t%s\t\t%s\n", 
               pilotos[i].id, 
               pilotos[i].nombre, 
               pilotos[i].numero, 
               equipo_nombre, 
               pais_nombre);
    }
}


/*
@fn Función que elimina un piloto.
@param Apuntador: pilotos, contador_pilotos.
*/
void eliminarPiloto(Piloto *pilotos, int *contador_pilotos) {
    if (*contador_pilotos == 0) {
        printf("No hay pilotos registrados para eliminar.\n");
        printf("Presione Enter para regresar al menú...\n");
        getchar(); // Captura el salto de línea residual
        getchar(); // Espera a que el usuario presione Enter
        return;
    }

    while (1) {
        system("clear"); // Limpia la pantalla

        // Mostrar pilotos registrados
        printf("=== Pilotos Registrados ===\n\n");
        printf("ID_Piloto\tNombre\t\tNúmero\tEquipo\t\tPaís\n");
        printf("-----------------------------------------------------------\n");
        for (int i = 0; i < *contador_pilotos; i++) {
            printf("%s\t\t%s\t%d\t%s\t\t%s\n",
                   pilotos[i].id,
                   pilotos[i].nombre,
                   pilotos[i].numero,
                   pilotos[i].id_equipo,
                   pilotos[i].id_pais);
        }

        // Preguntar si desea eliminar un piloto
        char opcion;
        printf("\n¿Desea eliminar algún piloto? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return; // Regresa al menú principal
        } else if (opcion == 's' || opcion == 'S') {
            char id[10];
            printf("\nIngrese el ID del piloto que desea eliminar: ");
            scanf("%s", id);

            // Buscar el piloto por ID
            int encontrado = -1;
            for (int i = 0; i < *contador_pilotos; i++) {
                if (strcmp(pilotos[i].id, id) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                // Confirmar eliminación
                char confirmacion;
                printf("\n¿Está seguro de que desea eliminar al piloto '%s'? (s/n): ", pilotos[encontrado].nombre);
                scanf(" %c", &confirmacion);

                if (confirmacion == 's' || confirmacion == 'S') {
                    // Eliminar el piloto desplazando los registros
                    for (int j = encontrado; j < *contador_pilotos - 1; j++) {
                        pilotos[j] = pilotos[j + 1];
                    }
                    (*contador_pilotos)--; // Disminuir el contador
                    printf("\nPiloto eliminado con éxito.\n");
                } else {
                    printf("\nEl piloto no se eliminó.\n");
                }
            } else {
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
            }

            printf("\nPresione cualquier tecla para continuar...\n");
            getchar(); // Captura el salto de línea residual
            getchar(); // Espera a que el usuario presione una tecla
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
            getchar(); // Captura el salto de línea residual
            getchar(); // Pausa antes de volver a la tabla
        }
    }
}

/*
@fn Función que muestra el menú de Carreras.
@param Apuntador: carreras, contador_carrercas, paises. Entero: total_paises.
*/
void menuCarreras(Carrera *carreras, int *contador_carreras, Pais *paises, int total_paises) {
    int opcion;

    while (1) {
        system("clear"); // Limpia la pantalla antes de mostrar el menú
        printf("\nGestión de Carreras:\n");
        printf("1) Agregar carrera\n");
        printf("2) Modificar carrera\n");
        printf("3) Eliminar carrera\n");
        printf("4) Mostrar carreras registradas\n"); 
        printf("5) Regresar al menú Catálogos\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                system("clear"); // Limpia la pantalla antes de agregar una carrera
                agregarCarrera(carreras, contador_carreras, paises, total_paises);
                printf("\nPresione Enter para regresar al menú...\n");
                getchar(); // Captura el salto de línea residual
                getchar(); // Pausa para el usuario
                break;
            case 2:
                system("clear"); // Limpia la pantalla antes de modificar una carrera
                modificarCarrera(carreras, *contador_carreras, paises, total_paises);
                break;
           case 3:
                system("clear"); // Limpia la pantalla antes de eliminar una carrera
                eliminarCarrera(carreras, contador_carreras);
                break;

            case 4:
                system("clear"); // Limpia la pantalla antes de mostrar carreras registradas
                mostrarCarreras(carreras, *contador_carreras);
                printf("\nPresione Enter para regresar al menú...\n");
                getchar();
                getchar();
                break;
            case 5:
                return; // Regresa al menú Catálogos
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                getchar();
                getchar(); // Pausa para que el usuario pueda leer el mensaje
        }
    }
}


/*
@fn Función que agrega una carrera a los registros.
@param Apuntador: carreras, contador_carreras, paises. Entero: total_paises.
*/
void agregarCarrera(Carrera *carreras, int *contador_carreras, Pais *paises, int total_paises) {
    char id_carrera[10];
    int indice_pais;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    if (*contador_carreras >= MAX_PAISES) {
        printf("No se pueden agregar más carreras.\n");
        return;
    }

    generarId("CA", *contador_carreras + 1, id_carrera);

    printf("Ingrese el nombre de la carrera: ");
    scanf("%s", carreras[*contador_carreras].nombre);

    carreras[*contador_carreras].numero = *contador_carreras + 1;

    if (total_paises > 0) {
        indice_pais = rand() % total_paises;
        strcpy(carreras[*contador_carreras].id_pais, paises[indice_pais].id);
    } else {
        printf("No hay países registrados para asignar.\n");
        strcpy(carreras[*contador_carreras].id_pais, "Desconocido");
    }

    strftime(carreras[*contador_carreras].fecha_hora, 30, "%Y-%m-%d %H:%M:%S", tm_info);

    strcpy(carreras[*contador_carreras].id, id_carrera);
    (*contador_carreras)++;

    printf("Carrera agregada con éxito.\n");
}

void modificarCarrera(Carrera *carreras, int contador_carreras, Pais *paises, int total_paises) {
    if (contador_carreras == 0) {
        printf("No hay carreras registradas para modificar.\n");
        return; // Regresa directamente al menú
    }

    while (1) {
        system("clear"); // Limpia la pantalla antes de mostrar las carreras registradas

        // Mostrar las carreras registradas
        printf("=== Carreras Registradas ===\n\n");
        printf("ID_Carrera\tNombre\t\tPaís\t\tFecha y Hora\n");
        printf("-----------------------------------------------------------\n");
        for (int i = 0; i < contador_carreras; i++) {
            char pais_nombre[50] = "Desconocido";

            // Buscar el nombre del país asociado a la carrera
            for (int j = 0; j < total_paises; j++) {
                if (strcmp(carreras[i].id_pais, paises[j].id) == 0) {
                    strcpy(pais_nombre, paises[j].nombre);
                    break;
                }
            }

            printf("%s\t\t%s\t\t%s\t\t%s\n",
                   carreras[i].id,
                   carreras[i].nombre,
                   pais_nombre,
                   carreras[i].fecha_hora);
        }

        // Preguntar si desea modificar una carrera
        char opcion;
        printf("\n¿Desea modificar alguna carrera? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return; // Regresa directamente al menú
        } else if (opcion == 's' || opcion == 'S') {
            char id[10];
            printf("\nIngrese el ID de la carrera que desea modificar: ");
            scanf("%s", id);

            int encontrado = -1;
            for (int i = 0; i < contador_carreras; i++) {
                if (strcmp(carreras[i].id, id) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                Carrera carrera_backup = carreras[encontrado]; // Respaldar datos originales

                printf("\nIngrese el nuevo nombre de la carrera: ");
                scanf("%s", carreras[encontrado].nombre);

                printf("Seleccione el nuevo país para la carrera:\n");
                mostrarPaises(paises, total_paises);
                printf("ID del país: ");
                scanf("%s", carreras[encontrado].id_pais);

                // Confirmar los cambios
                char confirmacion;
                printf("\n¿Desea guardar los cambios realizados a la carrera '%s'? (s/n): ", carrera_backup.nombre);
                scanf(" %c", &confirmacion);

                if (confirmacion == 's' || confirmacion == 'S') {
                    printf("Modificación realizada con éxito.\n");
                } else {
                    printf("Modificación cancelada. No se realizaron cambios.\n");
                }
            } else {
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
            }
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
    }
}


void eliminarCarrera(Carrera *carreras, int *contador_carreras) {
    if (*contador_carreras == 0) {
        printf("No hay carreras registradas para eliminar.\n");
        return; // Regresa al menú
    }

    while (1) {
        system("clear"); // Limpia la pantalla

        // Mostrar las carreras registradas
        printf("=== Carreras Registradas ===\n\n");
        printf("ID_Carrera\tNombre\t\tPaís\t\tFecha y Hora\n");
        printf("-----------------------------------------------------------\n");
        for (int i = 0; i < *contador_carreras; i++) {
            printf("%s\t\t%s\t\t%s\t\t%s\n",
                   carreras[i].id,
                   carreras[i].nombre,
                   carreras[i].id_pais,
                   carreras[i].fecha_hora);
        }

        // Preguntar si desea eliminar una carrera
        char opcion;
        printf("\n¿Desea eliminar alguna carrera? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            return; // Regresa directamente al menú principal
        } else if (opcion == 's' || opcion == 'S') {
            char id[10];
            printf("\nIngrese el ID de la carrera que desea eliminar: ");
            scanf("%s", id);

            // Buscar la carrera por ID
            int encontrado = -1;
            for (int i = 0; i < *contador_carreras; i++) {
                if (strcmp(carreras[i].id, id) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                // Confirmar eliminación
                char confirmacion;
                printf("\n¿Está seguro de que desea eliminar la carrera '%s'? (s/n): ", carreras[encontrado].nombre);
                scanf(" %c", &confirmacion);

                if (confirmacion == 's' || confirmacion == 'S') {
                    // Eliminar la carrera desplazando los registros
                    for (int j = encontrado; j < *contador_carreras - 1; j++) {
                        carreras[j] = carreras[j + 1];
                    }
                    (*contador_carreras)--; // Disminuir el contador
                    printf("\nCarrera eliminada con éxito.\n");
                } else {
                    printf("\nLa carrera no se eliminó.\n");
                }
            } else {
                printf("\033[31m(ID no existente) Intente de nuevo.\033[0m\n");
            }
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
    }
}




/*
@fn Función que muestra carreras previemente registradas.
@param Apuntador: carreras. Entero: total_carreras.
*/
void mostrarCarreras(Carrera *carreras, int total_carreras) {
    int i;
    
    if (total_carreras == 0) {
        printf("No hay carreras registradas.\n");
        return;
    }

    printf("\nCarreras Registradas:\n");
    printf("ID_Carrera    Nombre                        Fecha y Hora\n");
    printf("-------------------------------------------------------------\n");
    for (i = 0; i < total_carreras; i++) {
        printf("%-12s %-28s %s\n", carreras[i].id, carreras[i].nombre, carreras[i].fecha_hora);
    }
}

/*
@fn Función que muestra una barra de cargando...
*/
void cargarBarra() {
    int pausa = TOTAL_TIME / BAR_LENGTH;
    int i, j;

    printf("\nCarrera en proceso...\n");
    printf("[");
    for (i = 0; i < BAR_LENGTH; i++) {
        printf(" ");
    }
    printf("]\r[");
    fflush(stdout);

    for (i = 0; i < BAR_LENGTH; i++) {
        usleep(pausa); 
        printf("\033[47m \033[0m");
        fflush(stdout);
    }

    printf("]\n\033[32m¡Carrera terminada!\033[0m\n");
}

void simularCarrera(Piloto *pilotos, int total_pilotos, Carrera *carreras, int total_carreras) {
    int i, j, temp;
    
    if (total_pilotos < 22) {
        printf("Se requieren exactamente 22 pilotos registrados para realizar la simulación.\n");
        return;
    }

    printf("\nSeleccione la carrera que desea simular:\n");
    for (i = 0; i < total_carreras; i++) {
        printf("%s: %s (País: %s, Simulada: %s)\n", carreras[i].id, carreras[i].nombre,
               carreras[i].id_pais, carreras[i].simulada ? "Sí" : "No");
    }

    char id_carrera[10];
    printf("Ingrese el ID de la carrera: ");
    scanf("%s", id_carrera);

    Carrera *carrera_seleccionada = NULL;
    for (i = 0; i < total_carreras; i++) {
        if (strcmp(carreras[i].id, id_carrera) == 0) {
            carrera_seleccionada = &carreras[i];
            break;
        }
    }

    if (!carrera_seleccionada) {
        printf("No se encontró la carrera con el ID especificado.\n");
        return;
    }

    if (carrera_seleccionada->simulada) {
        printf("La carrera %s ya fue simulada.\n", carrera_seleccionada->nombre);
        return;
    }

    printf("Simulando carrera: %s\n", carrera_seleccionada->nombre);
    cargarBarra();

    int posiciones_iniciales[total_pilotos];
    for (i = 0; i < total_pilotos; i++) {
        posiciones_iniciales[i] = i + 1;
    }

    for (i = total_pilotos - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = posiciones_iniciales[i];
        posiciones_iniciales[i] = posiciones_iniciales[j];
        posiciones_iniciales[j] = temp;
    }

    int posiciones_finales[total_pilotos];
    memcpy(posiciones_finales, posiciones_iniciales, sizeof(posiciones_iniciales));
    for (i = total_pilotos - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = posiciones_finales[i];
        posiciones_finales[i] = posiciones_finales[j];
        posiciones_finales[j] = temp;
    }

    for (i = 0; i < total_pilotos; i++) {
        pilotos[i].posicion_inicial = posiciones_iniciales[i];
        pilotos[i].posicion_final = posiciones_finales[i];
        pilotos[i].puntos = (posiciones_finales[i] <= 10) ? 25 - (posiciones_finales[i] - 1) * 2 : 0;

        carrera_seleccionada->resultados[i][0] = posiciones_iniciales[i];
        carrera_seleccionada->resultados[i][1] = posiciones_finales[i];
        carrera_seleccionada->resultados[i][2] = pilotos[i].puntos;
    }

    carrera_seleccionada->simulada = 1;

    printf("La carrera %s ha finalizado. ¡Los resultados están disponibles!\n", carrera_seleccionada->nombre);
}

/*
@fn Función que muestra los resultados de una carrera simulada con base en el id_carrera.
@param Apuntador: carreras, pilotos, equipos, paises. Entero: total_carreras, total_pilotos, total_equipos, total_paises. 
*/
void mostrarResultadosCarrera(Carrera *carreras, int total_carreras, Piloto *pilotos, int total_pilotos, Equipo *equipos, int total_equipos, Pais *paises, int total_paises) {
    char id_carrera[10], pais_piloto[50] = "Desconocido", equipo_nombre[50] = "Desconocido", pais_equipo[50] = "Desconocido";
    int i, j, k;
    
    if (total_carreras == 0) {
        printf("No hay carreras registradas.\n");
        return;
    }

    printf("\nResultados de Carreras:\n");
    printf("ID_Carrera\tNombre\t\tFecha y Hora\t\tSimulada\n");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < total_carreras; i++) {
        printf("%s\t\t%s\t\t%s\t\t%s\n", carreras[i].id, carreras[i].nombre,
               carreras[i].fecha_hora, carreras[i].simulada ? "Sí" : "No");
    }

    printf("\nIngrese el ID de la carrera para ver los resultados: ");
    scanf("%s", id_carrera);

    Carrera *carrera_seleccionada = NULL;
    for (i = 0; i < total_carreras; i++) {
        if (strcmp(carreras[i].id, id_carrera) == 0) {
            carrera_seleccionada = &carreras[i];
            break;
        }
    }

    if (!carrera_seleccionada) {
        printf("No se encontró una carrera con el ID especificado.\n");
        return;
    }

    if (!carrera_seleccionada->simulada) {
        printf("La carrera aún no ha sido simulada.\n");
        return;
    }

    printf("\nResultados de la Carrera: %s - %s\n", carrera_seleccionada->id, carrera_seleccionada->nombre);
    printf("Fecha y Hora: %s\n\n", carrera_seleccionada->fecha_hora);

    printf("Nombre Piloto\tNum Piloto\tPais Piloto\tEquipo Piloto\tPais Equipo\tPosición Inicial\tPosición Final\tPuntos Ganados\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < total_pilotos; i++) {
        for (j = 0; j < total_paises; j++) {
            if (strcmp(pilotos[i].id_pais, paises[j].id) == 0) {
                strcpy(pais_piloto, paises[j].nombre);
                break;
            }
        }

        for (j = 0; j < total_equipos; j++) {
            if (strcmp(pilotos[i].id_equipo, equipos[j].id) == 0) {
                strcpy(equipo_nombre, equipos[j].nombre);
                for (k = 0; k < total_paises; k++) {
                    if (strcmp(equipos[j].id_pais, paises[k].id) == 0) {
                        strcpy(pais_equipo, paises[k].nombre);
                        break;
                    }
                }
                break;
            }
        }

        printf("%-15s %-12d %-15s %-15s %-15s %-18d %-15d %-15d\n",
               pilotos[i].nombre, pilotos[i].numero, pais_piloto, equipo_nombre, pais_equipo,
               carrera_seleccionada->resultados[i][0],
               carrera_seleccionada->resultados[i][1],
               carrera_seleccionada->resultados[i][2]);
    }
}

/*
@fn Función que genera un ID.
@param Apuntador: resultado, prefijo. Entero: numero.
*/
void generarId(char *prefijo, int numero, char *resultado) {
    sprintf(resultado, "%s%03d", prefijo, numero);
}
