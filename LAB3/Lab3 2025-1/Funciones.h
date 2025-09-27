
#ifndef LAB03_2025_1_FUNCIONES_H
#define LAB03_2025_1_FUNCIONES_H
using namespace std;

void ImprimirMultas(ifstream &archEmp,ifstream &archInf,ifstream &archTab,ofstream &archRep,int&dniMay,int&dniMen,
    double&pagMay,double&pagMen);
void ImprimirEncabeza(ofstream &archRep);
void ImprimirPrimerEncabezado(ifstream &archEmp,ofstream &archRep,int dni,int&cont);
void LeerEImprimir(ifstream &archEmp,ofstream &archRep,bool Mayus,bool Esp,char c,int i);
void LeerImprimirVehiculos(ifstream &archEmp,ifstream &archInf,ifstream &archTab,ofstream &archRep,int&cantL,
    int&cantG,int&cantMG,double&pagL,double&pagG,double&pagMG);
void BuscarFechaEInfraccion(ifstream &archInf,ifstream &archTab,ofstream &archRep,int placa1,int placa2,char tipo,
        int&cantL,int&cantG,int&cantMG,double&pagL,double&pagG,double&pagMG);
void BuscarInfraccion(ifstream &archTab,ofstream &archRep,char gravedad,int infraccion,
                    int&cantL,int&cantG,int&cantMG,double&pagL,double&pagG,double&pagMG);
void DescartarLinea(ifstream &archTab);

void ImprimirResumen(ofstream &archRep,int&dniMay,int&dniMen,double&pagMay,double&pagMen);

#endif //LAB03_2025_1_FUNCIONES_H