
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

using namespace std;

int obtenerAnchoConsola();
bool obtenerEntero(int& numero);

int main() {

    SetConsoleOutputCP(CP_UTF8);

    //Inicio de sesion
    crearUsuario(ListaUsers, "david.aldana", "1234", "ADMINISTRADOR");
    crearUsuario(ListaUsers, "gabriel.poma", "4321", "EMPLEADO");

    //Mostramos la pantalla para iniciar sesion
    pantallaInicioSesion(ListaUsers);

    Empleado* headEmpleados = nullptr;
    Empleado* tailEmpleados = nullptr;

    int opcionPrincipal;

    do {
        system("cls");
        int anchoConsola = obtenerAnchoConsola();
        int x = anchoConsola / 2 - 20; 

        gotoxy(x, 2);
        cout << "--- Menú Principal ---\n";
        gotoxy(x, 4);
        cout << "1. Gestión de empleados\n";
        gotoxy(x, 5);
        cout << "2. Evaluación de empleados\n";
        gotoxy(x, 6);
        cout << "3. Asistencia de empleados\n";
        gotoxy(x, 7);
        cout << "4. Solicitudes\n";
        gotoxy(x, 8);
        cout << "5. Volver a iniciar sesion\n";
        gotoxy(x, 9);
        cout << "6. Salir\n";

        bool entradaValida = false;
        do {
            gotoxy(x, 12);
            cout << "Ingrese una opción: ";
            entradaValida = obtenerEntero(opcionPrincipal);
            if (!entradaValida || opcionPrincipal < 1 || opcionPrincipal > 6) {
                gotoxy(x, 14);
                cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
                gotoxy(x, 12);
                cout << string(50, ' '); 
            }
        } while (!entradaValida || opcionPrincipal < 1 || opcionPrincipal > 6);
        Empleado* empleado;
        switch (opcionPrincipal) {
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

                int opcionEvaluacion;
                do {
                    system("cls");
                    gotoxy(x, 2);
                    cout << "--- Menú de Evaluación de Empleados ---\n";
                    gotoxy(x, 4);
                    cout << "Empleado: " << empleado->nombre << " " << empleado->apellido << "\n";
                    gotoxy(x, 6);
                    cout << "1. Agregar evaluación\n";
                    gotoxy(x, 7);
                    cout << "2. Mostrar evaluaciones\n";
                    gotoxy(x, 8);
                    cout << "3. Volver al menú principal\n";

                    bool entradaValida = false;
                    do {
                        gotoxy(x, 10);
                        cout << "Ingrese una opción: ";
                        entradaValida = obtenerEntero(opcionEvaluacion);
                        if (!entradaValida || opcionEvaluacion < 1 || opcionEvaluacion > 3) {
                            gotoxy(x, 11);
                            cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
                            gotoxy(x, 10);
                            cout << string(50, ' '); 
                        }
                    } while (!entradaValida || opcionEvaluacion < 1 || opcionEvaluacion > 3);

                    switch (opcionEvaluacion) {
                        case 1:
                            agregarEvaluacion(empleado->pilaEvaluaciones);
                            break;
                        case 2:
                            mostrarEvaluacionesEmpleado(empleado->pilaEvaluaciones);
                            break;
                        case 3:
                            break;
                        default:
                            gotoxy(x, 12);
                            cout << "Opción inválida.\n";
                            system("pause");
                            break;
                    }
                } while (opcionEvaluacion != 3);
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
                gotoxy(x, 14);
                cout << "Ingrese el ID del empleado para registrar asistencia: ";
                cin>>id;
                empleado = buscarEmpleado(headEmpleados, id);
                if (empleado == nullptr) {
                    gotoxy(x,16);
                    cout << "Empleado con ID " << id << " no encontrado.\n";
                    getch();
                    break;
                }

                int opcionEvaluacion;
                do {
                    system("cls");
                    gotoxy(x, 2);
                    cout << "--- Asistencia ---\n";
                    gotoxy(x, 4);
                    cout << "Empleado: " << empleado->nombre << " " << empleado->apellido << "\n";
                    gotoxy(x, 5);
                    cout << "1. Agregar registro de asistencia\n";
                    gotoxy(x, 6);
                    cout << "2. Mostrar registro de asistencias\n";
                    gotoxy(x, 7);
                    cout << "3. Volver al menú principal\n";

                    bool entradaValida = false;
                    do {
                        gotoxy(x, 10);
                        cout << "Ingrese una opción: ";
                        entradaValida = obtenerEntero(opcionEvaluacion);
                        if (!entradaValida || opcionEvaluacion < 1 || opcionEvaluacion > 3) {
                            gotoxy(x, 11);
                            cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
                            gotoxy(x, 10);
                            cout << string(50, ' '); 
                        }
                    } while (!entradaValida || opcionEvaluacion < 1 || opcionEvaluacion > 3);

                    switch (opcionEvaluacion) {
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
                        default:
                            gotoxy(x, 12);
                            cout << "Opción inválida.\n";
                            system("pause");
                            break;
                    }
                } while (opcionEvaluacion != 3);
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

                int opcionSolicitud;
                do {
                    system("cls");
                    gotoxy(x, 2);
                    cout << "--- Menú de Solicitudes de Empleados ---\n";
                    gotoxy(x, 4);
                    cout << "Empleado: " << empleado->nombre << " " << empleado->apellido << "\n";
                    gotoxy(x, 6);
                    cout << "1. Enviar solicitud\n";
                    gotoxy(x, 7);
                    cout << "2. Mostrar solicitudes\n";
                    gotoxy(x, 8);
                    cout << "3. Volver al menú principal\n";

                    // Validar la opción ingresada por el usuario
                    bool entradaValida = false;
                    do {
                        gotoxy(x, 10);
                        cout << "Ingrese una opción: ";
                        entradaValida = obtenerEntero(opcionSolicitud);
                        if (!entradaValida || opcionSolicitud < 1 || opcionSolicitud > 3) {
                            gotoxy(x, 11);
                            cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
                            gotoxy(x, 10);
                            cout << string(50, ' ');  // Limpia la línea
                        }
                    } while (!entradaValida || opcionSolicitud < 1 || opcionSolicitud > 3);

                    // Ejecutar la opción seleccionada
                    switch (opcionSolicitud) {
                        case 1:
                            enviarSolicitud(empleado->colaSolicitudes);  // Agregar una nueva solicitud a la cola del empleado
                            break;
                        case 2:
                            mostrarSolicitudesEmpleado(empleado->colaSolicitudes);  // Mostrar las solicitudes del empleado
                            break;
                        case 3:
                            break;  // Salir al menú principal
                        default:
                            gotoxy(x, 12);
                            cout << "Opción inválida.\n";
                            system("pause");
                            break;
                    }
                } while (opcionSolicitud != 3);  // Volver al menú principal cuando se selecciona la opción 3
                break;
            }
            case 5: {
                LoginUser = false;
                pantallaInicioSesion(ListaUsers);
                break;
            }
            case 6:{
                gotoxy(x, 12);
                cout << "Saliendo del programa...\n";
                system("pause");
                break;
            }
            default:{
                gotoxy(x, 12);
                cout << "Opción inválida. Intente de nuevo.\n";
                system("pause");
                break;
            }
        }
    } while (opcionPrincipal != 6);


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
