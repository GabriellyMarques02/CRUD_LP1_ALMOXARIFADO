#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <vector>
#include <string>
#include "Produto.h"

class Estoque {
public:
    Estoque();
    void adicionarProduto(const Produto& produto);
    void listarProdutos() const;
    Produto* pesquisarProduto(const std::string& nome);
    void alterarProduto(const std::string& nome, Produto& novoProduto);
    void removerProduto(const std::string& nome);
    void exibirRelatorio();

    // Funções para salvar e carregar dados de um arquivo
    bool salvarParaArquivo(const std::string& nomeArquivo) const;
    bool removerAtualizarArquivo(const std::string& nomeArquivo) const;
    bool carregarDeArquivo(const std::string& nomeArquivo);

private:
    std::vector<Produto> produtos;
    Produto produtoSalvar;
};

#endif // ESTOQUE_H 