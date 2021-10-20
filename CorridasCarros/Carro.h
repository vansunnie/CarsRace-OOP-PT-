#ifndef CARRO_H
#define CARRO_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Carro {
    string marca, modelo;
    static char letra;
    char id;
    double energia, capacidadeMaxima;
    int velocidade, velocidadeMaxima;
    int posicaoAtual = 0; //posição em m onde o carro se encontra na pista
    bool sinalEmergencia = false, danificado = false;
public:
    Carro(double energia, double capacidadeMaxima, int velocidadeMaxima,
            string marca, string modelo = "Modelo base");
    Carro(const Carro& other);
    ~Carro();

    string getMarca() const;
    void setMarca(string marca);
    
    string getModelo() const;
    void setModelo(string modelo);
    
    char getId();
    
    double getEnergia() const;
    void setEnergia(double energia);
    
    double getCapacidadeMaxima() const;
    void setCapacidadeMaxima(double capacidadeMaxima);
    
    int getVelocidade() const;
    void setVelocidade(int velocidade);
    
    int getVelocidadeMaxima() const;
    void setVelocidadeMaxima(int velocidadeMaxima);
    
    int getPosicaoAtual() const;
    void setPosicaoAtual();
    
    void setPosicao(int n);
    
    bool isSinalEmergencia() const;
    void setSinalEmergencia(bool sinalEmergencia);
    
    bool isDanificado() const;
    void setDanificado(bool danificado);
    

    void acelera();
    void trava();
    void moveCarro();
    bool emMovimento();
    
    bool carregaBateria(double n);
    void restauraValores();
    
    string getAsString() const;

    Carro* duplica();
    Carro& operator=(const Carro& orig);
};

#endif /* CARRO_H */

