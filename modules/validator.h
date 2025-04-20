#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "processor.h" // Para usar CityData

// Valida si el nivel sísmico es válido (1 a 5)
int validar_seismic_level(int level);

// Valida si el porcentaje de riesgo es válido (0.0 a 100.0)
int validar_risk_percent(float risk);

// Valida una ciudad completa: nivel sísmico y riesgo (si lo tiene)
int validar_ciudad(const CityData *ciudad);

#endif