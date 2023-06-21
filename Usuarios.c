
#include "Usuarios.h"

usuario RegistrarUsuario (char nombre[])
{
    usuario UsuarioNuevo;
    int num;
    printf("Ingrese el nombre del usuario: \n");
    fflush(stdin);
    gets(UsuarioNuevo.nombre);
    int A;
    A=RecorrerArchivos(nombre,UsuarioNuevo);
    while(A!=-1)
    {
        printf("Ese nombre de usuario ya existe, ingrese otro: \n");
        fflush(stdin);                                                  ///Permite registrar usuario
        gets(UsuarioNuevo.nombre);
        A=RecorrerArchivos(nombre,UsuarioNuevo);
    }
    printf("Ingrese una contraseña: \n");
    gets(UsuarioNuevo.contrasenia);
    strcpy(UsuarioNuevo.estado,"Activo");
    UsuarioNuevo.nroUsuario=NumeroUsuario(nombre);
    EscribirUsuario(UsuarioNuevo,nombre);

    return UsuarioNuevo;
}
void EscribirUsuario (usuario Usuario1, char nombre[])
{
    FILE * archi=fopen(nombre,"ab");
    if(archi)
    {
        fwrite(&Usuario1,sizeof(usuario),1,archi);                             ///Escribe en el archivo el nuevo usuario
        fclose(archi);
    }
    else
    {
        printf("El archivo no pudo abrirse:(\n");
    }
}
int RecorrerArchivos (char nombre[], usuario Usuario)
{
    usuario Aux;
    int pos=-1;
    int i=0;
    FILE * archi=fopen(nombre,"rb");
    if (archi)
    {
        while (pos==-1&&(fread(&Aux,sizeof(usuario),1,archi))>0)               ///Busca la existencia de un usuario, retorna su posicion en caso de encontrarlo
        {
            i++;
            if(strcmp(Usuario.nombre,Aux.nombre)==0)
            {
                pos=i;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("El archivo no pudo abrirse:(\n");
    }
    return pos;

}
usuario IniciarSesion (char nombre[])
{
    usuario Nuevo;
    int i;
    int cont=0;
    char opcion[10];
    int flag;

    printf("Ingrese su usuario: \n");
    fflush(stdin);
    gets(Nuevo.nombre);
    i=RecorrerArchivos(nombre,Nuevo);

    while(i<0)
    {
        printf("Ese usuario no existe, ingrese otro: \n");
        fflush(stdin);
        gets(Nuevo.nombre);
        i=RecorrerArchivos(nombre,Nuevo);
        cont=cont+1;


        if(cont==5)
        {
            printf("Usted ha usado muchos intentos. Desea crear un nuevo usuario?");  ///Inicia sesion y retorna el usuario en uso
            gets(opcion);
            if(strcmpi(opcion,"Si")==0)
            {
                Nuevo=RegistrarUsuario(nombre);
            }
        }
    }



    printf("Ingrese su contraseña: \n");
    fflush(stdin);
    gets(Nuevo.contrasenia);
    flag=RecorrerContrasenia(nombre,Nuevo);

    while(flag<1)
    {
        printf("Ingrese una contraseña correcta: \n");
        fflush(stdin);
        gets(Nuevo.contrasenia);
        flag=RecorrerContrasenia(nombre,Nuevo);
    }
    Nuevo=UsuarioEnUso(Nuevo,nombre);




    return Nuevo;
}
int RecorrerContrasenia (char nombre[], usuario Nuevo)
{
    FILE * buffer=fopen(nombre,"rb");
    usuario comparar;
    int flag=0;
    int flag2=0;
    if (buffer)
    {
        while(flag==0&&(fread(&comparar,sizeof(usuario),1,buffer))>0)                 ///Verifica que la contraseña sea correcta
        {
            if(strcmp(Nuevo.nombre,comparar.nombre)==0)
            {
                flag=1;
            }
        }
        if(strcmp(Nuevo.contrasenia,comparar.contrasenia)==0)
        {
            flag2=1;
        }
        fclose(buffer);
    }
    else
    {
        printf("El archivo no pudo abrirse:(\n");
    }
    return flag2;


}
void ModificarEstado (char nombre[],usuario Nuevo)
{
    char opcion[10];
    system("cls");
    system("color 3F");
    printf("Su estado es: %s\n",Nuevo.estado);
    if(strcmpi(Nuevo.estado,"Activo")==0)
    {
        printf("Desea darse de baja? Si pone no, volvera al menu anterior\n");
        fflush(stdin);
        gets(opcion);
        while((strcmpi(opcion,"si"))!=0&&(strcmpi(opcion,"no")!=0))
        {
            printf("Ingrese una opcion valida (si o no):\n");
            gets(opcion);
        }
        if(strcmpi(opcion,"Si")==0)
        {
            system("cls");
            system("color 3F");
            printf("Listo\n");
            strcpy(Nuevo.estado,"Inactivo");                                          ///Lee tu estado y dependiendo si estas activo o no, te permite dar de alta o de baja
            EscribirElEstado(nombre,Nuevo);
        }
        else
        {
            system("cls");
            system("color 3F");
            Menu2();
        }

    }
    else
    {
        printf("Desea darse de alta? Si pone no, volvera al menu anterior\n");
        fflush(stdin);
        gets(opcion);
        while((strcmpi(opcion,"si"))!=0&&(strcmpi(opcion,"no")!=0))
        {
            printf("Ingrese una opcion valida (si o no):\n");
            gets(opcion);
        }
        if(strcmpi(opcion,"si")==0)
        {
            system("cls");
            system("color 3F");
            printf("Listo\n");
            strcpy(Nuevo.estado,"Activo");
            EscribirElEstado(nombre,Nuevo);

        }
        else
        {
            system("cls");
            system("color 3F");
            Menu2();
        }
    }



}
void EscribirElEstado (char nombre [], usuario Nuevo)
{
   int flag=0;
   usuario Aux;
   FILE * archi=fopen(nombre,"r+b");
   if(archi)
   {
        while(flag==0&&(fread(&Aux,sizeof(usuario),1,archi)))                      ///Escribe en el archivo tu estado
             {
                 if(strcmp(Nuevo.nombre,Aux.nombre)==0)
                    {
                        flag=1;
                    }
             }
            fseek(archi,sizeof(usuario)*-1,SEEK_CUR);
            printf("Nuevo estado: %s",Nuevo.estado);
            fwrite(&Nuevo,sizeof(usuario),1,archi);
            fclose(archi);

   }
           else
        {
            printf("No se pudo abrir el archivo :(\n");
        }
}
usuario ModificarUsuario (char nombre[],usuario Nuevo)
{
    usuario Aux;
    char opcion[30];
    printf("Ingrese que quiere cambiar, usuario o contraseña? (Ingresar contrasenia por favor): \n");      ///Modifica tu nombre de usuario o contraseña, a eleccion
    fflush(stdin);
    gets(opcion);
    while((strcmpi(opcion,"usuario")!=0)&&(strcmpi(opcion,"contrasenia")!=0))
    {
        printf("Ese no es un campo valido, ingrese de nuevo la opcion (recuerde ingresar contrasenia):\n");
        gets(opcion);
    }
    if(strcmpi(opcion,"usuario")==0)
    {
        Aux=ModificarNombre(nombre,Nuevo);
    }
    else if(strcmpi(opcion,"contrasenia")==0)
    {
        Aux=ModificarContrasenia(nombre,Nuevo);
    }
    return Aux;
}
usuario ModificarNombre (char nombre[], usuario Nuevo)
{
    usuario Aux;
    strcpy(Aux.estado,Nuevo.estado);
    int A;
    system("cls");
    system("color 3F");
    printf("Usted cambiara su nombre de usuario\n");
    printf("Ingrese su nombre de usuario: \n");
    fflush(stdin);
    gets(Aux.nombre);
    while(strcmp(Aux.nombre,Nuevo.nombre)!=0)
    {
        printf("Ingrese el nombre de forma correcta: \n");                               ///Verifica si el cambio de nombre es valido
        fflush(stdin);
        gets(Aux.nombre);
    }
    printf("Ingrese su contraseña: \n");
    fflush(stdin);
    gets(Aux.contrasenia);
    while(strcmp(Aux.contrasenia,Nuevo.contrasenia)!=0)
    {
        printf("Ingrese la contraseña correcta: \n");
        fflush(stdin);
        gets(Aux.contrasenia);
    }

    system("cls");
    system("color 3F");
    printf("Ingrese su nuevo nombre de usuario: \n");
    fflush(stdin);
    gets(Aux.nombre);
    A=RecorrerArchivos(nombre,Aux);
    while(A!=-1)
    {
        printf("Ese nombre de usuario ya existe, ingrese otro: \n");
        fflush(stdin);
        gets(Aux.nombre);
        A=RecorrerArchivos(nombre,Aux);
    }
    Aux=EscribirNombre(nombre,Nuevo,Aux);

    return Aux;
}
usuario ModificarContrasenia (char nombre[],usuario Nuevo)
{
    usuario Aux;
    system("cls");
    system("color 3F");
    printf("Usted cambiara su contraseña\n");
    printf("Ingrese su nombre de usuario: \n");
    fflush(stdin);
    gets(Aux.nombre);
    while(strcmp(Aux.nombre,Nuevo.nombre)!=0)
    {
        printf("Ingrese el nombre de forma correcta: \n");                           ///Verifica los datos y el cambio de contraseña
        fflush(stdin);
        gets(Aux.nombre);
    }
    printf("Ingrese su contraseña: \n");
    fflush(stdin);
    gets(Aux.contrasenia);
      while(strcmp(Aux.contrasenia,Nuevo.contrasenia)!=0)
    {
        printf("Ingrese la contraseña correcta: \n");
        fflush(stdin);
        gets(Aux.contrasenia);
    }
    system("cls");
    system("color 3F");
    printf("Ingrese su nueva contraseña: \n");
    fflush(stdin);
    gets(Aux.contrasenia);
    Aux=EscribirContrasenia(nombre,Nuevo,Aux);
    return Aux;
}
usuario UsuarioEnUso (usuario nuevo, char nombre [])
{
    int flag=0;
    usuario Aux;
    FILE *archi=fopen(nombre,"rb");
    if(archi)
    {
        while (flag==0&&(fread(&Aux,sizeof(usuario),1,archi))>0)                        ///Retorna todos los campos del usuario en uso
        {
            if(strcmp(nuevo.nombre,Aux.nombre)==0)
            {
                flag=1;
                nuevo=Aux;
            }
        }
        fclose(archi);
    }
     else
    {
        printf("No se pudo abrir el archivo :(\n");
    }
    return nuevo;
}
usuario EscribirNombre (char nombre[],usuario Nuevo,usuario Aux)
{
    int flag=0;
    usuario Auxi;
    FILE * archi=fopen(nombre,"r+b");
    if(archi)
    {
        while(flag==0&&(fread(&Auxi,sizeof(usuario),1,archi))>0)                     ///Escribe el nuevo nombre en el archivo
        {
            if(strcmp(Nuevo.nombre,Auxi.nombre)==0)
            {
                flag=1;
            }
        }
        fseek(archi,sizeof(usuario)*-1,SEEK_CUR);
        fwrite(&Aux.nombre,sizeof(usuario),1,archi);
        fclose(archi);


    }
     else
    {
        printf("No se pudo abrir el archivo :(\n");
    }
    Aux=UsuarioEnUso(Aux,nombre);
    return Aux;
}
usuario EscribirContrasenia (char nombre[],usuario Nuevo, usuario Aux)
{
    int flag=0;
    usuario Auxi;
    FILE * archi=fopen(nombre,"r+b");
    if(archi)
    {
        while(flag==0&&(fread(&Auxi,sizeof(usuario),1,archi))>0)                   ///Escribe la nueva contraseña en el archivo
        {
            if(strcmp(Nuevo.nombre,Auxi.nombre)==0)
            {
                flag=1;
            }
        }
        fseek(archi,sizeof(usuario)*-1,SEEK_CUR);
        strcpy(Auxi.contrasenia,Aux.contrasenia);
        fwrite(&Auxi,sizeof(usuario),1,archi);
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo :(\n");
    }
    Aux=UsuarioEnUso(Aux,nombre);
    return Aux;
}
int NumeroUsuario (char nombre[])
{
    int num = 0;
    usuario Aux;
    FILE * archi=fopen(nombre,"rb");
    if(archi)
    {
        fseek(archi,sizeof(usuario)*-1 ,SEEK_END);
        fread(&Aux, sizeof(usuario), 1, archi);
        num=Aux.nroUsuario+1;
    }
    else
    {
        num=1;
    }

    return num;
}
void cargarTurnos(char nombre[]){
    FILE * buffer= fopen(nombre, "ab");
    turnosAnuales turnosGenerales[12];
    for(int i=0; i<12; i++){
        for(int c=0; c<4; c++){
            for(int f=0; f<7; f++){
               turnosGenerales[i].turnos.turno[c][f]=4;
               if(f==6){
                    turnosGenerales[i].turnos.turno[c][f]=0;
               }
            }
        }
    }
    cargarSemana(turnosGenerales, 12);
    cargarMes(turnosGenerales);
    if(buffer){
            for(int i=0; i<12; i++){
                fwrite(&turnosGenerales[i], sizeof(turnosAnuales), 1, buffer);
            }
            fclose(buffer);
    }
}
void cargarSemana (turnosAnuales turnosGenerales[], int dimension){
        for(int i=0; i<dimension; i++){
            strcpy(turnosGenerales[i].turnos.dia[0], "L");
            strcpy(turnosGenerales[i].turnos.dia[1], "M");
            strcpy(turnosGenerales[i].turnos.dia[2], "M");
            strcpy(turnosGenerales[i].turnos.dia[3], "J");
            strcpy(turnosGenerales[i].turnos.dia[4], "V");
            strcpy(turnosGenerales[i].turnos.dia[5], "S");
            strcpy(turnosGenerales[i].turnos.dia[6], "D");
        }
}
int mostrarTurnos (char nombre[]){
    turnosAnuales turnoGeneral[12];
    leerArchivo(nombre, turnoGeneral, 12);
    int q=0;
    printf("Dime el numero asociado al mes que quieres ver (1=enero, 2=febrero) : ");
    scanf("%i", &q);
    q--;
    mostrarFecha(turnoGeneral[q]);
    for(int f=0; f<4; f++){
        printf("\n");
        for(int c=0; c<7; c++){
            printf("|   %i   |", turnoGeneral[q].turnos.turno[f][c]);
        }
    }
    return q;
}
void leerArchivo (char nombre[],turnosAnuales turnito[], int dimension){
    FILE * buffer= fopen(nombre, "rb");
    int i=0;
    if(buffer){
        while(i<dimension && fread(&turnito[i], sizeof(turnosAnuales), 1, buffer)>0){
            i++;
        }
        fclose(buffer);
    }else{
        printf("NO SE PUDO LEER EL ARCHIVO");
    }
}
void mostrarFecha(turnosAnuales turnito){
    printf("TURNOS DISPONIBLES ESTE DE %s: \n\n", turnito.mes);
    for(int i=0; i<7; i++){
        printf("|   %s   |", turnito.turnos.dia[i]);
    }
}
void cargarMes(turnosAnuales turnosGenerales[12]){
    strcpy(turnosGenerales[0].mes, "Enero");
    strcpy(turnosGenerales[1].mes, "Febrero");
    strcpy(turnosGenerales[2].mes, "Marzo");
    strcpy(turnosGenerales[3].mes, "Abril");
    strcpy(turnosGenerales[4].mes, "Mayo");
    strcpy(turnosGenerales[5].mes, "Junio");
    strcpy(turnosGenerales[6].mes, "Julio");
    strcpy(turnosGenerales[7].mes, "Agosto");
    strcpy(turnosGenerales[8].mes, "Septiembre");
    strcpy(turnosGenerales[9].mes, "Octubre");
    strcpy(turnosGenerales[10].mes, "Noviembre");
    strcpy(turnosGenerales[11].mes, "Diciembre");
}
int solicitarTurno (char nombre[], int*q){
    *q=mostrarTurnos(nombre);
    int dia=0;
    printf("\n\nDime el numero del mes que queres reservar (Recuerda que el mes laboral es de 28 dias): ");
    scanf("%i", &dia);
    turnosAnuales turnito[12];
    leerArchivo(nombre, turnito, 12);
    while(dia % 7 == 0 || dia == 0){
        printf("\nNo contamos con turnos ese dia, por favor solicite otro turno, u oprima nuevamente 0 para cancelar la solicitud de turno");
        scanf("%i", &dia);
        if(dia==0){
            break;
        }
    }
    funcionDividir(dia, turnito, *q);
    FILE * buffer=fopen(nombre, "r+b");
    if(buffer){
        fseek(buffer, sizeof(turnosAnuales)*(*q), 0);
        fwrite(&turnito[*q], sizeof(turnosAnuales), 1, buffer);
        fclose(buffer);
    }
    return dia;
}
void funcionDividir(int dia, turnosAnuales turnito[], int q){
    int i=0;
    if(dia<7){
        restarTurno(dia-1, i, turnito, q);
    }else if(dia>7 && dia<14){
        restarTurno(dia-8, i+1, turnito, q);
    }else if(dia>14 && dia<21){
        restarTurno(dia-15, i+2, turnito, q);
    }else if(dia>21 && dia<28){
        restarTurno(dia-22, i+3, turnito, q);

    }

}
void restarTurno (int dia, int i, turnosAnuales turnito[], int q){
    while(turnito[q].turnos.turno[i][dia]==0){
            printf("\nNo contamos con turnos ese dia, por favor solicite otro turno, u oprima nuevamente 0 para cancelar la solicitud de turno");
            scanf("%i", &dia);
            dia--;
            if(dia==-1){
                break;
            }
        }
        if(dia>=0){
            turnito[q].turnos.turno[i][dia]-=1;
        }
}
int subirArchivo (int dia, int q, usuario *user, char nombre[]){
    int pos;
    user->DiaTurno[0]=dia;
    user->DiaTurno[1]=q;
    pos=RecorrerArchivos(nombre, *user);
    return pos;
}
void cargarTurnoEnUsuario (char nombre[], int pos, usuario user){
    FILE * buffer = fopen(nombre, "r+b");
    if(buffer){
        fseek(buffer, sizeof(usuario)*pos-1, SEEK_SET);
        fwrite(&user.DiaTurno, sizeof(usuario), 1, buffer);
        fclose(buffer);
    }
}
void MostrarUsuario (usuario nuevo)
{
    printf("------------------------------------------------------------\n");
    printf("Nombre de usuario: %s\n",nuevo.nombre);
    printf("Numero de usuario: %i\n",nuevo.nroUsuario);
    printf("Estado de usuario: %s\n",nuevo.estado);
    printf("Servicio adquirido: %s\n",nuevo.servicioAdquirido);
    printf("Dia de turno: %i/%i",nuevo.DiaTurno[0],nuevo.DiaTurno[1]);
    printf("------------------------------------------------------------\n");

}
void mostrarArchivo (char nombre[])
{
    usuario nuevo;
    FILE * archi=fopen(nombre,"rb");
    if (archi)
    {
        while(fread((&nuevo),sizeof(usuario),1,archi)>0)
        {
           printf("Nombre de usuario: %s\n",nuevo.nombre);
         printf("Numero de usuario: %i\n",nuevo.nroUsuario);
         printf("Estado de usuario: %s\n",nuevo.estado);
         printf("Servicio adquirido: %s\n",nuevo.servicioAdquirido);
         printf("Dia de turno: %i/%i\n",nuevo.DiaTurno[0],nuevo.DiaTurno[1]);
        }
    }
}

stProducto cargarProductos() /// PRINTFS PARA CARGA DE PRODUCTOS
{

    stProducto aux;

    printf("Ingrese el nombre del producto: \n");
    fflush(stdin);
    gets(aux.nombre);

    printf("Ingrese la descripcion del producto: \n");
    fflush(stdin);
    gets(aux.descripcion);

    printf("Ingrese el precio del producto: \n");
    scanf("%i", &aux.precio);

    printf("Ingrese la cantidad disponible del producto: \n");
    scanf("%i", &aux.stock);

    return aux;
}

void cargarArchivos(char nombre[]) /// CARGA DE PRODUCTOS EN EL ARCHIVO
{
    FILE * buffer = fopen(nombre, "ab");
    char control = 's';
    stProducto p;

    printf("Desea cargar productos? \n");
    fflush(stdin);
    scanf("%c", &control);

    if(buffer)
    {
        while(control == 's')
        {
            p = cargarProductos();
            fwrite(&p, sizeof(stProducto), 1, buffer);
            printf("Desea seguir cargando productos? \n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(buffer);
    }
}

void mostrarArchivoo(char nombre[]) /// MUESTRA LOS PRODUCTOS
{
    FILE * buffer = fopen(nombre, "rb");
    stProducto p;
    printf("         PRODUCTOS:  \n \n");
    if(buffer)
    {
        while(fread(&p, sizeof(stProducto), 1, buffer) > 0)
        {
            printf("Nombre: %s \n", p.nombre);
            printf("Descripcion: %s \n", p.descripcion);
            printf("Precio: $%i \n", p.precio);
            printf("Cantidad disponible: %i \n", p.stock);
            printf("------------------------------------\n");
        }
        fclose(buffer);
    }
}

void comprarProducto(char nombre[]) /// COMPRA DE PRODUCTOS, VERIFICACION DE DATOS DE PAGO
{

    FILE * buffer = fopen(nombre, "r+b");
    stProducto comprar;
    char control = 's';
    char nombreComprar[20];
    int cantidadComprar = 0;
    int formaDePago = 0;
    printf("Desea comprar algun producto? \n");
    fflush(stdin);
    scanf("%c", &control);


    if(control == 's')
    {
        printf("Dime el nombre del producto que desea comprar: \n");
        fflush(stdin);
        gets(nombreComprar);
        int flag = 1;

        if(buffer)
        {
            while(flag == 1 && fread(&comprar, sizeof(stProducto), 1, buffer) > 0)
            {
                if(strcmpi(nombreComprar, comprar.nombre) == 0)
                {
                    printf("Dime la cantidad de ' %s ' que quieres comprar: \n", comprar.nombre);
                    scanf("%i", &cantidadComprar);
                    while(cantidadComprar > comprar.stock)
                    {
                        printf("Dime una cantidad valida de ' %s ' que quieres comprar: \n", comprar.nombre);
                        scanf("%i", &cantidadComprar);
                    }
                    comprar.stock = (comprar.stock - cantidadComprar);
                    fseek(buffer, sizeof(stProducto)*-1, 1);
                    fwrite(&comprar, sizeof(stProducto), 1, buffer);
                    flag = 0;

                    int total = cantidadComprar * comprar.precio;
                    system("cls");
                    printf("El total a abonar es: $%i \n", total);
                    printf("Como desea abonar su pago? \n Ingrese 1 para abonar de manera online. \n Ingrese 2 para abonar de manera presencial. \n");
                    scanf("%i", &formaDePago);
                    if(formaDePago == 1)
                    {
                        cobrarConTarjeta();

                        char control2 = 's';
                        printf("Confirmar compra? (s/n) \n");
                        scanf("%c", &control2);

                        if(control2 == 'S' || control2 == 's')
                        {
                            system("cls");
                            printf("COMPRA REALIZADA CON EXITO! \n");
                            printf("----------------------------\n");
                            printf("|   COMPROBANTE DE PAGO:   |\n");
                            printf("|   RETIRO EN: Mitre 3128   |\n");
                            printf("| PRODUCTO: %s           |\n", comprar.nombre);
                            printf("| TOTAL: %i              |\n", total);
                            printf("----------------------------");
                        }
                    }
                    else if(formaDePago == 2)
                    {
                        printf("PEDIDO REALIZADO CON EXITO! \n");
                        printf("----------------------------\n");
                        printf("|   RETIRO EN: Mitre 3128   |\n");
                        printf("| PRODUCTO: %s           |\n", comprar.nombre);
                        printf("| TOTAL: %i              |\n", total);
                        printf("----------------------------");
                    }

                }
            }
            fclose(buffer);
        }
    }
}

void cobrarConTarjeta() /// VERIFICACION DE LOS DATOS DE PAGO
{
    char tarjetaNum[30];
    char tarjetaTitular[30];
    char tarjetaCodigo[10];

    printf("Ingrese los datos de pago: \n");

    printf("Nombre y apellido del titular de la tarjeta: \n");
    fflush(stdin);
    gets(tarjetaTitular);

    while(strchr(tarjetaTitular, ' ') == NULL)
    {
        printf("Ingrese un nombre y apellido valido: \n");
        fflush(stdin);
        gets(tarjetaTitular);
    }
    printf("Numero de tarjeta: \n");
    fflush(stdin);
    gets(tarjetaNum);

    int verificacion = strlen(tarjetaNum);

    while(verificacion > 16 || verificacion < 16)
    {
        printf("Numero de tarjeta inexistente, revisa los datos y vuelve a ingresarlos. \n");
        fflush(stdin);
        gets(tarjetaNum);
        verificacion = strlen(tarjetaNum);
    }

    printf("Codigo de seguridad: \n");
    fflush(stdin);
    gets(tarjetaCodigo);

    int verificacion2 = strlen(tarjetaCodigo);

    while(verificacion2 > 3 || verificacion2 < 3)
    {
        printf("Codigo de seguridad invalido. Verifique el codigo y vuelva a ingresarlo. \n");
        fflush(stdin);
        gets(tarjetaCodigo);
        verificacion2 = strlen(tarjetaCodigo);
    }
}

