#!/bin/bash

make clean && make

echo "--- RELATÓRIO DE TESTES - FILÓSOFOS ---" > resultados.txt

echo "Rodando teste de robustez (50 filósofos)..."
./solucao 50 >> resultados.txt


echo "Rodando Helgrind para detectar condições de corrida..."
valgrind --tool=helgrind ./solucao 5 2>> resultados.txt

echo "Testes concluídos. Resultados salvos em resultados.txt"
