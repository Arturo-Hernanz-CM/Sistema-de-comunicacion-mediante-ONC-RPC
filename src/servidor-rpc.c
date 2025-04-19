#include "claves.h"
#include "tuplas.h"
#include <stdio.h> 
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
/*
#include <rpc/rpc.h>
#include "estructuras.h"
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdint.h>
*/

// Funciones

// Funciones SVC
// Función destroy
int * destroy_1_svc(struct svc_req *rqstp) {
    static int resultado;
    resultado = destroy();
    return &resultado;
}

// Función set value
int * setvalue_1_svc(peticion argp, struct svc_req *rqstp) {
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
    static peticion res={0};
    if (res.value1 != NULL) {
        free(res.value1);
    }
    res.value1 = malloc(256);
    if(res.value1 == NULL){
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: getvalue_1_svc\nError: Error al reservar memoria para guardar el value1");
        res.key = -1;
        return &res;
    }
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
int *modifyvalue_1_svc(peticion argp, struct svc_req *rqstp) {
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