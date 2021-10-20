#include "Interface.h"

Interface::Interface() {
    this->campeonato = new Campeonato();
}

Interface::~Interface() {
    cout << "Destrutor da interface..." << endl;
    delete campeonato;
}

void Interface::menu() {
    int opcao;

    cout << "   ______                    ____                " << endl;
    cout << "  / ____/________________   / __ \\_______________ " << endl;
    cout << " / /   / __   / ___/ ___/  / /_/ / __   / ___/ _ \\ " << endl;
    cout << "/ /___/ /_/  / /  (__  )  / _  _/ /_/  / /__/  __/" << endl;
    cout << "\\____/\\__ /_/_/  /____/  /_/ |_|\\__ /_/\\___/\\___/ " << endl;
    cout << endl << endl;
    cout << "1 - INICIO" << endl;
    cout << "2 - SAIR" << endl;
    cout << "Opcao: ";
    cin >> opcao;

    do {
        switch (opcao) {
            case 1:
                cin.ignore();
                comandosModo1();
                break;
            case 2:
                return;
                break;
        }
    } while (opcao < 0 && opcao > 2);
}

void Interface::comandosModo1() {
    string input;
    comandos->listaComandosModo1();

    do {
        cout << endl << "Comando: ";
        getline(cin, input);
    } while (lerComandos1(input));
}

bool Interface::lerComandos1(string input) {
    istringstream linha(input);
    string comando;

    linha >> comando;

    //carregaP
    if (comando == "carregaP") {
        string filename;
        linha >> filename;
        if (ficheiroPilotos(filename))
            return true;
        cout << "Erro ao ler o ficheiro: " << filename << endl;
        return true;

    }//carregaC
    else if (comando == "carregaC") {
        string filename;
        linha >> filename;

        if (ficheiroCarros(filename))
            return true;
        cout << "Erro ao ler o ficheiro: " << filename << endl;
        return true;

    }//carregaA
    else if (comando == "carregaA") {
        string filename;
        linha >> filename;

        if (ficheiroAutodromos(filename))
            return true;
        cout << "Erro ao ler o ficheiro: " << filename << endl;
        return true;

    } else if (comando == "cria") {
        string letraTipo;
        linha >> letraTipo;

        if (letraTipo == "p") {
            string tipoPiloto, nome, name;
            //count - flag usada para contar os nomes lidos de um piloto
            //flag - trata do número de argumentos necessários para o comando ser válido
            int count = 0, flag = 0;

            linha >> tipoPiloto;
            flag++;
            while (linha >> nome) {
                if (count > 0)
                    name += " ";
                name += nome;
                count++;
            }
            flag++;
            if (flag < 2 || (!dgv.adicionaPiloto(name, tipoPiloto)))
                cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
        } else if (letraTipo == "c") {
            double energia, capMax;
            int velMax;
            string marca, modelo;

            if (linha >> energia >> capMax >> velMax >> marca) {
                linha >> modelo;
                dgv.adicionaCarro(energia, capMax, velMax, marca, modelo);
            } else
                cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
        } else if (letraTipo == "a") {
            int n, cmp;
            string nome;

            if (linha >> n >> cmp >> nome) {
                campeonato->adicionaAutodromo(n, cmp, nome);
            } else
                cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
        } else {
            cout << "Tipo de objeto nao identificado!" << endl;
        }
    }//apaga
    else if (comando == "apaga") {
        string letraTipo, nome;
        linha >> letraTipo;

        if (letraTipo == "p") {
            string nomePiloto;
            int count = 0;

            while (linha >> nomePiloto) {
                if (count > 0)
                    nome += " ";
                nome += nomePiloto;
                count++;
            }
            if (!dgv.removePiloto(nome)) {
                cout << "O piloto que pretende remover nao existe!\n" << endl;
            }
        } else if (letraTipo == "c") {
            char idCarro;

            if (linha >> idCarro) {
                if (!dgv.carroExiste(idCarro)) {
                    cout << "O carro que pretende remover nao existe!\n" << endl;
                }
                dgv.removeCarro(idCarro);
            } else
                cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
        } else if (letraTipo == "a") {
            string nome;

            if (linha >> nome) {
                if (!campeonato->removeAutodromo(nome)) {
                    cout << "O autodromo que pretende remover nao existe!\n" << endl;
                }
            } else
                cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
        } else {
            cout << "Tipo de objeto nao identificado!" << endl;
        }
    }//entranocarro
    else if (comando == "entranocarro") {
        char letra;
        string nome, nomePil;
        int count = 0, flag = 0;

        linha >> letra;
        flag++;

        while (linha >> nomePil) {
            flag++;
            if (count > 0)
                nome += " ";
            nome += nomePil;
            count++;
        }
        if (flag < 1) {
            cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
            return true;
        }

        if (!dgv.pilotoExiste(nome))
            cout << "O piloto nao existe!" << endl;
        else if (!dgv.pilotoVivo(nome))
            cout << "O piloto faleceu!" << endl;
        else if (!dgv.carroExiste(letra))
            cout << "O carro nao existe!" << endl;
        else if (!dgv.verificaCarroLivre(letra))
            cout << "O carro em questao ja se encontra ocupado!" << endl;
        else if (!dgv.verificaPilotoLivre(nome))
            cout << "O piloto em questao nao se encontra disponivel!" << endl;
        else if (dgv.verificaCarroNaGaragem(letra))
            cout << "Carro indisponivel por estar na garagem!" << endl;
        else
            dgv.entraNoCarro(letra, nome);

    }//saidocarro
    else if (comando == "saidocarro") {
        char letra;

        if (linha >> letra) {
            if (!dgv.carroExiste(letra))
                cout << "O carro nao existe!" << endl;
            else
                dgv.saiDoCarro(letra);
        } else
            cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
    }//lista
    else if (comando == "lista") {
        cout << "\n\tInformacao dos PILOTOS existentes" << endl;
        dgv.listaPilotos();
        cout << "\n\n\tInformacao dos CARROS existentes" << endl;
        dgv.listaCarros();
        cout << "\n\n\tInformacao dos AUTODROMOS existentes" << endl;
        campeonato->listaAutodromos();
        cout << "\n\n\tInformacao dos CARROS com PILOTOS" << endl;
        dgv.listaCarrosComPilotos();
    }//campeonato
    else if (comando == "campeonato") {
        if (dgv.pilotosComCarros() > 1) {
            string nome;

            while (linha >> nome) {
                if (!campeonato->adicionaAutodromoCampeonato(nome)) {
                    cout << "Autodromo [" << nome << "] inexistente";
                    return true;
                }
            }

            campeonato->criaCampeonato(&dgv);
            campeonato->carregaTodasBaterias();
            nCorrida = campeonato->getNumCorrida();
            campeonato->mostraPista(nCorrida);
            comandosModo2();
        } else
            cout << "Nao existem carros com pilotos suficientes" << endl;

    }//savedgv
    else if (comando == "savedgv") {
        string nome;
        if (linha >> nome) {
            DGV copia = dgv;
            copia.setNome(nome);
            dgvLista.push_back(copia);

        } else {
            cout << "Something went wrong" << endl;
        }
    }//loaddgv
    else if (comando == "loaddgv") {
        string nome;
        int count = 0;
        if (linha >> nome) {
            if (dgv.getNome() == nome) {
                cout << "A DGV que inseriu e a atual" << endl;
                return true;
            } else {
                for (int i = 0; i < dgvLista.size(); i++) {
                    if (dgvLista[i].getNome() == nome) {
                        dgv = dgvLista[i];
                        cout << "DGV carregada com sucesso" << endl;
                        count++;
                    }
                }
            }
            if (count == 0) {
                cout << "DGV nao existe" << endl;
            }
            // }
        } else {
            cout << "Nao foram introduzidos todos os dados" << endl;
        }
    }//deldgv
    else if (comando == "deldgv") {
        string nome;
        if (linha >> nome) {
            if (this->dgv.getNome() == nome) {
                cout << "A DGV que inseriu e a atual, elimine uma que nao esteja a utilizar de momento" << endl;
                return true;
            } else {
                for (int i = 0; i < dgvLista.size(); i++) {
                    if (dgvLista[i].getNome() == nome) {
                        dgvLista.erase(dgvLista.begin() + i);
                        cout << "DGV eliminada com sucesso!" << endl;
                        return true;
                    }
                }
                return false;
            }
        }
    } else if (comando == "sair" || comando == "Sair" || comando == "SAIR")
        return false;
    else {
        cout << "Comando inserido invalido! Tente novamente..." << endl;
    }

    return true;
}

void Interface::comandosModo2() {
    string input;
    comandos->listaComandosModo2();
    do {
        cout << endl << "Comando: ";
        getline(cin, input);
    } while (lerComandos2(input));
}

bool Interface::lerComandos2(string input) {
    istringstream linha(input);
    string comando;

    linha >> comando;
    if (comando == "passatempo") {
        int tempo;
        if (linha >> tempo) {
            if (tempo == 1) {
                campeonato->passaTempo(nCorrida);
            } else {
                int i = 0;
                while (!campeonato->verificaFinalCorrida(nCorrida) && i < tempo) {
                    campeonato->passaTempo(nCorrida);
                    if (!(campeonato->verificaFinalCorrida(nCorrida))) {
                        if (i != tempo - 1) {
                            cout << "Pressione uma tecla para continuar";
                            getchar();
                        }
                    }
                    i++;
                }
            }
            if (campeonato->verificaFinalCorrida(nCorrida)) {
                cout << "A corrida terminou!!" << endl;
                campeonato->mostraVencedoresCorrida(nCorrida);
                return true;
            }
        } else {
            cout << "Tempo (em segundos) nao foi inserido! Tente novamente..." << endl;
        }
        return true;

    } else if (comando == "corrida") { //ir para a proxima corrida
        if (!campeonato->verificaFinalCorrida(nCorrida)) {
            cout << "\n\nA corrida anterior tem de terminar primeiro!" << endl;
            return true;
        } else {
            if (!campeonato->verificaProximaCorrida()) { //se nao há proxima corrida
                cout << "\nNao existem mais corridas. O Campeonato chegou ao fim!" << endl;
                cout << "VENCEDORES DO CAMPEONATO:" << endl;
                campeonato->vencedoresCampeonato();
                return false;
            } else {
                if (campeonato->verificaPilotosSuficientes(&dgv)) {
                    campeonato->criaCampeonato(&dgv);
                    nCorrida = campeonato->getNumCorrida();
                    campeonato->mostraPista(nCorrida);
                    comandosModo2();
                } else {
                    cout << "\nNao ha pilotos suficientes para uma corrida. O Campeonato chegou ao fim!" << endl;
                    cout << "VENCEDORES DO CAMPEONATO:" << endl;
                    campeonato->vencedoresCampeonato();
                    return false;
                }
            }
        }

    } else if (comando == "listacarros") {
        campeonato->mostraInfoCarros(nCorrida);

    } else if (comando == "carregabat") {
        char letraCarro;
        double energia;

        if (linha >> letraCarro >> energia) {
            if (dgv.carregaBat(letraCarro, energia)) {
                cout << "Carro carregado com sucesso!" << endl;
            } else {
                cout << "Houve algum problema no carregamento. Verifique se introduziu um carro válido." << endl;
            }
        } else
            cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;

    } else if (comando == "carregatudo") {
        if (dgv.carregaTudo()) {
            cout << "Carros carregados com sucesso!" << endl;
        } else {
            cout << "Houve algum problema no carregamento." << endl;
        }

    } else if (comando == "acidente") {
        char letraCarro;

        if (linha >> letraCarro) {
            if (campeonato->verificaCarroCorrida(letraCarro, nCorrida)) {
                dgv.provocaAcidente(letraCarro);
                cout << "Acidente provocado com sucesso!" << endl;
            } else {
                cout << "Houve algum problema. Verifique se introduziu um carro válido." << endl;
            }
        } else
            cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;

    } else if (comando == "stop") {
        string nome;

        if (linha >> nome) {
            if (campeonato->saiDaCorrida(nome, nCorrida)) {
                cout << "Piloto saiu da corrida!" << endl;
            } else {
                cout << "Houve algum problema. Verifique se introduziu um piloto válido." << endl;
            }
        } else
            cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;

    } else if (comando == "destroi") {
        char letraCarro;

        if (linha >> letraCarro) {
            if (campeonato->removeCarroCorrida(letraCarro, nCorrida)) {
                cout << "Carro destruido com sucesso!" << endl;
                dgv.removeCarro(letraCarro);
            } else {
                cout << "Houve algum problema. Verifique se introduziu um carro válido." << endl;
            }
        } else
            cout << "Ups, nao foram inseridos todos os dados necessarios!\n" << endl;
    } else if (comando == "log") {
        campeonato->mostrarLogMensagens(nCorrida);

    } else if (comando == "info") { //informacao no decorrer da corrida para cada carro (o que faz, acelera, trava etc)
        campeonato->mostraInfo(nCorrida);

    } else if (comando == "garagem") {
        campeonato->mostraCarrosGaragem();

    } else if (comando == "modo1") {
        comandosModo1();

    } else if (comando == "sair" || comando == "Sair" || comando == "SAIR") {
        cout << "Estas de volta ao modo 1" << endl;
        return false;

    } else {
        cout << "Comando inserido invalido! Tente novamente..." << endl;
    }

    return true;
}

bool Interface::ficheiroPilotos(string nomeFich) {
    ifstream f(nomeFich);
    string linha;

    if (f.is_open()) {
        while (getline(f, linha)) {
            istringstream piloto(linha);
            string tipo, nome, nomePil;
            int count = 0;

            piloto >> tipo;

            while (piloto >> nomePil) {
                if (count > 0)
                    nome += " ";
                nome += nomePil;
                count++;
            }
            dgv.adicionaPiloto(nome, tipo);
        }
    } else return false;
    f.close();
    return true;
}

bool Interface::ficheiroCarros(string nomeFich) {
    ifstream f(nomeFich);
    string linha;

    if (f.is_open()) {
        while (getline(f, linha)) {
            stringstream carro(linha);
            double capInicial, capMax;
            int velMax;
            string marca, modelo;

            if (carro >> capInicial >> capMax >> velMax >> marca) {
                carro >> modelo;
                dgv.adicionaCarro(capInicial, capMax, velMax, marca, modelo);
            } else
                cout << "Ficheiro de texto invalido!" << endl;
        }
    } else
        return false;
    f.close();
    return true;
}

bool Interface::ficheiroAutodromos(string nomeFich) {
    ifstream f(nomeFich);
    string linha;

    if (f.is_open()) {
        while (getline(f, linha)) {
            stringstream autodromo(linha);
            int nCar, comp;
            string nome;

            if (autodromo >> nCar >> comp >> nome) {
                campeonato->adicionaAutodromo(nCar, comp, nome);
            } else
                cout << "Ficheiro de texto invalido!" << endl;
        }
    } else return false;
    f.close();
    return true;
}
