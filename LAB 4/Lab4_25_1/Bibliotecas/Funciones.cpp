
#include "Funciones.h"
#include <iostream>         //Para usar (cout, cin)
#include <fstream>          //Para usar(ifstream, ofstream)
#include <iomanip>          //Para usar setw,setfill y setprecision

using namespace std;

#define MAX_DIG 100

void imprimirLinea(ofstream &reporte, char c, int size){
    reporte<<endl;
    for(int i=0; i<size;i++){   // Bucle for que se ejecuta 'size' veces
        reporte<<c;
    }
    reporte<<endl;
}

// FUNCIÓN: leerArreglo - Lee números de un archivo y los almacena en un arreglo
bool leerArreglo(ifstream &archNumeros, int *numeroGrande1, int &cantNumG1){
    int num, i=0;               // Declara variables: 'num' para almacenar cada número leído, 'i' como contador
    while(true){
        archNumeros>>num;       // Lee un número del archivo
        if(archNumeros.eof()) return false;  // Si llegó al final del archivo, retorna false
        //detectar salto de linea
        numeroGrande1[i]=num;   // Almacena el número en la posición 'i' del arreglo

        i++;

        // Salta todos los espacios en blanco
        while(archNumeros.peek()==' ')archNumeros.get();  // peek() mira el siguiente carácter sin leerlo
        if(archNumeros.peek()=='\n')break;  // Si encuentra salto de línea, sale del bucle
    }
    cantNumG1=i;               // Guarda la cantidad de números leídos

    //mover los numeros al final del arreglo (alineación a la derecha)
    int temp=cantNumG1-1;      // Índice del último número leído
    i=1;                       // Contador para posiciones desde el final
    while(true){               // Bucle para mover números al final del arreglo
        numeroGrande1[MAX_DIG-i]=numeroGrande1[temp];  // Copia número a posición final
        numeroGrande1[temp]=0;                         // Limpia la posición original
        temp--;                // Decrementa índice origen
        i++;                   // Incrementa contador destino
        if(!(temp>=0)) break;  // Si ya procesó todos los números, sale del bucle
    }
    return true;               // Retorna true indicando éxito en la lectura
}

// FUNCIÓN: sumarArreglos - Suma dos números grandes representados como arreglos
void sumarArreglos(ofstream &reporte, int *numeroGrande1, int *numeroGrande2, int *totalGrande, int cantNumG1, int cantNumG2, int &cantTotalG){
    int i=1, lleva=0, sumaDig=0;  // Variables: contador, acarreo, suma de dígitos
    bool llevaQ=false, bandera=true;  // Flags: si hay acarreo, control de cálculo de cantidad

    //imprimir primer número (numeroGrande1)
    for(int i=MAX_DIG-cantNumG1; i<MAX_DIG; i++){  // Imprime desde la primera posición significativa
        reporte<<numeroGrande1[i];
    }
    reporte<<"  +"<<endl;       // Imprime el símbolo de suma

     //imprimir segundo número (numeroGrande2)
    for(int i=MAX_DIG-cantNumG2;i<MAX_DIG; i++){   // Imprime desde la primera posición significativa
        reporte<<numeroGrande2[i];
    }
    imprimirLinea(reporte, '-', MAX_DIG);  // Imprime línea separadora con guiones

    while(true){                // Bucle principal de suma
        // Suma dígitos correspondientes más el acarreo anterior
        sumaDig=numeroGrande1[MAX_DIG-i]+numeroGrande2[MAX_DIG-i];
        sumaDig+=lleva;         // Añade el acarreo

        if(sumaDig>9){          // Si la suma es mayor a 9
            llevaQ=true;        // Marca que hay acarreo
            lleva=sumaDig/10;   // Calcula el acarreo (parte entera de división por 10)
            sumaDig=sumaDig-10; // El dígito resultado es el residuo
        } else{
            llevaQ=false;       // No hay acarreo
            lleva=0;
        }
        totalGrande[MAX_DIG-i]=sumaDig;  // Guarda el dígito resultado
        i++;                    // Avanza al siguiente dígito

        //calcular cantidad de dígitos del total
        if(i>cantNumG1 && i>cantNumG2 && bandera){  // Si ya procesó todos los dígitos originales
            if(llevaQ){
                cantTotalG=i;   // Si hay acarreo, la cantidad incluye un dígito más
            } else{
                cantTotalG=i-1; // Si no hay acarreo, la cantidad es i-1
            }
            bandera=false;      // Evita recalcular la cantidad
        }
        //terminar el bucle
        if(i>MAX_DIG) break;    // Sale si excede el tamaño máximo del arreglo
    }

    //Impresión de la suma
//    for(int i=MAX_DIG-cantTotalG;i<MAX_DIG; i++){
//        reporte<<totalGrande[i];
//    }
    //reporte<<endl;
}

// FUNCIÓN: igualarArreglos - Copia el resultado de la suma al primer número para acumulación
void igualarArreglos(int *numeroGrande1, int &cantNumG1, int *totalGrande, int &cantTotalG){
    //reseteo de numeroGrande1 (limpia el arreglo)
    for(int i=0; i<MAX_DIG;i++){
        numeroGrande1[i]=0;
    }
    //copiando totalGrande a numeroGrande1
    for(int i=0;i<MAX_DIG;i++){
        numeroGrande1[i]=totalGrande[i];
    }
    //reseteando el arreglo suma
    for(int i=0; i<MAX_DIG;i++){
        totalGrande[i]=0;
    }
    cantNumG1=cantTotalG;       // Actualiza la cantidad de dígitos
    cantTotalG=0;               // Resetea el contador del total

    // CÓDIGO COMENTADO - Debug para mostrar el arreglo (deshabilitado)
//    for(int i=0; i<MAX_DIG;i++){
//        cout<<i+1<<") "<<numeroGrande1[i]<<endl;
//    }
}

// FUNCIÓN PRINCIPAL: calcularSuma - Coordina la lectura y suma de múltiples números grandes
void calcularSuma(ofstream &reporte, ifstream &archNumeros){
    // Declaración de arreglos para almacenar números grandes (inicializados en 0)
    int numeroGrande1[MAX_DIG]{},numeroGrande2[MAX_DIG]{}, totalGrande[MAX_DIG]{};
    int cantNumG1=0,cantNumG2=0, cantTotalG=0;  // Contadores de dígitos

    //lee el primer número del archivo
    leerArreglo(archNumeros, numeroGrande1, cantNumG1);

    // Bucle principal: lee cada número siguiente y lo suma al acumulado
    while(leerArreglo(archNumeros, numeroGrande2, cantNumG2)) {  // Mientras haya números que leer
        // Suma el número acumulado con el nuevo número leído
        sumarArreglos(reporte, numeroGrande1, numeroGrande2, totalGrande, cantNumG1, cantNumG2, cantTotalG);
        // Copia el resultado de la suma al primer número (para acumular)
        igualarArreglos(numeroGrande1, cantNumG1, totalGrande, cantTotalG);

        //reseteo del segundo número para la siguiente iteración
        for(int i=0; i<MAX_DIG;i++){
            numeroGrande2[i]=0;
        }
    }

    //imprimiendo la suma final
    for(int i=MAX_DIG-cantNumG1; i<MAX_DIG; i++){  // Imprime desde el primer dígito significativo
        reporte<<numeroGrande1[i];
    }
    reporte<<endl<<"SUMA TOTAL FINAL ^"<<endl;  // Etiqueta indicando que es el resultado final

    //Debug y pruebas
//    for(int i=0; i<MAX_DIG;i++){
//        cout<<i+1<<") "<<totalGrande[i]<<endl;
//    }
//    cout<<"la cantidad es "<<cantTotalG<<endl;
//    cout<<numeroGrande1[MAX_DIG-1];
}