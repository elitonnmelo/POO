#include <fn.hpp>


struct Cliente{
    std::string id;
    std::string fone;

    Cliente(std::string id = "", std::string fone = "") {
      this->id = id;
      this->fone = fone;
    }
    std::string str() {
        return id + ":" + fone; // todo
    }
};

class Sala{
    std::vector<std::shared_ptr<Cliente>> cadeiras;
    int procurar(std::string nome) {
    for (int i = 0; i < cadeiras.size(); i++) {
        if (cadeiras[i] != nullptr && cadeiras[i]->id == nome) {
            return i;
        }
    }
    return -1;
}


public:
    Sala(int qtd = 0) {
      for(int i = 0; i < qtd; i++){
        this->cadeiras.push_back(nullptr);
      }
    }


    void reservar(std::string id, std::string fone, int ind) {
      if (ind < 0 || ind > cadeiras.size()){
        fn::write("fail: cadeira nao existe");
        return;
      }
      if (cadeiras[ind] != nullptr){
        fn::write("fail: cadeira ja esta ocupada");
        return;
      }
      if (procurar(id) != -1) {
        fn::write("fail: cliente ja esta no cinema");
        return;
      }
      
      cadeiras[ind] = std::make_shared<Cliente>(id, fone);
      // this->cadeiras[ind] = cadeiras.insert(cadeiras.begin() + ind, std::make_shared<Cliente>(id, fone));

    }

    void cancelar(std::string id) {
      if (procurar(id) == -1) {
        fn::write("fail: cliente nao esta no cinema");
        return;
      }
      cadeiras[procurar(id)] = nullptr;
    }

    std::string str() {
      std::string cadeiras_str = "[";
      for (auto c : cadeiras) {
          if (c == nullptr)
              cadeiras_str += "- ";
          else
              cadeiras_str += c->str() + " ";
      }if (cadeiras.size() > 0 ){
        cadeiras_str.pop_back();
      }
      cadeiras_str += "]";
      return cadeiras_str;
    }

};


std::ostream& operator<<(std::ostream& os, Cliente c) { return os << c.str(); }
std::ostream& operator<<(std::ostream& os, Sala    c) { return os << c.str(); }

int main() {
    Sala sala;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "show") {
            fn::write(sala);
        } else if (args[0] == "init") {
            sala = Sala(+args[1]);
        } else if (args[0] == "reservar") {
            sala.reservar(args[1], args[2], (int) +args[3]);
        } else if (args[0] == "cancelar") {
            sala.cancelar(args[1]);
        } else {
            fn::write("fail: comando invalido");
        }
    }
}

