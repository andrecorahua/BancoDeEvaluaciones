#include <fstream>   //Para usar(ifstream, ofstream)
using namespace std;

// LAB4_24_2_FUNCIONES_H es un "macro guard"
#ifndef LAB4_24_2_FUNCIONES_H
#define LAB4_24_2_FUNCIONES_H

// ---------------- PROTOTIPOS DE FUNCIONES ----------------

// Lee los platos desde un archivo y los guarda en arrays
// arrCodPlato -> Arreglo de códigos de platos
// arrPrecioPlato -> Arreglo de precios de platos
// cantPlatos -> Variable donde se guarda cuántos platos fueron leídos
void leerPlatos(int *arrCodPlato, double *arrPrecioPlato, int &cantPlatos);

// Genera el reporte completo utilizando los arreglos de platos previamente cargados
void elaborarReporte(int *arrCodPlato, double *arrPrecioPlato, int cantPlatos);

// Elabora el encabezado para un repartidor en el reporte
// cantRepartidores -> Número de repartidor (contador)
// dni -> del repartidor
// archRepartidores -> Archivo desde donde se leen los datos
// archReporte -> Archivo de salida donde se escribe el reporte
// distrito -> Se devuelve aquí el distrito asignado al repartidor
// tipoVehiculo -> Se devuelve aquí el tipo de vehículo que utiliza el repartidor (ej. 'M' = moto, 'B' = bici)
void elaborarEncabezadoRepartidor(int cantRepartidores, int dni, ifstream &archRepartidores, ofstream &archReporte,
                                  int &distrito, char &tipoVehiculo);

// Función auxiliar para leer texto de un archivo hasta cierto carácter limitador y escribirlo en otro archivo
// archLectura -> archivo de entrada
// archImpresion -> archivo de salida
// carLimitador -> carácter hasta el cual se leerá (ej: espacio, salto de línea, etc.)
// espacio -> ancho de columna a completar con espacios al final
// imprimeMayuscula -> si es true convierte las letras minúsculas en mayúsculas
void leeryEscribir(ifstream &archLectura, ofstream &archImpresion, char carLimitador, int espacio,
                   bool imprimeMayuscula);

// Elabora el encabezado del reporte general (nombre empresa, título, etc.)
void elaborarEncabezadoReporte(ofstream &archReporte);

// Escribe una línea de caracteres repetidos (ej: ==== o ----)
void escribirLinea(char c, int cant, ofstream &arch);

// Elabora la lista de clientes que debe atender un repartidor en específico
// distrito y tipoVehiculo determinan los repartos filtrados para el repartidor actual
// totalRecaudadoRepartidor -> dinero total recaudado por ese repartidor
// totalPagarRepartidor -> dinero que se debe pagar a ese repartidor como comisión
void elaborarRelacionClientesAtender(int distrito, char tipoVehiculo, ifstream &archRepartos, int *arrCodPlato,
                                     double *arrPrecioPlato, int cantPlatos, ofstream &archReporte,
                                     double &totalRecaudadoRepartidor, double &totalPagarRepartidor);

// Elabora el encabezado de un cliente específico en el reporte
// nroCliente -> número correlativo del cliente que atiende este repartidor
void elaborarEncabezadoCliente(int nroCliente, ifstream &archRepartos, ofstream &archReporte);

// Elabora el resumen final del reporte (totales generales)
void elaborarResumenReporte(double totalRecaudado, double totalPagar, ofstream &archReporte);

// Procesa los pedidos de un cliente (lee cantidad y código plato, calcula precios, subtotales, etc.)
// totalPagar -> monto que paga el cliente por sus platos
// totalRepartidor -> monto de comisión que gana el repartidor por ese cliente (depende del vehículo)
void procesarPedidos(ifstream &archRepartos, int *arrCodPlato, double *arrPrecioPlato, int cantPlatos,
                     ofstream &archReporte, char tipoVehiculo, double &totalPagar, double &totalRepartidor);

// Busca un código de plato en el arreglo de platos
// Retorna la posición donde se encuentra, o -1 si no está
int buscarPlato(int codPlato, int *arrCodPlato, int cantPlatos);

// Elabora el resumen de un cliente (total a pagar, pago al repartidor, total recaudado)
// Se escribe en el archivo de reporte
void elaborarResumenCliente(double totalPagar, double totalRepartidor, double totalRecaudado, ofstream &archReporte);

// Fin de la protección contra inclusiones múltiples
#endif //LAB4_24_2_FUNCIONES_H