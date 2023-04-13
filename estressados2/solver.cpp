
#include <iostream>
#include <vector>
#include <fn.hpp>
using namespace fn;
using namespace std;

int count(std::vector<int> vet, int x) {
  int count = 0;
  for ( int i = 0; i < vet.size(); i++) {
      if ( vet[i] == x) {
        count++;
      }
    }
    return count;
}

int sum(std::vector<int> vet) {
  int count = 0;
  for ( int i = 0; i < vet.size(); i++) {
    if ( vet[i] < 0) {
      vet[i] = (vet[i] * (-1));
      count += vet[i];
    }
    else{
      count += vet[i];
    }
  }
    return count; // todo
}
double average(const std::vector<int>& vet) {
  int count = 0;
  int aux = 0;
  for (int i = 0; i < vet.size(); i++) {
    if (vet[i] < 0) {
      aux  = vet[i];
      aux *= -1;
      count += aux;
    }
    else{
      count += vet[i]; 
    }
    
  }
  return (count / (double) vet.size());
}


std::string more_men(const std::vector<int>& vet) {
  int countM = 0;
  int countW = 0;
  string draw = "draw";
  for ( int i = 0; i < vet.size(); i++) {
    if ( vet[i] < 0) {
      countW += 1;
    }
    else{
      countM += 1;
    }
  }
  if (countM > countW) {
    string men = "men";
    return men;
  }
  if (countM == countW){
      return draw;
  }
  if(countW > countM){
    string women = "women";
    return women;
  }
}

std::string half_compare(const std::vector<int>& vet) {
    int countF = 0;
    int countS = 0;
    std::string draw = "draw";
    int aux = 0;
    int j = vet.size();
    for ( int i = 0; i < j/2; i++) {
        if ( vet[i] < 0) {
            aux  = vet[i];
            aux *= -1;
            countF += aux;
        }
        if (vet[i] >= 0){
            countF += vet[i];
        }
    }
    for ( int i = j/2; i < j; i++) {
        if ( vet[i] < 0) {
            aux  = vet[i];
            aux *= -1;
            countS += aux;
        }
        if (vet[i] >= 0){
            countS += vet[i];
        }
    }
    if (countF > countS) {
        std::string first = "first";
        return first;
    }
    if (countF == countS){
        return draw;
    }
    if(countS > countF){
        std::string second = "second";
        return second;
    }
}


std::string sex_battle(const std::vector<int>& vet) {
  int countM = 0;
  int countW = 0;
  std::string draw = "draw";
  int aux = 0;
  for ( int i = 0; i < vet.size(); i++) {
      if ( vet[i] < 0) {
          aux  = vet[i];
          aux *= -1;
          countW += aux;
      }
      if (vet[i] >= 0){
          countM += vet[i];
      }
  }
  int resM = (countM / ((double) vet.size()/2));
  int resW = (countW / ((double) vet.size()/2));
  
  if (resM > resW) {
    string men = "men";
    return men;
  }
  if (resM == resW){
      return draw;
  }
  if(resW > resM){
    string women = "women";
    return women;
  }
}



int main() {

    auto str2vet = [](auto s) { return s.substr(1, s.size() - 2) | SPLIT(',') | MAP(FNT(x, (int)+x)); };

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"              ) { break;                                              }
        else if (args[0] == "count"            ) { count(str2vet(args[1]), +args[2])         | WRITE();}
        else if (args[0] == "sum"              ) { sum(str2vet(args[1]))                     | WRITE();}
        else if (args[0] == "more_men"         ) { more_men(str2vet(args[1]))                | WRITE();} 
        else if (args[0] == "half_compare"     ) { half_compare(str2vet(args[1]))            | WRITE();}
        else if (args[0] == "more_men_or_women") { more_men(str2vet(args[1]))                | WRITE();}
        else if (args[0] == "sex_battle"       ) { sex_battle(str2vet(args[1]))              | WRITE();}
        else if (args[0] == "average"          ) { average(str2vet(args[1])) | TOSTR("%.2f") | WRITE();}
        else                                     { "fail: unknown command"                   | WRITE();}
    }     
}

