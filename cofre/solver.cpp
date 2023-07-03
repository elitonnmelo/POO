/*
O que foi feito? tudo.
Com quem foi feito? sozinho e pesquisas na internet
O que foi aprendido? o uso de herança, classes e enuns, obtive difculdades no uso de ponteiros usando o sharedptr, acessar elemntos de outras classes e fazer algumas funçoes
Tempo estimado para fazer a atividade? 4:30 horas
*/

#include <fn.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

class Valuable {
public:
    virtual std::string getLabel()  const = 0;
    virtual double      getValue()  const = 0;
    virtual int         getVolume() const = 0;
    virtual std::string str()       const = 0;
    virtual ~Valuable() {}
};

std::ostream& operator<<(std::ostream& os, const Valuable& valuable) {
    return os << valuable.str();
}

class Coin : public Valuable {
  private:
    std::string label;
    double value;
    int volume;

  // Coin(const std::string& label, double value, int volume) : label(label), value(value), volume(volume) {}
  public:
    Coin(const std::string& label, double value, int volume) : label(label), value(value), volume(volume) {}
    static const Coin C10;
    static const Coin C25;
    static const Coin C50;
    static const Coin C100;

    std::string getLabel() const override {
        return label;
    }

    int getVolume() const override {
        return volume;
    }

    double getValue() const override {
        return value;
    }

    std::string str() const  {
        return fn::format("{}:{%.2f}:{}", label, value, volume);
    }
};

const Coin Coin::C10  { "M10", 0.10, 1};
const Coin Coin::C25  { "M25", 0.25, 2};
const Coin Coin::C50  { "M50", 0.50, 3};
const Coin Coin::C100 {"M100", 1.00, 4};


class Item : public Valuable {
  private:
    std::string label;
    double value;
    int volume;
  public:

    Item(const std::string& label, double value, int volume)
      : label(label), value(value), volume(volume) {}

    std::string getLabel() const override {
      return label;
    }

    double getValue() const override {
      return value;
    }

    int getVolume() const override {
      return volume;
    }

    int setVolume(int newVolume) {
      return volume = newVolume;
    }

    std::string setLabel(const std::string& newLabel) {
      return label = newLabel;
    }

    std::string str() const override {
      std::ostringstream valueStream;
      valueStream << std::fixed << std::setprecision(2) << value;
      std::string formattedValue = valueStream.str();
  
      return label + ":" + formattedValue + ":" + std::to_string(volume);
    }

};

class Pig {
    int volumeMax = 0;
    bool broken = false;
    std::vector<std::shared_ptr<Valuable>> valuables;
public:
    Pig(int volumeMax) : volumeMax(volumeMax) {}

    bool addValuable(const std::shared_ptr<Valuable>& valuable) {
      if (!broken && getVolume() + valuable->getVolume() <= volumeMax) {
        valuables.push_back(valuable);
        return true;
      }
      else if (!broken && getVolume() + valuable->getVolume() > volumeMax) {
        std::cout  << "fail: the pig is full" << std::endl;
        return false;
      }
      else {
        std::cout << "fail: the pig is broken"  << std::endl;
        return false;
      }
      
    }

    bool breakPig() {
      if (!broken) {
        broken = true;
        // for (const auto& valuable : valuables) {
        //     if (auto item = std::dynamic_pointer_cast<Item>(valuable)) {
        //         item->setVolume(0);
        //         //item->setLabel("");
        //     }
        // }
        return true;
      }
      return false;
    }


    std::vector<std::shared_ptr<Coin>> getCoins() {
        std::vector<std::shared_ptr<Coin>> coins;
        if (broken) {
            for (auto it = valuables.begin(); it != valuables.end(); ) {
                if (auto coin = std::dynamic_pointer_cast<Coin>(*it)) {
                    coins.push_back(coin);
                    it = valuables.erase(it);
                } else {
                    ++it;
                }
            }
          return coins;
        } else {
          throw std::runtime_error("you must break the pig first");
        }
    }

    std::vector<std::shared_ptr<Item>> getItems() {
        std::vector<std::shared_ptr<Item>> items;
        if (broken) {
            for (auto it = valuables.begin(); it != valuables.end(); ) {
                if (auto item = std::dynamic_pointer_cast<Item>(*it)) {
                    items.push_back(item);
                    it = valuables.erase(it);
                } else {
                    ++it;
                }
            }
          return items;
        } else {
          throw std::runtime_error("you must break the pig first");
        }
    }

    double calcValue() const {
        double totalValue = 0.0;
        for (const auto& valuable : valuables) {
            totalValue += valuable->getValue();
        }
        return totalValue;
    }

    int getVolume() const {
        if (isBroken()) {
        return 0;
      } else {
          int totalVolume = 0;
          for (const auto& valuable : valuables) {
              totalVolume += valuable->getVolume();
          }
          return totalVolume;
      }
    }

    int getVolumeMax() const {
        return volumeMax;
    }

    bool isBroken() const {
        return broken;
    }

    std::string str() const{
      std::string result = "[";

      for (const auto& valuable : valuables) {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << valuable->getValue();
        std::string formattedGetValue = stream.str();
          result += valuable->getLabel() + ":" + formattedGetValue + ":" + std::to_string(valuable->getVolume()) + ", ";
      }

      if (!valuables.empty()) {
          result = result.substr(0, result.length() - 2);  // Remove a última vírgula e espaço
      }

      std::ostringstream stream;
      stream << std::fixed << std::setprecision(2) << calcValue();
      std::string formattedCalcValue = stream.str();
    
      result += "] : " + formattedCalcValue + "$ : " + std::to_string(getVolume()) + "/" + std::to_string(volumeMax) + " : " + (isBroken() ? "broken" : "intact");

      return result;
    }
};


std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}

int main() {
    Pig pig(0);
    while (true) {
        // try {
            auto line = fn::input();
            auto args = fn::split(line, ' ');
            fn::write("$" + line);

            if      (args[0] == "end" ) { break; } 
            else if (args[0] == "init") { pig = Pig(+args[1]); }
            else if (args[0] == "addCoin") {
                switch((int) +args[1]) {
                    case  10: pig.addValuable(std::make_shared<Coin>(Coin::C10 )); break;
                    case  25: pig.addValuable(std::make_shared<Coin>(Coin::C25 )); break;
                    case  50: pig.addValuable(std::make_shared<Coin>(Coin::C50 )); break;
                    case 100: pig.addValuable(std::make_shared<Coin>(Coin::C100)); break;
                }
            }
            else if (args[0] == "addItem") {
                pig.addValuable(std::make_shared<Item>(args[1], +args[2], (int) +args[3]));
            }
            else if (args[0] == "break"       ) {
              pig.breakPig();
            }
            else if (args[0] == "extractCoins") {
              try {
                fn::write(pig.getCoins()); 
              } catch (const std::exception& e) {
                std::cout << "fail: " << e.what() << std::endl;
              }
            }
            else if (args[0] == "extractItems") { 
              try {
                fn::write(pig.getItems()); 
              } catch (const std::exception& e) {
                std::cout << "fail: " << e.what() << std::endl;
              }
            }
            else if (args[0] == "show") { 
              fn::write(pig);
            }
            else  { fn::write("fail: invalid command");           }
        // } catch (std::string s) {
        //     fn::write(s);
        // }
    }

}


