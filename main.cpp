
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

#define up 72
#define down 80
#define enter 13

using namespace std;

int obtenerAnchoConsola();
bool obtenerEntero(int& numero);
int menu(string titulo, string opciones[], int n);

int main() {

    SetConsoleOutputCP(CP_UTF8);

    //Inicio de sesion
    crearUsuario(ListaUsers, "david.aldana", "1234", "ADMINISTRADOR");
    crearUsuario(ListaUsers, "gabriel.poma", "4321", "EMPLEADO");

    //Mostramos la pantalla para iniciar sesion
    pantallaInicioSesion(ListaUsers);
    cin.ignore();

    Empleado* headEmpleados = nullptr;
    Empleado* tailEmpleados = nullptr;

    int opc;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    
    do {
        ocultarCursor();
        Empleado* empleado;
        string titulo = ".:Menú Principal:.";
        string opciones[] = {"1. Gestión de empleados", "2. Evaluación de empleados","3. Asistencia de empleados", "4. Solicitudes","5. Volver a iniciar sesion","6. Salir"};
        int n = 6;
        opc = menu(titulo,opciones,n);
        switch (opc) {
            case 1: {
                string titulo = "--- Menú de Gestión de Empleados ---";
                string opcionesEmpleado[] = {"1. Agregar empleado", "2. Mostrar empleados","3. Actualizar empleado", "4. Eliminar empleado","5. Volver al menú principal"};
                int n = 5;
                do{
                    ocultarCursor();
                    opc = menu(titulo, opcionesEmpleado, n);
                    switch (opc) {
                        case 1: {
                            mostrarCursor();
                            crearYAgregarEmpleado(headEmpleados,tailEmpleados);
                            break;
                        }
                        case 2:
                            mostrarCursor();
                            mostrarEmpleados(headEmpleados, tailEmpleados);
                            cin.ignore();
                            break;
                        case 3: {
                            mostrarCursor();
                            int id;
                            bool entradaValida = false;
                            do {
                                gotoxy(x, 12);
                                cout << "Ingrese el ID del empleado a actualizar: ";
                                entradaValida = obtenerEntero(id);
                                if (!entradaValida) {
                                    gotoxy(x, 13);
                                    cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                                    gotoxy(x, 12);
                                    cout << string(50, ' '); 
                                }
                            } while (!entradaValida);
                            actualizarEmpleado(headEmpleados,tailEmpleados, id);
                            break;
                        }
                        case 4: {
                            mostrarCursor();
                            int id;
                            bool entradaValida = false;
                            do {
                                gotoxy(x, 12);
                                cout << "Ingrese el ID del empleado a eliminar: ";
                                entradaValida = obtenerEntero(id);
                                if (!entradaValida) {
                                    gotoxy(x, 13);
                                    cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                                    gotoxy(x, 12);
                                    cout << string(50, ' '); 
                                }
                            } while (!entradaValida);
                            eliminarEmpleado(headEmpleados, tailEmpleados, id);
                            break;
                        }
                        case 5:
                            break;
                    }
                }while(opc!= 5);
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
                    mostrarCursor();
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
                    ocultarCursor();
                    opc= menu(titulo, opcionesEvaluacion, n);

                    switch (opc) {
                        case 1:
                            mostrarCursor();
                            agregarEvaluacion(empleado->pilaEvaluaciones);
                            break;
                        case 2:
                            mostrarCursor();
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
                    mostrarCursor();
                    gotoxy(x, 14);
                    cout << "Ingrese el ID del empleado para la asistencia: ";
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
                ocultarCursor();
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
                    mostrarCursor();
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
                ocultarCursor();
                titulo = "Solicitudes de " + empleado->nombre + " " + empleado->apellido;
                string opcionesSolicitud[] = {"1. Enviar solicitud", "2. Mostrar solicitudes", "3. Volver al menú principal"};
                n = 3;
                do {
                    opc = menu(titulo, opcionesSolicitud, n);
                    switch (opc) {
                        case 1:
                        mostrarCursor();
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
            case 5: { //Desloguearse
                LoginUser = false;
                mostrarCursor();
                pantallaInicioSesion(ListaUsers);
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
        
        gotoxy(anchoConsola/2-(longitud/2) - 5,2); cout<<titulo;
        gotoxy(x-5,3+opcion); cout<<"➤";
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