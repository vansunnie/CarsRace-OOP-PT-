#include "Rapido.h"

Rapido::Rapido(string nome) : Piloto(nome) {
    segundoDeAceleracao = 0;
    segundoEmergencia = 0;
}

//inicia a corrida no 1 seg

void Rapido::iniciaCorrida() {
    iniciaNoSegundo = 1;
}

void Rapido::entraEmAcao(int segundos, Piloto* p) {
    if (c->getEnergia() > (c->getCapacidadeMaxima()) / 2) { //acelera continuamente até atingir metade da energia da cap máxima 
        c->acelera();
        c->moveCarro();
        segundoDeAceleracao = segundos;
        ostringstream os;
        os << "Segundo: " << segundos << " - energia suficiente, acelerou";
        adicionaMensagemAoInfoPilotoCarro(os.str());

    } else { //acelera a cada 3 seg
        if (segundos == segundoDeAceleracao + 3) {
            c->acelera();
            c->moveCarro();
            segundoDeAceleracao = segundos;
            ostringstream os;
            os << "Segundo: " << segundos << " - pouca energia, acelerou (a cada 3 seg)";
            adicionaMensagemAoInfoPilotoCarro(os.str());
        } else {
            c->moveCarro();
            ostringstream os;
            os << "Segundo: " << segundos << " - pouca energia, manteve velocidade";
            adicionaMensagemAoInfoPilotoCarro(os.str());
        }
    }

    //probabilidade de ativar o botão de emergência a cada 10 seg
    if (segundos == segundoEmergencia + 10) { //se ja tiver passado 10 segundos 
        int prob = rand() % 100 + 1;

        ostringstream os;
        os << "Segundo: " << segundos << " - teve uma probabilidade de nao acender sinal de emergencia de: " << prob << "%";
        adicionaMensagemAoLog(os.str());

        if (prob <= 10) { //tem probabilidade de acender sinal de emergencia
            c->setSinalEmergencia(true);
            ostringstream os;
            os << "Segundo: " << segundos << " - acendeu o sinal de emergencia";
            adicionaMensagemAoInfoPilotoCarro(os.str());
        }
        segundoEmergencia = segundos;
    }
}

Piloto* Rapido::duplica() const {
    return new Rapido(*this);
}
