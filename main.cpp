
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
int obtenerAltoConsola();
bool obtenerEntero(int& numero);
int menu(string titulo, string opciones[], int n);
int menuAdministrador(string titulo, string opciones[], int n);

string rol = "";

int main() {
    SetConsoleOutputCP(CP_UTF8);

    //Inicio de sesion
    crearUsuario(ListaUsers, "david.aldana", "1234", "ADMINISTRADOR",0);


    //Mostramos la pantalla para iniciar sesion
    rol = pantallaInicioSesion(ListaUsers);
    cin.ignore();
    getch();

    Empleado* headEmpleados = nullptr;
    Empleado* tailEmpleados = nullptr;

    int opc;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    
while (true) {
        ocultarCursor();
        Empleado* empleado;
        string titulo = "";
        if (rol == "ADMINISTRADOR") {

            string opciones[] = {"1. Gestión de empleados", "2. Evaluación de empleados","3. Solicitudes", "4. Gestion de Proyectos","5. Volver a iniciar sesión","6. Salir"};   
            int n = 6;
            opc = menu("MENU PRINCIPAL ADMINISTRADOR", opciones, n);
            switch (opc) {
                case 1: {
                    string opcionesEmpleado[] = {"1. Agregar empleado", "2. Mostrar empleados","3. Actualizar empleado", "4. Eliminar empleado","5. Volver al menú principal"};
                    int n = 5;
                    int opcEmpleado;
                    do {
                        ocultarCursor();
                        opcEmpleado = menu("Gestion de Empleados", opcionesEmpleado, n);
                        switch (opcEmpleado) {
                            case 1: {
                                mostrarCursor();
                                crearYAgregarEmpleado(headEmpleados, tailEmpleados);
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
                                actualizarEmpleado(headEmpleados, tailEmpleados, id);
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
                    } while (opcEmpleado != 5);
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
                    string tituloEva = "Evaluaciones de " + empleado->nombre + " " + empleado->apellido;
                    string opcionesEva[] = {"1. Agregar evaluación", "2. Mostrar evaluaciones", "3. Volver al menú principal"};
                    int opcEvaluacion = 3;
                    do {
                        mostrarCursor();
                        opcEvaluacion = menu(tituloEva, opcionesEva, 3);
                        switch (opcEvaluacion) {
                            case 1:
                                agregarEvaluacion(empleado->pilaEvaluaciones);
                                break;
                            case 2:
                                mostrarEvaluacionesEmpleado(empleado->pilaEvaluaciones);
                                break;
                            case 3:
                                break;
                        }
                    } while (opcEvaluacion != 3);
                    break;
                }
                case 3: {
                    if (headEmpleados == nullptr) {
                        gotoxy(x, 14);
                        cout << "No hay empleados registrados. Regrese al menÃº y agregue empleados primero.\n";
                        system("pause");
                        break;
                    }
                    int id;
                    bool entradaValida = false;
                    do {
                        mostrarCursor();
                        gotoxy(x, 14);
                        cout << "Ingrese el ID del empleado para gestionar solicitudes: ";
                        entradaValida = obtenerEntero(id);
                        if (!entradaValida) {
                            gotoxy(x, 15);
                            cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                            gotoxy(x, 14);
                            cout << string(50, ' ');  // Limpia la lÃ­nea
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
                    atenderSolicitud(empleado->colaSolicitudes);
                    break;
                }
                case 4: {
                    //Por hacer
                    break;
                }
                case 5: {
                    LoginUser = false;
                    rol = pantallaInicioSesion(ListaUsers);
                    break;
                }
                case 6: {
                    gotoxy(x, 12);
                    cout << "Saliendo del programa...\n";
                    system("pause");
                    return 0;
                }
            }
        } else {
            string opciones[] = {"1. Evaluación de empleado", "2. Asistencia de empleado","3. Solicitudes","4. Volver a iniciar sesión","5. Salir"};
            int n = 5;
            opc = menu("MENU PRINCIPAL - EMPLEADO", opciones, n);
            switch (opc) {
                case 1: {
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
                    mostrarCursor();
                    mostrarEvaluacionesEmpleado(empleado->pilaEvaluaciones);
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
                    int opcAsistencia;
                    do {
                        opcAsistencia = menu(titulo, opcionesAsistencia, n);
                        switch (opcAsistencia) {
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
                    } while (opcAsistencia != 3);
                    break;
                }
                case 3: {
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
                            cout << string(50, ' ');  // Limpia la lÃ­nea
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
                    string opcionesSolicitud[] = {"1. Enviar solicitud", "2. Mostrar solicitudes", "3. Eliminar solicitud",  "4. Volver al menú principal"};
                    n = 4;
                    int opcSolicitud;
                    do {
                        opcSolicitud = menu(titulo, opcionesSolicitud, n);
                        switch (opcSolicitud) {
                            case 1:
                                mostrarCursor();
                                enviarSolicitud(empleado->colaSolicitudes);
                                break;
                            case 2:
                                mostrarSolicitudesEmpleado(empleado->colaSolicitudes);
                                break;
                            case 3:
                                eliminarSolicitud(empleado->colaSolicitudes);
                                break;
                            case 4:
                                break;
                        }
                    } while (opcSolicitud != 4);
                    break;
                }
                case 4: {
                    LoginUser = false;
                    rol = pantallaInicioSesion(ListaUsers);
                    getch();
                    break;
                }
                case 5: {
                    gotoxy(x, 12);
                    cout << "Saliendo del programa...\n";
                    system("pause");
                    return 0;
                }
            }
        }
    }    

    return 0;
}

int menu(string titulo, string opciones[], int n) {
    system("color 70");
    int opcion = 1, tecla;
    bool repite = true;

    do {
        system("cls");

        // Dimensiones de la consola
        int ancho = obtenerAnchoConsola();
        int alto = obtenerAltoConsola();

        // Calcular posición del marco y contenido
        int x = (ancho - 40) / 2; // Centrar el marco horizontalmente
        int y = (alto)/10; // Centrar el marco verticalmente

        // Dibujar marco superior
        gotoxy(x, y);     cout << "╔══════════════════════════════════════════╗";

        // Ajuste del título dentro del marco
        int espaciosTotales = 42 - (titulo.length());
        int espacioIzq = espaciosTotales / 2;
        int espacioDer = espaciosTotales - espacioIzq;

        gotoxy(x, y + 1);
        cout << "║" << string(espacioIzq, ' ') <<titulo << string(espacioDer, ' ') << "║";

        gotoxy(x, y + 2); cout << "╠══════════════════════════════════════════╣";

        // Espacios interiores para las opciones
        for (int i = 0; i < n * 2; i++) {
            gotoxy(x, y + 3 + i);
            cout << "║" << string(38, ' ') << "    ║";
        }

        // Marco inferior
        gotoxy(x, y + 3 + n * 2); cout << "╚══════════════════════════════════════════╝";

        // Mostrar opciones y flecha
        for (int i = 0; i < n; i++) {
            gotoxy(x + 3, y + 3 + i * 2);
            if (i + 1 == opcion) {
                color(113); //Le da color a la opcion seleccionada
                cout << "➤   " << opciones[i];
                color(112);
            } else {
                cout << "     " << opciones[i];
            }
        }

        // Detectar teclas
        do {
            tecla = getch();
        } while (tecla != 72 && tecla != 80 && tecla != 13); // Teclas: arriba (72), abajo (80), enter (13)

        // Cambiar opción según la tecla
        switch (tecla) {
            case 72: // Flecha hacia arriba
                opcion--;
                if (opcion < 1) opcion = n;
                break;
            case 80: // Flecha hacia abajo
                opcion++;
                if (opcion > n) opcion = 1;
                break;
            case 13: // Enter
                repite = false;
                break;
        }
    } while (repite);

    return opcion;
}

//Menu personalizado para administrador (PRUEBA)
int menuAdministrador(string titulo, string opciones[], int n){
    system("color 70");

    int opcion = 1;
    int tecla;
    bool repite = true;
    int longitud = titulo.length();
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    do{
        system("cls");
        
        gotoxy(x, 1);
        cout<<"╔══════════════════════════════════════╗";
        gotoxy(x,2);
        cout<<"║    MENÚ PRINCIPAL - ADMINISTRADOR    ║";
        gotoxy(x,3);
        cout<<"╠══════════════════════════════════════╣";  
        for(int i=0; i<=12; i++){
            gotoxy(x, 4 + i);
            cout<<"║                                      ║";
            if(i == 12){
                gotoxy(x, 4 + (i+1));
                cout<<"╚══════════════════════════════════════╝";
            }
        }     

        gotoxy(x+2,5+(opcion - 1) * 2); cout<<"➤";
        for(int i=0;i<n;i++){
            gotoxy(x + 6,5+2*i); cout<<opciones[i];
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
