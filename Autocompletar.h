#ifndef AUTOCOMPLETAR_H
#define AUTOCOMPLETAR_H

#include <string>
#include <vector>
#include "Termo.h"

class Autocompletar {
private:
    std::vector<Termo> termos;

    // Protótipos para as funções auxiliares (helpers) da busca binária. 
    int primeiroQueCasa(const std::string& prefixo);
    int ultimoQueCasa(const std::string& prefixo);

public:
    // Protótipo do construtor, que requer o caminho do arquivo de dados para inicialização.
    Autocompletar(const std::string& nome_arquivo);

    // Protótipo do método público principal, que executa a busca e retorna os resultados.
    std::vector<Termo> todasAsCorrespondencias(const std::string& prefixo);
};

#endif 