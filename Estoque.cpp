#include "Estoque.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream> // inclusão para processar o CSV

Estoque::Estoque() {}

// Função para adicionar um produto ao estoque
void Estoque::adicionarProduto(const Produto& produto) {
   
    produtoSalvar = produto;  

    

    // Salvando no arquivo
    if (!this->salvarParaArquivo("estoque.csv")) {
        std::cerr << "Falha ao salvar dados no arquivo." << std::endl;
        return;
    }
}



// Função para listar todos os produtos no estoque
void Estoque::listarProdutos() const {

    std::cout << "Produtos no estoque:" << produtos.size() << std::endl;
    for (const auto& produto : produtos) {
        std::cout << "ID: " << produto.getId() << ", Nome: " << produto.getNome() << ", Preco: " << produto.getPreco() << std::endl;
    }
    
}

// Função para pesquisar um produto por nome
Produto* Estoque::pesquisarProduto(const std::string& nome) {
    produtos.clear();
    
    if (!this->carregarDeArquivo("estoque.csv")) {
        std::cerr << "Falha ao carregar dados do arquivo." << std::endl;
        return nullptr;
    }
    
    for (auto& produto : produtos) {
        if (produto.getNome() == nome) {
            return &produto; // Retorna um ponteiro para o produto encontrado
        }
    }
    return nullptr; // Retorna nullptr se o produto não for encontrado
}

// Função para alterar um produto existente
void Estoque::alterarProduto(const std::string& nome, Produto& novoProduto) {
    
    // produtos.clear();

    // if (!this->carregarDeArquivo("estoque.csv")) {
    //     std::cerr << "Falha ao carregar dados do arquivo." << std::endl;
    //     return;
    // }

    bool isProdutoAtualizado = false;

    for (auto& produto : produtos) {
        if (produto.getNome() == nome) {
            //Produto nvProduto(novoProduto.getId(), novoProduto.getNome(), novoProduto.getPreco());
            produto =  novoProduto;// Atualiza o produto existente com as novas informações
            isProdutoAtualizado = true;
            break;
        }
    }

    if (isProdutoAtualizado){
        if (!this->removerAtualizarArquivo("estoqueAtualizado.csv")){
            std::cerr << "Falha ao atuallizar o produto." << std::endl;
            return;
        }
        std::cout << "Produto alterado com sucesso!" << std::endl;
    } 
    else {
        std::cout << "Produto nao encontrado." << std::endl;
    }

    produtos.clear();
}

// Função para remover um produto por nome
void Estoque::removerProduto(const std::string& nome) {
    
    produtos.clear();

    if (!this->carregarDeArquivo("estoque.csv")) {
        std::cerr << "Falha ao carregar dados do arquivo." << std::endl;
        return;
    }
    
    auto it = std::remove_if(produtos.begin(), produtos.end(), [&](const Produto& produto) {
        return produto.getNome() == nome;
    });

    if (it != produtos.end()) {
        produtos.erase(it, produtos.end());
        
        if (!this->removerAtualizarArquivo("estoqueAtualizado.csv")){
            std::cerr << "Falha ao remover produto." << std::endl;
            return;
        }

        std::cout << "Produto removido com sucesso!" << std::endl;
    } else {
        std::cout << "Produto nao encontrado." << std::endl;
    }

    produtos.clear();
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
    std::fstream arquivo;
    arquivo.open(nomeArquivo, std::fstream::in);

    //std::cout << "Entra no CarregarDeArquivo"<< std:: endl;

    // Verifica se o arquivo está aberto corretamente
    if (!arquivo) {
        // O arquivo não existe, não é um erro, apenas não há dados para carregar.
         //std::cout << "Entra no teste de CarregarDeArquivo"<< std:: endl;
        return false;
    }

    //std::cout << "Carregando dados do arquivo..." << std::endl;

    std::string linha, valorPorVirgula;
    std::vector<std::string> valoresLinhas;
    bool dadosLidos = false;

    // Loop para ler cada linha do arquivo
    while (std::getline(arquivo, linha)) {
        valoresLinhas.clear();

        // Prepara um fluxo de string para analisar a linha
        std::istringstream ss(linha);

        while (std::getline(ss, valorPorVirgula, ',')) {
            valoresLinhas.push_back(valorPorVirgula);
        }

        Produto produto(std::stoi(valoresLinhas[0]), valoresLinhas[1], std::stod(valoresLinhas[2]));
        produtos.push_back(produto);

    }
     //std::cout << "Saindo do while no CarregarDeArquivo"<< std:: endl;

    // Fecha o arquivo após a leitura
    arquivo.close();
   
    return true;
}


// Implementação das funções para salvar dados de um arquivo
bool Estoque::salvarParaArquivo(const std::string& nomeArquivo) const {
    std::fstream arquivo;
    arquivo.open(nomeArquivo, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return false;
    }
//    if (isAdicao) {
//         for (const auto& produto : produtoParaSalvar) {
//             arquivo << produto.getId() << "," << produto.getNome() << "," << produto.getPreco() << "\n";
//         }
//    }
    arquivo << produtoSalvar.getId() << "," << produtoSalvar.getNome() << "," << produtoSalvar.getPreco() << "\n";
//    if (!isAdicao) {
//         for (const auto& produto : produtos) {
//             arquivo << produto.getId() << "," << produto.getNome() << "," << produto.getPreco() << "\n";
//         }

//         remove("estoque.csv");
//         rename("estoqueAtualizado.csv", "estoque.csv")
//    }

    arquivo.close();

    return true;
}

bool Estoque::removerAtualizarArquivo(const std::string& nomeArquivo) const {
    std::fstream arquivo;
    arquivo.open(nomeArquivo, std::fstream::out);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return false;
    }
//    if (isAdicao) {
    for (const auto& produto : produtos) {
        arquivo << produto.getId() << "," << produto.getNome() << "," << produto.getPreco() << "\n";
    }
//    }
    //arquivo << produtoSalvar.getId() << "," << produtoSalvar.getNome() << "," << produtoSalvar.getPreco() << "\n";
//    if (!isAdicao) {
//         for (const auto& produto : produtos) {
//             arquivo << produto.getId() << "," << produto.getNome() << "," << produto.getPreco() << "\n";
//         }

    arquivo.close();
    
    remove("estoque.csv");
    rename("estoqueAtualizado.csv", "estoque.csv");
//    }


    return true;
}


