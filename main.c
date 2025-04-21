#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h" 
#include "validator.h"
#include "sorter.h"

int main(int argc, char *argv[]) {
    // Verificar que se pasen los argumentos correctos
    if (argc != 4) {
        printf("Uso: %s <input.csv> <N_Cities> <output.txt>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[3];

    int total_ciudades = 0;
    int n_cities = atoi(argv[2]); // Convertir N_Cities desde la línea de comandos
    if (n_cities <= 0) {
        printf("El numero de ciudades a ordenar debe ser mayor que 0.\n");
        return 1;
    }

    // Leer las ciudades desde el archivo CSV
    CityData *ciudades = read_csv(input_file, &total_ciudades);
    if (!ciudades) {
        printf("Error al leer el archivo.\n");
        return 1;
    }

    // Crear un arreglo temporal para las ciudades validas
    CityData *validas = malloc(total_ciudades * sizeof(CityData));
    int count_validas = 0;

    // Validar las ciudades y copiarlas al arreglo de validas
    for (int i = 0; i < total_ciudades; i++) {
        if (validar_ciudad(&ciudades[i])) {
            validas[count_validas++] = ciudades[i]; // Copiar la ciudad valida
        }
    }

    printf("Se leyeron %d ciudades. %d validas.\n", total_ciudades, count_validas);

    // Limitar el numero de ciudades validas a N_Cities
    if (count_validas > n_cities) {
        count_validas = n_cities;
    }

    // Aplicar el algoritmo "Quicksort" para ordenar las ciudades validas
    quicksort_ciudades(validas, 0, count_validas - 1);

    // Crear el archivo de salida
    remove(output_file); // Eliminar el archivo si ya existe
    FILE *salida = fopen(output_file, "w");
    if (!salida) {
        perror("No se pudo crear el archivo de salida");
        free_data(ciudades);
        free(validas);
        return 1;
    }
    
    // Escribir el encabezado en el archivo de salida
    fprintf(salida, "city_name seismic_level risk_percent \n");
    
    // Escribir los datos de las ciudades validas en el archivo de salida
    for (int i = 0; i < count_validas; i++) {
        if (validas[i].risk_percent == 0) {
            fprintf(salida, "%s / %d /  / \n", // Dejar en blanco si risk_percent es 0
                validas[i].city_name,
                validas[i].seismic_level);
        } else {
            fprintf(salida, "%s / %d / %.1f / \n", // Imprimir el valor si no es 0
                validas[i].city_name,
                validas[i].seismic_level,
                validas[i].risk_percent);
        }
    }
    
    fclose(salida); // Cerrar el archivo de salida
    printf("Archivo 'output.txt' generado con exito.\n");
    
    // Liberar memoria
    free_data(ciudades);
    free(validas);

    return 0;
}