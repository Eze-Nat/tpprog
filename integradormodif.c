#include <stdio.h>
#include <string.h>

#define MAX_PASAJEROS 100

char dni[MAX_PASAJEROS][9];
char apellido[MAX_PASAJEROS][50];
char nombre[MAX_PASAJEROS][50];
int edad[MAX_PASAJEROS];
char codigo_destino[MAX_PASAJEROS][4];
int total_pasajeros = 0;
int cuposBRA = 0, cuposMDQ = 0, cuposMZA = 0, cuposBRC = 0;

void cargar_pasajeros();
void mostrar_lista_ordenada_por_apellido();
void mostrar_lista_ordenada_por_destino();
void mostrar_lista_de_destinos();
void buscar_por_pasajero();
void mostrar_estadisticas();
int validar_dni(char dni[]);
void ordenar_por_apellido();
void ordenar_por_destino();

int main() {
    int opcion;

    cargar_pasajeros();
    do {
        printf("Menú de opciones:\n");
        printf("1. Mostrar lista de pasajeros ordenada por Apellido y Nombre\n");
        printf("2. Mostrar lista de pasajeros ordenada por Código Destino y Apellido - Nombre\n");
        printf("3. Mostrar lista de Destinos\n");
        printf("4. Buscar por pasajero\n");
        printf("5. Mostrar estadísticas\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrar_lista_ordenada_por_apellido();
                break;
            case 2:
                mostrar_lista_ordenada_por_destino();
                break;
            case 3:
                mostrar_lista_de_destinos();
                break;
            case 4:
                buscar_por_pasajero();
                break;
            case 5:
                mostrar_estadisticas();
                break;
            case 6:
                printf("Gracias por utilizar Viaje Mágico.\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}

int validar_dni(char dni[]) {
    int len = strlen(dni);
    if (len < 7 || len > 8)
        return 0;
    if (dni[0] == '5' || dni[0] == '6' || (dni[0] >= '1' && dni[0] <= '6'))
        return 1;
    return 0;
}

void cargar_pasajeros() {
    int cantidad_pasajeros;
    printf("Ingrese la cantidad de pasajeros: ");
    scanf("%d", &cantidad_pasajeros);

    for (int i = 0; i < cantidad_pasajeros; i++) {
        do {
            printf("Ingrese DNI: ");
            scanf("%s", dni[i]);
            if (!validar_dni(dni[i]))
                printf("DNI inválido. Debe ser un número entre 7 y 8 dígitos y debe comenzar con 5, 6, o un número entre 10 y 60.\n");
        } while (!validar_dni(dni[i]));

        printf("Ingrese Apellido: ");
        scanf("%s", apellido[i]);
        printf("Ingrese Nombre: ");
        scanf("%s", nombre[i]);
        printf("Ingrese Edad: ");
        scanf("%d", &edad[i]);

        do {
            printf("Ingrese Código de Destino (BRA, MDQ, MZA, BRC): ");
            scanf("%s", codigo_destino[i]);
            if (strcmp(codigo_destino[i], "BRA") == 0) {
                if (cuposBRA < 60)
                    cuposBRA++;
                else
                    printf("Capacidad máxima alcanzada para Brasil.\n");
            } else if (strcmp(codigo_destino[i], "MDQ") == 0) {
                if (cuposMDQ < 60)
                    cuposMDQ++;
                else
                    printf("Capacidad máxima alcanzada para Mar del Plata.\n");
            } else if (strcmp(codigo_destino[i], "MZA") == 0) {
                if (cuposMZA < 60)
                    cuposMZA++;
                else
                    printf("Capacidad máxima alcanzada para Mendoza.\n");
            } else if (strcmp(codigo_destino[i], "BRC") == 0) {
                if (cuposBRC < 60)
                    cuposBRC++;
                else
                    printf("Capacidad máxima alcanzada para Bariloche.\n");
            } else {
                printf("Código de destino inválido.\n");
            }
        } while (!(strcmp(codigo_destino[i], "BRA") == 0 || strcmp(codigo_destino[i], "MDQ") == 0 || strcmp(codigo_destino[i], "MZA") == 0 || strcmp(codigo_destino[i], "BRC") == 0));
        
        total_pasajeros++;
    }
}

void ordenar_por_apellido() {
    for (int i = 0; i < total_pasajeros - 1; i++) {
        for (int j = i + 1; j < total_pasajeros; j++) {
            if (strcmp(apellido[i], apellido[j]) > 0) {
                char temp[50];
                strcpy(temp, apellido[i]);
                strcpy(apellido[i], apellido[j]);
                strcpy(apellido[j], temp);
                strcpy(temp, nombre[i]);
                strcpy(nombre[i], nombre[j]);
                strcpy(nombre[j], temp);
                strcpy(temp, dni[i]);
                strcpy(dni[i], dni[j]);
                strcpy(dni[j], temp);
                int tempEdad = edad[i];
                edad[i] = edad[j];
                edad[j] = tempEdad;
                strcpy(temp, codigo_destino[i]);
                strcpy(codigo_destino[i], codigo_destino[j]);
                strcpy(codigo_destino[j], temp);
            }
        }
    }
}

void mostrar_lista_ordenada_por_apellido() {
    ordenar_por_apellido();
    for (int i = 0; i < total_pasajeros; i++) {
        printf("%s %s - DNI: %s - Edad: %d - Destino: %s\n", apellido[i], nombre[i], dni[i], edad[i], codigo_destino[i]);
    }
}

void ordenar_por_destino() {
    for (int i = 0; i < total_pasajeros - 1; i++) {
        for (int j = i + 1; j < total_pasajeros; j++) {
            if (strcmp(codigo_destino[i], codigo_destino[j]) > 0 || (strcmp(codigo_destino[i], codigo_destino[j]) == 0 && strcmp(apellido[i], apellido[j]) > 0)) {
                char temp[50];
                strcpy(temp, codigo_destino[i]);
                strcpy(codigo_destino[i], codigo_destino[j]);
                strcpy(codigo_destino[j], temp);
                strcpy(temp, apellido[i]);
                strcpy(apellido[i], apellido[j]);
                strcpy(apellido[j], temp);
                strcpy(temp, nombre[i]);
                strcpy(nombre[i], nombre[j]);
                strcpy(nombre[j], temp);
                strcpy(temp, dni[i]);
                strcpy(dni[i], dni[j]);
                strcpy(dni[j], temp);
                int tempEdad = edad[i];
                edad[i] = edad[j];
                edad[j] = tempEdad;
            }
        }
    }
}

void mostrar_lista_ordenada_por_destino() {
    ordenar_por_destino();
    for (int i = 0; i < total_pasajeros; i++) {
        printf("%s - %s %s - DNI: %s - Edad: %d\n", codigo_destino[i], apellido[i], nombre[i], dni[i], edad[i]);
    }
}

void mostrar_lista_de_destinos() {
    int importe_total = 0;
    int total_general = 0;

    // Mostrar datos para Brasil
    int importe_brazil = cuposBRA * 25000;
    total_general += importe_brazil;
    printf("BRA - Cantidad pasajeros: %d - Importe Total: $%d\n", cuposBRA, importe_brazil);

    // Mostrar datos para Mar del Plata
    int importe_mar_del_plata = cuposMDQ * 14000;
    total_general += importe_mar_del_plata;
    printf("MDQ - Cantidad pasajeros: %d - Importe Total: $%d\n", cuposMDQ, importe_mar_del_plata);

    // Mostrar datos para Mendoza
    int importe_mendoza = cuposMZA * 19000;
    total_general += importe_mendoza;
    printf("MZA - Cantidad pasajeros: %d - Importe Total: $%d\n", cuposMZA, importe_mendoza);

    // Mostrar datos para Bariloche
    int importe_bariloche = cuposBRC * 23000;
    total_general += importe_bariloche;
    printf("BRC - Cantidad pasajeros: %d - Importe Total: $%d\n", cuposBRC, importe_bariloche);

    // Mostrar total general
    printf("Importe Total de todos los destinos: $%d\n", total_general);
}

void buscar_por_pasajero() {
    char dni_buscado[9];
    printf("Ingrese el DNI a buscar: ");
    scanf("%s", dni_buscado);

    if (!validar_dni(dni_buscado)) {
        printf("DNI inválido. Debe ser un número entre 7 y 8 dígitos y debe comenzar con 5, 6, o un número entre 10 y 60.\n");
        return;
    }

    for (int i = 0; i < total_pasajeros; i++) {
        if (strcmp(dni[i], dni_buscado) == 0) {
            printf("Pasajero encontrado: %s %s - DNI: %s - Edad: %d - Destino: %s\n", apellido[i], nombre[i], dni[i], edad[i], codigo_destino[i]);
            if (strcmp(codigo_destino[i], "BRA") == 0) {
                printf("Importe a abonar: $25000\n");
            } else if (strcmp(codigo_destino[i], "MDQ") == 0) {
                printf("Importe a abonar: $14000\n");
            } else if (strcmp(codigo_destino[i], "MZA") == 0) {
                printf("Importe a abonar: $19000\n");
            } else if (strcmp(codigo_destino[i], "BRC") == 0) {
                printf("Importe a abonar: $23000\n");
            }
            return;
        }
    }
    printf("No existe pasajero con ese DNI.\n");
}

void mostrar_estadisticas() {
    int total_general = cuposBRA + cuposMDQ + cuposMZA + cuposBRC;
    int cantidad_total, cantidad_menores;
    float porcentaje, porcentaje_menores;

    // Calcular y mostrar estadísticas para Brasil
    cantidad_total = cuposBRA;
    cantidad_menores = 0;
    for (int i = 0; i < total_pasajeros; i++) {
        if (strcmp(codigo_destino[i], "BRA") == 0 && edad[i] < 5) {
            cantidad_menores++;
        }
    }
    porcentaje = (float)cantidad_total / total_general * 100;
    porcentaje_menores = (float)cantidad_menores / cantidad_total * 100;
    printf("BRA - Porcentaje de Pasajeros: %.2f%% - Porcentaje de Menores de 5 años: %.2f%%\n", porcentaje, porcentaje_menores);

    // Calcular y mostrar estadísticas para Mar del Plata
    cantidad_total = cuposMDQ;
    cantidad_menores = 0;
    for (int i = 0; i < total_pasajeros; i++) {
        if (strcmp(codigo_destino[i], "MDQ") == 0 && edad[i] < 5) {
            cantidad_menores++;
        }
    }
    porcentaje = (float)cantidad_total / total_general * 100;
    porcentaje_menores = (float)cantidad_menores / cantidad_total * 100;
    printf("MDQ - Porcentaje de Pasajeros: %.2f%% - Porcentaje de Menores de 5 años: %.2f%%\n", porcentaje, porcentaje_menores);

    // Calcular y mostrar estadísticas para Mendoza
    cantidad_total = cuposMZA;
    cantidad_menores = 0;
    for (int i = 0; i < total_pasajeros; i++) {
        if (strcmp(codigo_destino[i], "MZA") == 0 && edad[i] < 5) {
            cantidad_menores++;
        }
    }
    porcentaje = (float)cantidad_total / total_general * 100;
    porcentaje_menores = (float)cantidad_menores / cantidad_total * 100;
    printf("MZA - Porcentaje de Pasajeros: %.2f%% - Porcentaje de Menores de 5 años: %.2f%%\n", porcentaje, porcentaje_menores);

    // Calcular y mostrar estadísticas para Bariloche
    cantidad_total = cuposBRC;
    cantidad_menores = 0;
    for (int i = 0; i < total_pasajeros; i++) {
        if (strcmp(codigo_destino[i], "BRC") == 0 && edad[i] < 5) {
            cantidad_menores++;
        }
    }
    porcentaje = (float)cantidad_total / total_general * 100;
    porcentaje_menores = (float)cantidad_menores / cantidad_total * 100;
    printf("BRC - Porcentaje de Pasajeros: %.2f%% - Porcentaje de Menores de 5 años: %.2f%%\n", porcentaje, porcentaje_menores);

    // Determinar y mostrar el destino más solicitado
    printf("Destino más solicitado: ");
    if (cuposBRA > cuposMDQ && cuposBRA > cuposMZA && cuposBRA > cuposBRC) {
        printf("BRA\n");
    } else if (cuposMDQ > cuposMZA && cuposMDQ > cuposBRC) {
        printf("MDQ\n");
    } else if (cuposMZA > cuposBRC) {
        printf("MZA\n");
    } else {
        printf("BRC\n");
    }
}
