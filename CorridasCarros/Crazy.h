#ifndef CRAZY_H
#define CRAZY_H

#include <string>
#include <iostream>

#include "Piloto.h"

class Crazy : public Piloto {
public:
    Crazy(string nome);

    void iniciaCorrida() override;
    void entraEmAcao(int segundos, Piloto* p) override;
    Piloto* duplica() const override;
};

#endif /* CRAZY_H */

