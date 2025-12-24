// Autocompletar.cpp

#include "Autocompletar.h"
#include <fstream>   // Para manipulação de fluxos de arquivo (std::ifstream).
#include <algorithm> // Para o algoritmo std::sort.
#include <stdexcept> // Para as classes de exceção padrão (std::runtime_error).

// Implementação do construtor da classe Autocompletar.
// Responsável pela carga, parsing e pré-processamento dos dados.
Autocompletar::Autocompletar(const std::string &nome_arquivo)
{
    // Tentativa de abrir o arquivo de dados para leitura.
    std::ifstream arquivo(nome_arquivo);
    // Validação da abertura do arquivo. Se falhar, uma exceção é lançada
    // para sinalizar o erro de forma controlada.
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Nao foi possivel abrir o arquivo: " + nome_arquivo);
    }

    long peso;
    std::string termo_str;

    // Consome a primeira linha do arquivo, útil para datasets com cabeçalho.
    std::getline(arquivo, termo_str);

    // Loop de leitura e parsing dos dados do arquivo.
    // A condição continua enquanto for possível ler um 'long' (peso) e a linha seguinte (termo).
    while (arquivo >> peso && std::getline(arquivo, termo_str))
    {
        // Tratamento para remover um caractere de tabulação residual no início da string.
        if (!termo_str.empty() && termo_str[0] == '\t')
        {
            termo_str.erase(0, 1);
        }
        // Adiciona um novo objeto Termo ao vetor, desde que o termo não seja vazio.
        if (!termo_str.empty())
        {
            termos.push_back(Termo(termo_str, peso));
        }
    }

    // Etapa de pré-processamento fundamental: ordena todo o vetor lexicograficamente.
    // Esta operação, com complexidade O(N log N), é executada uma única vez e é
    // o pré-requisito para viabilizar a busca binária de complexidade O(log N) posteriormente.
    std::sort(termos.begin(), termos.end());
}

// Implementação da busca binária modificada para encontrar o primeiro índice de correspondência.
int Autocompletar::primeiroQueCasa(const std::string &prefixo)
{
    int low = 0, high = termos.size() - 1, idx = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int cmp = Termo::compararPeloPrefixo(termos[mid], prefixo);

        if (cmp == 0)
        {                   // Se uma correspondência é encontrada...
            idx = mid;      // ... o índice é salvo...
            high = mid - 1; // ... e a busca continua na metade esquerda para encontrar um índice menor.
        }
        else if (cmp < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return idx;
}

// Implementação da busca binária modificada para encontrar o último índice de correspondência.
int Autocompletar::ultimoQueCasa(const std::string &prefixo)
{
    int low = 0, high = termos.size() - 1, idx = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int cmp = Termo::compararPeloPrefixo(termos[mid], prefixo);

        if (cmp == 0)
        {                  // Se uma correspondência é encontrada.
            idx = mid;     //  o índice é salvo.
            low = mid + 1; //  e a busca continua na metade direita para encontrar um índice maior.
        }
        else if (cmp < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return idx;
}

// Implementação do método público que orquestra a busca completa.
std::vector<Termo> Autocompletar::todasAsCorrespondencias(const std::string &prefixo)
{
    std::vector<Termo> correspondencias;
    if (prefixo.empty())
    {
        return correspondencias;
    }

    // 1. Encontra os índices de início e fim do bloco de correspondências.
    int primeiro = primeiroQueCasa(prefixo);
    if (primeiro == -1)
    {
        return correspondencias; // Retorna vazio se nenhuma correspondência for encontrada.
    }
    int ultimo = ultimoQueCasa(prefixo);

    // 2. Copia o sub-vetor de correspondências para um novo vetor.
    for (int i = primeiro; i <= ultimo; ++i)
    {
        correspondencias.push_back(termos[i]);
    }

    // 3. Ordena o novo vetor de correspondências por peso, em ordem decrescente.
    std::sort(correspondencias.begin(), correspondencias.end(), Termo::compararPeloPeso);

    return correspondencias;
}