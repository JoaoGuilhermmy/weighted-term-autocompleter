// main.cpp

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Autocompletar.h"
#include "Termo.h"

// Ponto de entrada da aplicação.
// Recebe argumentos da linha de comando para configuração.
int main(int argc, char* argv[]) {
    // Validação do número de argumentos da linha de comando.
    if (argc != 3) {
        // Imprime mensagem de uso no fluxo de erro padrão se os argumentos forem inválidos.
        std::cerr << "Uso: " << argv[0] << " <arquivo_dataset> <k>" << std::endl;
        return 1; // Retorna um código de erro.
    }

    // Bloco try-catch para tratamento de exceções que possam ocorrer durante a execução.
    try {
        // Extrai o nome do arquivo e o valor de 'k' dos argumentos.
        std::string nome_arquivo = argv[1];
        int k = std::stoi(argv[2]); // std::stoi converte string para inteiro.

        // Instanciação do objeto Autocompletar, disparando o carregamento e ordenação dos dados.
        Autocompletar ac(nome_arquivo);
        std::string prefixo;

        // Loop principal da aplicação, para interação contínua com o usuário.
        while (true) {
            std::cout << std::endl << "Entre com o termo a ser auto-completado: (digite \"sair\" para encerrar o programa):" << std::endl;
            // Lê a linha inteira da entrada do usuário para permitir prefixos com espaços.
            std::getline(std::cin, prefixo);

            // Condição de término do loop.
            if (prefixo == "sair") {
                break;
            }

            // Executa a busca e armazena os resultados.
            std::vector<Termo> correspondencias = ac.todasAsCorrespondencias(prefixo);

            // Itera sobre os resultados e os imprime, respeitando o limite 'k'.
            int count = 0;
            for (const auto& termo : correspondencias) {
                if (count >= k) {
                    break;
                }
                std::cout << termo << std::endl;
                count++;
            }
        }
    } catch (const std::exception& e) {
        // Captura exceções padrão (ex: erro ao abrir arquivo, argumento 'k' inválido)
        // e informa o erro ao usuário antes de encerrar.
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0; // Retorna 0 para indicar execução bem-sucedida.
}