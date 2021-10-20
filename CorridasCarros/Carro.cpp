#include "Carro.h"

char Carro::letra = 96;

Carro::Carro(double energia, double capacidadeMaxima, int velocidadeMaxima, string marca, string modelo) :
marca(marca), modelo(modelo), energia(energia), capacidadeMaxima(capacidadeMaxima), velocidadeMaxima(velocidadeMaxima) {
    if (letra == 'z' || letra == '?')
        letra = '?';
    else
        letra++;
    id = letra;

    velocidade = 0;
}

//chama o operador atribuição...

Carro::Carro(const Carro& other) {
    *this = other;
}

Carro::~Carro() {
}

string Carro::getMarca() const {
    return marca;
}

void Carro::setMarca(string marca) {
    this->marca = marca;
}

string Carro::getModelo() const {
    return modelo;
}

void Carro::setModelo(string modelo) {
    this->modelo = modelo;
}

char Carro::getId() {
    return id;
}

double Carro::getEnergia() const {
    return energia;
}

void Carro::setEnergia(double energia) {
    this->energia = energia;
}

double Carro::getCapacidadeMaxima() const {
    return capacidadeMaxima;
}

void Carro::setCapacidadeMaxima(double capacidadeMaxima) {
    this->capacidadeMaxima = capacidadeMaxima;
}

int Carro::getVelocidade() const {
    return velocidade;
}

void Carro::setVelocidade(int velocidade) {
    this->velocidade = velocidade;
}

int Carro::getVelocidadeMaxima() const {
    return velocidadeMaxima;
}

void Carro::setVelocidadeMaxima(int velocidadeMaxima) {
    this->velocidadeMaxima = velocidadeMaxima;
}

int Carro::getPosicaoAtual() const {
    return posicaoAtual;
}

void Carro::setPosicaoAtual() {
    this->posicaoAtual += velocidade;
}

void Carro::setPosicao(int n) {
    posicaoAtual = n;
}

bool Carro::isSinalEmergencia() const {
    return sinalEmergencia;
}

void Carro::setSinalEmergencia(bool sinalEmergencia) {
    this->sinalEmergencia = sinalEmergencia;
}

bool Carro::isDanificado() const {
    return danificado;
}

void Carro::setDanificado(bool danificado) {
    this->danificado = danificado;
}

void Carro::acelera() {
    if (velocidade < velocidadeMaxima)
        velocidade++;
}

void Carro::trava() {
    if (velocidade > 0)
        velocidade--;
}

void Carro::moveCarro() {
    if (energia > 0) {
        energia -= 0.1;
    }
    if (energia == 0)
        velocidade--;

    setPosicaoAtual();
}

bool Carro::emMovimento() {
    if (velocidade != 0)
        return true;
    return false;
}

bool Carro::carregaBateria(double n) { //n - valor de energia recebido
    if (emMovimento() && energia + n < capacidadeMaxima)
        if (n > 0) {
            energia += n;
            return true;
        } else {
            cout << "Valor introduzido nao valido!" << endl;
            return false;
        }
}

void Carro::restauraValores() {
    posicaoAtual = 0;
    velocidade = 0;
}

string Carro::getAsString() const {
    ostringstream oss;
    oss << "ID: " << id << "\nEnergia: " << getEnergia()
            << "\tCapacidade maxima: " << getCapacidadeMaxima()
            << "\t\tVelocidade maxima: " << getVelocidadeMaxima()
            << "\t\tMarca: " << getMarca() << "\t\tModelo: " << getModelo() << endl;
    return oss.str();
}

Carro* Carro::duplica() {
    return new Carro(*this);
}

Carro& Carro::operator=(const Carro& orig) {
    marca = orig.marca;
    modelo = orig.modelo;
    id = orig.id;
    energia = orig.energia;
    capacidadeMaxima = orig.capacidadeMaxima;
    velocidade = orig.velocidade;
    velocidadeMaxima = orig.velocidadeMaxima;
    posicaoAtual = orig.posicaoAtual;
    sinalEmergencia = orig.sinalEmergencia;
    danificado = orig.danificado;

    return *this;
}


