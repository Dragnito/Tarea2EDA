#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct {
    char city_name[50];
    int seismic_level;
    float risk_percent;
    int has_risk_percent;
} CityData;

CityData *read_csv(const char *filename, int *num_cities);

void free_data(CityData *cities);


#endif