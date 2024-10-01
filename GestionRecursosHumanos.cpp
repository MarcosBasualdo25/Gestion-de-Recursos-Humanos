
#include <iostream>
#include "GestionEmpleados.h"
#include "EvaluacionEmpleado.h"
#include "gotoxy.h"
#include <windows.h>

using namespace std;

// Declaración de obtenerAnchoConsola si no está en los headers
int obtenerAnchoConsola();
// Declaración de obtenerEntero si no está en los headers
bool obtenerEntero(int& numero);

int main() {
    // Configuración para soportar caracteres acentuados
    SetConsoleOutputCP(CP_UTF8);

    Empleado* listaEmpleados = nullptr;
    int opcionPrincipal;

    do {
        system("cls");
        int anchoConsola = obtenerAnchoConsola();
        int x = anchoConsola / 2 - 20; // Posición X centrada

        gotoxy(x, 2);
        cout << "--- Menú Principal ---\n";
        gotoxy(x, 4);
        cout << "1. Gestión de empleados\n";
        gotoxy(x, 5);
        cout << "2. Evaluación de empleados\n";
        gotoxy(x, 6);
        cout << "3. Salir\n";

        bool entradaValida = false;
        do {
            gotoxy(x, 8);
            cout << "Ingrese una opción: ";
            entradaValida = obtenerEntero(opcionPrincipal);
            if (!entradaValida || opcionPrincipal < 1 || opcionPrincipal > 3) {
                gotoxy(x, 9);
                cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
                gotoxy(x, 8);
                cout << string(50, ' '); // Limpia la línea
            }
        } while (!entradaValida || opcionPrincipal < 1 || opcionPrincipal > 3);

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
                        cout << string(50, ' '); // Limpia la línea
                    }
                } while (!entradaValida);

                Empleado* empleado = buscarEmpleado(listaEmpleados, id);
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
                            cout << string(50, ' '); // Limpia la línea
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
                gotoxy(x, 10);
                cout << "Saliendo del programa...\n";
                system("pause");
                break;
            default:
                gotoxy(x, 10);
                cout << "Opción inválida. Intente de nuevo.\n";
                system("pause");
                break;
        }
    } while (opcionPrincipal != 3);

    // Liberar memoria
    Empleado* temp;
    while (listaEmpleados != nullptr) {
        temp = listaEmpleados;
        listaEmpleados = listaEmpleados->siguiente;

        // Liberar la pila de evaluaciones
        if (temp->pilaEvaluaciones != nullptr) {
            Evaluacion* evalTemp;
            while (temp->pilaEvaluaciones->cima != nullptr) {
                evalTemp = temp->pilaEvaluaciones->cima;
                temp->pilaEvaluaciones->cima = temp->pilaEvaluaciones->cima->siguiente;
                delete evalTemp;
            }
            delete temp->pilaEvaluaciones;
        }

        delete temp;
    }

    return 0;
}
