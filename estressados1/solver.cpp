
#include <iostream>
#include <vector>
#include <fn.hpp>

bool in(std::vector<int> vet, int x) {
        for( auto elem : vet) {
          if (x == elem){
            return true;
          }
        }
  return false;
}

int index_of(std::vector<int> vet, int x) {
  for ( int i = 0; i < vet.size(); i++) {
      if ( vet[i] == x) {
        return i;
      }
    }
    return -1;
}

int find_if(const std::vector<int>& vet) {
  for ( int i = 0; i < vet.size(); i++) {
      if ( vet[i] >= 0) {
        return i;
      }
    }
  return -1;
    
}

int min_element(const std::vector<int>& vet) {
  if (vet.size() == 0){
    return -1;
  }
  int min = vet[0];
  int count = 0;
  for ( int i = 0; i < vet.size(); i++) {
      if ( vet[i] < min) {
        min = vet[i];
        count = i;
      }
    }
  return count;
}
  
  

int find_min_if(const std::vector<int>& vet) {
  int min =vet[0];
  int count = 0;
  int flag = 1;
  for ( int i = 0; i < vet.size(); i++) {
      if ( vet[i] > 0) {
        if (vet[i] < min){
          count = i;
          min = vet[i];
          flag = 0;
        }
      }
    
    }
  if (flag == 1) {
    return -1;
  }
  return count;
}
#include <sstream>
#include <algorithm>

using namespace fn;

int main() {

    auto STRTOVET = [](auto s) { return map(split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x)); };

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"        ) { break;                                            }
        else if (args[0] == "in"         ) { write(   tostr(in(STRTOVET(args[1]), +args[2]))); }
        else if (args[0] == "index_of"   ) { write(   index_of(STRTOVET(args[1]), +args[2]));  }
        else if (args[0] == "find_if"    ) { write(    find_if(STRTOVET(args[1])));            }
        else if (args[0] == "min_element") { write(min_element(STRTOVET(args[1])));            }
        else if (args[0] == "find_min_if") { write(find_min_if(STRTOVET(args[1])));            }
        else                               { write("fail: unknown command");                   }
    }     
}