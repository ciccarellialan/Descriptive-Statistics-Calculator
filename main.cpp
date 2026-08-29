#include <string>
#include <iostream>
#include <iomanip>

#include "funciones.h"
#include "intervalos.h"

using namespace std;

int main() {

    int opcion = 0;


    do {
        cout << "-------------------------CALCULADORA: ESTADISTICA DESCRIPTIVA---------------------\n\n";


        cout << "1 - Datos individuales\n\n";

        cout << "2 - Calculo de intervalos\n\n";


        cout << "----------------------------------------------------------------------------------\n\n";

        cout << "3 - Salir\n";

        cout << "----------------------------------------------------------------------------------\n\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << "\n";

        switch (opcion) {

case 1: {

    ejecutarDatosIndividuales();

    break;
}

case 2: {

        ejecutarIntervalos();

    break;
}

        case 3:

            cout << "Saliendo...";

            break;

        default:

            cout << "----------------------------------------------------------------------------------\n\n";

            cout << "Opcion no valida (" << opcion << ").\n\n";
        }

    } while (opcion != 3);

    return 0;
}
