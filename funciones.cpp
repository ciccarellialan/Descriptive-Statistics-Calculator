#include "comun.h"
#include "funciones.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;


//    TABLA DE FRECUENCIAS
// --------------------------

void tablaDeFrecuencias(const vector<double>& datos,
            vector <double>& marcasDeClase,
            vector <int>& frecuencias,
            vector <int>& frecuenciaAcumulada,
            vector <double>& frecuenciaRelativa,
            vector <double>& frecuenciaRP,
            vector <double>& frecuenciaRA) {

    double valorActual = datos[0];
    int frecuenciaActual = 1;



        for (int i = 1; i < datos.size(); i++) {

            double dato = datos[i];

            if (dato == valorActual) {
                frecuenciaActual++;
            } else {
                marcasDeClase.push_back(valorActual);
                frecuencias.push_back(frecuenciaActual);

                valorActual = dato;
                frecuenciaActual = 1;
            }
        }
        marcasDeClase.push_back(valorActual);
        frecuencias.push_back(frecuenciaActual);

        frecuenciaAcumulada.push_back(frecuencias[0]);

        for(size_t i = 1; i < frecuencias.size(); i++) {

        frecuenciaAcumulada.push_back(frecuenciaAcumulada[i - 1] + frecuencias [i]);

        }
        for(size_t i = 0; i < frecuencias.size(); i ++) {

            frecuenciaRelativa.push_back((double)frecuencias[i] / datos.size());

        }

        for(size_t i = 0; i < frecuencias.size(); i++) {

            frecuenciaRP.push_back(frecuenciaRelativa[i] * 100);

        }

        frecuenciaRA.push_back(frecuenciaRelativa[0]);

         for(size_t i = 1; i < frecuenciaRelativa.size(); i++) {

         frecuenciaRA.push_back(frecuenciaRA[i - 1] + frecuenciaRelativa [i]);

         }
}

//          MEDIA
// --------------------------

    double calcularMedia(const vector<double>& datos) {

    double suma = 0;

    for (double x : datos){suma += x;

    }

        return suma / datos.size();
    }


//          MEDIANA
// --------------------------

double calcularMediana(const vector<double>& datos) {

    int n = datos.size();
    int mid = n / 2;

    if (n % 2 == 0) {
        return (datos[mid - 1] + datos[mid]) / 2;
    } else {
        return datos[mid];
    }
}

//          MODA
// --------------------------

double calcularModa(const vector<double>& datos, const vector<int>& frecuencias) {
    int indiceModa = 0;
    int frecuenciaMaxima = frecuencias[0];

    for (size_t i = 1; i < frecuencias.size(); i++) {
        if (frecuencias[i] > frecuenciaMaxima) {
            frecuenciaMaxima = frecuencias[i];
            indiceModa = i;
        }
    }
    return datos[indiceModa];
}


//   VARIANZA POBLACIONAL
// --------------------------

double calcularVarianzaPoblacional(const vector <double>& datos) {

    vector <double> cuadrados;
    double media = calcularMedia(datos);
    double sumaCuadrados = 0;

    for(size_t i = 0; i < datos.size(); i++) {

    cuadrados.push_back((datos[i] - media) * (datos[i] - media));;

    }
    for(size_t i = 0; i < datos.size(); i++) {

    sumaCuadrados += cuadrados[i];

    }

    return sumaCuadrados / datos.size();

}

//   VARIANZA MUESTRAL
// --------------------------
double calcularVarianzaMuestral(const vector <double>& datos) {

    vector <double> cuadrados;

    double media = calcularMedia(datos);

    double sumaCuadrados = 0;

    for(size_t i = 0; i < datos.size(); i++) {

    cuadrados.push_back((datos[i] - media) * (datos[i] - media));;

    }
    for(size_t i = 0; i < datos.size(); i++) {

    sumaCuadrados += cuadrados[i];

    }

    return sumaCuadrados / (datos.size() -  1);

}


// DESVIO POBLACIONAL
// --------------------------
double calcularDesvioPoblacional(const vector<double>& datos) {

        double varianza = calcularVarianzaPoblacional(datos);

return sqrt(varianza);
}

// DESVIO MUESTRAL
// --------------------------

double calcularDesvioMuestral(const vector<double>& datos) {

double varianza = calcularVarianzaMuestral (datos);

return sqrt(varianza);
}

// COEFICIENTE DE VARIACION PONBLACIONAL
// -------------------------------------

double CVpoblacional (const vector <double>& datos) {

double CV = calcularDesvioPoblacional(datos) / calcularMedia(datos);

return CV * 100;

}

// COEFICIENTE DE VARIACION MUESTRAL
// ---------------------------------

double CVmuestral (const vector <double>& datos) {

double CV = calcularDesvioMuestral(datos) / calcularMedia(datos);

return CV * 100;

}

//        MOSTRAR RESULTADOS
// ----------------------------------

void mostrarResultados(const MedidasDeDispersion& sDispersion, const MedidasDeTendencia& sTendencia, const DatosAgrupados& sDatos) {

    cout << "--------------------------------DATOS ORDENADOS-----------------------------------\n\n";

    for (size_t i = 0; i < sDatos.datos.size(); i++) {

    cout << "- " << sDatos.datos[i] << " ";

}

    cout << "\n\n";
    cout << "---------------------------TABLA DE FRECUENCIAS------------------------------------\n\n";

        cout << " x | fi | fa | fr | fr% | fra\n\n";

        cout << " " << sDatos.marcasDeClase [0] << " | " << sDatos.frecuencias[0] << " | "  << sDatos.frecuenciaAcumulada[0] << " | ";
        cout << sDatos.frecuenciaRelativa[0] << " | " << sDatos.frecuenciaRP[0] << "%" << " | " << sDatos.frecuenciaRA[0] << "\n";

        for(size_t i = 1; i < sDatos.marcasDeClase.size(); i++) {

        cout << " " << sDatos.marcasDeClase [i] << " | " << sDatos.frecuencias[i] << " | "  << sDatos.frecuenciaAcumulada[i] << " | ";
        cout << sDatos.frecuenciaRelativa[i] << " | " << sDatos.frecuenciaRP[i]<< "%" << " | " << sDatos.frecuenciaRA[i] << "\n";

    }

    cout << "\n";

    cout << "---------------------------DIAGRAMA DE BARRAS------------------------------------\n\n";

        for (size_t i = 0; i < sDatos.frecuencias.size(); i++) {

        cout << sDatos.marcasDeClase[i] << " ";

        for (int j = 0; j < sDatos.frecuencias[i]; j++) {
            cout << ">";
        }

        cout << " (" << sDatos.frecuencias[i] << ")\n";

}


    cout << "\n\n";

    cout << "-------------------------MEDIDAS DE TENDENCIA------------------------------------\n";

    cout << "Media: " << sTendencia.media << "\n";
    cout << "Mediana: " << sTendencia.mediana << "\n";
    cout << "Moda: " << sTendencia.moda << "\n";

    cout << "-------------------------MEDIDAS DE DISPERSION-----------------------------------\n";

    cout << "Rango: " << sDispersion.rango << "\n";
    cout << "Varianza Poblacional: " << sDispersion.varianzaP << "\n";
    cout << "Varianza Muestral: " << sDispersion.varianzaM << "\n";
    cout << "Desvío Poblacional: " << sDispersion.desvioP << "\n";
    cout << "Desvío Muestral: " << sDispersion.desvioM << "\n";
    cout << "CV poblacional: " << sDispersion.cvP << "% : " << sDispersion.interpretacionCVp << "\n";
    cout << "CV muestral: " << sDispersion.cvM << "% : " << sDispersion.interpretacionCVm << "\n";

    cout << "-----------------------------------------------------------------------------------\n";
}

void cargarDatos(DatosAgrupados& sDatos) {

    // 1. Ingresar datos
        int cantidad = totalDatos();
        sDatos.datos = ingresarDatos(cantidad);

    // 2. Pedir decimales
        int dec = pedirDecimales();
        aplicarDecimales(dec);

}

void construirTablaDatosIndividuales(DatosAgrupados& sDatos) {

    // Llenamos directamente los vectores dentro del struct
    tablaDeFrecuencias(
        sDatos.datos,
        sDatos.marcasDeClase,             // se llena dentro de la función
        sDatos.frecuencias,
        sDatos.frecuenciaAcumulada,
        sDatos.frecuenciaRelativa,
        sDatos.frecuenciaRP,
        sDatos.frecuenciaRA
    );

};

void asignarMedidasDeTendencia(MedidasDeTendencia& sTendencia,const DatosAgrupados& sDatos) {

    sTendencia.media = calcularMedia(sDatos.datos);
    sTendencia.mediana = calcularMediana(sDatos.datos);
    sTendencia.moda = calcularModa(sDatos.datos, sDatos.frecuencias);

};

void asignarMedidasDeDispersion(MedidasDeDispersion& sDispersion, const DatosAgrupados& sDatos) {


    sDispersion.rango = calcularRango(sDatos.datos);
    sDispersion.varianzaP = calcularVarianzaPoblacional(sDatos.datos);
    sDispersion.varianzaM = calcularVarianzaMuestral(sDatos.datos);
    sDispersion.desvioP = calcularDesvioPoblacional(sDatos.datos);
    sDispersion.desvioM = calcularDesvioMuestral(sDatos.datos);
    sDispersion.cvP = CVpoblacional(sDatos.datos);
    sDispersion.cvM = CVmuestral(sDatos.datos);

    sDispersion.interpretacionCVp = interpretacionCV(sDispersion.cvP);
    sDispersion.interpretacionCVm = interpretacionCV(sDispersion.cvM);

}

void ejecutarDatosIndividuales() {

    DatosAgrupados sDatos;
    MedidasDeTendencia sTendencia;
    MedidasDeDispersion sDispersion;

    cargarDatos(sDatos);
    construirTablaDatosIndividuales(sDatos);
    asignarMedidasDeTendencia(sTendencia, sDatos);
    asignarMedidasDeDispersion(sDispersion, sDatos);
    mostrarResultados(sDispersion, sTendencia, sDatos);
}
