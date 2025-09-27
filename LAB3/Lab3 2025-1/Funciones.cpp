
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Funciones.h"

using namespace std;

#define TAM_NOMBRE 40
#define TAM_DISTRITO 30
#define TAM_LINEA 150

void ImprimirMultas(ifstream &archEmp,ifstream &archInf,ifstream &archTab,ofstream &archRep,int&dniMay,int&dniMen,
    double&pagMay,double&pagMen) {
    int dni,cantG,cantL,cantMG,cont=1;
    double pagG,pagL,pagMG,pagototal;
    ImprimirEncabeza(archRep);
    while (true) {
        archEmp>>dni;
        if (archEmp.eof()) break;
        ImprimirPrimerEncabezado(archEmp,archRep,dni,cont);
        pagG=pagL=pagMG=cantG=cantL=cantMG=0;
        LeerImprimirVehiculos(archEmp,archInf,archTab,archRep,cantL,cantG,cantMG,pagL,pagG,pagMG);
        pagototal=pagL+pagG+pagMG;
        archRep<<setw(29)<<"CANTIDAD"<<setw(16)<<"MONTO PAGADO"<<endl;
        archRep<<"FALTAS LEVES:"<<setw(13)<<cantL<<setw(15)<<pagL<<endl;
        archRep<<"FALTAS GRAVES:"<<setw(12)<<cantG<<setw(15)<<pagG<<endl;
        archRep<<"FALTAS MUY GRAVES:"<<setw(8)<<cantMG<<setw(15)<<pagMG<<endl;
        archRep<<setfill('-')<<setw(46)<<"-"<<endl<<setfill(' ')<<"PAGO TOTAL: "<<setw(29)<<pagototal<<endl
        <<setfill('=')<<setw(TAM_LINEA)<<"="<<endl<<setfill(' ');
        if (pagototal<pagMen) {
            pagMen=pagototal;
            dniMen=dni;
        }
        if (pagototal>pagMay) {
            pagMay=pagototal;
            dniMay=dni;
        }
    }

}
void ImprimirEncabeza(ofstream &archRep) {
    archRep<<fixed<<setprecision(2);
    archRep<<setw(85)<<"MINISTERIO DE TRANSPORTE"<<endl<<setw(89)<<"MULTAS IMPUESTAS A LAS COMPANIAS"<<endl
    <<setfill('=')<<setw(TAM_LINEA)<<"="<<endl<<setfill(' ');

}
void ImprimirPrimerEncabezado(ifstream &archEmp,ofstream &archRep,int dni,int&cont) {
    archRep
    <<"COMPANIA No. "<<cont<<endl<<"REPRESENTANTE LEGAL: ";
    LeerEImprimir(archEmp,archRep,true,true,' ',TAM_NOMBRE);
    archRep<<"DNI: "<<dni<<setw(15)<<"DISTRITO: ";
    LeerEImprimir(archEmp,archRep,false,false,' ',TAM_DISTRITO);
    archRep<<endl<<setfill('-')<<setw(TAM_LINEA)<<"-"<<endl<<setfill(' ')<<"VEHICULOS INFRACCIONADOS:"<<endl
    ;
    cont++;
}
void LeerEImprimir(ifstream &archEmp,ofstream &archRep,bool Mayus,bool Esp,char c, int i) {
    int contador=0;
    char car;
    bool a=false;
    archEmp>>ws;
    while (true) {
        car=archEmp.get();
        if (Mayus) {
            if ((a or contador==0) and (car>='a' and car<='z')) {
                car=car-('a'-'A');
                a=false;
            }
            if (car=='/' or car=='-') a=true;
        }
        contador++;
        if (car=='/' or car=='-' or car=='_') car=' ';
        archRep.put(car);
        if (archEmp.peek()==c) break;
    }
    if (Esp) archRep<<setw(i-contador)<<" ";
}
void LeerImprimirVehiculos(ifstream &archEmp,ifstream &archInf,ifstream &archTab,ofstream &archRep,int&cantL,
    int&cantG,int&cantMG,double&pagL,double&pagG,double&pagMG) {
    char tipo,c,gravedad;
    int placa1,placa2,d,m,a,cont=1,infraccion;
    double multa;
    archEmp>>ws;
    while (true) {
        archEmp>>tipo>>placa1>>c>>placa2;
        archRep<<setw(2)<<" "<<setfill('0')<<setw(2)<<cont<<setfill(' ')<<")"<<setw(10)<<"PLACA: "
        <<tipo<<placa1<<"-"<<placa2<<setw(10)<<"TIPO: ";
        if (tipo=='P')archRep<<"PEQUEÑO"<<endl;
        if (tipo=='M')archRep<<"MEDIANO"<<endl;
        if (tipo=='G')archRep<<"GRANDE"<<endl;
        archRep<<setw(11)<<"No."<<setw(9)<<"FECHA"<<setw(16)<<"INFRACCION"<<setw(12)<<"GRAVEDAD"<<setw(14)<<"MULTA"
        <<setw(17)<<"DESCRIPCION"<<endl;

        BuscarFechaEInfraccion(archInf,archTab,archRep,placa1,placa2,tipo,cantL,cantG,cantMG,pagL,pagG,pagMG);
        archRep<<setfill('-')<<setw(TAM_LINEA)<<"-"<<endl<<setfill(' ');
        cont++;
        if (archEmp.peek()=='\n') break;
    }

}
void BuscarFechaEInfraccion(ifstream &archInf,ifstream &archTab,ofstream &archRep,int placa1,int placa2,char tipo,
            int&cantL,int&cantG,int&cantMG,double&pagL,double&pagG,double&pagMG) {
    int d,m,a,cont=1,plac1,plac2,infraccion;
    char c,plac,gravedad;
    bool encontrado;
    archInf.clear();
    archInf.seekg(0,ios::beg);
    while (true) {
        archInf>>d>>c>>m>>c>>a>>plac>>plac1>>c>>plac2>>gravedad>>infraccion;
        if (archInf.eof()) break;
        if (plac==tipo and plac1==placa1 and plac2==placa2) {
            archRep<<setw(7)<<" "<<setfill('0')<<setw(2)<<cont<<setfill(' ')<<")"<<setw(2)<<" "
            <<setfill('0')<<setw(2)<<d<<"/"<<setw(2)<<m<<"/"<<a<<setfill(' ')<<setw(10)<<infraccion;
            BuscarInfraccion(archTab,archRep,gravedad,infraccion,cantL,cantG,cantMG,pagL,pagG,pagMG);
            cont++;
        }

    }

}
void BuscarInfraccion(ifstream &archTab,ofstream &archRep,char gravedad,int infraccion,
                    int&cantL,int&cantG,int&cantMG,double&pagL,double&pagG,double&pagMG) {
    bool indicador=false;
    char grav;
    double multa;
    int inf;
    archTab.clear();
    archTab.seekg(0,ios::beg);
    while (true) {
        archTab>>grav>>inf;
        if (archTab.eof()) break;
        if (gravedad==grav and inf==infraccion) {
            archTab>>multa;
            archTab>>ws;
            archRep<<setw(8)<<" ";
            if (grav=='L') {
                archRep<<"LEVE"<<setw(9)<<" ";
                cantL++;
                pagL+=multa;
            }
            if (grav=='M') {
                archRep<<"MUY GRAVE"<<setw(4)<<" ";
                cantMG++;
                pagMG+=multa;
            }
            if (grav=='G') {
                archRep<<"GRAVE"<<setw(8)<<" ";
                cantG++;
                pagG+=multa;
            }
            archRep<<setw(10)<<multa<<setw(5)<<" ";
            LeerEImprimir(archTab,archRep,false,false,'\n',20);
            archRep<<endl;
            indicador=true;
            break;
        }
        else {
            DescartarLinea(archTab);
        }
    }
    if (not indicador) archRep<<"No se encontro esa infraccion."<<endl;
}
void DescartarLinea(ifstream &archTab) {
    double d;
    char c;
    archTab>>d;
    archTab>>ws;
    while (true) {
        archTab>>c;
        if (archTab.peek()=='\n') break;
    }
}
void ImprimirResumen(ofstream &archRep,int&dniMay,int&dniMen,double&pagMay,double&pagMen) {
    archRep<<setfill('+')<<setw(46)<<"+"<<endl<<setfill(' ')
    <<"+ COMPANIA CON MAYOR PAGO POR INFRACCIONES"<<setw(4)<<"+"<<endl
    <<"+ DNI:"<<setw(19)<<dniMay<<setw(21)<<"+"<<endl
    <<"+ TOTAL PAGADO:"<<setw(10)<<pagMay<<setw(21)<<"+"<<endl;
    archRep<<setfill('+')<<setw(46)<<"+"<<endl<<setfill(' ')
    <<"+ COMPANIA CON MENOR PAGO POR INFRACCIONES"<<setw(4)<<"+"<<endl
    <<"+ DNI:"<<setw(19)<<dniMen<<setw(21)<<"+"<<endl
    <<"+ TOTAL PAGADO:"<<setw(10)<<pagMen<<setw(21)<<"+"<<endl;
    archRep<<setfill('+')<<setw(46)<<"+"<<endl<<setfill(' ');
}