#ifndef CAMPEONATO_H
#define CAMPEONATO_H


#include <vector>
#include "Autodromo.h"
#include "Corrida.h"
#include "DGV.h"

class Campeonato {
    vector <Autodromo *> autodromos;
    vector <Autodromo *> autodromosCampeonato; //autodromos que participam no campeonato
    vector <Corrida *> corridas; //o campeonato tem um conjunto de corridas
    vector <Piloto *> pilotosCampeonato; //pilotos que participam no campeonato
    vector <Piloto *> pilotosCorrida; //pilotos que participam na corrida
    static int nAutodromo;
    int numAutodromo;
    int numCorrida;
public:
    Campeonato();
    ~Campeonato();
    
    string verificaNomeAutodromo(string nome);
    string geraNomeAutodromo(string nome, int i);
    
    bool adicionaAutodromo(int nCar, int comp, string nome);
    bool removeAutodromo(string nome);
    bool listaAutodromos();
    
    bool adicionaAutodromoCampeonato(string nome);
    
    int getNumCorrida() const;
    int getNumTotalCorridas() const;
    void setNumCorrida(int numCorrida);
    
    void criaCampeonato(DGV *dgv);
    void passaTempo(int nCorrida);
    void mostraPista(int nCorrida);
    bool verificaFinalCorrida(int nCorrida);
    void vencedoresCampeonato();
    void mostraVencedoresCorrida(int nCorrida);
    bool verificaProximaCorrida();
    
    void carregaTodasBaterias();
    
    void mostrarLogMensagens(int nCorrida);
    void mostraInfo(int nCorrida);
    void mostraInfoCarros(int nCorrida);
    void mostraCarrosGaragem();
    
    bool removeCarroCorrida(char id, int nCorrida);
    bool saiDaCorrida(string nome, int nCorrida);
    bool verificaCarroCorrida(char id, int nCorrida);
    bool verificaPilotosSuficientes(DGV * dgv);
    
};

#endif /* CAMPEONATO_H */

