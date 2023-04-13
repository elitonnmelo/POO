
#include <iostream>
#include <algorithm>
#include <vector>
#include <fn.hpp>

using namespace fn;

std::vector<int> get_men(std::vector<int> vet) {
  std::vector<int> vetAux;
  for ( int i = 0; i < vet.size(); i++ ) {
      if ( vet[i] > 0) {
        vetAux.push_back(vet[i]);
      }
  }
  return vetAux; // todo
}

std::vector<int> get_calm_women(std::vector<int> vet) {
  std::vector<int> vetAux;
  for ( int i = 0; i < vet.size(); i++ ) {
      if ( vet[i]  < 0 && vet[i] > -10) {
        vetAux.push_back(vet[i]);
      }
  }
  return vetAux; 
}

std::vector<int> sort(std::vector<int> vet) {
  
  //std::sort(vet.begin(), vet.end());
  int i, j, temp;
  int n = vet.size();
  for(i = 0; i < n; i++) {
    for(j = 0; j < n-i-1; j++) {
      if(vet[j] > vet[j+1]) {
        temp = vet[j];
        vet[j] = vet[j+1];
        vet[j+1] = temp;
      }
    }
  }
  return vet;
}

std::vector<int> sort_stress(std::vector<int> vet) {
  int i, j, temp;
  int n = vet.size();
  for(i = 0; i < n; i++) {
    for(j = 0; j < n-i-1; j++) {
      if(abs(vet[j]) > abs(vet[j+1])) {
        temp = vet[j];
        vet[j] = vet[j+1];
        vet[j+1] = temp;
      }
    }
  }
  return vet; 
}

std::vector<int> reverse(std::vector<int> vet) {
  std::vector<int> reversevet;
  int size = vet.size();
  for(int i = size-1; i >= 0; i--) {
    reversevet.push_back(vet[i]);
  }
  return reversevet;
}

std::vector<int> unique(std::vector<int> vet) {
  std::vector<int> noDuplicates;
  for(int i = 0; i < vet.size(); i++) {
    if(find(noDuplicates.begin(), noDuplicates.end(), vet[i]) == noDuplicates.end()) {
      noDuplicates.push_back(vet[i]);
    }
  }
  return noDuplicates; 
}

std::vector<int> repeated(std::vector<int> vet) {
    // std::vector<int> repeated;
    // for(int i = 0; i < vet.size(); i++) {
    //     if(count(vet.begin(), vet.end(), vet[i]) > 1) {
    //         if(find(repeated.begin(), repeated.end(), vet[i]) == repeated.end()) {
    //             repeated.push_back(vet[i]);
    //         }
    //     }
    // }
    // return repeated;
  std::vector<int> noDuplicates;
  std::vector<int> Duplicates;
  for(int i = 0; i < vet.size(); i++) {
    if(find(noDuplicates.begin(), noDuplicates.end(), vet[i]) == noDuplicates.end()) {
      noDuplicates.push_back(vet[i]);
    }
    else {
      Duplicates.push_back(vet[i]);
    }
  }
  return Duplicates;

}


int main() {
    auto strToVet = [](auto s) { return s.substr(1, s.size() - 2) | SPLIT(',') | MAP(FNT(x, (int)+x)); };

    while(true) {
        std::string line = input();
        auto args = split(line, ' ');
        write('$' + line);

        if     (args[0] == "get_men"        ) { write(get_men(strToVet(args[1])));        }
        else if(args[0] == "get_calm_women" ) { write(get_calm_women(strToVet(args[1]))); }
        else if(args[0] == "sort"           ) { write(sort(strToVet(args[1])));           }
        else if(args[0] == "sort_stress"    ) { write(sort_stress(strToVet(args[1])));    }
        else if(args[0] == "reverse"        ) { write(reverse(strToVet(args[1])));        }
        else if(args[0] == "unique"         ) { write(unique(strToVet(args[1])));         }
        else if(args[0] == "repeated"       ) { write(repeated(strToVet(args[1])));       }
        else if(args[0] == "end"            ) { break;                                    }
    }
}


