#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;

void elaborarReporte(ifstream &archTwitch, ofstream &archReporte);
void elaborarEncabezado(int diaI, int mesI, int anoI, int diaF, int mesF, int anoF,
                       double tarifaXReproducciones, double tarifaXTiempo, ofstream &archReporte);
void imprimirFecha(int dia, int mes, int ano, ofstream &archReporte);
void imprimirLinea(char c, int cant, ofstream &archReporte);
void imprimircanales(int nCanal, double &index, ifstream &archTwitch, ofstream &archReporte, 
                    int dia, int mes, int ano);
void imprimirUltimasReproduccionesYResumenCanal(double index, int &cantStreams, int &duracionStreams, 
                                               int &cantEspectadores, ifstream &archTwitch, 
                                               ofstream &archReporte, double tarifaXReproducciones, 
                                               double tarifaXTiempo);
void imprimirHora(int horas, int minutos, int segundos, ofstream &archReporte);
void transformarHora(int duracion, ofstream &archReporte);

#endif