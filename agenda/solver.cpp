
#include <fn.hpp>
#include <algorithm>


class Fone {
    std::string id;
    std::string number;
public:
    Fone(std::string id = "", std::string number= "") {
      this->id = id;
      this->number = number;
    }
    std::string getId() {
        return id;
    }
    std::string getNumber() {
        return number;
    }
    bool isValid() {
    for(auto elem : number){
      if ((elem < '0' || elem > '9') && elem != '(' && elem != ')' && elem != '.'){
        return false;
      }
    }
    return true;
  }
    std::string str() {
      return this->id + ":" + this->number;
    }   
};

class Contact{
    std::string name;
    bool favorited;
    std::vector<Fone> fones;
public:
    Contact(std::string name = "") {
      this->name = name;
      this->favorited = false;
    }

    std::string getName() {
      return name; 
    }
  
    std::vector<Fone> getFones() {
      return fones; 
    }
  
    void addFone(std::string id, std::string number) {
      Fone fone(id, number);
      if( !fone.isValid()){
        std::cout << "fail: invalid number" << std::endl;
        return;
      }
      else{
        this->fones.push_back(fone);
      }
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
      return this->favorited;
    }

    std::string str() {
      std::stringstream ss;
      ss << (this->favorited ? "@ " : "- ") << this->getName() << " [";
      for (int i = 0; i < (int)fones.size(); i++) {
        ss << (i == 0 ? "" : ", ") << fones[i].str();
      }
      ss << "]";
      return ss.str();
    }
};

class Agenda {
    std::vector<Contact> contatos;

    int findContact(std::string id) {
      for (int i = 0; i < (int)contatos.size(); i++) {
        if (contatos[i].getName() == id){
          return i;
        }
      }
      return -1;
    }

public:
    //add contato que não existe ou adicionar fones ao contato que existe
    void addContato(std::string name, std::vector<Fone> fones) {
      int pos = findContact(name);
      if ( pos != -1 ){
        for (auto fone : fones) {
          contatos[pos].addFone(fone.getId(), fone.getNumber()); 
        }
      }
      else {
        Contact contato(name);
        for (auto fone : fones) {
          contato.addFone(fone.getId(), fone.getNumber());
        }
        
        contatos.push_back(contato); 
      }
      std::sort(contatos.begin(), contatos.end(),[](auto a, auto b){return a.getName() < b.getName();});
    }

    void rmContact(std::string name) {
      int pos = findContact(name);
      if (pos != -1) {
        contatos.erase(contatos.begin() + pos);
        return;
      }
      else {
        std::cout << "fail: contato inexistente " << std::endl;
        return;
      }
    }

    Contact * getContact(std::string id) {
      int pos = findContact(id);
        if (pos != -1) {
          return  &contatos[pos];
        } 
        else {
          std::cout << "fail: contato inexistente " << std::endl;
          return {};
        }
    }

    std::vector<Contact> getContatos() {
        return contatos;
    }

    std::vector<Contact> search(std::string pattern) {
      std::vector<Contact> results;
      for (auto contato : contatos) {
        if (contato.getName().find(pattern) != std::string::npos) {
          results.push_back(contato);
        } else {
          for (auto fone : contato.getFones()) {
            if (fone.getNumber().find(pattern) != std::string::npos) {
              results.push_back(contato);
              break;
            }
          }
        }
      }
      return results;

    }

    std::vector<Contact> getFavorited() {
      std::vector<Contact> favorites;
      //for(int i = 0; i < (int)contatos.size(); i++){
      for(auto contato : contatos){
        if (contato.isFavorited()){
          favorites.push_back(contato);
        }
      }
      return favorites;
    }

    std::string str() {
      std::stringstream ss;
      for (int i = 0; i < (int)contatos.size(); i++) {
        ss << contatos[i].str() << (i < (int)(contatos.size() -1) ? "\n" : "");
      }
      return ss.str();
    }
};


std::ostream& operator<<(std::ostream& out, Fone fone      ) { return out << fone.str();    }
std::ostream& operator<<(std::ostream& out, Contact contato) { return out << contato.str(); }
std::ostream& operator<<(std::ostream& out, Agenda agenda  ) { return out << agenda.str();  }

int main() {
    Agenda agenda;
    while(true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line, ' ');
        if(args[0] == "end") {
            break;
        }
        else if(args[0] == "add") {//name id:fone id:fone ...
            std::vector<Fone> fones;
            for (int i = 2; i < (int) args.size(); i++) {
                auto parts = fn::split(args[i], ':');
                fones.push_back(Fone(parts[0], parts[1]));
            }
            agenda.addContato(args[1], fones);
        }
        else if(args[0] == "show") {
            fn::write(agenda);
        }
        else if(args[0]== "rmFone") {//id index
            Contact * contato = agenda.getContact(args[1]);
            if(contato != nullptr)
                contato->rmFone((int) +args[2]);
        }
        else if(args[0] == "rm") {//id
            agenda.rmContact(args[1]);
        }
        else if(args[0] == "tfav") {//id 1 ou 0
            Contact * contato = agenda.getContact(args[1]);
            if(contato != nullptr)
                contato->toogleFavorited();
        }
        else if(args[0] == "favs") {
            agenda.getFavorited() | fn::JOIN("\n") | fn::WRITE();
        }
        else if(args[0] == "search") {//pattern
            agenda.search(args[1]) | fn::JOIN("\n") | fn::WRITE();
        }
        else{
            fn::write("fail: comando invalido");
        }
    }
}
