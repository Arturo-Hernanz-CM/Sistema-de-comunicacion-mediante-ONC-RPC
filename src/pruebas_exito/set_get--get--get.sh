#!/bin/bash

# Función para limpiar
cleanup(){
    echo "Limpiando..."
    pkill -P $$
    exit 1
}

trap cleanup SIGINT

env IP_TUPLAS=localhost ./app-cliente-1
env IP_TUPLAS=localhost ./app-cliente-2&
env IP_TUPLAS=localhost ./app-cliente-2&
env IP_TUPLAS=localhost ./app-cliente-2


wait 
exit 0