#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>

#include "Comandos.h"
#include "DGV.h"
#include "Campeonato.h"

using namespace std;

class Interface {
    Comandos * comandos;
    DGV dgv;
    Campeonato *campeonato = nullptr;
    int nCorrida;
    vector<DGV> dgvLista;

public:
    Interface();
    ~Interface();
    
    void menu();
    void comandosModo1();
    bool lerComandos1(string input);
    void comandosModo2();
    bool lerComandos2(string input);
    void subModo2();
    bool lerSubModo2(string input);

    bool ficheiroPilotos(string nomeFich);
    bool ficheiroCarros(string nomeFich);
    bool ficheiroAutodromos(string nomeFich);
};

#endif /* INTERFACE_H */

