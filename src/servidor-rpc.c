#include "claves.h"
#include "estructuras.h"
#include "tuplas.h"
#include <rpc/rpc.h>
#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Variables globales
char *ip_servidor;
char *puerto_servidor_char;
Lista * base_datos = NULL;

pthread_mutex_t mutex_mensaje;
pthread_cond_t condicion_mensaje;
pthread_mutex_t mutex_funcion;
int ocupado = 0;

// Funciones

// Funciones SVC
// Función destroy
int * destroy_1_svc(struct svc_req *rqstp) {
    static int resultado;
    resultado = destroy();
    return &resultado;
}

// Función set value
int * setvalue_1_svc(struct Peticion argp, struct svc_req *rqstp) {
    static int resultado;
    struct Coord value3 = {argp.value3.x, argp.value3.y};
    resultado = set_value(argp.key, argp.value1, argp.N_value2, argp.value2, value3);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: setvalue_1_svc\nError: Error al insertar");
        resultado = -1;
    }

    return &resultado;
}

// Función get value
peticion *getvalue_1_svc(int argp, struct svc_req *rqstp) {
    static peticion res;
    int resultado;
    struct Coord value3 = {res.value3.x, res.value3.y};
    resultado = get_value(argp, res.value1, &res.N_value2, res.value2, &value3);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: getvalue_1_svc\nError: Error al insertar");
        res.key = -1;
        return &res;
    }

    res.key = argp;
    return &res;
}

// Función modify value
int *modifyvalue_1_svc(struct Peticion argp, struct svc_req *rqstp) {
    static int resultado;
    struct Coord value3 = {argp.value3.x, argp.value3.y};
    resultado = modify_value(argp.key, argp.value1, argp.N_value2, argp.value2, value3);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: modifyvalue_1_svc\nError: Error al insertar");
        resultado = -1;
    }

    return &resultado;
}

// Función delete key
int *deletekey_1_svc(int argp, struct svc_req *rqstp) {
    static int resultado;
    resultado = delete_key(argp);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: deletekey_1_svc\nError: Error al insertar");
        resultado = -1;
    }

    return &resultado;
}

// Funcion exist
int *exist_1_svc(int argp, struct svc_req *rqstp) {
    static int resultado;
    resultado = exist(argp);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: exist_1_svc\nError: Error al insertar");
        resultado = -1;
    }   
    
    return &resultado;
}



int main(int argc, char **argv) {
    // Comprobacion de argumentos
    if(argc != 1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: main\nError: Número de argumentos incorrecto\n");
        return -1;
    }

    // Inicializar la base de datos
    base_datos = (Lista *) malloc(sizeof(Lista));
    if (base_datos == NULL) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: main\nError: Error al reservar memoria para la lista de claves");
        return -1;
    }
    base_datos->inicio = NULL;
    base_datos->final = NULL;
    base_datos->size = 0;


    // RPC
    // Registrar el servicio
    register SVCXPRT *transp;
    pmap_unset(TUPLAS, TUPLASVER);

    // Socket TCP
    transp = svctcp_create(RPC_ANYSOCK, 0, 0);
    if (transp == NULL) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: main\nError: Error al crear el socket TCP");    
        return -1;
    }

    // Registrar el servicio
    if (!svc_register(transp, TUPLAS, TUPLASVER, tuplas_1, IPPROTO_TCP)) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: main\nError: Error al registrar el servicio");
        return -1;
    }

    // Arrancar el servidor
    svc_run();
    
    return 0;
}