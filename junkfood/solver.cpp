
#include <fn.hpp>
#include <utility>
#include <vector>


class Slot {
  std::string name;
  float price {0};
  int quantity {0};

  public:

    Slot(std::string name = "empty", float price = 0, int quantity = 0){
      this->name = name;
      this->price = price;
      this->quantity = quantity;
    }

    std::string getName() {
      return this->name;
    }

    float getPrice() {
      return this->price;
    }

    int  getQuantity() {
      return this->quantity;
    }

    void setName( std::string name) {
      this->name = name;
    }

    void setPrice(float price) {
      this->price = price;
    }

    void setQuantity( int quantity) {
      this->quantity = quantity;
    }
    std::string str() const {
      return fn::tostr(this->name, "%7s") + " : " + std::to_string(this->quantity) + " U : " + fn::tostr(this->price, "%.2f") ;
      
    }
  
};

class VendingMachoine {
  std::vector<Slot> slots;
  float profit {0};
  float cash {0};
  int capacity {0};

  public:

    VendingMachoine(int capacity = 0) {
      this->capacity = capacity;
      for (int i = 0; i < capacity; i++) {
        slots.push_back(Slot("empty", 0, 0.00));
      }
    }

    // Slot getSlot(int index) {
     
    // }

    void setSlot(int index, Slot slot) {
      if (index > this->capacity){
        fn::write("fail: indice nao existe");
      }
      else{
        slots[index].setName(slot.getName());
        slots[index].setQuantity(slot.getQuantity());
        slots[index].setPrice(slot.getPrice());
      }
    }

    void insertCash(float cash){
      this->cash += cash;
    }

    float withDrawCash(){
      float aux =  this->cash;
      this->cash = 0;
      return aux;
    }

    void buyItem(int index) {
      if (index > capacity){
        fn::write("fail: indice nao existe");
        return;
      }
      if( (cash - slots[index].getPrice()) < 0) {
        fn::write("fail: saldo insuficiente");
        return;
      }
      if ( slots[index].getQuantity() == 0) {
        fn::write("fail: espiral sem produtos");
        return;
      }
      // else{
        
      //   if ( slots[index].getQuantity() < 0) {
      //     fn::write("fail: espiral sem produtos");
      //   }
      //   else{
          cash -= slots[index].getPrice();
          slots[index].setQuantity(slots[index].getQuantity() - 1);
          fn::write("voce comprou um " + slots[index].getName());
      //   }
        
      // }
      
    }

    void clearSlot(int index) {
      if (index > capacity){
        fn::write("fail: indice nao existe");
      }
      else{
        slots[index].setName(fn::tostr("empty", "%7s"));
        slots[index].setQuantity(0);
        slots[index].setPrice(0.00);
      }
      
    }

    std::string str() const {
      std::string retorno;
      for (int i = 0; i < capacity; i++) {
        retorno += std::to_string(i) + " [ " + slots[i].str() + " RS]\n";
      }
      return "saldo: " + fn::tostr(this->cash, "%.2f") + "\n" + retorno;
    }
};

int main() {
  VendingMachoine vendingMachoine;
    while (true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line);

        if (args[0] == "end") { 
          break;
        }
        else if ( args[0] == "init"){
            vendingMachoine = VendingMachoine(+args[1]);
        }
        else if (args[0] == "show") { 
          std::cout<<(vendingMachoine.str()); 
        }
        else if (args[0] == "set"){
          Slot slot(args[2], (float)+args[4], +args[3]);
          vendingMachoine.setSlot(+args[1], slot);
        }
        else if (args[0] == "limpar") {
          vendingMachoine.clearSlot(+args[1]);
        }
        else if (args[0] == "dinheiro"){
          vendingMachoine.insertCash(+args[1]);
        }
        else if (args[0] == "troco"){
          fn::write("voce recebeu " + fn::tostr(vendingMachoine.withDrawCash(), "%.2f") + " RS");
        }
        else if (args[0] == "comprar") {
          vendingMachoine.buyItem(+args[1]);
        }
          
        else {
          fn::write("fail: invalid command"); 
        }
    }
}