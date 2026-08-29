#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "comun.h"
#include <vector>
#include <string>

void tablaDeFrecuencias
(
 const std::vector<double>& datos,
 std::vector <double>& valores,
 std::vector <int>& frecuencias,
 std::vector <int>& frecuenciaAcumulada,
 std::vector <double>& frecuenciaRelativa,
 std::vector <double>& frecuenciaRP,
 std::vector <double>& frecuenciaRA
 );
//  MEDIDAS DE TENDENCIA
//-------------------------

double calcularMedia(const std::vector<double>& datos);

double calcularMediana(const std::vector<double>& datos);

double calcularModa(const std::vector<double>& datos, const std::vector<int>& frecuencias);

//  MEDIDAS DE VARIACIÓN
//-------------------------

double calcularVarianzaPoblacional(const std::vector<double>& datos);

double calcularVarianzaMuestral(const std::vector<double>& datos);

double calcularDesvioPoblacional(const std::vector<double>& datos);

double calcularDesvioMuestral(const std::vector<double>& datos);

double CVpoblacional (const std::vector <double>& datos);

double CVmuestral (const std::vector <double>& datos);

//  MOSTRAR RESULTADOS
//-------------------------

    void mostrarResultados(const MedidasDeDispersion& sDispersion, const MedidasDeTendencia& sTendencia, const DatosAgrupados& sDatos);

    void construirTablaDatosIndividuales(DatosAgrupados& sDatos);

    void asignarMedidasDeTendencia(MedidasDeTendencia& sTendencia,const DatosAgrupados& sDatos);

    void asignarMedidasDeDispersion(MedidasDeDispersion& sDispersion, const DatosAgrupados& sDatos);

void ejecutarDatosIndividuales();

#endif
