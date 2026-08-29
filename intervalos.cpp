#include "comun.h"
#include "funciones.h"
#include "intervalos.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

int calcularClasesSturges(int n) {
    return static_cast<int>(1 + 3.322 * log10(n));
}

double calcularAmplitud(double rango, int clases) {

    return rango / clases;
}

vector <pair<double, double>> calcularIntervalos(const vector <double>&datos, double amplitud, int clases) {

vector <pair<double, double>> intervalos;

double  limInf = datos[0];

for(size_t i = 0; i < clases; i++) {

    double actualInf = limInf + i * amplitud;
    double actualSup = limInf + (i + 1) * amplitud;

    intervalos.push_back({actualInf, actualSup});
}

return intervalos;
}

void tablaDeFrecuenciasIntervalos(const vector <double>& datos,
                             const vector <pair<double, double>>& intervalos,
                             vector <int>& frecuencias,
                             vector <int> & frecuenciaAcumulada,
                             vector<double>& frecuenciaRelativa,
                             vector<double>& frecuenciaRP,
                             vector <double>& frecuenciaRA) {

    // Recorremos cada intervalo
for (size_t i = 0; i < intervalos.size(); i++) {

    double limInf = intervalos[i].first;
    double limSup = intervalos[i].second;
    int freq = 0;

    for (double dato : datos) {

       if (i == intervalos.size() - 1) {
    if (dato >= limInf && dato <= limSup)
        freq++;
} else {
    if (dato >= limInf && dato < limSup)
        freq++;
}

    }

    frecuencias.push_back(freq);
}

int acumulada = 0;

    for (size_t i = 0; i < frecuencias.size(); i++) {

        frecuenciaAcumulada.push_back(acumulada += frecuencias[i]);
}
    for(size_t i = 0; i < frecuencias.size(); i++){

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


vector<double> calcularPuntosMedios(const vector<pair<double,double>>& intervalos) {

    vector<double> marcasDeClase;

    for (const pair<double,double>& intervalo : intervalos) {
        double limInf = intervalo.first;
        double limSup = intervalo.second;

        double puntoMedio = (limInf + limSup) / 2.0;
        marcasDeClase.push_back(puntoMedio);
    }

    return marcasDeClase;
}
//          MEDIA INTERVALOS
// -------------------------------------

double clasesPorFrecuencias(const vector <double>& valores,
                            const vector <int>& frecuencias) {

 double clasesXFrecuencias = 0;

for (size_t i = 0; i < frecuencias.size(); i++) {

    clasesXFrecuencias +=  frecuencias [i] * valores[i];

}
return clasesXFrecuencias;
}

double mediaIntervalos (const vector <int> & frecuencias,

                        double clasesXfrecuencias) {
    int fTotales = 0;

    for (size_t i = 0; i < frecuencias.size(); i++) {

       fTotales += frecuencias [i];

    }
    return clasesXfrecuencias / fTotales;

}
double calcularMediaIntervalos (const vector <pair<double, double>>& intervalos,
                                const vector <int>& frecuencias){

            vector <double> puntosMedios = calcularPuntosMedios(intervalos);

            double suma = clasesPorFrecuencias(puntosMedios, frecuencias);

            return mediaIntervalos(frecuencias, suma);
            }

//         MEDIANA INTERVALOS
// -------------------------------------

size_t encontrarIndiceMedianaIntervalos(const vector<int>& frecuenciaAcumulada) {
    double mitad = frecuenciaAcumulada.back() / 2;
    for(size_t i = 0; i < frecuenciaAcumulada.size(); i++) {
        if(mitad <= frecuenciaAcumulada[i]) return i;
    }
    return frecuenciaAcumulada.size() - 1; // fallback
}

double calcularMedianaIntervalos(const vector<pair<double, double>>& intervalos,const vector<int>& frecuencias,const vector<int>& frecuenciaAcumulada,double amplitud){
    size_t i = encontrarIndiceMedianaIntervalos(frecuenciaAcumulada);
    double ultimaP = frecuenciaAcumulada.back() / 2;

    if(i == 0) return intervalos[i].first + (ultimaP / frecuencias[i]) * amplitud;
    return intervalos[i].first + ((ultimaP - frecuenciaAcumulada[i-1]) / frecuencias[i]) * amplitud;
}

//           MODA INTERVALOS
// -------------------------------------

size_t encontrarIndiceModal(const vector<int>& frecuencias) {

    int indiceModa = 0;

    int frecuenciaMaxima = frecuencias[0];

    // Encontrar el índice del intervalo modal
    for (size_t i = 1; i < frecuencias.size(); i++) {
        if (frecuencias[i] > frecuenciaMaxima) {
            frecuenciaMaxima = frecuencias[i];
            indiceModa = i;
        }
    }
    return indiceModa;
}

pair<int, int> calcularSubidaBajada(const vector<int>& frecuencias,
                          int indiceModa) {

    int subida = 0;
    int bajada = 0;

    // Calcular subida y bajada según la posición
    if (indiceModa > 0 && indiceModa < frecuencias.size() - 1) {
        // intervalo modal en el medio
        subida = frecuencias[indiceModa] - frecuencias[indiceModa - 1];
        bajada = frecuencias[indiceModa] - frecuencias[indiceModa + 1];
    }
    else if (indiceModa == 0) {
        // primer intervalo → solo bajada
        subida = frecuencias[indiceModa];
        bajada = frecuencias[indiceModa] - frecuencias[indiceModa + 1];
    }
    else {
        // último intervalo → solo subida
        subida = frecuencias[indiceModa] - frecuencias[indiceModa - 1];
        bajada = frecuencias[indiceModa];
    }

    return {subida, bajada};
}

double calcularProporcionIntervalos(const vector<int>& frecuencias, int indiceModa) {

    auto [subida, bajada] = calcularSubidaBajada(frecuencias, indiceModa);

    if (subida + bajada == 0) return 0; // evitar división por cero

    return subida / static_cast<double>(subida + bajada);

}

double calcularModaIntervalos (const vector <pair<double, double>>& intervalos,
                               const vector<int>& frecuencias,
                               double amplitud) {

    int indiceModa = encontrarIndiceModal(frecuencias);

    double proporcion = calcularProporcionIntervalos(frecuencias, indiceModa);

    return intervalos[indiceModa].first + proporcion * amplitud;

}

//     RANGO (MEDIDA DE DISPERSION)
// -------------------------------------

double rangoDispersion(const vector<pair<double, double>>& intervalos) {

    if(intervalos.empty()) return 0.0; // chequeo de seguridad

    return intervalos.back().second - intervalos[0].first;
}


double calcularVarianzaPoblacionalIntervalos(const vector<double>& valores,
                                             const vector<int>& frecuencias,
                                             double media,
                                             const vector<int>& frecuenciaAcumulada) {

    double varianzaP = 0;

    double suma = 0;

    for (size_t i = 0; i < valores.size(); i++) {
        suma += pow(valores[i] - media, 2) * frecuencias[i];
    }

    return varianzaP = suma / frecuenciaAcumulada.back();

}

double calcularVarianzaMuestralIntervalos(const vector<double>& valores,
                                             const vector<int>& frecuencias,
                                             double media,
                                             const vector<int>& frecuenciaAcumulada) {

    double varianzaM = 0;

    double suma = 0;

    for (size_t i = 0; i < valores.size(); i++) {
        suma += pow(valores[i] - media, 2) * frecuencias[i];
    }

    return varianzaM = suma / (frecuenciaAcumulada.back() - 1);

}

double calcularDesvioPoblacionalIntervalos(double varianzaP) {

    return sqrt(varianzaP);

}

double calcularDesvioMuestralIntervalos(double varianzaM) {

    return sqrt(varianzaM);

}

// COEFICIENTE DE VARIACION PONBLACIONAL
// -------------------------------------

double CVpoblacionalIntervalos(double desvioP, double media) {

double CV = desvioP / media;

return CV * 100;

}

// COEFICIENTE DE VARIACION MUESTRAL
// ---------------------------------

double CVmuestralIntervalos(double desvioM, double media) {

double CV = desvioM / media;

return CV * 100;

}

void mostrarResultadosIntervalos(const calculoIntervalosStruct& sIntervalos, const MedidasDeDispersion& sDispersion, const MedidasDeTendencia& sTendencia, const DatosAgrupados& sDatos) {

    cout << "-------------------------RANGO, CLASES, AMPLITUD----------------------------------\n";

    cout << "Rango (datos): " << sIntervalos.rangoDatos << "\n";

    cout << "Clases: " << sIntervalos.clases << "\n";

    cout << "Amplitud (Sturges): " << sIntervalos.amplitud << "\n";

    cout << "\n";
    cout << "-------------------------------INTERVALOS-----------------------------------------\n";

    cout << "\n";

    for(size_t i = 0; i < sDatos.intervalos.size(); i++) {

    cout << "[" << sDatos.intervalos[i].first << ", " << sDatos.intervalos[i].second << "]\n";

}
    cout << "\n";


    cout << "---------------------------TABLA DE FRECUENCIAS------------------------------------\n\n";

        cout << " marcas de clase | fi | fa | fr | fr% | fra\n\n";

        cout << sDatos.marcasDeClase[0] << " | " << sDatos.frecuencias[0] << " | "  << sDatos.frecuenciaAcumulada[0] << " | ";
        cout << sDatos.frecuenciaRelativa[0] << " | " << sDatos.frecuenciaRP[0] << "%" << " | " << sDatos.frecuenciaRA[0] << "\n";

        for(size_t i = 1; i < sDatos.frecuencias.size(); i++) {

        cout << sDatos.marcasDeClase[i] << " | " << sDatos.frecuencias[i] << " | "  << sDatos.frecuenciaAcumulada[i] << " | ";
        cout << sDatos.frecuenciaRelativa[i] << " | " << sDatos.frecuenciaRP[i]<< "%" << " | " << sDatos.frecuenciaRA[i] << "\n\n";
        }

    cout << "------------------------------HISTOGRAMA---------------------------------------\n\n";

        for (size_t i = 0; i < sIntervalos.clases; i++) {

    cout << "[" << sDatos.intervalos[i].first << ", " << sDatos.intervalos[i].second << "] ";

        for (int j = 0; j < sDatos.frecuencias[i]; j++) {
            cout << ">";
        }

        cout << " (" << sDatos.frecuencias[i] << ")\n";

}

cout << "\n\n";

    cout << "-------------------------MEDIDAS DE TENDENCIA------------------------------------\n";

    cout << "Media: "<< sTendencia.media << "\n";
    cout << "Mediana: " << sTendencia.mediana << "\n";
    cout << "Moda: " << sTendencia.moda << "\n";

    cout << "-------------------------MEDIDAS DE DISPERSION-----------------------------------\n";

    cout << "Rango: " << sDispersion.rango << "\n";
    cout << "Varianza Poblacional: "<< sDispersion.varianzaP << "\n";
    cout << "Varianza Muestral: " << sDispersion.varianzaM << "\n";
    cout << "Desvío Poblacional: " << sDispersion.desvioP << "\n";
    cout << "Desvío Muestral: " << sDispersion.desvioM << "\n";
    cout << "CV poblacional: " << sDispersion.cvP << "% : " << sDispersion.interpretacionCVp << "\n";
    cout << "CV muestral: " << sDispersion.cvM << "% : " << sDispersion.interpretacionCVm << "\n";

    cout << "-----------------------------------------------------------------------------------\n";
}


void calcularRangoClasesAmplitud(calculoIntervalosStruct& sIntervalos,  const DatosAgrupados& sDatos) {

    // 3. Calcular rango, clases y amplitud
        sIntervalos.rangoDatos = calcularRango(sDatos.datos);
        sIntervalos.clases = calcularClasesSturges(sDatos.datos.size());
        sIntervalos.amplitud = calcularAmplitud(sIntervalos.rangoDatos, sIntervalos.clases);

}

void calcularParametrosIntervalos(calculoIntervalosStruct& sIntervalos, DatosAgrupados& sDatos) {

    // 4. Calcular intervalos
        sDatos.intervalos = calcularIntervalos(sDatos.datos, sIntervalos.amplitud, sIntervalos.clases);

    // 5. Calcular marcas de clase
        sDatos.marcasDeClase = calcularPuntosMedios(sDatos.intervalos);

}

void construirTablaIntervalos(DatosAgrupados& sDatos, const calculoIntervalosStruct& sIntervalos) {

    // 6. Tabla de frecuencias
        tablaDeFrecuenciasIntervalos(
        sDatos.datos,
        sDatos.intervalos,
        sDatos.frecuencias,
        sDatos.frecuenciaAcumulada,
        sDatos.frecuenciaRelativa,
        sDatos.frecuenciaRP,
        sDatos.frecuenciaRA);

}

void asignarMedidasDeTendenciaIntervalos(MedidasDeTendencia& sTendencia, const DatosAgrupados& sDatos, const calculoIntervalosStruct& sIntervalos) {
    // 7. Medidas estadísticas
        sTendencia.media = calcularMediaIntervalos(sDatos.intervalos, sDatos.frecuencias);
        sTendencia.mediana = calcularMedianaIntervalos(sDatos.intervalos, sDatos.frecuencias, sDatos.frecuenciaAcumulada, sIntervalos.amplitud);
        sTendencia.moda = calcularModaIntervalos(sDatos.intervalos, sDatos.frecuencias, sIntervalos.amplitud);

}

void asignarMedidasDeDispersionIntervalos(MedidasDeDispersion& sDispersion, const DatosAgrupados& sDatos, const MedidasDeTendencia& sTendencia) {

        sDispersion.rango = rangoDispersion(sDatos.intervalos);
        sDispersion.varianzaP = calcularVarianzaPoblacionalIntervalos(sDatos.marcasDeClase, sDatos.frecuencias, sTendencia.media, sDatos.frecuenciaAcumulada);
        sDispersion.varianzaM = calcularVarianzaMuestralIntervalos(sDatos.marcasDeClase, sDatos.frecuencias, sTendencia.media, sDatos.frecuenciaAcumulada);
        sDispersion.desvioP = calcularDesvioPoblacionalIntervalos(sDispersion.varianzaP);
        sDispersion.desvioM = calcularDesvioMuestralIntervalos(sDispersion.varianzaM);
        sDispersion.cvP = CVpoblacionalIntervalos(sDispersion.desvioP, sTendencia.media);
        sDispersion.cvM = CVmuestralIntervalos(sDispersion.desvioM, sTendencia.media);

        sDispersion.interpretacionCVp = interpretacionCV(sDispersion.cvP);
        sDispersion.interpretacionCVm = interpretacionCV(sDispersion.cvM);

}

void ejecutarIntervalos() {

    DatosAgrupados sDatos;
    calculoIntervalosStruct sIntervalos;
    MedidasDeTendencia sTendencia;
    MedidasDeDispersion sDispersion;

    cargarDatos(sDatos);
    calcularRangoClasesAmplitud(sIntervalos, sDatos);  // si la tenés separada
    calcularParametrosIntervalos(sIntervalos, sDatos);
    construirTablaIntervalos(sDatos, sIntervalos);
    asignarMedidasDeTendenciaIntervalos(sTendencia, sDatos, sIntervalos);
    asignarMedidasDeDispersionIntervalos(sDispersion, sDatos, sTendencia);
    mostrarResultadosIntervalos(sIntervalos, sDispersion, sTendencia, sDatos);
}




