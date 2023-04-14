
#include <fn.hpp>
#include <iostream>
using namespace fn;
using namespace std;

class Time {
  int hora {0};
  int minuto {0};
  int segundo {0};

//funções publicas
public:

  Time(int hora = 0, int minuto = 0, int segundo = 0) {
    this->set_hora(hora);
    this->set_minuto(minuto);
    this->set_segundo(segundo);
  }
  int get_hora() {
    return hora;
  }
  int get_minuto() {
    return minuto;
  }
  int get_segundo() {
    return segundo;
  }
  void set_hora(int hora) {
    if (hora >= 0 && hora <= 23) {
      this->hora = hora;
    }
    else{
      write("fail: hora invalida");
    }
  }
  void set_minuto(int minuto) {
    if (minuto >= 0 && minuto <= 59) {
      this->minuto = minuto;
    }
    else{
      write("fail: minuto invalido");
    }
  }
  void set_segundo(int segundo) {
    if (segundo >= 0 && segundo <= 59) {
      this->segundo = segundo;
    }
    else {
      write("fail: segundo invalido");
    }
  }
  string str (){
    return format("{%02d}:{%02d}:{%02d}", hora, minuto, segundo);
  }
  void increment_segundo() {
    this->segundo = segundo += 1;
  }
  int verifica_hora() {
    if (this->segundo == 60) {
      if (this->minuto == 59) {
        if (this->hora == 23){
          //this->hora = 0;
          //this->minuto = 0;
          return this->segundo = 0, this->minuto = 0, this->hora = 0;
        }
        //this->hora += 1;
        //this->segundo = 0;
        return this->minuto = 0, this->segundo = 0, this->hora += 1;
      }
      //this->minuto += 1;
      return this->segundo = 0, this->minuto += 1;
    }
    return true;
  }
};
int main() {

  Time time;
  while(true) {
    auto line = input();
    write("$" + line);
    vector<string> args = split(line, ' ');
    if (args[0] == "end") {
      break;
    }
    if (args[0] == "show") {
      write(time.str());
    }
    else if (args[0] == "set") {
      time.set_hora(number(args[1]));
      time.set_minuto(number(args[2]));
      time.set_segundo(number(args[3]));
    }
    else if (args[0] == "next") {
      time.increment_segundo();
      time.verifica_hora();
    }
    else if (args[0] == "init"){
      time = Time(number(args[1]), number(args[2]), number(args[3]));
      
    }
    
  }
  
}