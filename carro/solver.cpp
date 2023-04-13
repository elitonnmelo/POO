/* Foi feito tudo, passado em todos os casos de teste, feito sozinho depois da aula, já que foi começado em sala com ajuda do professor. Com essa atividade foi possivel aprender e conhecer funcoes relacionadas a c++ como tranformacoes de string para numeros e entre outros que foi descritos no codigo abaixo. O tempo estimado para fazer a atividade foi 30 minutos em sala e 1 hora fora de sala
*/
#include <fn.hpp>
#include <iostream>
using namespace fn;
using namespace std;

//atributos da minha entidade
struct Car {
  int pass {0};
  int gas {0};
  int km {0};
  int gas_max = {100};
  int pass_max = {2};

  void entrar(){
    if (pass >= pass_max){
      write("fail: limite de pessoas atingido");
      return;
    }
    pass += 1;
    return;
  }
  void sair(){
    if (pass == 0){
      write("fail: nao ha ninguem no carro");
      return;
    }
    pass -= 1;
  }
void add_gas(int valor){
  gas += valor;
  if (gas > gas_max){
    gas = 100;
    return;
  }
  return;
}
void dirigir(int drive){
  if (pass < 1){
    write("fail: nao ha ninguem no carro");
    return;
  }
  if (gas == 0){
      write("fail: tanque vazio");
      return;
    }
  if ( drive > gas){
    write("fail: tanque vazio apos andar " + tostr(gas) + " km");
    km += gas;
    gas = 0;
  }
  else {
    gas -= drive;
    km += drive;
    return;
    
  }
}

  string str(){
    return "pass: " + tostr(pass)  + ", gas: " + tostr(gas) +  ", km: " + tostr(km);
  }
};

int main(){
  Car car;
  while( true ){
    auto line = input();
    write("$" + line);
    vector<string> args = split(line, ' ');
    if (args[0] == "end"){
      break;
    }
    else if (args[0] == "show"){
      write(car.str());
    }
    else if ( args[0] == "enter"){
      car.entrar();
    }
    else if ( args[0] == "leave"){
      car.sair();
    }
    else if (args[0] == "fuel"){
      car.add_gas(number(args[1]));
    }
    else if ( args[0] == "drive"){
      car.dirigir(number(args[1]));
    }
  }
}
