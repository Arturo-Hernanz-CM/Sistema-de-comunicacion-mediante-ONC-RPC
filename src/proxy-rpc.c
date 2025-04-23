#include "proxy-rpc.h"
#include "tuplas.h"
#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

// Variable global
peticion pet = {0};
char *ip_servidor;


// Funciones
// Funcion destroy
int destroy(void){
    // Variable de entorno
    ip_servidor = getenv("IP_TUPLAS");

    // Creacion del cliente
    CLIENT *cliente = clnt_create(ip_servidor, TUPLAS, TUPLASVER, "tcp");
    if(cliente == NULL){
        clnt_pcreateerror("ERROR:\nFile: proxy-rpc.c\nFunction: destroy\nError: Error al crear el cliente");
        return -1;
    }

    int resultado;

    enum clnt_stat stat = destroy_1(&resultado, cliente);
    if (stat != RPC_SUCCESS || resultado == -1){
        clnt_perror(cliente, "ERROR:\nFile: proxy-rpc.c\nFunction: destroy\nError: Error al destruir");
        clnt_destroy(cliente);
        return -1;
    }

    clnt_destroy(cliente);
    printf("Lista destruida.\n");
    return 0;
}

// Funcion set_value
int set_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3){
    // Variable de entorno
    ip_servidor = getenv("IP_TUPLAS");

    // Asignacion de valores a la estructura
    pet.key = key;
    pet.value1 = malloc(strlen(value1) + 1);
    if (pet.value1 == NULL) {
        perror("ERROR:\nFile: proxy-rpc.c\nFunction: set_value\nError: Error al reservar memoria para guardar el value1");
        return -1;
    }
    strcpy(pet.value1, value1);
    pet.N_value2 = N_value2;
    memcpy(&pet.value2, V_value2, N_value2*sizeof(double));
    pet.value3.x = value3.x;
    pet.value3.y = value3.y;
    pet.operacion = 1;

    // Creacion del cliente
    CLIENT *cliente = clnt_create(ip_servidor, TUPLAS, TUPLASVER, "tcp");
    if(cliente == NULL){
        clnt_pcreateerror("ERROR:\nFile: proxy-rpc.c\nFunction: set_value\nError: Error al crear el cliente");
        return -1;
    }

    int resultado;

    enum clnt_stat stat = setvalue_1(pet, &resultado, cliente);

    // LLamada al servicio
    if (stat != RPC_SUCCESS || resultado == -1){
        clnt_perror(cliente, "ERROR:\nFile: proxy-rpc.c\nFunction: set_value\nError: Error al hacer set");
        return -1;
    }

    clnt_destroy(cliente);
    free(pet.value1);
    printf("Mensaje guardado en la lista.\n");
    return 0;
}

// Funcion get_value
int get_value(int key, char *value1, int *N_value2, double *V_value2, struct Coord *value3){
    // Variable de entorno
    ip_servidor = getenv("IP_TUPLAS");

    // Creacion del cliente
    CLIENT *cliente = clnt_create(ip_servidor, TUPLAS, TUPLASVER, "tcp");
    if(cliente == NULL){
        clnt_pcreateerror("ERROR:\nFile: proxy-rpc.c\nFunction: get_value\nError: Error al crear el cliente");
        return -1;
    }

    // LLamada al servicio
    peticion * resp = NULL;

    enum clnt_stat stat = getvalue_1(key, resp, cliente);

    if (stat != RPC_SUCCESS || resp->key == -1){
        clnt_perror(cliente, "ERROR:\nFile: proxy-rpc.c\nFunction: get_value\nError: Error al hacer get");
        return -1;
    }
    // Escribir la respuesta en los valores que se pasan como argumentos
    strcpy(value1, resp->value1);
    *N_value2 = resp->N_value2;
    memcpy(V_value2, &resp->value2, (*N_value2)*sizeof(double));
    value3->x = resp->value3.x;
    value3->y = resp->value3.y;

    // Prints para comprobar el resultado
    printf("\nDatos de la clave %d recuperados:\n", key);
    printf("\tvalue1: %s\n", value1);
    printf("\tN_value2: %d\n", *N_value2);
    for (int i = 0; i < *N_value2; i++){
        printf("\tvalue2[%d]: %f\n", i, V_value2[i]);
    }
    printf("\tvalue3.x: %d\n", value3->x);
    printf("\tvalue3.y: %d\n", value3->y);
    
    clnt_destroy(cliente);
    return 0;
}

// Funcion modify_value
int modify_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3){
    // Variable de entorno
    ip_servidor = getenv("IP_TUPLAS");

    // Asignacion de valores a la estructura
    pet.key = key;
    pet.value1 = malloc(strlen(value1) + 1);
    if (pet.value1 == NULL) {
        perror("ERROR:\nFile: proxy-rpc.c\nFunction: set_value\nError: Error al reservar memoria para guardar el value1");
        return -1;
    }
    strcpy(pet.value1, value1);
    pet.N_value2 = 2;
    memcpy(&pet.value2, V_value2, sizeof(double));
    pet.value3.x = value3.x;
    pet.value3.y = value3.y;
    pet.operacion = 3;

    // Creacion del cliente
    CLIENT *cliente = clnt_create(ip_servidor, TUPLAS, TUPLASVER, "tcp");
    if(cliente == NULL){
        clnt_pcreateerror("ERROR:\nFile: proxy-rpc.c\nFunction: modify_value\nError: Error al crear el cliente");
        return -1;
    }

    int resultado;

    enum clnt_stat stat = modifyvalue_1(pet, &resultado, cliente);
    // LLamada al servicio
    if (stat != RPC_SUCCESS || resultado == -1){
        clnt_perror(cliente, "ERROR:\nFile: proxy-rpc.c\nFunction: modify_value\nError: Error al modificar");
        return -1;
    }

    clnt_destroy(cliente);
    free(pet.value1);
    printf("Datos modificados.\n");
    return 0;
}

// Funcion delete_key
int delete_key(int key){
    // Variable de entorno
    ip_servidor = getenv("IP_TUPLAS");

    // Creacion del cliente
    CLIENT *cliente = clnt_create(ip_servidor, TUPLAS, TUPLASVER, "tcp");
    if(cliente == NULL){
        clnt_pcreateerror("ERROR:\nFile: proxy-rpc.c\nFunction: delete_key\nError: Error al crear el cliente");
        return -1;
    }

    int resultado;

    enum clnt_stat stat = deletekey_1(key, &resultado, cliente);

    // LLamada al servicio
    if (stat != RPC_SUCCESS || resultado == -1){
        clnt_perror(cliente, "ERROR:\nFile: proxy-rpc.c\nFunction: delete_key\nError: Error al borrar");
        return -1;
    }

    clnt_destroy(cliente);
    printf("Datos asociados a la clave destruidos.\n");
    return 0;
}

// Funcion exist
int exist(int key){
    // Variable de entorno
    ip_servidor = getenv("IP_TUPLAS");

    // Creacion del cliente
    CLIENT *cliente = clnt_create(ip_servidor, TUPLAS, TUPLASVER, "tcp");
    if(cliente == NULL){
        clnt_pcreateerror("ERROR:\nFile: proxy-rpc.c\nFunction: exist\nError: Error al crear el cliente");
        return -1;
    }

    int resultado;

    enum clnt_stat stat = exist_1(key, &resultado, cliente);

    // LLamada al servicio
    if (stat != RPC_SUCCESS || resultado == -1){
        clnt_perror(cliente, "ERROR:\nFile: proxy-rpc.c\nFunction: exist\nError: Error al comprobar existencia");
        return -1;
    }

    clnt_destroy(cliente);
    printf("Clave encontrada.\n");
    return 0;
}