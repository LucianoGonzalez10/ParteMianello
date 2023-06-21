#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include "gotoxy.h"
#include "Usuarios.h"



int menu();
usuario switchMenu (int opcion, char nombre[], char archivo[]);
int Menu2 ();
void switch2 (int opcion, int*dia, int*mes, char nombre[],usuario Nuevo, char archivo[], char nombreProductos[]);

int main()
{

    char nombreProductos[20];
    strcpy(nombreProductos, "productos.bin");
    usuario Nuevo;
    int num=0;
    char nombre[20]="Usuarios";
    char archivo[20]="turnos.bin";
    int mes=0;
    int dia=0;
    int opcion;
    int opcion2;
    opcion=menu();

    system("cls");
    Nuevo=switchMenu(opcion,nombre, archivo);

    opcion2=Menu2();
    switch2(opcion2, &dia, &mes, nombre,Nuevo, archivo, nombreProductos);


    return 0;
}
int menu()
{
    system("color 3F");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("                                             SPA DIBU                                                      \n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    int opcion;
    printf("Ingrese que quiere realizar\n");
    printf("---------------------------------\n");
    printf("1-Iniciar sesion\n");
    printf("---------------------------------\n");
    printf("2-Registrarse\n");
    printf("---------------------------------\n");
    printf("3-Iniciar como administrador\n");
    printf("---------------------------------\n");
    printf("4-Cargar Nuevo año\n");
    printf("---------------------------------\n");
    scanf("%i",&opcion);
    while(opcion!=1&&opcion!=2&&opcion!=3 &&opcion!=4)
    {
        printf("Ingrese una opcion valida: \n");
        scanf("%i",&opcion);
    }
    return opcion;

}
usuario switchMenu (int opcion, char nombre[], char archivo[])
{
    usuario Nuevo;
    switch(opcion)
    {

    case 1:
        ;
        system("color 3F");
        Nuevo=IniciarSesion(nombre);


        break;
    case 2:
        ;
        system("color 3F");
        Nuevo=RegistrarUsuario(nombre);

        break;

    case 4:
        cargarTurnos(archivo);
        break;
    default:
        printf("Ingrese una opcion valida\n");
        break;
    }

    return Nuevo;

}





int Menu2 ()
{
    system("color 3F");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("                                             SPA DIBU                                                      \n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    int opcion;
    printf("1-Estado de usuario\n");
    printf("2-Ver servicios y productos\n");
    printf("3-Modificar usuario\n");
    printf("4-Solicitar turno\n");
    scanf("%i",&opcion);
    while(opcion!=1&&opcion!=2&&opcion!=3 &&opcion!=4)
    {
        printf("Ingrese una opcion valida: \n");
        scanf("%i",&opcion);
    }
    return opcion;


}
void switch2 (int opcion, int*dia, int*mes, char nombre[],usuario Nuevo, char archivo[], char nombreProductos[])
{
    switch(opcion)
    {
    case 1:

        system("cls");
        system("color 3F");
        ModificarEstado (nombre,Nuevo);
        break;
    case 2:
        mostrarArchivoo(nombreProductos);
        comprarProducto(nombreProductos);
        break;
    case 3:
        system("cls");
        system("color 3F");
        ModificarUsuario(nombre,Nuevo);
        break;

    case 4:
        system("cls");
        *dia=solicitarTurno(archivo, mes);
        break;
    }
}










