#include "claves.h"
#include "tuplas.h"
#include <stdio.h> 
#include <stdlib.h>
#include <rpc/pmap_clnt.h>

// Funciones

// Funciones SVC
// Función destroy
bool_t destroy_1_svc(int * result, struct svc_req *rqstp) {
    static int resultado;
    resultado = destroy();
    *result = resultado;
    return TRUE;
}

// Función set value
bool_t setvalue_1_svc(peticion argp, int * result, struct svc_req *rqstp) {
    static int resultado;
    struct Coord value3 = {argp.value3.x, argp.value3.y};
    resultado = set_value(argp.key, argp.value1, argp.N_value2, argp.value2, value3);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: setvalue_1_svc\nError: Error al insertar");
        resultado = -1;
    }
    *result = resultado;
    return TRUE;
}

// Función get value
bool_t getvalue_1_svc(int argp, peticion * result, struct svc_req *rqstp) {
    result->value1 = malloc(256);
    if(result->value1 == NULL){
        perror("ERROR:\nFile: servidor-rpc->c\nFunction: getvalue_1_svc\nError: Error al resultervar memoria para guardar el value1");
        result->key = -1;
        return FALSE;
    }
    static int resultultado;
    struct Coord value3 = {result->value3.x, result->value3.y};
    resultultado = get_value(argp, result->value1, &result->N_value2, result->value2, &value3);
    if (resultultado == -1) {
        perror("ERROR:\nFile: servidor-rpc->c\nFunction: getvalue_1_svc\nError: Error al insertar");
        result->key = -1;
        return FALSE;
    }
    result->key = argp;
    result->value3.x = value3.x;
    result->value3.y = value3.y;
    return TRUE;
}

// Función modify value
bool_t modifyvalue_1_svc(peticion argp, int * result, struct svc_req *rqstp) {
    static int resultado;
    struct Coord value3 = {argp.value3.x, argp.value3.y};
    resultado = modify_value(argp.key, argp.value1, argp.N_value2, argp.value2, value3);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: modifyvalue_1_svc\nError: Error al insertar");
        resultado = -1;
    }

    *result = resultado;
    return TRUE;
}

// Función delete key
bool_t deletekey_1_svc(int argp, int * result, struct svc_req *rqstp) {
    static int resultado;
    resultado = delete_key(argp);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: deletekey_1_svc\nError: Error al insertar");
        resultado = -1;
    }

    *result = resultado;
    return TRUE;
}

// Funcion exist
bool_t exist_1_svc(int argp, int * result, struct svc_req *rqstp) {
    static int resultado;
    resultado = exist(argp);

    if (resultado == -1) {
        perror("ERROR:\nFile: servidor-rpc.c\nFunction: exist_1_svc\nError: Error al insertar");
        resultado = -1;
    }   
    
    *result = resultado;
    return TRUE;
}