#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h" // Incluir el encabezado que contiene CityData
#include "validator.h"
#include "sorter.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <input.csv> <N_Cities> <output.txt>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    int n_ciudades = atoi(argv[2]);
    const char *output_file = argv[3];

    int total_ciudades = 0;
    CityData *ciudades = read_csv(input_file, &total_ciudades);
    if (!ciudades) {
        printf("Error al leer el archivo.\n");
        return 1;
    }

    // Crear un arreglo temporal para las ciudades válidas
    CityData *validas = malloc(total_ciudades * sizeof(CityData));
    int count_validas = 0;

    for (int i = 0; i < total_ciudades; i++) {
        if (validar_ciudad(&ciudades[i])) {
            validas[count_validas++] = ciudades[i]; // Copiar la válida
        }
    }

    printf("Se leyeron %d ciudades. %d validas.\n", total_ciudades, count_validas);

    // Aplicacion del algoritmo "Quicksort" para ordenar las ciudades válidas
    quicksort_ciudades(validas, 0, count_validas - 1);

    printf("\nCiudades validas ordenadas:\n");
    for (int i = 0; i < count_validas; i++) {
        printf("%s - Nivel: %d - Riesgo: %.1f - Tiene riesgo: %d\n",
            validas[i].city_name,
            validas[i].seismic_level,
            validas[i].risk_percent,
            validas[i].has_risk_percent);
    }

    // Crea el archivo de salida
    FILE *salida = fopen(output_file, "w");
    if (!salida) {
        perror("No se pudo crear el archivo de salida");
        free_data(ciudades);
        free(validas);
        return 1;
    }
    
    fprintf(salida, "city_name,seismic_level,risk_percent,has_risk_percent\n");
    
    for (int i = 0; i < count_validas; i++) {
        fprintf(salida, "%s,%d,%.1f,%d\n",
            validas[i].city_name,
            validas[i].seismic_level,
            validas[i].risk_percent,
            validas[i].has_risk_percent);
    }
    
    fclose(salida);
    printf("Archivo 'output.csv' generado con éxito.\n");
    
    



    // Liberar memoria
    free_data(ciudades);
    free(validas);

    return 0;
}