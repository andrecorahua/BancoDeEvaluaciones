
#include <fstream>          //Para usar(ifstream, ofstream)

using namespace std;

#ifndef LAB4_25_1_FUNCIONES_H    // "if not defined" - Si LAB4_25_1_FUNCIONES_H no está definido
#define LAB4_25_1_FUNCIONES_H    // Define LAB4_25_1_FUNCIONES_H para marcar que este archivo ya fue incluido

// DECLARACIONES DE FUNCIONES (Function Prototypes)
// Estas son solo las "firmas" de las funciones, no su implementación

// FUNCIÓN: imprimirLinea
// Parámetros: referencia a archivo de salida, carácter a imprimir, tamaño de la línea
// Propósito: Imprime una línea de caracteres repetidos en el archivo de reporte
void imprimirLinea(ofstream &reporte, char c, int size);

// FUNCIÓN: calcularSuma
// Parámetros: referencia a archivo de salida (reporte), referencia a archivo de entrada (números)
// Propósito: Función principal que coordina la lectura y suma de números grandes
void calcularSuma(ofstream &reporte, ifstream &archNumeros);

// FUNCIÓN: leerArreglo
// Parámetros: archivo de entrada, puntero a arreglo, referencia a contador de dígitos
// Retorna: bool (true si leyó exitosamente, false si llegó al final del archivo)
// Propósito: Lee una línea de números del archivo y los almacena en un arreglo
bool leerArreglo(ifstream &archNumeros, int *numeroGrande1, int &cantNumG1);

// FUNCIÓN: sumarArreglos
// Parámetros: archivo reporte, dos arreglos de números, arreglo resultado, contadores de dígitos
// Propósito: Suma dos números grandes representados como arreglos, simula suma manual
void sumarArreglos(ofstream &reporte, int *numeroGrande1, int *numeroGrande2, int *totalGrande,
                   int cantNumG1, int cantNumG2, int &cantTotalG);

// FUNCIÓN: igualarArreglos
// Parámetros: arreglo destino, su contador, arreglo origen, su contador
// Propósito: Copia el resultado de una suma al primer arreglo para acumulación
void igualarArreglos(int *numeroGrande1, int &cantNumG1, int *totalGrande, int &cantTotalG);

#endif //LAB4_25_1_FUNCIONES_H    // Fin de la guarda de inclusión