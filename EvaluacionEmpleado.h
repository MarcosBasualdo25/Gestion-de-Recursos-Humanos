
#pragma once

#include <iostream>
#include <string>
#include "GestionEmpleados.h"
#include "gotoxy.h"
#include <limits> 

using namespace std;

// Funciones para manejar evaluaciones
void agregarEvaluacion(PilaEvaluaciones*& pila);
void mostrarEvaluacionesEmpleado(PilaEvaluaciones* pila);

// Implementación de funciones

inline void agregarEvaluacion(PilaEvaluaciones*& pila) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 

    gotoxy(x, 2);
    cout << "--- Agregar Evaluación ---\n";

    string comentario;
    int calificacion;

    gotoxy(x, 4);
    cout << "Ingrese el comentario de la evaluación: ";
    getline(cin, comentario);

    bool entradaValida = false;
    do {
        gotoxy(x, 5);
        cout << "Ingrese la calificación (0-10): ";
        entradaValida = obtenerEntero(calificacion);
        if (!entradaValida || calificacion < 0 || calificacion > 10) {
            gotoxy(x, 6);
            cout << "Entrada no aceptada. Por favor, ingrese un número entre 0 y 10.";
            gotoxy(x, 5);
            cout << string(50, ' '); 
        }
    } while (!entradaValida || calificacion < 0 || calificacion > 10);

    Evaluacion* nuevaEvaluacion = new Evaluacion();
    nuevaEvaluacion->comentario = comentario;
    nuevaEvaluacion->calificacion = calificacion;
    nuevaEvaluacion->siguiente = nullptr;

    if (pila == nullptr) {
        pila = new PilaEvaluaciones();
        pila->cima = nullptr;
    }

    // Apilar la nueva evaluación
    nuevaEvaluacion->siguiente = pila->cima;
    pila->cima = nuevaEvaluacion;

    gotoxy(x, 8);
    cout << "Evaluación agregada exitosamente.\n";
    system("pause");
}

inline void mostrarEvaluacionesEmpleado(PilaEvaluaciones* pila) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30; 

    gotoxy(x, 2);
    cout << "--- Evaluaciones del Empleado ---\n";

    if (pila == nullptr || pila->cima == nullptr) {
        gotoxy(x, 4);
        cout << "No hay evaluaciones para este empleado.\n";
    } else {
        Evaluacion* actual = pila->cima;
        int numeroEvaluacion = 1;
        int y = 4;
        int sumaCalificaciones = 0;
        int totalEvaluaciones = 0;

        while (actual != nullptr) {
            gotoxy(x, y++);
            if (actual == pila->cima) {
                cout << "Evaluación #" << numeroEvaluacion << " (Más reciente):";
            } else {
                cout << "Evaluación #" << numeroEvaluacion << ":";
            }
            gotoxy(x, y++);
            cout << "Calificación: " << actual->calificacion << "/10";
            gotoxy(x, y++);
            cout << "Comentario: " << actual->comentario;
            gotoxy(x, y++);
            cout << "-------------------------";
            sumaCalificaciones += actual->calificacion;
            totalEvaluaciones++;
            actual = actual->siguiente;
            numeroEvaluacion++;
            y++; 
        }

        // Calcular y mostrar el promedio
        double promedio = static_cast<double>(sumaCalificaciones) / totalEvaluaciones;
        gotoxy(x, y++);
        cout << "Promedio de calificaciones: " << promedio << "/10";
    }
    cout << "\n";
    system("pause");
}
