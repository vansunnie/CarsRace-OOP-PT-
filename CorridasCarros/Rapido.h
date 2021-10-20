#ifndef RAPIDO_H
#define RAPIDO_H

#include <string>
#include <iostream>

#include "Piloto.h"

class Rapido : public Piloto {
    int segundoDeAceleracao;
    int segundoEmergencia;
public:
    Rapido(string nome);
    
    void iniciaCorrida() override;
    void entraEmAcao(int segundos, Piloto* p) override;
    Piloto* duplica() const override;
};

#endif /* RAPIDO_H */

