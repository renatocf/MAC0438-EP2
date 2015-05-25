MAC0438-EP2
============

Threads
--------

Segundo exercício-programa da disciplina de MAC0438 (Programação
Concorrente).

Neste programa, utilizamos a biblioteca "pthread.h" para implementação
da barreira, colocada dentro de uma classe C++ para melhor proveito da
administração de memória por construtores/destrutures das classes. A
biblioteca pthread é implementada por meio de rotinas de baixo nível do
sistema operacional, usando um sistema de 'lock' com primitivas simples
(palavras da memória) para as quais há garantia de um acesso sequencial
(sem instruções especiais - apenas operações simples de carregar e
atribuir na memória). Por meio destas primitivas e da exclusão mútua, a
biblioteca mantém contadores que são incrementados de acordo com o
número de threads a serem sincronizadas. As primeiras threads ficam
travadas esperando a liberação de um semáforo, sendo por fim liberadas
quando a última chega à barreira.

Compilação
-----------
Para compilar, basta rodar o comando `make`

Para rodar os testes de unidade, coloque `make check`
