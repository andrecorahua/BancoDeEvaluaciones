//
// Created by Andre on 22/09/2025.
//
#include <iostream>//para usar cin y cout
#include <iomanip>//para usar setw,setfill,setprecision
#include <fstream>//ifstream , ofstream
#include "Funciones.h"
#define CANT_MAX_LINEA 140
using namespace std;

void elaborarReporte (ifstream &archTwitch,ofstream &archReporte) {
    int diaI, mesI, anoI, diaF, mesF, anoF, dia, mes, ano, fechaI, nCanal = 1,
    fechaF, fecha, cantEspectadoresTotales = 0;
    int cantStreams, duracionStreams, cantEspectadores, totalStreams = 0, duraciontotal = 0;
    double tarifaXReproducciones, tarifaXTiempo, index, ingresosTXPublicidad, intresosTXDuracion;
    char c;
    cin >> diaI >> c >> mesI >> c >> anoI >> diaF >> c >> mesF >> c
    >> anoF >> tarifaXReproducciones >> tarifaXTiempo;
    fechaI = anoI*10000 + mesI*100 + diaI;
    fechaF = anoF*10000 + mesF*100 + diaF;
    elaborarEncabezado(diaI, mesI, anoI, diaF, mesF, anoF,
        tarifaXReproducciones, tarifaXTiempo, archReporte);
    while (true) {
        archTwitch >> dia;
        if (archTwitch.eof()) break;
        archTwitch >> c >> mes >> c >> ano;
        fecha = ano*10000 + mes*100 + dia;
        if (fecha >= fechaI and fecha <= fechaF) {
            //proseguir
            imprimircanales(nCanal, index, archTwitch, archReporte, dia, mes, ano);
            imprimirUltimasReproduccionesYResumenCanal(index, cantStreams, duracionStreams, cantEspectadores,
                                                       archTwitch, archReporte,
                                                       tarifaXReproducciones, tarifaXTiempo);
            cantEspectadoresTotales = cantEspectadoresTotales + cantEspectadores;
            totalStreams = totalStreams + cantStreams;
            duraciontotal = duraciontotal + duracionStreams;
            //hallar totales
            nCanal++;
        } else {
            while (archTwitch.get() != '\n');
        }
    }
}

void elaborarEncabezado(int diaI,int  mesI,int  anoI,int  diaF,int  mesF,int  anoF,
        double tarifaXReproducciones,double  tarifaXTiempo,ofstream &archReporte) {

    archReporte<<setw(70)<<"PLATAFORMA TP_Twitch"<<endl;
    archReporte<<setw(75)<<"REGISTRO DE LOS CANALES AFILIADOS"<<endl;
    archReporte<<setw(60)<<"FECHAS DE CREACION ENTRE EL ";
    imprimirFecha(diaI, mesI, anoI, archReporte);
    archReporte<<" Y EL ";
    imprimirFecha(diaF, mesF, anoF, archReporte);
    archReporte << endl << setw(59) << "TARIFA POR NUMERO DE REPRODUCCIONES: " << tarifaXReproducciones
    << " POR CADA 1,000 REPRODUCCIONES Y FRACCION \n";
    archReporte << setw(61) << "TARIFA POR DURACION DEL STREAM: " << tarifaXTiempo
    << " POR CADA MINUTO Y FRACCION" << endl;
    imprimirLinea('=', CANT_MAX_LINEA, archReporte);
}

void imprimirFecha(int dia,int  mes,int  ano,ofstream &archReporte) {
    archReporte << right << setfill('0') << setw(2) << dia << "/"
    << setw(2) << mes << "/" << setw(4) << ano << setfill(' ');
}

void imprimirLinea(char c, int cant, ofstream &archReporte) {
    for (int i=0;i <cant;i++) {
        archReporte << c;
    }
    archReporte << endl;
}

void imprimircanales(int nCanal,double &index, ifstream &archTwitch,ofstream &archReporte,int dia,int mes,int ano) {
    int codigoCanal, i = 0;
    long long seguidoresNuevos, vistasXMes, maxEspectadores;
    char letraCodigo, c;
    archReporte << "CANAL No. " << nCanal <<endl;
    archReporte << right << setw(4) << " " << "NOMBRE" << setw(15) << "CODIGO" << setw(18)
    << "CREADO EL" << setw(30) << "SEGUIDORES NUEVOS POR MES" << setw(27)
    << "NUEVAS VISTAS POR MES" << setw(28) << "MAXIMO DE ESPECTADORES" << endl;
    archTwitch >> letraCodigo >> codigoCanal >> ws;//ws: para saltar espacios en blanco, tabulaciones y saltos de linea
    archReporte << setw(4) << " ";//los 5 espacios antes del nombre (se itera en los siguientes canales)
    while (true) {
        c = archTwitch.get();//lee el nombre
        if (c == ' ') break;//rompe el bucle
        if (c <= 'z' and c>= 'a') c = c-'a'+'A';//cambiar a mayúscula
        archReporte.put(c);//imprime el nombre en mayusculas
        i++;
    }
    archTwitch >> seguidoresNuevos >> vistasXMes >> maxEspectadores;
    archReporte << setw(16-i) << letraCodigo << codigoCanal << setw(10)
    << " ";//alineacion del espaciado
    imprimirFecha(dia, mes, ano, archReporte);
    archReporte << setw(18) << seguidoresNuevos << setw(30) << vistasXMes
    << setw(26) << maxEspectadores << endl;
    index = ((seguidoresNuevos+(vistasXMes/100))/maxEspectadores);
    imprimirLinea('-', CANT_MAX_LINEA, archReporte);
}

void imprimirUltimasReproduccionesYResumenCanal(double index,int &cantStreams,int &duracionStreams,int &cantEspectadores,ifstream &archTwitch,ofstream &archReporte,
                double tarifaXReproducciones,double tarifaXTiempo) {
    char c;
    double subingresosXDuracion, subingresosXPublicidad, ingresosXPublicidad = 0, ingresosXDuracion = 0;
    int dia, mes, ano, horas, minutos, segundos, cantReproducciones, duracion;
    archReporte << setw(5) << " " << "ULTIMAS REPRODUCCIONES \n";
    archReporte << setw(10) << " " << "FECHA DE PUBLICACION" << setw(20)
    << "TIEMPO DE DURACION" << setw(25) << "INGRESOS POR DURACION"
    << setw(30) << "NUMERO DE REPRODUCCIONES" << endl;
    duracionStreams = 0;
    cantStreams = 0;
    cantEspectadores = 0;
    while (true) {
        archTwitch >> dia >> c >> mes >> c >> ano >> horas >> c >> minutos
        >> c >> segundos >> cantReproducciones;
        duracion = horas *3600 + minutos*60 + segundos;
        subingresosXDuracion = duracion * tarifaXTiempo/60;
        ingresosXDuracion = ingresosXDuracion + subingresosXDuracion;
        cantEspectadores = cantEspectadores + cantReproducciones;
        duracionStreams = duracionStreams + duracion;
        cantStreams++;
        archReporte << fixed << setprecision(2) <<setw(10) << " ";
        imprimirFecha(dia, mes, ano, archReporte);
        archReporte << setw(18) << " ";
        imprimirHora(horas, minutos, segundos, archReporte);
        archReporte << setw(20) << subingresosXDuracion << setw(25)
        << cantReproducciones << endl;
        c = archTwitch.get();
        if (c == '\n') break;
    }
    ingresosXPublicidad = cantEspectadores * tarifaXReproducciones/1000;
    imprimirLinea('-', CANT_MAX_LINEA, archReporte);
    archReporte << setw(5) << " " << "RESUMEN DEL CANAL \n";
    archReporte << setw(5) << " " << left << setw(50)
    << "DURACION TOTAL DE LAS REPRODUCCIONES: ";
    transformarHora(duracionStreams, archReporte);
    archReporte << endl;
    archReporte << setw(5) << " " << left << setw(50)
    << "INGRESOS POR DURACION: " << ingresosXDuracion;
    archReporte << endl;
    archReporte << setw(5) << " " << left << setw(50)
    << "TOTAL DE REPRODUCCIONES: " << cantEspectadores;
    archReporte << endl;
    archReporte << setw(5) << " " << left << setw(50)
    << "INGRESOS POR PUBLICIDAD: " << ingresosXPublicidad;
    archReporte << endl;
    archReporte << setw(5) << " " << left << setw(50)
    << "ENGAGEMENT INDEX: " << index;
    archReporte << endl;
    imprimirLinea('-', CANT_MAX_LINEA, archReporte);
}

void imprimirHora(int horas,int  minutos,int  segundos,ofstream &archReporte) {
    while (segundos >= 60) {
        segundos = segundos - 60;
        minutos ++;
    }
    while (minutos >= 60) {
        minutos = minutos - 60;
        horas ++;
    }
    archReporte << right << setfill('0') << setw(2) << horas << ":"
    << setw(2) << minutos << ":" << setw(2) << segundos << setfill(' ');
}

void transformarHora(int duracion, ofstream &archReporte) {
    int minutos, segundos, horas;
    horas = duracion/3600;
    minutos = (duracion%3600)/60;
    segundos = (duracion%3600)%60;
    archReporte << right << setfill('0') << setw(2) << horas << ":"
    << setw(2) << minutos << ":" << setw(2) << segundos << setfill(' ');
}