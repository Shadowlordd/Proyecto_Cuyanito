#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct empleado {
    char tipo;
    int cod;
    char dni[9];
    char cuil[15];
    char nombres[40];
    char apellidos[40];
    struct empleado *siguiente;
};

struct empresa {
    int cod;
    char cuit[15];
    char nombreE[40];
    struct empresa *siguiente;
};

struct reparacion {
    int dispositivo;
    int codigoEmpleado;
    char fecha[11];
    float costoH;
    float costoS;
    char nombEmpresa[100];
    int codigoEmpresa;
    float precioFinal;
    struct reparacion *siguiente;
};
struct reparacion *headReparacion = NULL;
struct empleado *headEmpleado = NULL;
struct empresa *headEmpresa = NULL;
// Prototipos de funciones ---------------------------------------------------------------------------

void ingresarReparacion();
void buscarReparacionPorTipo();
void buscarReparacionMayorPrecio();
void mostrarReparacionesPorEmpleado();
void mostrarReparacionesPorEmpresa();
void mostrarReparacionesPorFecha();
void almacenarReparaciones();
void salir();
void cargarEmpleados();
void cargarEmpresas();
void imprimirEmpresas();
void imprimirEmpleados();
void liberarMemoriaEmpresas();

//cargar datod----------------------------------------------------------------
void cargarEmpleados() {
    FILE *archivo = fopen("empleados.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de empleados.\n");
        return;
    }

    struct empleado *nuevoEmpleado;
    while (1) {
        nuevoEmpleado = (struct empleado*) malloc(sizeof(struct empleado));
        if (fread(nuevoEmpleado, sizeof(struct empleado), 1, archivo) != 1) {
            free(nuevoEmpleado);
            break;
        }
        nuevoEmpleado->tipo = 'E'; //tip

        //Guardart
        FILE *archivoReparaciones = fopen("reparaciones.dat","ab");
        if (archivoReparaciones == NULL)
        {
            printf("Error al abrir el archivo de reparaciones.\n");
            free(nuevoEmpleado);
            break;
        }
        fwrite(nuevoEmpleado, sizeof(struct empleado), 1, archivoReparaciones);
        fclose(archivoReparaciones);

        nuevoEmpleado->siguiente = headEmpleado;
        headEmpleado = nuevoEmpleado;
    }

    fclose(archivo);
    printf("Empleados cargados con exito!!!!\n");
}
// cargar empresas......................................
void cargarEmpresas() {
    FILE *archivo = fopen("empresas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de empresas.\n");
        return;
    }

    struct empresa *nuevaEmpresa;
    while (1) {
        nuevaEmpresa = (struct empresa*) malloc(sizeof(struct empresa));
        if (fread(nuevaEmpresa, sizeof(struct empresa), 1, archivo) != 1) {
            free(nuevaEmpresa);
            break;
        }
        nuevaEmpresa->siguiente = headEmpresa;
        headEmpresa = nuevaEmpresa;
    }

    fclose(archivo);
    printf("Empresas cargadas con exito!!!!!!!\n");
}
// imprimir----------------------------------------------------
void imprimirEmpresas() {
    struct empresa *actual = headEmpresa;
    while (actual != NULL) {
        printf("Codigo: %d, CUIT: %s, Nombre: %s\n", actual->cod, actual->cuit, actual->nombreE);
        actual = actual->siguiente;
    }
}
void imprimirEmpleados() {
    struct empleado *actual = headEmpleado;
    while (actual != NULL) {
        printf("Codigo: %d, DNI: %s, CUIL: %s, Nombres: %s, Apellidos: %s\n",
               actual->cod, actual->dni, actual->cuil, actual->nombres, actual->apellidos);
        actual = actual->siguiente;
    }
}

void cargarReparaciones() {
    FILE *archivo = fopen("reparaciones.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de reparaciones.\n");
        return;
    }

    struct reparacion *nuevaReparacion;
    while (1) {
        nuevaReparacion = (struct reparacion*) malloc(sizeof(struct reparacion));
        if (fread(nuevaReparacion, sizeof(struct reparacion), 1, archivo) != 1) {
            free(nuevaReparacion);
            break;
        }
        nuevaReparacion->siguiente = headReparacion;
        headReparacion = nuevaReparacion;
    }

    fclose(archivo);
    printf("Reparaciones cargadas con exito!!!!!!!\n");
}






//------------------------------------------------------------------------------------------------------
int main() {
    int opcion;
    cargarEmpleados();
    cargarEmpresas();
    cargarReparaciones();

    do {
        printf("Menu de opciones\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("1. Ingresar Reparacion\n");
        printf("2. Buscar Reparacion por Tipo de Dispositivo\n");
        printf("3. Buscar Reparacion con Mayor Precio Final\n");
        printf("4. Mostrar Reparaciones por Empleado Especifico\n");
        printf("5. Mostrar Reparaciones por Empresa\n");
        printf("6. Mostrar Reparaciones por Fecha\n");
        printf("7. Almacenar Todas las Reparaciones\n");
        printf("8. Imprimir Empleados\n");
        printf("9. Imprimir Empresas\n");
        printf("10. Salir del Programa\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                ingresarReparacion();
                break;
            case 2:
                buscarReparacionPorTipo();
                break;
            case 3:
                buscarReparacionMayorPrecio();
                break;
            case 4:
                mostrarReparacionesPorEmpleado();
                break;
            case 5:
                mostrarReparacionesPorEmpresa();
                break;
            case 6:
                mostrarReparacionesPorFecha();
                break;
            case 7:
                almacenarReparaciones();
                break;
            case 8:
                imprimirEmpleados();
                break;
            case 9:
                imprimirEmpresas();
                break;
            case 10:
                salir();
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while(opcion != 10);

    return 0;
}
// FUNCIONES------------------------

  void ingresarReparacion() {
    struct reparacion *nuevaReparacion = (struct reparacion*) malloc(sizeof(struct reparacion));

    printf("Ingrese el tipo de dispositivo (0: PC, 1: Notebook, 2: Celular): ");
    scanf("%d", &nuevaReparacion->dispositivo);

    printf("Ingrese el codigo del empleado: ");
    scanf("%d", &nuevaReparacion->codigoEmpleado);

    printf("Ingrese la fecha (DD-MM-YYYY): ");
    scanf("%s", nuevaReparacion->fecha);

    printf("Ingrese el costo de hardware: ");
    scanf("%f", &nuevaReparacion->costoH);

    printf("Ingrese el costo de software: ");
    scanf("%f", &nuevaReparacion->costoS);

    printf("Ingrese el nombre de la empresa: ");
    scanf("%s", nuevaReparacion->nombEmpresa);

    printf("Ingrese el codigo de la empresa: ");
    scanf("%d", &nuevaReparacion->codigoEmpresa);

    nuevaReparacion->precioFinal = nuevaReparacion->costoH + nuevaReparacion->costoS;

    nuevaReparacion->siguiente = headReparacion;
    headReparacion = nuevaReparacion;

    // Guardar la reparación en el archivo
    FILE *archivo = fopen("reparaciones.dat", "ab");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de reparaciones.\n");
        return;
    }
    fwrite(nuevaReparacion, sizeof(struct reparacion), 1, archivo);
    fclose(archivo);

    printf("Reparacion ingresada con exito !!!!!!!!!!!!!!!!\n");
}



void buscarReparacionPorTipo() {
    int tipoDispositivo;
    printf("Ingrese el tipo de dispositivo a buscar (0: PC, 1: Notebook, 2: Celular): ");
    scanf("%d", &tipoDispositivo);

    struct reparacion *actual = headReparacion;
    while (actual != NULL) {
        if (actual->dispositivo == tipoDispositivo) {
            printf("Reparacion encontrada: Empleado %d, Fecha %s, Precio Final %.2f\n",
                   actual->codigoEmpleado, actual->fecha, actual->precioFinal);
        }
        actual = actual->siguiente;
    }
}


void buscarReparacionMayorPrecio() {
    if (headReparacion == NULL) {
        printf("No hay reparaciones registradas.\n");
        return;
    }

    struct reparacion *actual = headReparacion;
    struct reparacion *mayorPrecio = headReparacion;

    while (actual != NULL) {
        if (actual->precioFinal > mayorPrecio->precioFinal) {
            mayorPrecio = actual;
        }
        actual = actual->siguiente;
    }

    printf("Reparacion con mayor precio final: Empleado %d, Fecha %s, Precio Final %.2f\n",
           mayorPrecio->codigoEmpleado, mayorPrecio->fecha, mayorPrecio->precioFinal);
}


void mostrarReparacionesPorEmpleado() {
    int codigoEmpleado;
    printf("Ingrese el codigo del empleado: ");
    scanf("%d", &codigoEmpleado);

    FILE *archivo = fopen("reparaciones.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de reparaciones.\n");
        return;
    }

    int encontrado = 0;
    while (1) {
        char tipo;
        if (fread(&tipo, sizeof(char), 1, archivo) != 1) {
            break;
        }

        if (tipo == 'R') {
            struct reparacion reparacion;
            fread(&reparacion.dispositivo, sizeof(struct reparacion) - sizeof(char), 1, archivo);
            if (reparacion.codigoEmpleado == codigoEmpleado) {
                printf("Reparacion: Dispositivo %d, Fecha %s, Precio Final %.2f\n",
                       reparacion.dispositivo, reparacion.fecha, reparacion.precioFinal);
                encontrado = 1;
            }
        }
    }

    fclose(archivo);

    if (!encontrado) {
        printf("No se encontraron reparaciones para el empleado con codigo %d.\n", codigoEmpleado);
    }
}


// Errorrrrr cambiar los flotantes----------------------------------------------------------------------------------------------
void mostrarReparacionesPorEmpresa() {
    char nombreEmpresa[100];
    printf("Ingrese el nombre de la empresa: ");
    scanf("%s", nombreEmpresa);

    struct reparacion *actual = headReparacion;
    while (actual != NULL) {
        if (strcmp(actual->nombEmpresa, nombreEmpresa) == 0) {
            printf("Reparacion: Dispositivo %d, Empleado %d, Fecha %s, Precio Final %.2f\n",
                   actual->dispositivo, actual->codigoEmpleado, actual->fecha, actual->precioFinal);
        }
        actual = actual->siguiente;
    }
}


void mostrarReparacionesPorFecha() {
    char fecha[11];
    printf("Ingrese la fecha (DD-MM-YYYY): ");
    scanf("%s", fecha);

    struct reparacion *actual = headReparacion;
    while (actual != NULL) {
        if (strcmp(actual->fecha, fecha) == 0) {
            printf("Reparacion: Dispositivo %d, Empleado %d, Precio Final %.2f\n",
                   actual->dispositivo, actual->codigoEmpleado, actual->precioFinal);
        }
        actual = actual->siguiente;
    }
}


void almacenarReparaciones() {
    FILE *archivo = fopen("reparaciones.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    struct reparacion *actual = headReparacion;
    while (actual != NULL) {
        fwrite(actual, sizeof(struct reparacion), 1, archivo);
        actual = actual->siguiente;
    }

    fclose(archivo);
    printf("Reparaciones almacenadas con exito!!!!!!!!!!!!!!!!!!!!!\n");
}


void salir() {
    printf("Salir del Programa\n");
}
