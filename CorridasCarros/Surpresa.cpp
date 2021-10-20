
#include "Surpresa.h"

Surpresa::Surpresa(string nome) : Piloto(nome) {

}

//a corrida inicia no 2 seg

void Surpresa::iniciaCorrida() {
    iniciaNoSegundo = 2;
}

//prob de 50%: <50 - trava; >50 - acelera
//se a energia <5 - ativa sinal de emergência

void Surpresa::entraEmAcao(int segundos, Piloto* p) {
    int prob = rand() % 100 + 1;

    ostringstream os;
    os << "Segundo: " << segundos << " - teve uma probabilidade de acelerar(>=50%)/travar: " << prob << "%";
    adicionaMensagemAoLog(os.str());

    if (prob < 50) {
        c->trava();
        c->moveCarro();
    } else {
        c->acelera();
        c->moveCarro();
    }

    if (c->getEnergia() <= 5) {
        c->setSinalEmergencia(true);
        ostringstream os;
        os << "Segundo: " << segundos << " - acendeu o sinal de emergencia";
        adicionaMensagemAoInfoPilotoCarro(os.str());
    }
}

Piloto* Surpresa::duplica() const {
    return new Surpresa(*this);
}
