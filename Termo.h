#ifndef TERMO_H
#define TERMO_H

#include <string>
#include <iostream>

class Termo
{
private:
    std::string termo;
    long peso;

public:
    Termo();
    Termo(std::string termo, long peso);

    // Protótipo da sobrecarga do operador de comparação '<', criado
    // para permitir que algoritmos da STL, como std::sort, ordenem
    // os objetos.
    bool operator<(const Termo &outro) const;

    // Protótipo da sobrecarga do operador de inserção em fluxo '<<'.
    // Criado para facilitar a impressão de objetos Termo em fluxos de saída.
    friend std::ostream &operator<<(std::ostream &os, const Termo &t);

    // Protótipo de método estático para comparação baseada no peso.
    static bool compararPeloPeso(const Termo &T1, const Termo &T2);

    // Protótipo de método estático para comparação de prefixo.
    // Projetado para ser usado pelo algoritmo de busca binária.
    static int compararPeloPrefixo(const Termo &T1, const std::string &prefixo);

    // Protótipos de métodos de acesso (getters).
    std::string getTermo() const;
    long getPeso() const;
};

#endif