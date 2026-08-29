#include "comun.h"
#include <algorithm>
#include <vector>

using namespace std;
//         TOTAL DATOS
// --------------------------

int leerEntero() {
    int n;
    cin >> n;
    return n;
}

bool esValido(int n, int min, int max) {
    return n >= min && n <= max;
}

int totalDatos() {

    int n;

    cout << "----------------------------------------------------------------------------------\n";

    while (true) {

        cout << "Ingrese la cantidad de datos (2 - 20): ";

        if (!(cin >> n)) {
            cout << "Error: solo se permiten numeros enteros.\n";

            cin.clear(); // limpia el estado de error
            cin.ignore(10000, '\n'); // descarta lo que quedo en el buffer
            continue;
        }

        if (n < 2 || n > 20) {
            cout << "Error: el numero debe estar entre 2 y 20.\n";
            continue;
        }

        break;
    }

    cout << "----------------------------------------------------------------------------------\n";

    return n;
}


//      INGRESAR DATOS
// --------------------------

double leerDato(int i) {

    double valor;

    cout << "Dato " << i + 1 << ": ";

    cin >> valor;

    return valor;
}

vector<double> ingresarDatos(int cantidad) {
    vector<double> datos(cantidad);

    for (size_t i = 0; i < cantidad; i++) {
        double valor;

        do {
            cout << "Dato " << i + 1 << ": ";
            cin >> valor;

            if (!cin) {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "Error: solo ingresar números.\n";

            } else if (valor < 1) {

                cout << "Error: el número no puede ser negativo ni cero.\n";
            }
        } while (!cin || valor < 1);

        datos[i] = valor;
    }

    sort(datos.begin(), datos.end());
    return datos;
}

// MOSTRAR DECIMALES
// --------------------------
int pedirDecimales() {

    int dec;

    cout << "----------------------------------------------------------------------------------\n";

    do {
        cout << "Ingrese la cantidad de decimales a mostrar: ";
        cin >> dec;

        if (!cin) {

            cout << "El numero ingresado debe ser un entero.\n";

            cin.clear();               // limpia el estado de error
            cin.ignore(10000, '\n');   // limpia el buffer
        }

        else if (dec < 0 || dec > 6) {

            cout << "Opción no válida (" << dec << ").\n";
        }

        cout << "----------------------------------------------------------------------------------\n";

    } while (!cin || dec < 0 || dec > 6);

    return dec;
}

void aplicarDecimales(int decimales) {
    cout << fixed << setprecision(decimales);
}


//          RANGO
// --------------------------

double calcularRango(const vector<double>& datos) {

    double minimo = *min_element(datos.begin(), datos.end());

    double maximo = *max_element(datos.begin(), datos.end());
    return maximo - minimo;
}

//
// ----------------------------------

string interpretacionCV (double CV) {

if (CV < 10) return "Muy representativo (menor al 10% - baja variabilidad)";
else if (CV < 20) return "Representativo aceptable (menor al 20% - variabilidad moderada)";
else if (CV < 30) return "Media poco representativa (menor al 30% - alta variabilidad)";
else return "No representativo (variabilidad muy alta)";

}
