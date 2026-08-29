#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

int leerEntero();

bool esValido(int n, int min, int max);

int totalDatos();



double leerDato(int i);

std::vector<double> ingresarDatos(int cantidad);



int pedirDecimales();

void aplicarDecimales(int decimales);

double calcularRango(const std::vector<double>& datos);

std::string interpretacionCV (double CV);

struct MedidasDeDispersion {
    std::string interpretacionCVp;
    std::string interpretacionCVm;
    double cvP;
    double cvM;
    double desvioP;
    double desvioM;
    double varianzaM;
    double varianzaP;
    double rango;
};

struct MedidasDeTendencia {
    double moda;
    double media;
    double mediana;
};

struct DatosAgrupados{
    std::vector <std::pair<double, double>> intervalos;
    std::vector<double> datos;
    std::vector<double> marcasDeClase;
    std::vector<int> frecuencias;
    std::vector<int> frecuenciaAcumulada;
    std::vector<double> frecuenciaRelativa;
    std::vector<double> frecuenciaRP;
    std::vector<double> frecuenciaRA;
};

void cargarDatos(DatosAgrupados& sDatos);
