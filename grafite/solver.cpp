#include <iostream>
#include <sstream>
#include <memory>  //sharedptr
#include <iomanip> //setprecision
#include <utility> //exchange
#include <fn.hpp>
using namespace fn;

class Lead {
    float thickness;
    std::string hardness;
    int size;

public:
    Lead(float thickness, std::string hardness, int size) {
      this->thickness = thickness;
        this->hardness = hardness;
        this->size = size;
    }

    int usagePerSheet() const {
      if (hardness == "HB"){
        return 1;
      }
      if (hardness == "2B"){
        return 2;
      }
      if (hardness == "4B"){
        return 4;
      }
      if (hardness == "6B"){
        return 6;
      }
      //return {}; // todo
    }

    float getThickness() const {
      return this->thickness; // todo
    }

    std::string getHardness() const {
      return this->hardness; // todo
    }

    int getSize() const {
      return this->size; // todo
    }

    void setSize(int size) {
      this->size = size;
    }
    std::string str() const {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) 
           << thickness << ":" << hardness << ":" << size;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& ss, Lead gr) {
    return ss << gr.str();
}

struct Pencil {
    float thickness {0.f};
    std::shared_ptr<Lead> tip {nullptr};

    Pencil(float thickness = 0.0) { 
       this->thickness = thickness;
    }

    bool hasGrafite() {
        return (tip == nullptr) ? true : false ; 
    }

    bool insert(std::shared_ptr<Lead> grafite) {
      if (grafite->getThickness() != thickness) {
            write("fail: calibre incompativel");
            return false;
        }
        if (!hasGrafite()) {
            write("fail: ja existe grafite");
            return false;
        }
        tip = grafite;
        return true;
    }
    std::shared_ptr<Lead> remove() {
      auto aux = this->tip;
      this->tip = nullptr;
      return aux; // todo
    }

    void writePage() {
      if (hasGrafite()){
        write("fail: nao existe grafite");
        return;
      }
      //auto usage_per_sheet = tip->usagePerSheet();
      if (tip->getSize() <= 10) {
        write("fail: tamanho insuficiente");
        
        return;
      }
      tip->setSize(tip->getSize() - tip->usagePerSheet());
      if (tip->getSize() < 10) {
          write("fail: folha incompleta");
          tip->setSize(10); 
          return;
        }
    }

    std::string str() {
        std::stringstream ss;
        ss << "calibre: " << thickness << ", grafite: ";
        if (tip != nullptr)
            ss << "[" << *tip << "]";
        else
            ss << "null";
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pencil l) {
    return os << l.str();
}



int main() {
    Pencil pencil;

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"   ) { break;                                                                                  }
        else if (args[0] == "show"  ) { write(pencil);                                                                    }
        else if (args[0] == "init"  ) { pencil = Pencil(number(args[1]));                                                       }
        else if (args[0] == "insert") { pencil.insert(std::make_shared<Lead>(number(args[1]), args[2], (int) number(args[3]))); }
        else if (args[0] == "remove") { pencil.remove();                                                                        }
        else if (args[0] == "write" ) { pencil.writePage();                                                                     }
    }
}
