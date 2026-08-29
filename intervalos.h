#ifndef INTERVALOS_H
#define INTERVALOS_H

#include "comun.h"
#include <vector>
#include <utility>


int calcularClasesSturges(int n);

double calcularAmplitud(double rango, int clases);

std::vector<double> calcularPuntosMedios(const std::vector<std::pair<double,double>>& intervalos);

double clasesPorFrecuencias(const std::vector <double>& valores,
                            const std::vector <int>& frecuencias);

double mediaIntervalos (const std::vector <int> & frecuencias,
                        double clasesXfrecuencias);

double calcularMediaIntervalos (const std::vector <std::pair<double, double>>& intervalos,
                                const std::vector <int>& frecuencias);

size_t encontrarIndiceMedianaIntervalos(const std::vector<int>& frecuenciaAcumulada);

double calcularMedianaIntervalos(
    const std::vector<std::pair<double, double>>& intervalos,
    const std::vector<int>& frecuencias,
    const std::vector<int>& frecuenciaAcumulada,
    double amplitud);


std::vector<std::pair<double, double>> calcularIntervalos(
    const std::vector<double>& datos,
    double amplitud,
    int clases
);

size_t encontrarIndiceModalIntervalos(const std::vector<int>& frecuencias);


std::pair<int, int> calcularSubidaBajada(const std::vector<int>& frecuencias,
                          int indiceModa);

double calcularProporcionIntervalos(const std::vector<int>& frecuencias,
                          int indiceModa);

double calcularModaIntervalos (const std::vector <std::pair<double, double>>& intervalos,
                               const std::vector<int>& frecuencias,
                               double amplitud);

double rangoDispersion(const std::vector<std::pair<double, double>>& intervalos);

double calcularVarianzaPoblacionalIntervalos(const std::vector<double>& valores,
                                             const std::vector<int>& frecuencias,
                                             double media,
                                             const std::vector<int>& frecuenciaAcumulada);

double calcularVarianzaMuestralIntervalos(const std::vector<double>& valores,
                                             const std::vector<int>& frecuencias,
                                             double media,
                                             const std::vector<int>& frecuenciaAcumulada);

double calcularDesvioPoblacionalIntervalos(double varianzaP);

double calcularDesvioMuestralIntervalos(double varianzaM);

double CVpoblacionalIntervalos(double desvioP, double media);

double CVmuestralIntervalos(double desvioM, double media);

void tablaDeFrecuenciasIntervalos(const std::vector <double>& datos,
                             const std::vector <std::pair<double, double>>& intervalos,
                             std::vector <int>& frecuencias,
                             std::vector <int> & frecuenciaAcumulada,
                             std::vector<double>& frecuenciaRelativa,
                             std::vector<double>& frecuenciaRP,
                             std::vector <double>& frecuenciaRA);

struct calculoIntervalosStruct{
    double rangoDatos;
    int clases;
    double amplitud;
};

void mostrarResultadosIntervalos(const calculoIntervalosStruct& sIntervalos, const MedidasDeDispersion& sDispersion, const MedidasDeTendencia& sTendencia, const DatosAgrupados& sDatos);


void calcularRangoClasesAmplitud(calculoIntervalosStruct& sIntervalos,  const DatosAgrupados& sDatos);

void construirTablaIntervalos(DatosAgrupados& sDatos, const calculoIntervalosStruct& sIntervalos);

void asignarMedidasDeTendenciaIntervalos(MedidasDeTendencia& sTendencia, const DatosAgrupados& sDatos, const calculoIntervalosStruct& sIntervalos);

void asignarMedidasDeDispersionIntervalos(MedidasDeDispersion& sDispersion, const DatosAgrupados& sDatos, const MedidasDeTendencia& sTendencia);

void ejecutarIntervalos();

#endif
