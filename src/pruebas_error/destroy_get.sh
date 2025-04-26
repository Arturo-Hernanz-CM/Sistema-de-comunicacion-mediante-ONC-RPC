# Prueba destroy y get de dos keys diferentes

#!/bin/bash

# Función para limpiar
cleanup(){
    echo "Limpiando..."
    pkill -P $$
    exit 1
}

trap cleanup SIGINT

env ./app-cliente-0
env ./app-cliente-2


wait 
exit 0