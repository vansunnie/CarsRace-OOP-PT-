#ifndef PILOTO_H
#define PILOTO_H


#include <cstdlib>
#include <string>
#include <sstream>

#include "Autodromo.h"
#include "Carro.h"

class Piloto {
protected:
    string nome;
    int id;
    int linha;
    int pontuacao;
    int iniciaNoSegundo; //saber em que segundo o piloto inicia a corrida
    bool temCarro;
    
    //crazy
    int posicaoActual;
    int posicaoAnterior;
    bool ultimoLugar;
    
    bool morto;

    static int identificacao;

    Carro *c = nullptr;

    ostringstream log; //log de mensagens
    ostringstream infoPilotoCarro;

public:
    Piloto(string nome);
    Piloto(const Piloto& other);
    ~Piloto();

    string getNome() const;
    void setNome(string nome);

    int getLinha() const;
    void setLinha(int linha);

    int getPontuacao() const;
    void setPontuacao(int pontuacao);

    int getIniciaNoSegundo() const;

    bool isTemCarro() const;
    void setTemCarro(bool temCarro);

    int getPosicaoActual() const;
    void setPosicaoActual(int posActual);

    int getPosicaoAnterior() const;
    void setPosicaoAnterior(int posAnterior);

    void setUltimoLugar(bool ultimoLugar);

    bool isMorto() const;
    void setMorto(bool morto);

    Carro* getC() const;

    void associaCarro(Carro *carro);
    void separarDeCarro();

    char getIdCarro() const;

    void deleteCarro();

    string getLog();
    void adicionaMensagemAoLog(const string &mensagem);
    void adicionaMensagemAoInfoPilotoCarro(const string &mensagem);
    string getInfoPilotoCarro();

    void limpaLog();
    void limpaInfo();

    string getAsString() const;

    virtual void iniciaCorrida() = 0; //=0 faz com que a classe seja abstracta
    virtual void entraEmAcao(int segundos, Piloto* p) = 0;
    virtual Piloto* duplica()const = 0;

    Piloto& operator=(const Piloto& orig);

};

#endif /* PILOTO_H */

