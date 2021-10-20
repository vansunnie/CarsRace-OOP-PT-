#ifndef DGV_H
#define DGV_H

#include "Carro.h"
#include "Piloto.h"
#include "Crazy.h"
#include "Rapido.h"
#include "Surpresa.h"

#include <vector>

class DGV {
    //regista todos os carros e pilotos

    vector<Carro *> carros;
    vector<Piloto *> pilotos;

    static int identificacao;
    int id;
    string nome;

public:

    DGV(string nome = "unsaved");
    DGV(const DGV & other);
    ~DGV();

    string getNome() const;
    void setNome(string nome);
    
    vector<Carro*> getCarros() const;
    vector<Piloto*> getPilotos() const;

    bool adicionaPiloto(string nome, string tipo);
    bool removePiloto(string nome);
    bool listaPilotos();

    bool adicionaCarro(double capInicial, double capMax, int velMax, string marca, string modelo);
    bool removeCarro(char id);
    bool listaCarros();

    string verificaNomePiloto(string nome);
    bool verificaPilotoLivre(string nome);
    string geraNomePiloto(string nome, int i);
    bool pilotoExiste(string nome);
    bool pilotoVivo(string nome);

    bool verificaCarroLivre(char id);
    bool verificaCarroNaGaragem(char id);
    bool carroExiste(char id);

    void entraNoCarro(char id, string nome);
    void saiDoCarro(char id);

    bool listaCarrosComPilotos();
    int pilotosComCarros();

    bool carregaBat(char id, double n);
    bool carregaTudo();
    bool provocaAcidente(char id);

    DGV& operator=(const DGV& other);
};

#endif /* DGV_H */

