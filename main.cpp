
#include <iostream>
#include "GestionEmpleados.h"
#include "Asistencia.h"
#include "EvaluacionEmpleado.h"
#include "InicioSesion.h"
#include "gotoxy.h"
#include <windows.h>

using namespace std;

int obtenerAnchoConsola();
bool obtenerEntero(int& numero);

int main() {

    SetConsoleOutputCP(CP_UTF8);

    //Inicio de sesion
    crearUsuario(PilaUsers, "david.aldana", "1234", "ADMINISTRADOR");
    crearUsuario(PilaUsers, "gabriel.poma", "4321", "EMPLEADO");

    //Mostramos la pantalla para iniciar sesion
    pantallaInicioSesion(PilaUsers);

    Empleado* listaEmpleados = nullptr;
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
        cout << "4. Volver a iniciar sesion\n";
        gotoxy(x, 8);
        cout << "5. Salir\n";

        bool entradaValida = false;
        do {
            gotoxy(x, 10);
            cout << "Ingrese una opción: ";
            entradaValida = obtenerEntero(opcionPrincipal);
            if (!entradaValida || opcionPrincipal < 1 || opcionPrincipal > 5) {
                gotoxy(x, 12);
                cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
                gotoxy(x, 10);
                cout << string(50, ' '); 
            }
        } while (!entradaValida || opcionPrincipal < 1 || opcionPrincipal > 5);
        Empleado* empleado;
        switch (opcionPrincipal) {
            case 1: {
                int continuar;
                do {
                    continuar = mostrarMenuGestionEmpleados(listaEmpleados);
                } while (continuar != 0);
                break;
            }
            case 2: {
                if (listaEmpleados == nullptr) {
                    gotoxy(x, 10);
                    cout << "No hay empleados registrados. Regrese al menú y agregue empleados primero.\n";
                    system("pause");
                    break;
                }
                int id;
                bool entradaValida = false;
                do {
                    gotoxy(x, 10);
                    cout << "Ingrese el ID del empleado para evaluar: ";
                    entradaValida = obtenerEntero(id);
                    if (!entradaValida) {
                        gotoxy(x, 11);
                        cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                        gotoxy(x, 10);
                        cout << string(50, ' ');
                    }
                } while (!entradaValida);

                empleado = buscarEmpleado(listaEmpleados, id);
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
            case 3: 
                if (listaEmpleados == nullptr) {
                    gotoxy(x, 12);
                    cout << "No hay empleados registrados. Regrese al menú y agregue empleados primero.\n";
                    getch();
                    break;
                }
                int id;
                gotoxy(x, 12);
                cout << "Ingrese el ID del empleado para registrar asistencia: ";
                cin>>id;
                empleado = buscarEmpleado(listaEmpleados, id);
                if (empleado == nullptr) {
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
                            getch();
                            break;
                    }
                } while (opcionEvaluacion != 3);
                break;
            case 4: 
                LoginUser = false;
                pantallaInicioSesion(PilaUsers);
                break;
            case 5:
                gotoxy(x, 12);
                cout << "Saliendo del programa...\n";
                getch();
                break;
            default:
                gotoxy(x, 12);
                cout << "Opción inválida. Intente de nuevo.\n";
                getch();
                break;
        }
    } while (opcionPrincipal != 5);


    Empleado* temp;
    while (listaEmpleados != nullptr) {
        temp = listaEmpleados;
        listaEmpleados = listaEmpleados->siguiente;


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
