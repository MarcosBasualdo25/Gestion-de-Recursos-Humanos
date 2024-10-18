
#include <iostream>
#include "GestionEmpleados.h"
#include "Asistencia.h"
#include "EvaluacionEmpleado.h"
#include "InicioSesion.h"
#include "gotoxy.h"
#include "Solicitudes.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>

#define up 105
#define down 107
#define enter 13

using namespace std;

int obtenerAnchoConsola();
bool obtenerEntero(int& numero);
int menu(string titulo, string opciones[], int n);

int main() {

    SetConsoleOutputCP(CP_UTF8);

    //Inicio de sesion
    crearUsuario(PilaUsers, "david.aldana", "1234", "ADMINISTRADOR");
    crearUsuario(PilaUsers, "gabriel.poma", "4321", "EMPLEADO");

    //Mostramos la pantalla para iniciar sesion
    pantallaInicioSesion(PilaUsers);

    Empleado* headEmpleados = nullptr;
    Empleado* tailEmpleados = nullptr;

    int opc;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    
    do {
        string titulo = "---Menú Principal---";
        string opciones[] = {"1. Gestión de empleados", "2. Evaluación de empleados","3. Asistencia de empleados", "4. Solicitudes","5. Volver a iniciar sesion","6. Salir"};
        int n = 6;
        opc = menu(titulo,opciones,n);
        
        Empleado* empleado;
        switch (opc) {
            case 1: {
                int continuar;
                do {
                    continuar = mostrarMenuGestionEmpleados(headEmpleados,tailEmpleados);
                } while (continuar != 0);
                break;
            }
            case 2: {
                
                if (headEmpleados == nullptr) {
                    gotoxy(x, 14);
                    cout << "No hay empleados registrados. Regrese al menú y agregue empleados primero.\n";
                    system("pause");
                    break;
                }
                int id;
                bool entradaValida = false;
                do {
                    gotoxy(x, 14);
                    cout << "Ingrese el ID del empleado para evaluar: ";
                    entradaValida = obtenerEntero(id);
                    if (!entradaValida) {
                        gotoxy(x, 15);
                        cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                        gotoxy(x, 14);
                        cout << string(50, ' ');
                    }
                } while (!entradaValida);

                empleado = buscarEmpleado(headEmpleados, id);
                if (empleado == nullptr) {
                    gotoxy(x, 12);
                    cout << "Empleado con ID " << id << " no encontrado.\n";
                    system("pause");
                    break;
                }
                titulo = "Evaluaciones de " + empleado->nombre + " " + empleado->apellido;
                string opcionesEvaluacion[] = {"1. Agregar evaluación", "2. Mostrar evaluaciones", "3. Volver al menú principal"};
                n = 3;
                do {
                    
                    opc= menu(titulo, opcionesEvaluacion, n);

                    switch (opc) {
                        case 1:
                            agregarEvaluacion(empleado->pilaEvaluaciones);
                            break;
                        case 2:
                            mostrarEvaluacionesEmpleado(empleado->pilaEvaluaciones);
                            break;
                        case 3:
                            break;
                    }
                } while (opc != 3);
                break;
            }
            case 3: {//Asistencias de empleados
                if (headEmpleados == nullptr) {
                    gotoxy(x, 14);
                    cout << "No hay empleados registrados. Regrese al menú y agregue empleados primero.\n";
                    system("pause");
                    break;
                }
                int id;
                bool entradaValida = false;
                do {
                    gotoxy(x, 14);
                    cout << "Ingrese el ID del empleado para evaluar: ";
                    entradaValida = obtenerEntero(id);
                    if (!entradaValida) {
                        gotoxy(x, 15);
                        cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                        gotoxy(x, 14);
                        cout << string(50, ' ');
                    }
                } while (!entradaValida);
                empleado = buscarEmpleado(headEmpleados, id);
                if (empleado == nullptr) {
                    gotoxy(x,16);
                    cout << "Empleado con ID " << id << " no encontrado.\n";
                    getch();
                    break;
                }
                titulo = "Asistencias de " + empleado->nombre + " " + empleado->apellido;
                string opcionesAsistencia[] = {"1. Agregar registro de asistencia", "2. Mostrar registro de asistencia", "3. Volver al menú principal"};
                n = 3;
                do {
                    opc= menu(titulo, opcionesAsistencia, n);

                    switch (opc) {
                        case 1:
                            agregarRegistro(empleado->pilaAsistencias);
                            getch();
                            break;
                        case 2:
                            imprimirRegistros(empleado->pilaAsistencias);
                            getch();
                            break;
                        case 3:
                            break;
                    }
                } while (opc != 3);
                break;
            }
            case 4:{ //solicitud
                if (headEmpleados == nullptr) {
                    gotoxy(x, 14);
                    cout << "No hay empleados registrados. Regrese al menú y agregue empleados primero.\n";
                    system("pause");
                    break;
                }
                int id;
                bool entradaValida = false;

                // Solicitar el ID del empleado para gestionar solicitudes
                do {
                    gotoxy(x, 14);
                    cout << "Ingrese el ID del empleado para gestionar solicitudes: ";
                    entradaValida = obtenerEntero(id);
                    if (!entradaValida) {
                        gotoxy(x, 15);
                        cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                        gotoxy(x, 14);
                        cout << string(50, ' ');  // Limpia la línea
                    }
                } while (!entradaValida);

                empleado = buscarEmpleado(headEmpleados, id);  // Busca el empleado por ID
                if (empleado == nullptr) {
                    gotoxy(x, 12);
                    cout << "Empleado con ID " << id << " no encontrado.\n";
                    system("pause");
                    break;
                }
                titulo = "Solicitudes de " + empleado->nombre + " " + empleado->apellido;
                string opcionesSolicitud[] = {"1. Enviar solicitud", "2. Mostrar solicitudes", "3. Volver al menú principal"};
                n = 3;
                do {
                    opc = menu(titulo, opcionesSolicitud, n);
                    switch (opc) {
                        case 1:
                            enviarSolicitud(empleado->colaSolicitudes);
                            break;
                        case 2:
                            mostrarSolicitudesEmpleado(empleado->colaSolicitudes);
                            break;
                        case 3:
                            break;
                    }
                } while (opc != 3);
                break;
            }
            case 5: {
                LoginUser = false;
                pantallaInicioSesion(PilaUsers);
                break;
            }
            case 6:{
                gotoxy(x, 12);
                cout << "Saliendo del programa...\n";
                system("pause");
                break;
            }
        }
    } while (opc != 6);


    Empleado* temp;
    while (headEmpleados != nullptr) {
        temp = headEmpleados;
        headEmpleados = headEmpleados->siguiente;


        if (temp->pilaEvaluaciones != nullptr) {
            Evaluacion* evalTemp;
            while (temp->pilaEvaluaciones->cima != nullptr) {
                evalTemp = temp->pilaEvaluaciones->cima;
                temp->pilaEvaluaciones->cima = temp->pilaEvaluaciones->cima->siguiente;
                delete evalTemp;
            }
            delete temp->pilaEvaluaciones;
        }
        if (temp->pilaAsistencias != nullptr) {
            RegistroAsistencia* asisTemp;
            while (temp->pilaAsistencias->cima != nullptr) {
                asisTemp = temp->pilaAsistencias->cima;
                temp->pilaAsistencias->cima = temp->pilaAsistencias->cima->siguiente;
                delete asisTemp;
            }
            delete temp->pilaEvaluaciones;
        }

        delete temp;
    }

    return 0;
}

int menu(string titulo, string opciones[], int n){
    int opcion = 1;
    int tecla;
    bool repite = true;
    int longitud = titulo.length();
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    do{
        system("cls");
        
        gotoxy(anchoConsola/2-(longitud/2),2); cout<<titulo;
        gotoxy(x-5,3+opcion); cout<<"--->";
        for(int i=0;i<n;i++){
            gotoxy(x,4+i); cout<<opciones[i];
        }
        do{
            tecla = getch();
        }while(tecla != up && tecla!= down && tecla != enter);

        switch(tecla){
            case up:{
                opcion--;
                if(opcion < 1){
                    opcion = n;
                }
                break;
            }
            case down:{
                opcion++;
                if(opcion > n){
                    opcion = 1;
                }
                break;
            }
            case enter:{
                repite=false;
                break;
            }
        }

    }while(repite);
    return opcion;
}