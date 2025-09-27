#include <iostream> //Librería para usar cout y cin
#include <iomanip> //Librería para usar setw, setprecision y setfill
#include <fstream> //Librería para usar ifstream, ofstream y fstream(lectura y escritura de archivos)

using namespace std;
#include "Funciones.h"
#define CANT_MAX_LINEA 140  // Constante que define el ancho máximo de línea para el reporte

void elaborarReporte(ifstream &archCitas, ifstream &archMedicos, ofstream &archReporte) {
    int dia, mes, anho, // Fecha de la cita
            horaIni, minIni, segIni, // Hora de inicio (horas, minutos, segundos)
            horaFin, minFin, segFin, // Hora de fin
            codMedico, // Código del médico
            dni, // DNI del paciente
            horaDura, minDura, segDura, // Duración calculada de la cita
            dniMax; // DNI del paciente con mayor gasto

    double porcentaje, // Porcentaje de descuento por seguro
            montoMedicina, // Costo de medicinas
            tarifaMedico, // Tarifa por hora del médico
            duracionHoras, // Duración en horas (decimal)
            pago, // Pago total de cada cita
            totalIngresos = 0, // Suma total de todos los ingresos
            max = 0; // Mayor pago registrado

    char c, // Variable auxiliar para leer caracteres separadores
            tieneMedicina; // Indica si la cita incluye medicinas ('S' o 'N')

    elaborarEncabezadoReporte(archReporte);

    archReporte.precision(2); // Mostrar 2 decimales
    archReporte << fixed; // Formato fijo (no notación científica)

    while (true) {
        archCitas >> dia;
        if (archCitas.eof()) break; // Si llegamos al final del archivo, salir del bucle

        archCitas >> c >> mes >> c >> anho >> dni >> porcentaje
                >> horaIni >> c >> minIni >> c >> segIni
                >> horaFin >> c >> minFin >> c >> segFin
                >> codMedico >> tieneMedicina;
        // las variables tipo char solo guardan un caracter y es por eso que no hay problema con el espacio intermedio

        // Formato esperado: dd/mm/aaaa dni porcentaje hh:mm:ss hh:mm:ss codMedico S/N

        // VERIFICAR SI LA CITA INCLUYE MEDICINAS
        if (tieneMedicina == 'S') {
            archCitas >> montoMedicina; // Leer monto si hay medicinas
        } else {
            montoMedicina = 0; // Sin medicinas, monto = 0
        }

        calcularDuracion(horaIni, minIni, segIni, horaFin, minFin, segFin,
                         duracionHoras, horaDura, minDura, segDura);

        imprimirCita(dia, mes, anho, dni, horaIni, minIni, segIni, horaFin, minFin, segFin,
                     horaDura, minDura, segDura, porcentaje, archReporte);

        buscarMedico(codMedico, archMedicos, tarifaMedico, archReporte);

        // CALCULAR PAGO TOTAL DE LA CITA
        // Fórmula: (tarifa × duración × descuento_consulta) + (medicinas × descuento_medicinas)
        pago = (tarifaMedico * duracionHoras) * (1 - porcentaje / 100) +
               montoMedicina * (1 - (porcentaje / 2) / 100);

        archReporte << setw(8) << pago << endl;
        totalIngresos = totalIngresos + pago; // Acumular ingresos totales

        // VERIFICAR SI ES EL PAGO MÁS ALTO
        if (pago > max) {
            max = pago; // Actualizar máximo
            dniMax = dni; // Guardar DNI del paciente con mayor gasto
        }
    }

    imprimirResumenReporte(totalIngresos, max, dniMax, archReporte);
}

void elaborarEncabezadoReporte(ofstream &archReporte) {
    archReporte << setw(70) << "EMPRESA DE SALUD S.A." << endl;

    escribirLinea('=', CANT_MAX_LINEA, archReporte);

    archReporte << setw(72) << "REGISTRO DE CITAS MEDICAS" << endl;
    escribirLinea('=', CANT_MAX_LINEA, archReporte);

    archReporte << "Fecha" << setw(15) << "Paciente" << setw(10) << "Inicio"
            << setw(7) << "Fin" << setw(13) << "Duracion" << setw(15) << "% por Seguro"
            << setw(15) << "Medico" << setw(35) << "Especialidad"
            << setw(30) << "Pago (citas+medicinas)" << endl;

    escribirLinea('-', CANT_MAX_LINEA, archReporte);
}

void escribirLinea(char c, int cant, ofstream &arch) {
    // c: carácter a repetir
    // cant: cantidad de repeticiones
    // arch: archivo donde escribir

    for (int i = 0; i < cant; i++) {
        // Bucle para repetir el carácter
        arch.put(c); // Escribir un carácter
    }
    arch << endl; // Salto de línea al final
}

void calcularDuracion(int horaIni, int minIni, int segIni, int horaFin, int minFin, int segFin,
                      double &duracionHoras, int &horaDura, int &minDura, int &segDura) {
    int segundos;
    segundos = (horaFin * 3600 + minFin * 60 + segFin) - (horaIni * 3600 + minIni * 60 + segIni);
    // 3600 segundos = 1 hora, 60 segundos = 1 minuto

    // CONVERTIR DURACIÓN A DIFERENTES FORMATOS
    duracionHoras = (double) segundos / 3600; // Duración en horas decimales (para cálculos)
    horaDura = segundos / 3600; // Horas enteras
    minDura = (segundos % 3600) / 60; // Minutos restantes
    segDura = (segundos % 3600) % 60; // Segundos restantes
}

void imprimirCita(int dia, int mes, int anho, int dni, int horaIni, int minIni, int segIni,
                  int horaFin, int minFin, int segFin, int horaDura, int minDura, int segDura,
                  double porcentaje, ofstream &archReporte) {
    archReporte << setfill('0') << setw(2) << dia << '/' << setw(2) << mes << '/' << anho << "  ";

    archReporte << dni << "  ";

    archReporte << setw(2) << horaIni << ':' << setw(2) << minIni << ':' << setw(2) << segIni << "  ";

    archReporte << setw(2) << horaFin << ':' << setw(2) << minFin << ':' << setw(2) << segFin << "  ";

    archReporte << setw(2) << horaDura << ':' << setw(2) << minDura << ':' << setw(2) << segDura;

    // RESTAURAR RELLENO CON ESPACIOS Y MOSTRAR PORCENTAJE
    archReporte << setfill(' ') << setw(10) << porcentaje << '%' << setw(5) << ' ';
}

void imprimirResumenReporte(double totalIngresos, double max, int dniMax, ofstream &archReporte) {
    escribirLinea('=', CANT_MAX_LINEA, archReporte);
    archReporte << "Total de ingresos: " << totalIngresos << endl;
    escribirLinea('=', CANT_MAX_LINEA, archReporte);
    archReporte << "Paciente que mas gasto en una cita medica: " << dniMax << endl;
    archReporte << "Monto gastado" << setw(40) << max << endl;
}

void buscarMedico(int codMedico, ifstream &archMedicos, double &tarifaMedico, ofstream &archReporte) {
    int codigo;

    archMedicos.clear(); // Limpiar flags de error
    archMedicos.seekg(0); // Posicionar al inicio del archivo

    // BUSCAR EL MÉDICO CON EL CÓDIGO ESPECIFICADO
    while (true) {
        archMedicos >> codigo; // Leer código del médico
        if (archMedicos.eof()) break; // Si llegamos al final, salir

        if (codigo == codMedico) {
            // ¿Es el médico que buscamos?
            leereImprimirNombreMedico(archMedicos, archReporte);

            leereImprimirEspecialidadMedico(archMedicos, archReporte);

            archMedicos >> tarifaMedico;
            break; // Médico encontrado, salir del bucle
        } else {
            // DESCARTAR EL RESTO DE LA LÍNEA SI NO ES EL MÉDICO BUSCADO
            while (archMedicos.get() != '\n'); // Leer hasta encontrar salto de línea
        }
    }
}

void leereImprimirNombreMedico(ifstream &archMedicos, ofstream &archReporte) {
    int cant = 0;
    char c;
    bool mayuscula = true; //conversión activada (de minúscula a mayúscula)

    archMedicos >> c;

    while (true) {
        if (c != '_') {
            if (mayuscula) {
                if (c >= 'a' && c <= 'z') {
                    c = c - 'a' + 'A'; // Convertir a mayúscula (mayuscula = true)
                }
                mayuscula = false; //activa la conversión contraria (mayúscula a minúscula)
            } else {
                if (c >= 'A' && c <= 'Z') {
                    c = c - 'A' + 'a'; // Convertir a minúscula
                }
            }
            archReporte.put(c);
        } else {
            archReporte.put(' ');
            mayuscula = true;
        }

        cant++;
        c = archMedicos.get();
        if (c == ' ') break;
    }
    //COMPLETAR CONN ESPACIOS (ALINEACION DE 40)
    for (int i = 0; i < 40 - cant; i++) {
        archReporte.put(' ');
    }
}

// FUNCIÓN PARA LEER E IMPRIMIR LA ESPECIALIDAD DEL MÉDICO
void leereImprimirEspecialidadMedico(ifstream &archMedicos, ofstream &archReporte) {
    int cant; // Contador de caracteres
    char c;

    archMedicos >> c; // Leer primer carácter de la especialidad
    cant = 0;

    while (true) {
        // CONVERTIR MINÚSCULAS A MAYÚSCULAS
        if (c >= 'a' and c <= 'z') {
            c = c - 'a' + 'A';
        }

        cant++;
        archReporte.put(c); // Escribir carácter
        c = archMedicos.get(); // Leer siguiente
        if (c == ' ') break; // Espacio indica fin de especialidad
    }

    // COMPLETAR CON ESPACIOS HASTA 25 CARACTERES
    for (int i = 0; i < 25 - cant; i++) {
        archReporte.put(' ');
    }
}
