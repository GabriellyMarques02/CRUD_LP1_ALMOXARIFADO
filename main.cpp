#include "Gerenciador.h"
#include "Estoque.h"

#include <iostream>
#include <fstream>
#include <string>
//#include <stdexcept> // Inclusão para captura de exceções

int main() {
    Gerenciador gerenciador;
    Estoque estoque;

    // Carrega os dados do arquivo no início do programa
    if (!estoque.carregarDeArquivo("estoque.csv")) {
        std::cerr << "Falha ao carregar dados do arquivo." << std::endl;
        return 1;
    }

    gerenciador.executar();

    // Salva os dados no arquivo ao finalizar o programa
    if (!estoque.salvarParaArquivo("estoque.csv")) {
        std::cerr << "Falha ao salvar dados no arquivo." << std::endl;
        return 1;
    }

    return 0;
}




