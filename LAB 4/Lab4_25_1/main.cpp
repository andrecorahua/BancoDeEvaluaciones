#include <iostream>         //Para usar (cout, cin)
#include <fstream>          //Para usar(ifstream, ofstream)
#include <iomanip>          //Para usar setw,setfill y setprecision
#include "Bibliotecas/Funciones.h"
using namespace std;

int main() {
    ifstream archNumeros("ArchivoDeDatos/NumerosASumar.txt", ios::in);
    if(not archNumeros.is_open()){
        cout<<"El archivo NumerosASumar.txt no se pudo abrir"<<endl;
        exit(1);
    }
    ofstream reporte("ArchivoDeReporte/Reporte.txt", ios::out);
    if(not reporte.is_open()){
        cout<<"El archivo Reporte.txt no se pudo abrir"<<endl;
        exit(1);
    }
    calcularSuma(reporte, archNumeros);
    return 0;
}

