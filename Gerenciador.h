#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "Estoque.h"

class Gerenciador {
public:
    void adicionarProduto(Estoque& estoque);
    void listarProdutos(Estoque& estoque);
    void pesquisarExibirProduto(Estoque& estoque);
    void alterarProduto(Estoque& estoque);
    void removerProduto(Estoque& estoque);
    void exibirRelatorioEstoque(const Estoque& estoque);
    void executar();

private:
    std::string lerString(const std::string& mensagem) const;
    int lerInteiro(const std::string& mensagem) const;
    double lerDouble(const std::string& mensagem) const;
};

#endif // GERENCIADOR_H