#include "validator.h"
#include "processor.h" // Incluir el encabezado que contiene la definición de CityData
#include <stdio.h>

// Nivel sísmico válido: entre 1 y 5
int validar_seismic_level(int level) {
    return (level >= 1 && level <= 5);
}

// Porcentaje de riesgo válido: entre 0.0 y 100.0
int validar_risk_percent(float risk) {
    return (risk >= 0.0 && risk <= 100.0);
}

// Valida una ciudad completa
int validar_ciudad(const CityData *ciudad) {
    if (!validar_seismic_level(ciudad->seismic_level)) {
        printf("Ciudad '%s' tiene nivel sismico invalido: %d\n",
               ciudad->city_name, ciudad->seismic_level);
        return 0;
    }

    if (ciudad->has_risk_percent && !validar_risk_percent(ciudad->risk_percent)) {
        printf("Ciudad '%s' tiene porcentaje de riesgo invalido: %.1f\n",
               ciudad->city_name, ciudad->risk_percent);
        return 0;
    }

    return 1; // Todo bien
}
