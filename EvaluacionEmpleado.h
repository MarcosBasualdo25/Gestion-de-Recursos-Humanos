
#pragma once

#include <iostream>
#include <string>
#include "GestionEmpleados.h"
#include "gotoxy.h"
#include <limits> 
#include <iomanip>

using namespace std;

// Funciones para manejar evaluaciones
void agregarEvaluacion(PilaEvaluaciones*& pila);
void mostrarEvaluacionesEmpleado(PilaEvaluaciones* pila);

// Implementación de funciones

inline void agregarEvaluacion(PilaEvaluaciones*& pila) {
    system("cls");
    system("color 70"); // Fondo gris claro, texto negro
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 40; // Centrar la interfaz

    // Cuadro para el título
    color(113); // Texto azul sobre fondo gris claro
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                           AGREGAR EVALUACIÓN                               ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    color(112); // Texto negro sobre fondo gris claro

    string comentario;
    int calificacion;
    bool entradaValida = false;

    // Cuadro para el comentario
    gotoxy(x, 6);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 7);
    cout << "║ Ingrese el comentario de la evaluación:                                    ║";
    gotoxy(x, 8);
    cout << "║                                                                            ║";
    gotoxy(x, 9);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";

    // Entrada del comentario
    do {
        gotoxy(x + 4, 8);
        getline(cin, comentario);
        if (comentario.empty()) {
            gotoxy(x + 4, 10);
            color(124); // Texto rojo sobre fondo gris claro
            cout << "Error: El comentario no puede estar vacío. Por favor, ingréselo.";
            color(112); // Regresar a texto negro
        }
    } while (comentario.empty());

    // Cuadro para la calificación
    gotoxy(x, 12);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 13);
    cout << "║ Ingrese la calificación (0-10):                                            ║";
    gotoxy(x, 14);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";

    // Validar la entrada de la calificación
    do {
        gotoxy(x + 34, 13);
        entradaValida = obtenerEntero(calificacion);
        if (!entradaValida || calificacion < 0 || calificacion > 10) {
            gotoxy(x + 4, 15);
            color(124); // Texto rojo sobre fondo gris claro
            cout << "Error: Entrada no válida. Ingrese un número entre 0 y 10.";
            gotoxy(x + 4, 13);
            cout << string(50, ' '); // Limpia la línea de entrada
            color(112); // Regresar a texto negro
        }
    } while (!entradaValida || calificacion < 0 || calificacion > 10);

    // Crear y apilar la evaluación
    Evaluacion* nuevaEvaluacion = new Evaluacion();
    nuevaEvaluacion->comentario = comentario;
    nuevaEvaluacion->calificacion = calificacion;
    nuevaEvaluacion->siguiente = nullptr;

    if (pila == nullptr) {
        pila = new PilaEvaluaciones();
        pila->cima = nullptr;
    }

    nuevaEvaluacion->siguiente = pila->cima;
    pila->cima = nuevaEvaluacion;

    // Mensaje de confirmación
    color(114); // Texto verde sobre fondo gris claro
    gotoxy(x, 17);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 18);
    cout << "║                  Evaluación agregada exitosamente.                         ║";
    gotoxy(x, 19);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    color(112); // Regresar a texto negro

    getch();
}


void mostrarEvaluacionesEmpleado(PilaEvaluaciones* pila) {
    system("cls");
    system("color 70");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 40;  // Centrar tabla
    
    double suma = 0;
    int contador = 0;
    if (pila != nullptr) {
        Evaluacion* actual = pila->cima;
        while (actual != nullptr) {
            suma += actual->calificacion;
            contador++;
            actual = actual->siguiente;
        }
    }
    double promedio = (contador > 0) ? suma / contador : 0;

    color(113);
    // Cuadro para el título
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                     EVALUACIONES DEL EMPLEADO -                            ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    gotoxy(x+52,3);
    cout << promedio;
    color(112);
    // Espaciado entre el título y la tabla
    gotoxy(x, 6);

    // Cuadro para la tabla
    cout << "╔═══════╦═════════════════╦══════════════════════════════════════════════════╗";
    gotoxy(x, 7);
    cout << "║  No.  ║   Calificación  ║                    Comentario                    ║";
    gotoxy(x, 8);
    cout << "╠═══════╬═════════════════╬══════════════════════════════════════════════════╣";

    if (pila == nullptr || pila->cima == nullptr) {
        gotoxy(x, 9);
        cout << "║                         No hay evaluaciones disponibles.                   ║";
        gotoxy(x, 10);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    } else {
        Evaluacion* actual = pila->cima;
        int i = 1, y = 9;

        // Iterar sobre la pila
        while (actual != nullptr) {
            gotoxy(x, y++);
            cout << "║ " << setw(5) << left << i++
                 << " ║ " << setw(15) << centerText(to_string(actual->calificacion) + "/10", 15)
                 << " ║ " << setw(48) << centerText(actual->comentario, 48) << " ║";

            actual = actual->siguiente;

            // Si hay más evaluaciones, dibujar separador
            if (actual != nullptr) {
                gotoxy(x, y++);
                cout << "╠═══════╬═════════════════╬══════════════════════════════════════════════════╣";
            }
        }

        // Dibujar el pie de la tabla
        gotoxy(x, y);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    }
    getch();
}
