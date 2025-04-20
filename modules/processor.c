#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

CityData *read_csv(const char *filename, int *num_cities) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    // Contar registros
    int count = 0;
    char line[256];
    fgets(line, sizeof(line), file); // Saltar cabecera

    while (fgets(line, sizeof(line), file)) {
        count++;
    }

    rewind(file);
    fgets(line, sizeof(line), file); // Saltar cabecera otra vez

    CityData *cities = malloc(count * sizeof(CityData));
    if (!cities) {
        perror("No se pudo asignar memoria");
        fclose(file);
        return NULL;
    }

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",\n"); // Usar coma como delimitador
        if (!token) continue;

        strncpy(cities[i].city_name, token, 50);

        token = strtok(NULL, ",\n"); // Leer el siguiente campo (seismic_level)
        if (token) {
            cities[i].seismic_level = atoi(token);
        } else {
            cities[i].seismic_level = -1; // valor inválido
        }

        token = strtok(NULL, ",\n"); // Leer el siguiente campo (risk_percent)
        if (token) {
            cities[i].risk_percent = atof(token);
            cities[i].has_risk_percent = 1;
        } else {
            cities[i].risk_percent = 0.0f;
            cities[i].has_risk_percent = 0;
        }

        i++;
    }

    fclose(file);
    *num_cities = count;
    return cities;
}
void free_data(CityData *cities) {
    if (cities != NULL) {
        free(cities);
    }
}