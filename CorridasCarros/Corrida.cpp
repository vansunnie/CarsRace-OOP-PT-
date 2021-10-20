#include "Corrida.h"

Corrida::Corrida(Autodromo* autodromo, vector<Piloto*> pilotosCorrida) :
autodromo(autodromo), pilotosCorrida(pilotosCorrida) {
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        pilotosCorrida[i]->getC()->restauraValores();
        pilotosCorrida[i]->iniciaCorrida();
        pilotosCorrida[i]->limpaLog();
        pilotosCorrida[i]->limpaInfo();
    }
    int nCarros = pilotosCorrida.size();
    segundosDecorridos = 0;
}

Corrida::~Corrida() {
}

Autodromo* Corrida::getAutodromo() const {
    return autodromo;
}

vector<Piloto*> Corrida::getPilotosCorrida() const {
    return pilotosCorrida;
}

void Corrida::mostraPista() {
    int comp = autodromo->getCompPista();
    int nCarros = autodromo->getNCar();

    for (int i = 0; i < nCarros; i++) {
        for (int k = 0; k < pilotosCorrida.size(); k++) {
            if (pilotosCorrida[k]->getLinha() == i + 1) {
                for (int j = 0; j <= comp; j++) {
                    Carro *c = pilotosCorrida[k]->getC();
                    if (c->getPosicaoAtual() == j) {
                        char letra = c->getId();
                        letra = toupper(letra);
                        cout << " " << letra << " ";
                    } else if (j == 0) {
                        cout << "[" << i + 1 << "]";
                    } else
                        cout << " . ";
                }
                cout << "\n";
            }
        }
    }
    cout << endl;
}

void Corrida::passaTempo() {
    segundosDecorridos++; //aumenta os segundos da var segundo

    //VER SE ALGUM CARRO FICOU DANIFICADO ANTES DE COMEÇAR A CORRIDA
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (pilotosCorrida[i]->getC()->isDanificado()) {
            pilotosForaCorrida.push_back(pilotosCorrida[i]);
            autodromo->adicionaCarroGaragem(pilotosCorrida[i]->getC());
            removePilotoDaCorrida(pilotosCorrida[i]);
            //piloto morre
            pilotosCorrida[i]->setMorto(true);
        }
    }

    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (pilotosCorrida[i]->getIniciaNoSegundo() <= segundosDecorridos && !(pilotosCorrida[i]->getC()->isDanificado())) {
            if (i + 1 != pilotosCorrida.size()) {
                pilotosCorrida[i]->entraEmAcao(segundosDecorridos, pilotosCorrida[i - 1]);
            } else
                pilotosCorrida[i]->entraEmAcao(segundosDecorridos, nullptr);
            if (pilotosCorrida[i]->getC()->getPosicaoAtual() >= autodromo->getCompPista()) {
                pilotosCorrida[i]->getC()->setPosicao(autodromo->getCompPista());
            }
        }
    }

    mostraPista();

    //VER SE ALGUM PILOTO LIGOU O SINAL DE EMERGÊNCIA
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (pilotosCorrida[i]->getC()->isSinalEmergencia()) {
            autodromo->adicionaCarroGaragem(pilotosCorrida[i]->getC());
            removePilotoDaCorrida(pilotosCorrida[i]);
            pilotosForaCorrida.push_back(pilotosCorrida[i]);
        }
    }

    //sort lugares na corrida dos pilotos
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (pilotosCorrida[j]->getC()->getPosicaoAtual() <
                    pilotosCorrida[i]->getC()->getPosicaoAtual()) {
                Piloto *temp = pilotosCorrida[i];
                pilotosCorrida[i] = pilotosCorrida[j];
                pilotosCorrida[j] = temp;
            }
        }
    }

    //informar pilotos do seu lugar na corrida
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (i == pilotosCorrida.size()) {
            pilotosCorrida[i]->setUltimoLugar(true);
        } else {
            pilotosCorrida[i]->setUltimoLugar(false);
            if (pilotosCorrida[i]->getPosicaoActual()== 0) {
                pilotosCorrida[i]->setPosicaoActual(i + 1);
                pilotosCorrida[i]->setPosicaoAnterior(i + 1);
            } else {
                pilotosCorrida[i]->setPosicaoAnterior(pilotosCorrida[i]->getPosicaoActual());
                pilotosCorrida[i]->setPosicaoActual(i + 1);
            }
        }
    }
}

bool Corrida::verificaFinalCorrida() {
    int comp = autodromo->getCompPista();
    int flag = 0;

    for (int i = 0; i < pilotosCorrida.size(); i++) { //percorrer pilotos na corrida
        Carro *c = pilotosCorrida[i]->getC();
        if (c->getPosicaoAtual() < comp) { //Se houver algum piloto que ainda não tenha chegado ao fim
            flag++;
        }
    }
    if (flag > 0) {
        return false;
    } else {
        return true;
    }
}

bool Corrida::verificaCarroCorrida(char id) {
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (pilotosCorrida[i]->getC()->getId() == id)
            return true;
    }
    return false;
}

void Corrida::mostraVencedores() {
    for (int i = 0; i < pilotosCorrida.size(); i++) {

        if (i == 0) { //se em 1º lugar
            pilotosCorrida[i]->setPontuacao(pilotosCorrida[i]->getPontuacao() + FIRSTPLACE);
            cout << "\n Primeiro Lugar na corrida: " << pilotosCorrida[i]->getNome() <<
                    " com o carro: " << pilotosCorrida[i]->getC()->getId() <<
                    " e uma pontuacao total de: " << pilotosCorrida[i]->getPontuacao() << " pontos!!" << endl;
        }
        if (i == 1) { //se em 2º lugar
            pilotosCorrida[i]->setPontuacao(pilotosCorrida[i]->getPontuacao() + SECONDPLACE);
            cout << "\n Segundo Lugar na corrida: " << pilotosCorrida[i]->getNome() <<
                    " com o carro: " << pilotosCorrida[i]->getC()->getId() <<
                    " e uma pontuacao total de: " << pilotosCorrida[i]->getPontuacao() << " pontos!!" << endl;
        }
        if (i == 2) { //se em 3ºlugar
            pilotosCorrida[i]->setPontuacao(pilotosCorrida[i]->getPontuacao() + THIRDPLACE);
            cout << "\n Terceiro Lugar na corrida: " << pilotosCorrida[i]->getNome() <<
                    " com o carro: " << pilotosCorrida[i]->getC()->getId() <<
                    " e uma pontuacao total de: " << pilotosCorrida[i]->getPontuacao() << " pontos!!" << endl;
        }
    }
}

bool Corrida::removePilotoDaCorrida(Piloto* p) {
    for (auto it = pilotosCorrida.begin(); it != pilotosCorrida.end(); it++) {
        if ((*it) == p) {
            p->setTemCarro(false);
            pilotosCorrida.erase(it);
            return true;
        }
    }
    return false;
}

//para remover o carro é preciso remover o piloto

bool Corrida::removeCarroDaCorrida(char id) {
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (id == pilotosCorrida[i]->getC()->getId()) {

            pilotosForaCorrida.push_back(pilotosCorrida[i]);
            removePilotoDaCorrida(pilotosCorrida[i]);

            return true;
        }
    }
    return false;
}

bool Corrida::removePilotoApenasDeUmaCorrida(Piloto* p) {
    for (auto it = pilotosCorrida.begin(); it != pilotosCorrida.end(); it++) {
        if ((*it) == p) {
            pilotosCorrida.erase(it);
            return true;
        }
    }
    return false;
}

bool Corrida::saiDaCorrida(string nome) {
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (nome == pilotosCorrida[i]->getNome()) {
            if (removePilotoApenasDeUmaCorrida(pilotosCorrida[i]))
                return true;
        }
    }
    return false;
}

void Corrida::mostraCarrosGaragem() {
    autodromo->mostraCarrosGaragem();
}

void Corrida::mostraInfoCarros() {
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        cout << pilotosCorrida[i]->getC()->getAsString() << endl;
    }
}

void Corrida::mostraInfoCorrida() {
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        if (pilotosCorrida[i]->getInfoPilotoCarro() != "") {
            cout << "Info durante a corrida para o piloto: " << pilotosCorrida[i]->getNome() 
                    << " com o carro: " << pilotosCorrida[i]->getC()->getId() << endl;
            cout << pilotosCorrida[i]->getInfoPilotoCarro() << endl;
        }
    }

    for (int i = 0; i < pilotosForaCorrida.size(); i++) {
        if (pilotosForaCorrida[i]->getInfoPilotoCarro() != "") {
            cout << "Info durante a corrida para o piloto que ja esta fora da corrida: " 
                    << pilotosForaCorrida[i]->getNome() << endl;
            cout << pilotosForaCorrida[i]->getInfoPilotoCarro() << endl;
        }
    }
}

void Corrida::mostraLogMensagens() {
    for (int i = 0; i < pilotosCorrida.size(); i++) {
        cout << "Log de mensagens para o piloto: " << pilotosCorrida[i]->getNome() 
                << " com o carro: " << pilotosCorrida[i]->getC()->getId() << endl;
        cout << pilotosCorrida[i]->getLog() << endl;
    }

    for (int i = 0; i < pilotosForaCorrida.size(); i++) {
        if (pilotosForaCorrida[i]->getLog() != "") {

            cout << "Log de mensagens para o piloto que ja esta fora da corrida: " 
                    << pilotosForaCorrida[i]->getNome() << endl;
            cout << pilotosForaCorrida[i]->getLog() << endl;
        }

    }
}
