#pragma once

#include <iostream>
#include <iomanip>
#include "GestionEmpleados.h"
#include "Asistencia.h"
#include "EvaluacionEmpleado.h"
#include "gotoxy.h"

using namespace std;

// Función para mostrar el menú de vista del empleado
void menuEmpleado(Empleado* empleado) {
    system("cls");
    int opcion;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    do {
        system("cls");
        gotoxy(x, 2);
        cout << "--- Menú del Empleado ---\n";
        gotoxy(x, 4);
        cout << "1. Ver Datos Personales\n";
        gotoxy(x, 5);
        cout << "2. Ver Evaluaciones\n";
        gotoxy(x, 6);
        cout << "3. Ver Asistencias\n";
        gotoxy(x, 7);
        cout << "4. Salir\n";

        gotoxy(x, 9);
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                mostrarDatosPersonales(empleado);
                break;
            case 2:
                mostrarEvaluacionesEmpleado(empleado->pilaEvaluaciones);
                break;
            case 3:
                imprimirRegistros(empleado->pilaAsistencias);
                break;
            case 4:
                gotoxy(x, 11);
                cout << "Saliendo del menú del empleado...\n";
                system("pause");
                break;
            default:
                gotoxy(x, 11);
                cout << "Opción inválida. Intente nuevamente.\n";
                system("pause");
                break;
        }
    } while (opcion != 4);
}

// Función para mostrar datos personales del empleado
void mostrarDatosPersonales(Empleado* empleado) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    gotoxy(x, 2);
    cout << "--- Datos Personales ---\n";
    gotoxy(x, 4);
    cout << "ID: " << empleado->idEmpleado << "\n";
    gotoxy(x, 5);
    cout << "Nombre: " << empleado->nombre << " " << empleado->apellido << "\n";
    gotoxy(x, 6);
    cout << "Puesto: " << empleado->puesto << "\n";

    gotoxy(x, 8);
    cout << "Presione cualquier tecla para volver al menú.\n";
    system("pause");
}
