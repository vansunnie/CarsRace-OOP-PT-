
#include "Autodromo.h"

Autodromo::Autodromo(string name, int n, int comprimento) : nome(name), nCar(n),
compPista(comprimento) {

}

Autodromo::~Autodromo() {
}

string Autodromo::getNome() const {
    return nome;
}

int Autodromo::getNCar() const {
    return nCar;
}

int Autodromo::getCompPista() const {
    return compPista;
}

void Autodromo::adicionaCarroGaragem(Carro* c) {
    garagem.push_back(c);
}

void Autodromo::mostraCarrosGaragem() {
    for (int i = 0; i < garagem.size(); i++) {
        cout << garagem[i]->getAsString() << endl;
    }
}

string Autodromo::getAsString() {
    ostringstream oss;
    oss << "Nome: " << nome << "\tNumero maximo carros: " << nCar << "\t\tComprimento pista: " << compPista << endl;
    return oss.str();
}





