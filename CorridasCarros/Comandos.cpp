#include "Comandos.h"

void Comandos::listaComandosModo1() {
    cout << "Lista de comandos do modo 1:" << endl;
    cout << "[1] carregaP <nomeFicheiro>" << endl;
    cout << "[2] carregaC <nomeFicheiro>" << endl;
    cout << "[3] carregaA <nomeFicheiro>" << endl;
    cout << "[4] cria <letraTipo> <dados do objeto>";
    cout << "\t\t\tLetras: p - piloto; c - carro; a - autodromo" << endl;
    cout << "[5] apaga <letraTipo> identificador" << endl;
    cout << "[6] entranocarro <letraCarro> <nomePiloto> " << endl;
    cout << "[7] saidocarro <letraCarro>" << endl;
    cout << "[8] lista" << endl;
    cout << "[9] campeonato <A1> <A2> ... <An>" << endl;
    cout << "[10] savedgv <nome>" << endl;
    cout << "[11] loaddgv <nome> " << endl;
    cout << "[12] deldgv <nome>" << endl;
    cout << "[0] SAIR" << endl;
}

void Comandos::listaComandosModo2() {
    cout << "Comandos a executar durante o campeonato" << endl;
    cout << "[13] passatempo <n>" << endl;
    cout << "[14] listacarros" << endl;
    cout << "[15] carregabat <letraCarro> <Q>" << endl;
    cout << "[16] carregatudo" << endl;
    cout << "[17] corrida " << endl;
    cout << "[18] acidente <letraCarro>" << endl;
    cout << "[19] stop <nomePiloto>" << endl;
    cout << "[20] destroi <letraCarro>" << endl;
    cout << "[21] garagem" << endl;
    cout << "[22] passatempo <n>" << endl;
    cout << "[23] log" << endl;
    cout << "[24] info" << endl;
    cout << "[0] SAIR" << endl;
}
