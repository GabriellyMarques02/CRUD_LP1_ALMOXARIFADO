#include "Gerenciador.h"
#include <iostream>

// Implementação das funções utilitárias
std::string Gerenciador::lerString(const std::string& mensagem) const {
    std::string entrada;
    std::cout << mensagem;
    std::cin >> entrada;
    return entrada;
}

int Gerenciador::lerInteiro(const std::string& mensagem) const {
    int entrada;
    std::cout << mensagem;
    std::cin >> entrada;
    return entrada;
}

double Gerenciador::lerDouble(const std::string& mensagem) const {
    double entrada;
    std::cout << mensagem;
    std::cin >> entrada;
    return entrada;
}

// Implementação das funções de interação do usuário
void Gerenciador::adicionarProduto(Estoque& estoque) {
    int id = lerInteiro("Digite o ID do produto: ");
    std::string nome = lerString("Digite o nome do produto: ");
    double preco = lerDouble("Digite o preco do produto: ");

    Produto novoProduto(id, nome, preco);
    estoque.adicionarProduto(novoProduto);
    std::cout << "Produto adicionado com sucesso!" << std::endl;
}

void Gerenciador::listarProdutos(const Estoque& estoque) {
    estoque.listarProdutos();
}

void Gerenciador::pesquisarExibirProduto(const Estoque& estoque) {
    std::string nome = lerString("Digite o nome do produto a ser pesquisado: ");
    const Produto* produto = estoque.pesquisarProduto(nome);

    if (produto) {
        std::cout << "Produto encontrado:" << std::endl;
        std::cout << "ID: " << produto->getId() << ", Nome: " << produto->getNome() << ", Preco: " << produto->getPreco() << std::endl;
    } else {
        std::cout << "Produto nao encontrado." << std::endl;
    }
}

void Gerenciador::alterarProduto(Estoque& estoque) {
    std::string nome = lerString("Digite o nome do produto a ser alterado: ");
    const Produto* produto = estoque.pesquisarProduto(nome);

    if (produto) {
        int id = produto->getId();
        std::string novoNome = lerString("Digite o novo nome do produto: ");
        double novoPreco = lerDouble("Digite o novo preço do produto: ");

        Produto novoProduto(id, novoNome, novoPreco);
        estoque.alterarProduto(nome, novoProduto);
    } else {
        std::cout << "Produto nao encontrado." << std::endl;
    }
}

void Gerenciador::removerProduto(Estoque& estoque) {
    std::string nome = lerString("Digite o nome do produto a ser removido: ");
    estoque.removerProduto(nome);
}

void Gerenciador::exibirRelatorioEstoque(const Estoque& estoque) {
    //std::cout << "Relatorio do Estoque:" << std::endl;
    estoque.exibirRelatorio();
}

void Gerenciador::executar() {
    Estoque estoque; // Cria um objeto Estoque

    // Carrega os dados do arquivo no início do programa
    if (!estoque.carregarDeArquivo("estoque.csv")) {
        std::cerr << "Falha ao carregar dados do arquivo." << std::endl;
        return;
    }

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Adicionar Produto\n";
        std::cout << "2. Listar Produtos\n";
        std::cout << "3. Pesquisar e Exibir Produto\n";
        std::cout << "4. Alterar Produto\n";
        std::cout << "5. Remover Produto\n";
        std::cout << "6. Exibir Relatorio de Estoque\n";
        std::cout << "7. Sair\n";
        int opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                adicionarProduto(estoque);
                break;
            case 2:
                listarProdutos(estoque);
                break;
            case 3:
                pesquisarExibirProduto(estoque);
                break;
            case 4:
                alterarProduto(estoque);
                break;
            case 5:
                removerProduto(estoque);
                break;
            case 6:
                exibirRelatorioEstoque(estoque);
                break;
            case 7:
                std::cout << "Saindo do programa..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida!" << std::endl;

        }
        if(opcao ==7){
            break;
        }
    }

    // Salva os dados no arquivo ao finalizar o programa
    if (!estoque.salvarParaArquivo("estoque.csv")) {
        std::cerr << "Falha ao salvar dados no arquivo." << std::endl;
        return;
    }
}

