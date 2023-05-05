#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <fn.hpp>

class Pessoa {
    std::string nome;
public:
    Pessoa(std::string nome) {
      this->nome = nome; 
    } 
    std::string getNome() const {
        return nome; 
    }
    std::string str() const {
      return this->getNome();
    }
};
std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
    return (os << p.str());
}

class Mercantil {
    std::vector<std::shared_ptr<Pessoa>> caixas; //caixas do supermercado
    std::list  <std::shared_ptr<Pessoa>> esperando; //lista de clientes esperando

    bool validarIndice(int indice) {
      if ((indice < 0 ) || (indice >= this->caixas.size()) ){
        fn::write("fail: caixa inexistente");
        return false;
      }
      else{
        return true; 
      }
      
    }

public:
    Mercantil(int qtd_caixas) {
      for (int i = 0; i < qtd_caixas; i++) {
        this->caixas.push_back(nullptr);
      }
    }
    
    void chegar(const std::shared_ptr<Pessoa>& person) {
      this->esperando.push_back(person);
    }

    bool chamarNoCaixa(int indice) {
      if (this->validarIndice(indice) == false){
        return false;
      }
      if (this->esperando.size() == 0 ){
        fn::write("fail: sem clientes");
        return false;
      }
      if(this->caixas[indice] != nullptr){
        fn::write("fail: caixa ocupado");
        return false;
      }
      
      this->caixas[indice] = this->esperando.front();
      this->esperando.pop_front();
      return true;
    }
    
    std::shared_ptr<Pessoa> finalizar(int indice) {
      if (this->validarIndice(indice) == false){
        return {};
      }
      //validarIndice(indice);
      if ( this->caixas[indice] == nullptr) {
        fn::write("fail: caixa vazio");
        return {};
      }
      this->caixas[indice] = nullptr;
      return {}; 
    }

    std::string str() const {
        auto caixas_str = caixas | fn::MAP(FNT(c, c == nullptr ? "-----" : c->getNome()));
        return "Caixas: " + fn::tostr(caixas_str) + "\n" + "Espera: " + fn::tostr(esperando);
    }
};

std::ostream& operator<<(std::ostream& os, const Mercantil& b) {
    return (os << b.str());
}

int main() {
    Mercantil bank(0);
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end"   ) { break;                                          }
        else if (args[0] == "init"  ) { bank = Mercantil(+args[1]);                     }
        else if (args[0] == "call"  ) { bank.chamarNoCaixa(+args[1]);                   }
        else if (args[0] == "finish") { bank.finalizar(+args[1]);                       }
        else if (args[0] == "arrive") { bank.chegar(std::make_shared<Pessoa>(args[1])); }
        else if (args[0] == "show"  ) { fn::write(bank);                                }
        else                          { fn::write("fail: comando invalido");            }
        
    }
}

