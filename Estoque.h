#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <vector>
#include <string>
#include "Produto.h"

class Estoque {
public:
    void adicionarProduto(const Produto& produto);
    void listarProdutos() const;
    const Produto* pesquisarProduto(const std::string& nome) const;
    void alterarProduto(const std::string& nome, const Produto& novoProduto);
    void removerProduto(const std::string& nome);
    void exibirRelatorio() const;

    // Funções para salvar e carregar dados de um arquivo
    bool salvarParaArquivo(const std::string& nomeArquivo) const;
    bool carregarDeArquivo(const std::string& nomeArquivo);

private:
    std::vector<Produto> produtos;
};

#endif // ESTOQUE_H
