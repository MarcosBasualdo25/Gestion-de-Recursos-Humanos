
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
string rol = "";

int main() {

    SetConsoleOutputCP(CP_UTF8);

    //Inicio de sesion
    crearUsuario(ListaUsers, "david.aldana", "1234", "ADMINISTRADOR",0);


    //Mostramos la pantalla para iniciar sesion
    rol = pantallaInicioSesion(ListaUsers);
    cin.ignore();

    Empleado* headEmpleados = nullptr;
    Empleado* tailEmpleados = nullptr;

    int opc;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    
while (true) {
        ocultarCursor();
        Empleado* empleado;
        string titulo = ".:MENÃš PRINCIPAL - " + rol + ":.";
        if (rol == "ADMINISTRADOR") {
            string opciones[] = {"1. GestiÃ³n de empleados", "2. EvaluaciÃ³n de empleados","3. Solicitudes", "4. Gestion de Proyectos","5. Volver a iniciar sesion","6. Salir"};   
            int n = 6;
            opc = menu(titulo, opciones, n);
            switch (opc) {
                case 1: {
                    string titulo = "--- MenÃº de GestiÃ³n de Empleados ---";
                    string opcionesEmpleado[] = {"1. Agregar empleado", "2. Mostrar empleados","3. Actualizar empleado", "4. Eliminar empleado","5. Volver al menÃº principal"};
                    int n = 5;
                    int opcEmpleado;
                    do {
                        ocultarCursor();
                        opcEmpleado = menu(titulo, opcionesEmpleado, n);
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
                                        cout << "Entrada no aceptada. Por favor, ingrese un nÃºmero entero.";
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
                                        cout << "Entrada no aceptada. Por favor, ingrese un nÃºmero entero.";
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
                        cout << "No hay empleados registrados. Regrese al menÃº y agregue empleados primero.\n";
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
                            cout << "Entrada no aceptada. Por favor, ingrese un nÃºmero entero.";
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
                    string opcionesEva[] = {"1. Agregar evaluaciÃ³n", "2. Mostrar evaluaciones", "3. Volver al menÃº principal"};
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
                            cout << "Entrada no aceptada. Por favor, ingrese un nÃºmero entero.";
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
            string opciones[] = {"1. EvaluaciÃ³n de empleado", "2. Asistencia de empleado","3. Solicitudes","4. Volver a iniciar sesion","5. Salir"};
            int n = 5;
            opc = menu(titulo, opciones, n);
            switch (opc) {
                case 1: {
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
                        cout << "Ingrese el ID del empleado para evaluar: ";
                        entradaValida = obtenerEntero(id);
                        if (!entradaValida) {
                            gotoxy(x, 15);
                            cout << "Entrada no aceptada. Por favor, ingrese un nÃºmero entero.";
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
                        cout << "No hay empleados registrados. Regrese al menÃº y agregue empleados primero.\n";
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
                            cout << "Entrada no aceptada. Por favor, ingrese un nÃºmero entero.";
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
                    string opcionesAsistencia[] = {"1. Agregar registro de asistencia", "2. Mostrar registro de asistencia", "3. Volver al menÃº principal"};
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
                        cout << "No hay empleados registrados. Regrese al menÃº y agregue empleados primero.\n";
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
                            cout << "Entrada no aceptada. Por favor, ingrese un nÃºmero entero.";
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
                    string opcionesSolicitud[] = {"1. Enviar solicitud", "2. Mostrar solicitudes", "3. Eliminar solicitud",  "4. Volver al menÃº principal"};
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

int menu(string titulo, string opciones[], int n){
    system("color 70");

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