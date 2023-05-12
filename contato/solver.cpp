/*
O que foi feito? tudo.
Com quem foi feito? sozinho
O que foi aprendido? o uso de classes, obtive dificuldades em strings de formatação
Tempo estimado para fazer a atividade? 1:30 

*/#include <fn.hpp>

class Fone {
  std::string id;
  std::string number;

public:
  Fone(std::string id = "", std::string number = "") {
    this->id = id;
    this->number = number;
  }
  std::string getId() { return id; }
  std::string getNumber() { return number; }
  bool isValid() {
    return {}; // todo
  }
  std::string str() { return this->id + ":" + this->number; }
};
std::ostream &operator<<(std::ostream &out, Fone fone) {
  return out << fone.str();
}

class Contact {
  std::string name;
  bool favorited;
  std::vector<Fone> fones;

public:
  Contact(std::string name = "") { // todo
    this->name = name;
    this->favorited = false;
  }

  std::string getName() {
    return name; // todo
  }

  std::vector<Fone> getFones() {
    return {}; // todo
  }

  void addFone(std::string id, std::string number) {
    for(auto elem : number){
      if ((elem < '0' || elem > '9') && elem != '(' && elem != ')' && elem != '.'){
        fn::write("fail: invalid number");
        return;
      }
    }
    this->fones.push_back(Fone(id, number));
  }

  void rmFone(int index) {
    for(int i = 0; i < (int) fones.size() - 1; i++) {
      if ( i >= index){
        fones[i] = fones[i+1];
      }
    }
    fones.pop_back();
  }

  void toogleFavorited() {
    this->favorited ^= 1;
  }

  bool isFavorited() {
    return {}; // todo
  }

  std::string str() {
    std::stringstream ss;
    ss << (this->favorited ? "@ " : "- ") << name << " [";
    for (int i = 0; i < (int)fones.size(); i++) {
      ss << (i == 0 ? "" : ", ") << fones[i].str();
    }
    ss << "]";
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &out, Contact contato) {
  return out << contato.str();
}



int main() {
  Contact contato;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');

    if (args[0] == "end") {
      break;
    } else if (args[0] == "init") { // name
      contato = Contact(args[1]);
    } else if (args[0] == "add") { // id fone
      contato.addFone(args[1], args[2]);
    } else if (args[0] == "rm") { // id
      contato.rmFone(+args[1]);
    } else if (args[0] == "tfav") {
      contato.toogleFavorited();
    } else if (args[0] == "show") {
      fn::write(contato);
    } else {
      fn::write("fail: comando invalido");
    }
  }
}