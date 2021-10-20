#ifndef SURPRESA_H
#define SURPRESA_H

#include <string>
#include <iostream>

#include "Piloto.h"
#include "Corrida.h"

class Surpresa : public Piloto {
public:
    Surpresa(string nome);

    void iniciaCorrida() override;
    void entraEmAcao(int segundos, Piloto* p) override;
    Piloto* duplica() const override;
};

#endif /* SURPRESA_H */

