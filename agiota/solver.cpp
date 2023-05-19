#include <fn.hpp>
#include <algorithm>
#include <cmath>

enum Label {
    GIVE, TAKE, PLUS
};

std::ostream& operator<<(std::ostream& os, Label label) {
    switch (label) {
        case GIVE: os << "give"; break;
        case TAKE: os << "take"; break;
        case PLUS: os << "plus"; break;
    }
    return os;
}

class Operation {
    int id;           //id único da transação
    std::string name; //id único do cliente
    Label label;      //label da operação
    int value;        //valores são sempre positivo  
public:

    Operation(int id, std::string name, Label label, int value) {
        this->id    = id;
        this->name  = name;
        this->label = label;
        this->value = value;
    }

    std::string getName() {
        return name;
    }

    Label getLabel() {
        return label;
    }

    int getValue() {
        return value;
    }

    std::string str() {
        return "id:{} {}:{} {}" | fn::FORMAT(id, label, name, value);
    }
};

std::ostream& operator<<(std::ostream& os, Operation tr) {
    return os << tr.str();
}

class Client {
    std::string name; // nome do cliente
    int limite;    // o maximo que ele pode ficar devendo
    std::vector<std::shared_ptr<Operation>> operations; //dívidas e pagamentos 
public:

    Client(std::string name = "", int limite = 0) {
        this->name = name;
        this->limite = limite;
    }
    std::string getName() {
        return name;
    }
    int getLimite() {
        return limite;
    }

    int getBalance() {
      int balance = 0;
      for (const auto& op : operations) {
          if (op->getLabel() == GIVE || op->getLabel() == PLUS)
              balance += op->getValue();
          else if (op->getLabel() == TAKE)
              balance -= op->getValue();
      }
      return balance;
    }

    void addOperation(std::shared_ptr<Operation> tr) {
        operations.push_back(tr);
    }

    std::vector<std::shared_ptr<Operation>> getOperations() {
        return this->operations;
    }

    std::string str() {
        return "{} {}/{}" | fn::FORMAT(name, getBalance(), limite);
    }
};

std::ostream& operator<<(std::ostream &os, Client cliente) {
    return os << cliente.str();
}



class Agiota {
    //ordenado por nome do cliente
    //nome deve ser único
    std::vector<Client> alive_list;

    //nome não precisa ser único na lista de clientes mortos
    //ordenado pela data da morte
    std::vector<Client> death_list;

    //as transações dos vivos
    std::vector<std::shared_ptr<Operation>> alive_oper;
    //as transações dos mortos
    std::vector<std::shared_ptr<Operation>> death_oper;
        
    //guarda o id da próxima transação
    int nextOpId = 0;

    //retorna a posição desse cliente no vetor de vivos ou -1 se não existir
    int searchClient(std::string name) {
      int j = 0;
      for (auto cliente : alive_list) {
        if (cliente.getName().find(name) != std::string::npos) {
          return j;
        }
        j++;
      }
      return -1;
    }

    void pushOperation(Client& cli, Label label, int value) {
        std::shared_ptr<Operation> op = std::make_shared<Operation>(nextOpId, cli.getName(), label, value);
        cli.addOperation(op);
        alive_oper.push_back(op);
        nextOpId++;
    }

public:
    Agiota() {
    }

    Client* getClient(std::string name) {
      int pos = searchClient(name);
      if (pos == -1) {
        fn::write("fail: cliente nao existe");
        return nullptr;
      }
      return &alive_list[pos];
    }

    void addClient(std::string name, int limite) {
      int pos = searchClient(name);
      if (pos!= -1){
        fn::write("fail: cliente ja existe");
        return;
      }
      else { 
        this->alive_list.push_back( Client(name, limite));
      }
      std::sort(alive_list.begin(), alive_list.end(),[](auto a, auto b){return a.getName() < b.getName();});
    }

    void give(std::string name, int value) {
      Client* client = getClient(name);
      if (client == nullptr){
        return;
      }
      if (client != nullptr) {
        if (client->getBalance() + value <= client->getLimite()) {
          pushOperation(*client, GIVE, value);
          return;
        }
        else {
          fn::write("fail: limite excedido");
          return;
        }
      }
    }

    void take(std::string name, int value) {
      Client* client = getClient(name);
      if (client == nullptr){
        return;
      }
      if (client != nullptr) {
        if (client->getLimite() > 0) {
          pushOperation(*client, TAKE, value);
          return;
        }
        else {
          fn::write("fail: limite excedido");
          return;
        }
      }
      
    }

    void plus() {
      std::vector<Client> clientsUpdate;
      for (Client& client : alive_list) {
        int balance = client.getBalance();
        int plusValue = std::ceil(balance * 0.1);
        pushOperation(client, PLUS, plusValue);
        clientsUpdate.push_back(client);
      }
      for (auto client : clientsUpdate) {
          if (client.getBalance() > client.getLimite()) {
              kill(client.getName());
          }
      }
      
    }

    void kill(std::string name) {
      int pos = searchClient(name);
      if (pos == -1) {
          fn::write("fail: cliente nao existe");
          return;
      }
      Client client = alive_list[pos];
      alive_list.erase(alive_list.begin() + pos);
      death_list.push_back(client);
  
      std::vector<std::shared_ptr<Operation>> operationsRemove;
      
      for (auto operation : alive_oper) {
          if (operation->getName() == name) {
              operationsRemove.push_back(operation);
          }
      }
  
      for (auto operation : operationsRemove) {
          alive_oper.erase(std::remove(alive_oper.begin(), alive_oper.end(), operation), alive_oper.end());
          death_oper.push_back(operation);
      }
    }

    std::string str() {
        std::stringstream ss;
        for (auto cli : alive_list)
            ss << ":) " << cli.str() << '\n';
        for (auto tr : alive_oper)
            ss << "+ " << tr->str() << '\n';
        for (auto cli : death_list)
            ss << ":( " << cli.str() << '\n';
        for (auto tr : death_oper)
            ss << "- " << tr->str() << '\n';
        auto output = ss.str();
        if (output.back() == '\n')
            output.pop_back();
        return output;
    }
    
};

std::ostream& operator<<(std::ostream& os, Agiota agiota) {
    return os << agiota.str();
}



int main() {
    Agiota agiota;
    while(true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);
        
        try{
            if(args[0] == "end") {
                break;
            } else if(args[0] == "addCli") {
                agiota.addClient(args[1], +args[2]);
            } else if(args[0] == "show") {
                agiota | fn::WRITE();
            } else if(args[0] == "showCli") {
                auto cli = agiota.getClient(args[1]);
                if (cli != nullptr) {
                    cli->str() | fn::WRITE();
                    cli->getOperations() | fn::JOIN("\n") | fn::WRITE();
                }
            } else if(args[0] == "kill") {
                agiota.kill(args[1]);
            } else if(args[0] == "give") {
                agiota.give(args[1], +args[2]);
            } else if(args[0] == "take") {
                agiota.take(args[1], +args[2]);
            } else if(args[0] == "plus") {
                agiota.plus();
            } else {
                fn::write("fail: comando invalido");
            }
        } catch(std::string s) {
            fn::write(s);
        }
    }
}


