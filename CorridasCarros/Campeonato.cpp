#include "Campeonato.h"

int Campeonato::nAutodromo = 0;

Campeonato::Campeonato() {
    numCorrida = 0;
}

Campeonato::~Campeonato() {
    //Campeonato é a classe responsável pelos autodromos e pelas corridas
    for (Autodromo* autodromo : autodromos) {
        delete (autodromo);
    }

    for (Corrida* corrida : corridas) {
        delete (corrida);
    }
}

string Campeonato::verificaNomeAutodromo(string nome) {
    int tam = autodromos.size();

    for (int i = 0; i < tam; i++) {
        if (nome == autodromos[i]->getNome()) {
            numAutodromo = nAutodromo;
            nome = geraNomeAutodromo(nome, numAutodromo);
            nAutodromo++;
        }
    }
    return nome;
}

string Campeonato::geraNomeAutodromo(string nome, int i) {
    ostringstream oss;
    oss << nome << i;
    return oss.str();
}

bool Campeonato::adicionaAutodromo(int nCar, int comp, string nome) {
    if (nome == "")
        return false;
    nome = verificaNomeAutodromo(nome);
    autodromos.push_back(new Autodromo(nome, nCar, comp));
    return true;
}

bool Campeonato::removeAutodromo(string nome) {
    for (auto it = autodromos.begin(); it != autodromos.end(); it++) {
        if ((*it)->getNome() == nome) {
            autodromos.erase(it);
            return true;
        }
    }
    return false;
}

bool Campeonato::listaAutodromos() {
    int flag = 0;

    for (int i = 0; i < autodromos.size(); i++) {
        cout << autodromos[i]->getAsString() << endl;
        flag++;
    }
    if (flag > 0)
        return true;

    cout << "A lista de AUTODROMOS encontra-se vazia!" << endl;
    return false;
}

bool Campeonato::adicionaAutodromoCampeonato(string nome) {
    int flag = 0;
    for (int i = 0; i < autodromos.size(); i++) {
        if (nome == autodromos[i]->getNome()) {
            autodromosCampeonato.push_back(autodromos[i]);
            flag++;
        }
    }
    if (flag > 0)
        return true;
    return false;
}

int Campeonato::getNumCorrida() const {
    return numCorrida;
}

void Campeonato::setNumCorrida(int numCorrida) {
    this->numCorrida = numCorrida;
}

int Campeonato::getNumTotalCorridas() const {
    return autodromosCampeonato.size();
}

void Campeonato::criaCampeonato(DGV* dgv) {
    /**********VERIFICAÇÃO SE TODOS OS AUTODROMOS INSERIDOS ESTAO NO CAMPEONATO*/
//    for (int i = 0; i < autodromosCampeonato.size(); i++) {
//        cout << "o autodromo " << autodromosCampeonato[i]->getNome() << " esta a participar" << endl;
//    }

    //ir buscar os pilotos que estao num carro
    pilotosCampeonato.clear();
    pilotosCorrida.clear();
    auto aux = dgv->getPilotos(); //vai buscar todos os pilotos guardados no dgv
    for (int i = 0; i < aux.size(); i++) { //percorre todos os pilotos
        if (aux[i]->isTemCarro()) { //se o piloto lido estiver associado a um carro
            pilotosCampeonato.push_back(aux[i]); //adiciona o piloto ao vector pilotosCampeonato (pilotos que podem participar no campeonato)
        }
    }

    int nPilotos = pilotosCampeonato.size();
    int nMaxCar = autodromosCampeonato[numCorrida]->getNCar(); //num máximo de carros que podem participar

    for (int j = 0; j < pilotosCampeonato.size(); j++) {
        if (nMaxCar > 0 && nPilotos > 0) { //vê se há espaço para os carros na pista e se o array de pilotos a correr não está vazio
            pilotosCampeonato[j]->setLinha(pilotosCorrida.size() + 1); //define posicao do piloto na pista (pos 0 em cada linha)
            pilotosCorrida.push_back(pilotosCampeonato[j]);
            nMaxCar--;
            nPilotos--;
        }
    }

    corridas.push_back(new Corrida(autodromosCampeonato[numCorrida], pilotosCorrida));
}

void Campeonato::passaTempo(int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i)
            corridas[i]->passaTempo();
    }
}

void Campeonato::mostraPista(int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i)
            corridas[i]->mostraPista();
    }
}

bool Campeonato::verificaFinalCorrida(int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i)
            if (corridas[i]->verificaFinalCorrida())
                return true;
            else
                return false;
    }
}

void Campeonato::vencedoresCampeonato() {
    for (int i = 0; i < pilotosCampeonato.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (pilotosCampeonato[j]->getPontuacao() < pilotosCampeonato[i]->getPontuacao()) {
                Piloto *temp = pilotosCampeonato[i];
                pilotosCampeonato[i] = pilotosCampeonato[j];
                pilotosCampeonato[j] = temp;
            }
        }
    }

    for (int i = 0; i < pilotosCampeonato.size(); i++) {
        if (i == 0)
            cout << "Campeao: " << pilotosCampeonato[i]->getNome() << endl;
        if (i == 1)
            cout << "Vice-Campeao: " << pilotosCampeonato[i]->getNome() << endl;
    }
}

void Campeonato::mostraVencedoresCorrida(int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i)
            corridas[i]->mostraVencedores();
    }
}

bool Campeonato::verificaProximaCorrida() {
    numCorrida++;
    if (autodromosCampeonato.size() < numCorrida + 1) {
        cout << "\nNao existe proxima corrida" << endl;
        return false;
    } else {
        cout << "Vamos iniciar a proxima corrida!" << endl;
        return true;
    }
}

void Campeonato::carregaTodasBaterias() {
    for (int i = 0; i < pilotosCampeonato.size(); i++) {
        Carro * c = pilotosCampeonato[i]->getC();
        c->setEnergia(c->getCapacidadeMaxima());
    }
}

void Campeonato::mostrarLogMensagens(int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i)
            corridas[i]->mostraLogMensagens();
    }
}

void Campeonato::mostraInfo(int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i)
            corridas[i]->mostraInfoCorrida();
    }
}

void Campeonato::mostraInfoCarros(int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i) {
            corridas[i]->mostraInfoCarros();
        }

    }
}

void Campeonato::mostraCarrosGaragem() {
    for (int i = 0; i < corridas.size(); i++) {
        cout << "Carros na garagem do autodromo " << corridas[i]->getAutodromo()->getNome() << ": " << endl;

        corridas[i]->mostraCarrosGaragem();
        cout << endl;
    }
}

bool Campeonato::removeCarroCorrida(char id, int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i) {
            if (corridas[i]->removeCarroDaCorrida(id))
                return true;
        }
    }

    return false;
}

bool Campeonato::saiDaCorrida(string nome, int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i) {
            if (corridas[i]->saiDaCorrida(nome))
                return true;
        }
    }
    return false;
}

bool Campeonato::verificaCarroCorrida(char id, int nCorrida) {
    for (int i = 0; i < corridas.size(); i++) {
        if (nCorrida == i) {
            if (corridas[i]->verificaCarroCorrida(id))
                return true;
        }
    }
    return false;
}

bool Campeonato::verificaPilotosSuficientes(DGV* dgv) {
    int count = 0;

    auto aux = dgv->getPilotos(); //vai buscar todos os pilotos guardados no dgv
    for (int i = 0; i < aux.size(); i++) { //percorre todos os pilotos
        if (aux[i]->isTemCarro()) { //se o piloto lido estiver associado a um carro
            count++;
        }
    }
    if (count > 1)
        return true;
    else
        return false;
}
