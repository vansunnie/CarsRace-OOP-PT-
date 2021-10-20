#ifndef CORRIDA_H
#define CORRIDA_H

#include <vector>

#include "Autodromo.h"
#include "Carro.h"
#include "Piloto.h"

class Corrida {
    Autodromo *autodromo;
    vector <Carro *> carrosCorrida;
    vector <Piloto *> pilotosCorrida;
    vector <Piloto *> pilotosForaCorrida; //so para mostrar log dos pilotos que ja nao estao na corrida

    int segundosDecorridos;

    const int FIRSTPLACE = 10;
    const int SECONDPLACE = 5;
    const int THIRDPLACE = 2;
public:
    Corrida(Autodromo* autodromo, vector<Piloto*> pilotosCorrida);
    ~Corrida();

    Autodromo* getAutodromo() const;
    vector<Piloto*> getPilotosCorrida() const;

    void mostraPista();
    void passaTempo();

    bool verificaFinalCorrida();
    bool verificaCarroCorrida(char id);

    bool removePilotoDaCorrida(Piloto *p);
    bool removePilotoApenasDeUmaCorrida(Piloto *p);
    bool removeCarroDaCorrida(char id);
    bool saiDaCorrida(string nome);

    void mostraVencedores();
    void mostraLogMensagens();
    void mostraInfoCorrida();
    void mostraInfoCarros();
    void mostraCarrosGaragem();

};

#endif /* CORRIDA_H */

