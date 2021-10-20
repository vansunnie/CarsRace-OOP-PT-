#include "Piloto.h"

int Piloto::identificacao = 0;


//    void adicionaMensagemAoLog(const string &mensagem);
//    string getLog();
//    void adicionaMensagemAoInfoPilotoCarro(const string &mensagem);
//    string getInfoPilotoCarro();
//    void limpaLog();
//    void limpaInfo();
//    string getAsString() const;
//    virtual void iniciaCorrida() = 0; //=0 faz com que a classe seja abstracta
//    virtual void entraEmAcao(int segundos, Piloto* p) = 0;
//    virtual Piloto* duplica()const = 0;
//    Piloto& operator=(const Piloto& orig);

Piloto::Piloto(string nome) : nome(nome) {
    temCarro = false;
    identificacao++;
    id = identificacao;
    pontuacao = 0;
    iniciaNoSegundo = 0;

    //Crazy
    posicaoActual = 0;
    posicaoAnterior = 0;
    ultimoLugar = false;

    morto = false;
}

Piloto::Piloto(const Piloto& other) {
    c = nullptr; //para quando se chamar operador atribuição ele poder fazer delete (este delete não irá funcionar se carro estiver a apontar para lixo)
    *this = other; //isto chama o operador atribuição... se nao o tivermos temos de chamar campo a campo
}

Piloto::~Piloto() {
}

string Piloto::getNome() const {
    return nome;
}

void Piloto::setNome(string nome) {
    this->nome = nome;
}

int Piloto::getLinha() const {
    return linha;
}

void Piloto::setLinha(int linha) {
    this->linha = linha;
}

int Piloto::getPontuacao() const {
    return pontuacao;
}

void Piloto::setPontuacao(int pontuacao) {
    this->pontuacao = pontuacao;
}

int Piloto::getIniciaNoSegundo() const {
    return iniciaNoSegundo;
}

bool Piloto::isTemCarro() const {
    return temCarro;
}

void Piloto::setTemCarro(bool temCarro) {
    this->temCarro = temCarro;
    if (temCarro == false)
        c = nullptr;
}

int Piloto::getPosicaoActual() const {
    return posicaoActual;
}

void Piloto::setPosicaoActual(int posActual) {
    this->posicaoActual = posActual;
}

int Piloto::getPosicaoAnterior() const {
    return posicaoAnterior;
}

void Piloto::setPosicaoAnterior(int posAnterior) {
    this->posicaoAnterior = posAnterior;
}

void Piloto::setUltimoLugar(bool ultimoLugar) {
    this->ultimoLugar = ultimoLugar;
}

bool Piloto::isMorto() const {
    return morto;
}

void Piloto::setMorto(bool morto) {
    this->morto = morto;
}

Carro* Piloto::getC() const {
    return c;
}

void Piloto::associaCarro(Carro* carro) {
    setTemCarro(true);
    this->c = carro;
}

void Piloto::separarDeCarro() {
    setTemCarro(false);
    this->c = nullptr;
}

char Piloto::getIdCarro() const {
    if (isTemCarro())
        return c->getId();
}

void Piloto::deleteCarro() {
    this->c = nullptr;
}

string Piloto::getLog() {
    return log.str();
}

void Piloto::adicionaMensagemAoLog(const string& mensagem) {
    log << mensagem << endl;
}

void Piloto::adicionaMensagemAoInfoPilotoCarro(const string& mensagem) {
    infoPilotoCarro << mensagem << endl;
}

string Piloto::getInfoPilotoCarro() {
    return infoPilotoCarro.str();
}

void Piloto::limpaLog() {
    log.str("");
    log.clear();
}

void Piloto::limpaInfo() {
    infoPilotoCarro.str("");
    infoPilotoCarro.clear();
}

string Piloto::getAsString() const {
    ostringstream os;
    os << "Nome do piloto " << id << " [" << nome << "] ";
    return os.str();
}

Piloto& Piloto::operator=(const Piloto& orig) {
    delete c;
    nome = orig.nome;
    temCarro = orig.temCarro;
    id = orig.id;
    linha = orig.linha;
    pontuacao = orig.pontuacao;
    c = orig.c;
    morto = orig.morto;

    return *this;
}
