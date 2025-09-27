
#ifndef FUNCIONES_H
#define FUNCIONES_H
void elaborarReporte(ifstream &archCitas,ifstream &archMedicos, ofstream &archReporte);
void elaborarEncabezadoReporte(ofstream &archReporte);
void escribirLinea(char c, int cant, ofstream &arch);
void calcularDuracion(int horaIni, int minIni, int segIni, int horaFin, int minFin, int segFin, double &duracionHoras,
        int &horaDura, int &minDura, int &segDura);

void imprimirCita(int dia, int mes, int anho, int dni, int horaIni, int minIni, int segIni, int horaFin, int minFin,
        int segFin, int horaDura, int minDura, int segDura, double porcentaje, ofstream &archReporte);

void imprimirResumenReporte(double totalIngresos, double max, int dniMax, ofstream &archReporte);

void buscarMedico(int codMedico, ifstream &archMedicos, double &tarifaMedico, ofstream &archReporte);
void leereImprimirEspecialidadMedico(ifstream &archMedicos, ofstream &archReporte);
void leereImprimirNombreMedico(ifstream &archMedicos, ofstream &archReporte);

#endif

