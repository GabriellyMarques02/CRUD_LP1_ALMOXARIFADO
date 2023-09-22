#include "Estoque.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream> // inclusão para processar o CSV

// Função para adicionar um produto ao estoque
void Estoque::adicionarProduto(const Produto& produto) {
    produtos.push_back(produto);
    //salvarParaArquivo("estoque.csv"); // Salva o estoque no arquivo após adicionar um produto
}

// Função para listar todos os produtos no estoque
void Estoque::listarProdutos() const {
    std::cout << "Produtos no estoque:" << produtos.size() << std::endl;
    for (const auto& produto : produtos) {
        std::cout << "ID: " << produto.getId() << ", Nome: " << produto.getNome() << ", Preco: " << produto.getPreco() << std::endl;
    }
}

// Função para pesquisar um produto por nome
const Produto* Estoque::pesquisarProduto(const std::string& nome) const {
    for (const auto& produto : produtos) {
        if (produto.getNome() == nome) {
            return &produto; // Retorna um ponteiro para o produto encontrado
        }
    }
    return nullptr; // Retorna nullptr se o produto não for encontrado
}

// Função para alterar um produto existente
void Estoque::alterarProduto(const std::string& nome, const Produto& novoProduto) {
    for (auto& produto : produtos) {
        if (produto.getNome() == nome) {
            produto = novoProduto; // Atualiza o produto existente com as novas informações
            std::cout << "Produto alterado com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Produto nao encontrado." << std::endl;
}

// Função para remover um produto por nome
void Estoque::removerProduto(const std::string& nome) {
    auto it = std::remove_if(produtos.begin(), produtos.end(), [&](const Produto& produto) {
        return produto.getNome() == nome;
    });

    if (it != produtos.end()) {
        produtos.erase(it, produtos.end());
        std::cout << "Produto removido com sucesso!" << std::endl;
    } else {
        std::cout << "Produto nao encontrado." << std::endl;
    }
}

// Função para exibir um relatório do estoque
void Estoque::exibirRelatorio() const {
    int totalProdutos = produtos.size();
    double valorTotal = 0.0;

    for (const auto& produto : produtos) {
        valorTotal += produto.getPreco();
    }

    std::cout << "Relatorio do Estoque:" << std::endl;
    std::cout << "Total de Produtos: " << totalProdutos << std::endl;
    std::cout << "Valor Total: R$" << valorTotal << std::endl;
}


bool Estoque::carregarDeArquivo(const std::string& nomeArquivo) {
    // Abre o arquivo para leitura
    std::ifstream arquivo;
    arquivo.open(nomeArquivo);

    std::cout << "Entra no CarregarDeArquivo"<< std:: endl;

    // Verifica se o arquivo está aberto corretamente
    if (!arquivo.is_open()) {
        // O arquivo não existe, não é um erro, apenas não há dados para carregar.
         std::cout << "Entra no teste de CarregarDeArquivo"<< std:: endl;
        return false;
    }

    std::cout << "Carregando dados do arquivo..." << std::endl;

    std::string linha;
    bool dadosLidos = false;

    // Loop para ler cada linha do arquivo
    while (std::getline(arquivo, linha)) {
        // Prepara um fluxo de string para analisar a linha
        std::istringstream ss(linha);
        int id;
        std::string nome;
        double preco;

        // Tenta extrair os dados da linha
        if (ss >> id >> nome >> preco) {
            std::cout << "Lendo: " << linha << std::endl;
            
            // Cria um objeto Produto com os dados lidos
            Produto produto(id, nome, preco);
            
            // Adiciona o produto à lista de produtos
            produtos.push_back(produto);
            dadosLidos = true;
        }
    }
     std::cout << "Saindo do while no CarregarDeArquivo"<< std:: endl;

    // Fecha o arquivo após a leitura
    arquivo.close();

    if (!dadosLidos) {
        std::cerr << "Nenhum dado válido encontrado no arquivo." << std::endl;
        return false;
    }
    
    return true;
}


// Implementação das funções para salvar dados de um arquivo
bool Estoque::salvarParaArquivo(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return false;
    }

    std::cout << "Salvando...."<< std::endl;
    
    for (const auto& produto : produtos) {
        arquivo << produto.getId() << "," << produto.getNome() << "," << produto.getPreco() << "\n";
    }

    arquivo.close();
    return true;
}





