#include "sorter.h"
#include <string.h>

// Función de comparación personalizada entre dos ciudades
int comparar_ciudades(const CityData *a, const CityData *b) {

// 1. Nivel sísmico: mayor prioridad al más alto
    if (a->seismic_level != b->seismic_level)
        return b->seismic_level - a->seismic_level;

// 2. Si ambos tienen riesgo: mayor riesgo = más prioridad
    if (a->has_risk_percent && b->has_risk_percent) {
        if (a->risk_percent != b->risk_percent)
            return (b->risk_percent > a->risk_percent) ? 1 : -1;
    }

    // 3. Si solo uno tiene riesgo → usar prioridad por nivel sísmico
    if (a->has_risk_percent != b->has_risk_percent) {
        int a_cat = 2, b_cat = 2;

        if (!a->has_risk_percent) {
            if (a->seismic_level <= 2) a_cat = 3;
            else if (a->seismic_level >= 4) a_cat = 1;
        }

        if (!b->has_risk_percent) {
            if (b->seismic_level <= 2) b_cat = 3;
            else if (b->seismic_level >= 4) b_cat = 1;
        }

        return a_cat - b_cat;
    }

    // 4. Desempate: orden alfabético inverso (Z-A)
    return -strcmp(a->city_name, b->city_name);
}

// Algoritmo de QuickSort para CityData
void quicksort_ciudades(CityData *ciudades, int inicio, int fin) {
    if (inicio >= fin) return;

    CityData pivote = ciudades[fin];
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (comparar_ciudades(&ciudades[j], &pivote) < 0) {
            i++;
            CityData temp = ciudades[i];
            ciudades[i] = ciudades[j];
            ciudades[j] = temp;
        }
    }

    CityData temp = ciudades[i + 1];
    ciudades[i + 1] = ciudades[fin];
    ciudades[fin] = temp;

    quicksort_ciudades(ciudades, inicio, i);
    quicksort_ciudades(ciudades, i + 2, fin);
}