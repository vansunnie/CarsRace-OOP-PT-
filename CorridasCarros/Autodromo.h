#ifndef AUTODROMO_H
#define AUTODROMO_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "Carro.h"

using namespace std;

class Autodromo {
    string nome;
    int nCar;
    int compPista;
    vector <Carro *> garagem;

    bool destruido = false;
public:
    Autodromo(string name, int n, int comprimento);
    ~Autodromo();
    
    string getNome() const;
    int getCompPista() const;
    int getNCar() const;

    void adicionaCarroGaragem(Carro* c);
    void mostraCarrosGaragem();

    string getAsString();
};

#endif /* AUTODROMO_H */

