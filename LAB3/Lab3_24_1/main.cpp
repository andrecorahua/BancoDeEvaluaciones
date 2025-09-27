
#include <iostream>    //Librería para usar cout y cin
#include <iomanip>     //Librería para usar setw, setprecision y setfill
#include <fstream>     //Librería para usar ifstream, ofstream y fstream(lectura y escritura de archivos)

using namespace std;   // Permite usar elementos de std sin prefijo (cout en lugar de std::cout)

#include "Bibliotecas/Funciones.h"

int main(int argc, char** argv) {
    // Parámetros de la función main:
    // argc: número de argumentos de línea de comandos
    // argv: array de punteros a los argumentos de línea de comandos

    // APERTURA DE ARCHIVO DE ENTRADA PARA CITAS MÉDICAS
    ifstream archCitas("ArchivoDeDatos/CitasMedicas.txt", ios::in);
    // ifstream: flujo de entrada de archivo (input file stream)
    // ios::in: modo de apertura para lectura

    // VERIFICACIÓN DE APERTURA EXITOSA DEL ARCHIVO DE CITAS
    if (not archCitas.is_open()){
        // not: operador lógico de negación (equivale a !)
        // is_open(): metodo que verifica si el archivo se abrió correctamente
        cout << "ERROR, No se ha podido abrir el archivo CitasMedicas.txt" << endl;
        exit(1);
        // Termina el programa con código de error 1 (indica fallo)
    }

    // APERTURA DE ARCHIVO DE ENTRADA PARA MÉDICOS
    ifstream archMedicos("ArchivoDeDatos/Medicos.txt", ios::in);

    // VERIFICACIÓN DE APERTURA EXITOSA DEL ARCHIVO DE MÉDICOS
    if (not archMedicos.is_open()){
        cout << "ERROR, No se ha podido abrir el archivo Medicos.txt" << endl;
        exit(1);
    }

    // APERTURA DE ARCHIVO DE SALIDA PARA EL REPORTE
    ofstream archReporte("ArchivoDeReporte/Reporte.txt", ios::out);
    // ofstream: flujo de salida de archivo (output file stream)
    // ios::out: modo de apertura para escritura

    // VERIFICACIÓN DE APERTURA EXITOSA DEL ARCHIVO DE REPORTE
    if (not archReporte.is_open()){
        cout << "ERROR, No se ha podido abrir el archivo Reporte.txt" << endl;
        exit(1);
    }

    elaborarReporte(archCitas, archMedicos, archReporte);
    // Función definida en funciones.cpp que procesa los datos
    // Recibe los tres archivos como parámetros:
    return 0;
    // Los archivos se cierran automáticamente al salir del ámbito
}