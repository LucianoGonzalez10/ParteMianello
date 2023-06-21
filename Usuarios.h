#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include "Usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include "gotoxy.h"

typedef struct
{
    char nombre[20];
    char contrasenia[20];
    int nroUsuario;
    int DiaTurno[2];
    char servicioAdquirido[30];                                                ///Estructura usuarios
    char EmpleadoDeServicio[30];
    int precioTotal;
    char estado[20];
} usuario;


typedef struct{
    char dia[7][10];
    int turno [4][7];
}turnoMensuales;

typedef struct{
    char mes[20];
    turnoMensuales turnos;
}turnosAnuales;

typedef struct
{
    char nombre[20];
    char descripcion[300];
    int precio;
    int stock;
} stProducto;

void cargarTurnos(char nombre[]);
void cargarSemana (turnosAnuales turnosGenerales[], int dimension);
void cargarMes(turnosAnuales turnosGenerales[]);
int mostrarTurnos (char nombre[]);
void leerArchivo (char nombre[],turnosAnuales turnito[], int dimension);
void mostrarFecha(turnosAnuales turnito);
int solicitarTurno (char nombre[], int*mes);
void funcionDividir(int dia, turnosAnuales turnito[], int q);
void restarTurno (int dia, int i, turnosAnuales turnito[], int q);
usuario RegistrarUsuario (char nombre[]);
void EscribirUsuario (usuario Usuario1, char nombre[]);
int RecorrerArchivos (char nombre[], usuario Usuario); ///Verifica la existencia del nombre de usuario
usuario IniciarSesion (char nombre[]);
int RecorrerContrasenia (char nombre[], usuario Nuevo);
void ModificarEstado (char nombre[],usuario Nuevo);
void EscribirElEstado (char nombre [], usuario Nuevo);
usuario ModificarUsuario (char nombre[],usuario Nuevo);
usuario ModificarNombre (char nombre[], usuario Nuevo);
usuario ModificarContrasenia (char nombre[],usuario Nuevo);
usuario EscribirNombre (char nombre[],usuario Nuevo,usuario Aux);
usuario EscribirContrasenia (char nombre[],usuario Nuevo, usuario Aux);
usuario UsuarioEnUso (usuario nuevo, char nombre []);
int NumeroUsuario (char nombre[]);
void MostrarUsuario (usuario nuevo);
void mostrarArchivo (char nombre[]);
stProducto cargarProductos();
void cargarArchivos(char nombreProductos[]);
void mostrarArchivoo(char nombreProductos[]);
void comprarProducto(char nombreProductos[]);
void cobrarConTarjeta();






#endif // USUARIOS_H_INCLUDED
