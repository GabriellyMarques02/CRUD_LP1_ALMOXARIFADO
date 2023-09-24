#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto {
public:
    Produto();
    Produto(int id, const std::string& nome, double preco);

    int getId() const;
    const std::string& getNome() const;
    double getPreco() const;

private:
    int id;
    std::string nome;
    double preco;
};

#endif // PRODUTO_H
