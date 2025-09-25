#include <iostream>    //Para usar (cin, cout)
#include <iomanip>     //Para usar(setfill, setw, setprecision)
#include <fstream>     // Para usar(ifstream, ofstream)
using namespace std;
#define CANT_MAX_LINEA 120
#include "Funciones.h"

void leerPlatos(int *arrCodPlato, double *arrPrecioPlato, int &cantPlatos) {
    int codPlato;      //código del plato
    double precio;

    ifstream archPlatos("ArchivoDeDatos/PlatosOfrecidos.txt", ios::in);

    if (not archPlatos.is_open()) {
        cout << "ERROR, No se ha podido abrir el archivo PlatosOfrecidos.txt" << endl;
        exit(1);
    }

    cantPlatos = 0;

    while (true) {
        archPlatos >> codPlato;
        if (archPlatos.eof()) break;

        archPlatos >> ws;  // Consume espacios en blanco
        while (archPlatos.get() != ' ');
        archPlatos >> precio;
        while (archPlatos.get() != '\n');

        // Almacena los datos en los arreglos
        arrCodPlato[cantPlatos] = codPlato;
        arrPrecioPlato[cantPlatos] = precio;
        cantPlatos++;  // Incrementa el contador de platos
    }
}

// Función principal que elabora el reporte completo
void elaborarReporte(int *arrCodPlato, double *arrPrecioPlato, int cantPlatos) {
    // Abre el archivo de repartidores en modo lectura
    ifstream archRepartidores("ArchivoDeDatos/Repartidores.txt", ios::in);
    if (not archRepartidores.is_open()) {
        cout << "ERROR, No se ha podido abrir el archivo Repartidores.txt" << endl;
        exit(1);
    }

    ifstream archRepartos("ArchivoDeDatos/RepartosARealizar.txt", ios::in);
    if (not archRepartos.is_open()) {
        cout << "ERROR, No se ha podido abrir el archivo RepartosARealizar.txt" << endl;
        exit(1);
    }

    ofstream archReporte("ArchivoDeReporte/Reporte.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "ERROR, No se ha podido abrir el archivo Reporte.txt" << endl;
        exit(1);
    }

    int cantRepartidores = 0, distrito, dni;
    char tipoVehiculo;
    double totalRecaudado, totalPagar, totalRecaudadoRepartidor, totalPagarRepartidor;

    elaborarEncabezadoReporte(archReporte);

    totalRecaudado = 0;
    totalPagar = 0;

    archReporte.precision(2);//dos decimales
    archReporte << fixed;  // Formato de punto fijo para decimales

    // Bucle para procesar cada repartidor
    while (true) {
        archRepartidores >> dni;
        if (archRepartidores.eof()) break;

        cantRepartidores++;  // Incrementa el contador de repartidores

        // Elabora el encabezado para este repartidor
        elaborarEncabezadoRepartidor(cantRepartidores, dni, archRepartidores, archReporte, distrito, tipoVehiculo);

        // Procesa los clientes que debe atender este repartidor
        elaborarRelacionClientesAtender(distrito, tipoVehiculo, archRepartos, arrCodPlato, arrPrecioPlato,
                                        cantPlatos, archReporte, totalRecaudadoRepartidor, totalPagarRepartidor);

        // Acumula los totales generales
        totalRecaudado = totalRecaudado + totalRecaudadoRepartidor;
        totalPagar = totalPagar + totalPagarRepartidor;
    }

    // Elabora el resumen final del reporte
    elaborarResumenReporte(totalRecaudado, totalPagar, archReporte);
}

// Función que crea el encabezado de información de cada repartidor
void elaborarEncabezadoRepartidor(int cantRepartidores, int dni, ifstream &archRepartidores, ofstream &archReporte,
                                  int &distrito, char &tipoVehiculo) {

    escribirLinea('=', CANT_MAX_LINEA, archReporte);

    // Imprime el número de repartidor con formato (rellenado con ceros)
    archReporte << setfill('0') << setw(2) << cantRepartidores << setfill(' ') << " REPARTIDOR:" << endl;

    // Imprime los encabezados de las columnas
    archReporte << setw(10) << "NOMBRE" << setw(40) << "DNI" << setw(20) << "VEHICULO" << setw(30) <<
            "DISTRITO A ATENDER" << endl;

    archReporte << setw(3) << ' ';  // Espaciado inicial

    // Lee y escribe el nombre del repartidor (hasta encontrar un espacio)
    leeryEscribir(archRepartidores, archReporte, ' ', 40, true);

    archReporte << dni << setw(4) << ' ';  // Imprime el DNI con espaciado

    archRepartidores >> ws;  // Consume espacios en blanco
    archRepartidores >> tipoVehiculo;  // Lee el tipo de vehículo
    archReporte << tipoVehiculo;  // Imprime el tipo de vehículo

    // Lee y escribe información adicional del vehículo
    leeryEscribir(archRepartidores, archReporte, ' ', 20, true);

    archRepartidores >> distrito;

    // Lee y escribe el resto de la línea hasta el final
    leeryEscribir(archRepartidores, archReporte, '\n', 0, false);

    archReporte << endl;
    escribirLinea('-', CANT_MAX_LINEA, archReporte);
    archReporte << setw(3) << ' ' << "CLIENTES A ATENDER" << endl;
}

// Función auxiliar para leer de un archivo y escribir en otro con formato
void leeryEscribir(ifstream &archLectura, ofstream &archImpresion, char carLimitador, int espacio,
                   bool imprimeMayuscula) {
    char c;    // Variable para leer carácter por carácter
    int cant;  // Contador de caracteres leídos

    archLectura >> c;  // Lee el primer carácter (omite espacios iniciales)
    cant = 0;

    // Bucle para leer hasta encontrar el carácter limitador
    while (true) {
        // Si el carácter no es '/' ni '-', lo procesa normalmente
        if (c != '/' and c != '-') {
            // Convierte a mayúscula si se solicita
            if (imprimeMayuscula) {
                if (c >= 'a' and c <= 'z') {
                    c = c - 'a' + 'A';  // Conversión a mayúscula
                }
            }
            archImpresion.put(c);  // Escribe el carácter
        } else {
            archImpresion.put(' ');  // Reemplaza '/' y '-' con espacios
        }

        cant++;  // Incrementa el contador
        c = archLectura.get();  // Lee el siguiente carácter
        if (c == carLimitador) break;  // Si encuentra el limitador, termina
    }

    // Rellena con espacios hasta completar el ancho especificado
    for (int i = 0; i < espacio - cant; i++) {
        archImpresion.put(' ');
    }
}

// Función que crea el encabezado principal del reporte
void elaborarEncabezadoReporte(ofstream &archReporte) {
    // Imprime el título centrado de la empresa
    archReporte << setw(70) << "EMPRESA DE REPARTOS A DOMICILIO TP S.A." << endl;
    // Imprime el subtítulo centrado
    archReporte << setw(73) << "ENTREGAS QUE DEBEN REALIZAR LOS REPARTIDORES" << endl;
}

void escribirLinea(char c, int cant, ofstream &arch) {
    // Bucle que imprime el carácter 'c' 'cant' veces
    for (int i = 0; i < cant; i++) {
        arch.put(c);
    }
    arch << endl;  // Termina con un salto de línea
}

// Función que procesa los clientes que debe atender un repartidor específico
void elaborarRelacionClientesAtender(int distrito, char tipoVehiculo, ifstream &archRepartos, int *arrCodPlato,
                                     double *arrPrecioPlato, int cantPlatos, ofstream &archReporte,
                                     double &totalRecaudadoRepartidor, double &totalPagarRepartidor) {

    int codDistrito, nroCliente;  // Variables para distrito y número de cliente
    char vehiculo;                // Tipo de vehículo leído del archivo
    double totalPagar, totalRepartidor, totalRecaudado;

    archRepartos.clear();    // Limpia los flags de error del stream
    archRepartos.seekg(0);   // Posiciona el cursor al inicio del archivo

    nroCliente = 0;  // Inicializa el contador de clientes

    // Inicializa los totales del repartidor
    totalRecaudadoRepartidor = 0;
    totalPagarRepartidor = 0;

    // Bucle para leer todos los repartos del archivo
    while (true) {
        archRepartos >> codDistrito;  // Lee el código del distrito
        if (archRepartos.eof()) break;  // Si llegó al final, termina

        archRepartos >> vehiculo;  // Lee el tipo de vehículo

        // Verifica si este reparto corresponde al repartidor actual
        if (codDistrito == distrito and vehiculo == tipoVehiculo) {
            nroCliente++;  // Incrementa el número de cliente

            // Elabora el encabezado para este cliente
            elaborarEncabezadoCliente(nroCliente, archRepartos, archReporte);

            // Procesa los pedidos de este cliente
            procesarPedidos(archRepartos, arrCodPlato, arrPrecioPlato, cantPlatos, archReporte, tipoVehiculo,
                            totalPagar, totalRepartidor);

            totalRecaudado = totalPagar + totalRepartidor;  // Calcula el total recaudado

            // Elabora el resumen para este cliente
            elaborarResumenCliente(totalPagar, totalRepartidor, totalRecaudado, archReporte);

            // Acumula los totales del repartidor
            totalRecaudadoRepartidor = totalRecaudadoRepartidor + totalRecaudado;
            totalPagarRepartidor = totalPagarRepartidor + totalRepartidor;
        } else {
            // Si no corresponde a este repartidor, descarta la línea completa
            while (archRepartos.get() != '\n');
        }
    }
}

// Función que crea el encabezado de información de cada cliente
void elaborarEncabezadoCliente(int nroCliente, ifstream &archRepartos, ofstream &archReporte) {
    // Imprime el número de cliente con formato
    archReporte << setw(3) << ' ' << setfill('0') << setw(2) << nroCliente << setfill(' ') << ' ';

    // Lee y escribe el nombre del cliente (hasta encontrar ']')
    leeryEscribir(archRepartos, archReporte, ']', 0, true);

    archReporte << endl;
    archReporte << setw(7) << ' ' << "PLATOS SOLICITADOS:" << endl;

    // Imprime los encabezados de las columnas de platos
    archReporte << setw(15) << "CODIGO" << setw(15) << "CANTIDAD" << setw(12) << "PRECIO" << setw(15) << "SUBTOTAL" <<
            endl;
}

// Función que elabora el resumen final del reporte
void elaborarResumenReporte(double totalRecaudado, double totalPagar, ofstream &archReporte) {
    escribirLinea('=', CANT_MAX_LINEA, archReporte);  // Línea separadora

    // Imprime el total recaudado alineado a la izquierda y derecha
    archReporte << left << setw(50) << "TOTAL RECAUDADO POR LOS PEDIDOS SOLICITADOS:" << right << setw(10) <<
            totalRecaudado << endl;

    // Imprime el total a pagar a repartidores
    archReporte << left << setw(50) << "TOTAL A PAGAR A LOS REPARTIDORES: " << right << setw(10) << totalPagar << endl;

    escribirLinea('=', CANT_MAX_LINEA, archReporte);  // Línea separadora final
}

// Función que procesa los pedidos de un cliente específico
void procesarPedidos(ifstream &archRepartos, int *arrCodPlato, double *arrPrecioPlato, int cantPlatos,
                     ofstream &archReporte, char tipoVehiculo, double &totalPagar, double &totalRepartidor) {

    int cantidad, codPlato, pos, nroPlato;  // Variables para procesar cada pedido
    double subtotal;  // Subtotal de cada plato

    nroPlato = 0;   // Inicializa el contador de platos
    totalPagar = 0; // Inicializa el total a pagar

    // Bucle para leer todos los pedidos del cliente
    while (true) {
        archRepartos >> cantidad >> codPlato;  // Lee cantidad y código del plato

        // Busca el plato en el arreglo de platos disponibles
        pos = buscarPlato(codPlato, arrCodPlato, cantPlatos);

        if (pos != -1) {  // Si se encontró el plato
            nroPlato++;  // Incrementa el número de plato
            subtotal = cantidad * arrPrecioPlato[pos];  // Calcula el subtotal

            // Imprime la información del plato con formato
            archReporte << setw(6) << ' ' << setfill('0') << setw(2) << nroPlato << setfill(' ') << setw(8) << codPlato
                    << setw(10) << cantidad << setw(15) << arrPrecioPlato[pos] << setw(12) << subtotal << endl;

            totalPagar = totalPagar + subtotal;  // Acumula el total
        }

        // Si encuentra un salto de línea, termina de leer pedidos de este cliente
        if (archRepartos.get() == '\n') break;
    }

    // Calcula la comisión del repartidor según el tipo de vehículo
    if (tipoVehiculo == 'M') {        // Motocicleta
        totalRepartidor = 0.1 * totalPagar;   // 10% de comisión
    } else if (tipoVehiculo == 'B') { // Bicicleta
        totalRepartidor = 0.05 * totalPagar;  // 5% de comisión
    }
}

// Función que busca un plato en el arreglo de códigos
int buscarPlato(int codPlato, int *arrCodPlato, int cantPlatos) {
    // Recorre todo el arreglo de códigos de platos
    for (int i = 0; i < cantPlatos; i++) {
        if (arrCodPlato[i] == codPlato) {  // Si encuentra el código
            return i;  // Retorna la posición donde se encontró
        }
    }

    return -1;  // Retorna -1 si no se encontró el plato
}

// Función que elabora el resumen de cada cliente
void elaborarResumenCliente(double totalPagar, double totalRepartidor, double totalRecaudado, ofstream &archReporte) {
    escribirLinea('-', CANT_MAX_LINEA, archReporte);

    // Imprime el total a pagar por el cliente
    archReporte << setw(5) << ' ' << left << setw(40) << "TOTAL PAGAR: " << right << setw(8) << totalPagar << endl;

    // Imprime la comisión del repartidor
    archReporte << setw(5) << ' ' << left << setw(40) << "PAGO AL REPARTIDOR: " << right << setw(8) << totalRepartidor
            << endl;

    escribirLinea('-', CANT_MAX_LINEA, archReporte);

    // Imprime el total recaudado (cliente + repartidor)
    archReporte << setw(5) << ' ' << left << setw(40) << "TOTAL RECAUDADO: " << right << setw(8) << totalRecaudado <<
            endl;

    escribirLinea('=', CANT_MAX_LINEA, archReporte);
}