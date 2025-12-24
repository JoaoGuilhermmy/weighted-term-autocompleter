#include "Termo.h"

// Implementação do construtor padrão. Utiliza a lista de inicialização de membros
// para definir 'peso' como 0. O membro 'termo' é inicializado por seu próprio construtor padrão.
Termo::Termo() : peso(0) {}

// Implementação do construtor parametrizado.
// É utilizada para inicializar os membros da classe.
Termo::Termo(std::string termo, long peso) : termo(termo), peso(peso) {}

// Implementação da sobrecarga do operador '<'.
// A lógica é delegada ao operador '<' da classe std::string,
// resltando em uma comparação.
bool Termo::operator<(const Termo& outro) const {
    return this->termo < outro.termo;
}

// Implementação da sobrecarga do operador '<<'.
// Serializa o objeto Termo para um fluxo de saída (ostream), formatando
// com o peso e o termo separados por uma tabulação.
std::ostream& operator<<(std::ostream& os, const Termo& t) {
    os << t.peso << "\t" << t.termo;
    return os;
}

// Implementação do método estático de comparação por peso.
// A lógica 'T1.getPeso() > T2.getPeso()' é usada para que, quando
// esta função for passada ao std::sort, a ordenação resultante seja decrescente.
bool Termo::compararPeloPeso(const Termo& T1, const Termo& T2) {
    return T1.getPeso() > T2.getPeso();
}

// Implementação do método estático de comparação por prefixo.
// Utiliza o método 'compare' de std::string para comparar uma substring do membro 'termo'
// com o prefixo fornecido.
int Termo::compararPeloPrefixo(const Termo& T1, const std::string& prefixo) {
    return T1.getTermo().compare(0, prefixo.length(), prefixo);
}

// Implementação dos métodos de acesso (getters).
// Retornam os valores dos respectivos membros de dados privados.
std::string Termo::getTermo() const {
    return termo;
}

long Termo::getPeso() const {
    return peso;
}