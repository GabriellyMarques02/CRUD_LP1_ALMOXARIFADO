#include "Estoque.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream> // inclusão para processar o CSV

// Função para adicionar um produto ao estoque
void Estoque::adicionarProduto(const Produto& produto) {
    produtos.push_back(produto);
}

// Função para listar todos os produtos no estoque
void Estoque::listarProdutos() const {
    std::cout << "Produtos no estoque:" << std::endl;
    for (const auto& produto : produtos) {
        std::cout << "ID: " << produto.getId() << ", Nome: " << produto.getNome() << ", Preço: " << produto.getPreco() << std::endl;
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
    std::cout << "Produto não encontrado." << std::endl;
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
        std::cout << "Produto não encontrado." << std::endl;
    }
}

// Função para exibir um relatório do estoque
void Estoque::exibirRelatorio() const {
    int totalProdutos = produtos.size();
    double valorTotal = 0.0;

    for (const auto& produto : produtos) {
        valorTotal += produto.getPreco();
    }

    std::cout << "Relatório do Estoque:" << std::endl;
    std::cout << "Total de Produtos: " << totalProdutos << std::endl;
    std::cout << "Valor Total: R$" << valorTotal << std::endl;
}

//Criando o arquivo, caso não tenham
bool Estoque::carregarDeArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "O arquivo não existe ou não pode ser aberto. Um novo arquivo será criado." << std::endl;
        
        // Crie um novo arquivo
        std::ofstream novoArquivo(nomeArquivo);
        if (!novoArquivo.is_open()) {
            std::cerr << "Erro ao criar o novo arquivo." << std::endl;
            return false;
        }
        novoArquivo.close();
    } else {
        produtos.clear(); // Limpa os produtos existentes

        std::string linha;
        bool dadosLidos = false;

        while (std::getline(arquivo, linha)) {
            std::istringstream ss(linha);
            int id;
            std::string nome;
            double preco;

            if (ss >> id >> nome >> preco) {
                Produto produto(id, nome, preco);
                produtos.push_back(produto);
                dadosLidos = true;
            }
        }

        arquivo.close();

        if (!dadosLidos) {
            std::cerr << "Nenhum dado válido encontrado no arquivo." << std::endl;
            return false;
        }
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

    for (const auto& produto : produtos) {
        arquivo << produto.getId() << "," << produto.getNome() << "," << produto.getPreco() << "\n";
    }

    arquivo.close();
    return true;
}


