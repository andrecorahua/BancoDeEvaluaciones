#include <iostream>//para usar cin y cout
#include <iomanip>//para usar setw,setfill,setprecision
#include <fstream>//ifstream , ofstream
#include "Bibliotecas/Funciones.h"

using namespace std;
int main() {
    ifstream archTwitch("ArchivoDeDatos/twitchdataTP.txt",ios::in);
    if(not archTwitch.is_open()) {
        cout << "Error al abrir el archivo twitchdataTP.txt" << endl;
    }
    ofstream archReporte ("ArchivoDeReporte/Reporte.txt",ios::out);
    if(not archReporte.is_open()) {
        cout << "Error al abrir el Reporte.txt" << endl;
    }
    elaborarReporte (archTwitch,archReporte);
    return 0;
}