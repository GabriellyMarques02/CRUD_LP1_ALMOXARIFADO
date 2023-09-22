#include "Produto.h"

Produto::Produto(int id, const std::string& nome, double preco)
    : id(id), nome(nome), preco(preco) {}

int Produto::getId() const {
    return id;
}

const std::string& Produto::getNome() const {
    return nome;
}

double Produto::getPreco() const {
    return preco;
} 

