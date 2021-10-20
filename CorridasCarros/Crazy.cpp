#include "Crazy.h"

Crazy::Crazy(string nome) : Piloto(nome) {
}

//a corrida só inicia passados x seg (desatento)

void Crazy::iniciaCorrida() {
    int n = (rand() % 5) + 1;
    iniciaNoSegundo = n;

    ostringstream os;
    os << "Comeca a correr no segundo " << iniciaNoSegundo;
    adicionaMensagemAoLog(os.str());
}

//p - piloto dentro do carro que está imediatamente atrás do carro atual

void Crazy::entraEmAcao(int segundos, Piloto* p) {
    int prob = 0;
    prob = rand() % 100 + 1;

    ostringstream os;
    os << "Segundo: " << segundos << " - teve uma probabilidade de nao danificar o carro de: " << prob << "%";
    adicionaMensagemAoLog(os.str());

    //existe prob de 5% de danificar o carro
    if (prob <= 5) {
        c->setDanificado(true);
        c->setEnergia(0);
        ostringstream os;
        os << "Segundo: " << segundos << " - danificou o carro";
        adicionaMensagemAoInfoPilotoCarro(os.str());

        //danifica carro no lugar atrás
        if (p != nullptr) {
            p->getC()->setDanificado(true);
            ostringstream os;
            os << "Carro danificado pelo carro no lugar imediatamente a seguir";
            p->adicionaMensagemAoInfoPilotoCarro(os.str());
        }

    } else { //se nao danificou o carro
        if (posicaoActual == 1) { //se estiver em primeiro lugar mantém a velocidade
            c->moveCarro();
            ostringstream os;
            os << "Segundo: " << segundos << " - 1º lugar, manteve velocidade";
            adicionaMensagemAoInfoPilotoCarro(os.str());
        } else if (ultimoLugar) { //se estiver em último lugar
            c->trava();
            c->moveCarro();
            ostringstream os;
            os << "Segundo: " << segundos << " - ultimo lugar, travou";
            adicionaMensagemAoInfoPilotoCarro(os.str());

        } else { //se nao estiver em primeiro nem em ultimo acelera
            if (posicaoActual < posicaoAnterior) {
                c->acelera(); // c->acelera(int n)!!!!!!!!!!!!!!!!!!
                c->acelera();
                c->moveCarro();
                ostringstream os;
                os << "Segundo: " << segundos << " - desceu de lugar, acelerou a dobrar";
                adicionaMensagemAoInfoPilotoCarro(os.str());
            } else {
                c->acelera();
                c->moveCarro();
                ostringstream os;
                os << "Segundo: " << segundos << " - nao desceu de lugar, acelerou";
                adicionaMensagemAoInfoPilotoCarro(os.str());
            }
        }
    }

    if (c->getEnergia() < 1 && !c->isDanificado()) {
        c->isSinalEmergencia();
        ostringstream os;
        os << "Segundo: " << segundos << " - acendeu o sinal de emergencia";
        adicionaMensagemAoInfoPilotoCarro(os.str());
    }
}

Piloto* Crazy::duplica() const {
    return new Crazy(*this);
}


