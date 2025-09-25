#include <iostream>//para usar cin y cout
#include <iomanip>//para usar setfill, setw y setprecision
#include <fstream>//para usar ifstream, ofstream
using namespace std;
#define MAX_CANT_PLATOS 150
#include "Bibliotecas/Funciones.h"

int main() {
    int arrCodPlato[MAX_CANT_PLATOS];
    double arrPrecioPlato[MAX_CANT_PLATOS];

    int cantPlatos;

    leerPlatos(arrCodPlato, arrPrecioPlato, cantPlatos);
    elaborarReporte(arrCodPlato, arrPrecioPlato, cantPlatos);


    return 0;
}
