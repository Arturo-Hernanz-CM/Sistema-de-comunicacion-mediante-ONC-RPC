#!/bin/bash
shopt -s nullglob


# Función para limpiar si se interrumpe
cleanup(){
    echo "Limpiando procesos..."
    pkill -P $$
    exit 1
}

trap cleanup SIGINT

export IP_TUPLAS=localhost

echo "Ejecutando pruebas de éxito"
for fichero in pruebas_exito/*.sh; do
    echo "-------------------------"
    echo "Limpiando base de datos:"
    ./app-cliente-0
    echo "Ejecutando $(basename "$fichero")"
    bash "$fichero"
    echo "-------------------------"
done

printf "\n\n"

echo "Ejecutando pruebas de error"
for fichero in pruebas_error/*.sh; do
    echo "-------------------------"
    echo "Limpiando base de datos:"
    ./app-cliente-0
    echo "Ejecutando $(basename "$fichero")"
    bash "$fichero"
    echo "-------------------------"
done

printf "\n\n"

echo "Ejecutando pruebas de hilos posibles error"
for fichero in pruebas_hilos_posible_error/*.sh; do
    echo "-------------------------"
    echo "Limpiando base de datos:"
    ./app-cliente-0
    echo "Ejecutando $(basename "$fichero")"
    bash "$fichero"
    echo "-------------------------"
done

wait
exit 0