#include <iostream>
#include <tuple>
#include <vector>
 // APREDENDO C++
 /*
 */
//PAERA SIMPLIFICAR O USO DA BIBLIOTECA IOSTREAM, É RECOMENDADO USAR O COMANDOP ABAIXO
using namespace std;

string num_para_nome (int num) {
    if (num == 0) 
        return "zero";
    if (num == 1) 
        return "um";
    if (num == 2) 
        return "dois";
    return "Erro";
}
string num_para_nome_otimizado( int num) {
    vector <string> res = {"zero", "um", "dois", "tres", "quatro"};
    return res[num];
}

int main(){
    string nome = "Eliton";
    int x = min(4, 8);
    cout << "Teste\n" << nome << x << '\n' ;

    for (int i = 0; i < 10; i++) {
        if (i  % 2 == 0) {
            cout << "Numero par:" << i << '\n';
        }
    }
    //OPERADOR TERNARIO
    cout << "7 e maior que 5? ";
    cout << (7 > 5 ? "maior" : "menor") << '\n';
    puts ("a funcao puts imprime apenas uma string");

    int num;
    cin >> num;
    cout << num_para_nome(num);
    cout << num_para_nome_otimizado(num); 
}

