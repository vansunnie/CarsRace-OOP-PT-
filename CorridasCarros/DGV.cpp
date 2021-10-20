#include "DGV.h"

int DGV::identificacao = 0;

DGV::DGV(string nome) {
    this->nome = nome;
}

DGV::DGV(const DGV& other) {
    *this = other;
}

DGV::~DGV() {
    for (Carro* carro : carros) {
        delete (carro);
    }

    for (Piloto* piloto : pilotos) {
        delete (piloto);
    }
}

string DGV::getNome() const {
    return nome;
}

void DGV::setNome(string nome) {
    cout << "Nome atribuido a dgv: " << nome << endl;
    this->nome = nome;
}

vector<Carro*> DGV::getCarros() const {
    return carros;
}

vector<Piloto*> DGV::getPilotos() const {
    return pilotos;
}

bool DGV::adicionaPiloto(string nome, string tipo) {
    nome = verificaNomePiloto(nome);
    if (tipo == "crazy") {
        pilotos.push_back(new Crazy(nome));
        return true;
    } else if (tipo == "rapido") {
        pilotos.push_back(new Rapido(nome));
        return true;
    } else if (tipo == "surpresa") {
        pilotos.push_back(new Surpresa(nome));
        return true;
    } else {
        return false;
    }
}

bool DGV::removePiloto(string nome) {
    for (auto it = pilotos.begin(); it != pilotos.end(); it++) {
        if ((*it)->getNome() == nome) {
            pilotos.erase(it);
            return true;
        }
    }
}

bool DGV::listaPilotos() {
    int flag = 0;

    for (int i = 0; i < pilotos.size(); i++) {
        cout << pilotos[i]->getAsString() << endl;
        flag++;
    }
    if (flag > 0)
        return true;
    cout << "A lista de PILOTOS encontra-se vazia!" << endl;
    return false;
}

bool DGV::adicionaCarro(double capInicial, double capMax, int velMax, string marca, string modelo) {
    if (modelo == "") {
        carros.push_back(new Carro(capInicial, capMax, velMax, marca));
        return true;
    } else {
        carros.push_back(new Carro(capInicial, capMax, velMax, marca, modelo));
        return true;
    }
    return false;
}

bool DGV::removeCarro(char id) {
    for (auto it = carros.begin(); it != carros.end(); it++) {
        if ((*it)->getId() == id) {
            carros.erase(it);

            for (int i = 0; i < pilotos.size(); i++) {
                if (pilotos[i]->isTemCarro()) {
                    if (pilotos[i]->getIdCarro() == id) {
                        pilotos[i]->deleteCarro();
                        pilotos[i]->setTemCarro(false);
                        return true;

                    }
                }
            }
        }
    }
    return false;
}

bool DGV::listaCarros() {
    int flag = 0;
    for (int i = 0; i < carros.size(); i++) {
        cout << carros[i]->getAsString() << endl;
        flag++;
    }

    if (flag > 0)
        return true;

    cout << "A lista de CARROS encontra-se vazia!" << endl;
    return false;
}

string DGV::verificaNomePiloto(string nome) {
    int tam = pilotos.size();

    for (int i = 0; i < tam; i++) {
        if (nome == pilotos[i]->getNome()) {
            id = identificacao;
            nome = geraNomePiloto(nome, id);
            cout << "\n Ja existe piloto com o mesmo nome. Vai ser alterado para: " << nome << endl;
            identificacao++;
        }
    }
    return nome;
}

bool DGV::verificaPilotoLivre(string nome) {
    for (int i = 0; i < pilotos.size(); i++) {
        if (pilotos[i]->getNome() == nome)
            if (pilotos[i]->isTemCarro())
                return false;
    }
    return true;
}

string DGV::geraNomePiloto(string nome, int i) {
    ostringstream oss;
    oss << nome << i;
    return oss.str();
}

bool DGV::pilotoExiste(string nome) {
    for (int i = 0; i < pilotos.size(); i++) {
        if (nome == pilotos[i]->getNome())
            return true;
    }
    return false;
}

bool DGV::pilotoVivo(string nome) {
    for (int i = 0; i < pilotos.size(); i++) {
        if (nome == pilotos[i]->getNome())
            if (!pilotos[i]->isMorto())
                return true;
    }
    return false;
}

bool DGV::verificaCarroLivre(char id) {
    for (int i = 0; i < pilotos.size(); i++) {
        if (pilotos[i]->isTemCarro())
            if (pilotos[i]->getIdCarro() == id) {
                return false;
            }
    }
    return true;
}

bool DGV::verificaCarroNaGaragem(char id) {
    for (int i = 0; i < carros.size(); i++) {
        if (carros[i]->isDanificado() && carros[i]->isSinalEmergencia())
            return true; //está na garagem
    }
    return false;
}

bool DGV::carroExiste(char id) {
    for (int i = 0; i < carros.size(); i++) {
        if (carros[i]->getId() == id)
            return true;
    }
    return false;
}

void DGV::entraNoCarro(char id, string nome) {
    for (int i = 0; i < pilotos.size(); i++)
        if (pilotos[i]->getNome() == nome)
            for (int j = 0; j < carros.size(); j++)
                if (carros[j]->getId() == id)
                    pilotos[i]->associaCarro(carros[j]);
}

void DGV::saiDoCarro(char id) {
    for (int i = 0; i < pilotos.size(); i++) {
        if (pilotos[i]->getIdCarro() == id) {
            pilotos[i]->separarDeCarro();
        }
    }
}

bool DGV::listaCarrosComPilotos() {
    int flag = 0;
    for (int i = 0; i < pilotos.size(); i++) {
        if (pilotos[i]->isTemCarro()) {
            cout << "Piloto [" << pilotos[i]->getNome() << "] esta no carro [" << pilotos[i]->getIdCarro() << "]" << endl;
            flag++;
        }
    }
    if (flag > 0)
        return true;
    cout << "A lista de CARROS com PILOTOS encontra-se vazia!" << endl;
    return false;
}

int DGV::pilotosComCarros() {
    int totPilotos = 0;
    for (int i = 0; i < pilotos.size(); i++) {
        if (pilotos[i]->isTemCarro())
            totPilotos++;
    }
    return totPilotos;
}

bool DGV::carregaBat(char id, double n) {
    for (int i = 0; i < carros.size(); i++) {
        if (id == carros[i]->getId()) {
            if (carros[i]->carregaBateria(n))
                return true;
        }
    }
    return false;
}

bool DGV::carregaTudo() {
    int count = 0;
    for (int i = 0; i < carros.size(); i++) {
        carros[i]->setEnergia(carros[i]->getCapacidadeMaxima());
        count++;
    }
    if (count > 0)
        return true;
    else
        return false;
}

bool DGV::provocaAcidente(char id) {
    for (int i = 0; i < carros.size(); i++) {
        if (id == carros[i]->getId()) {
            carros[i]->setDanificado(true);
            return true;
        }
    }
    return false;
}

DGV& DGV::operator=(const DGV& other) {
    nome = other.nome;

    //evitar auto-atribuição
    if (this == &other) {
        return *this;
    }

    //delete pilotos e carros
    for (auto piloto : pilotos)
        delete piloto;
    for (auto carro : carros)
        delete carro;

    //limpar os vetores
    pilotos.clear();
    carros.clear();

    //salvar duplicados
    for (int i = 0; i < other.pilotos.size(); i++) {
        Piloto *p = other.pilotos[i]->duplica();
        pilotos.push_back(p);
    }
    for (int i = 0; i < other.carros.size(); i++) {
        Carro *c = other.carros[i]->duplica();
        carros.push_back(c);
    }

    identificacao = other.identificacao;
    return *this;
}
