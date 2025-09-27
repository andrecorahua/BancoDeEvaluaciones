#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/Funciones.h"

int main() {
    int dniMay,dniMen;
    double pagMay=-1,pagMen=10000;

    ifstream archEmp ("ArchivosDeDatos/EmpresasRegistradas_Lab03.txt", ios::in);
    if (not archEmp.is_open()) {
        cout << "Error al abrir el archivo: ArchivosDeDatos/EmpresasRegistradas_Lab03.txt" << endl;
        exit(1);
    }
    ifstream archTab ("ArchivosDeDatos/TablaDeInfracciones_Lab03.txt", ios::in);
    if (not archTab.is_open()) {
        cout << "Error al abrir el archivo: ArchivosDeDatos/TablaDeInfracciones_Lab03.txt" << endl;
        exit(1);
    }
    ifstream archInf ("ArchivosDeDatos/InfraccionesCometidas_Lab03.txt", ios::in);
    if (not archInf.is_open()) {
        cout << "Error al abrir el archivo: ArchivosDeDatos/InfraccionesCometidas_Lab03.txt" << endl;
        exit(1);
    }
    ofstream archRep("ArchivosDeReporte/Reporte.txt", ios::out);
    if (not archRep.is_open()) {
        cout << "Error al abrir el archivo: ArchivosDeReporte/Reporte.txt" << endl;
        exit(1);
    }

    ImprimirMultas(archEmp,archInf,archTab,archRep,dniMay,dniMen,pagMay,pagMen);
    ImprimirResumen(archRep,dniMay,dniMen,pagMay,pagMen);

    return 0;
}