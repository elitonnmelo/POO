#include <iostream>

using namespace std;
int main (){
    int capacidade = 0;
    cin >> capacidade;
    int onibus = 0;
    int entram = 0;
    while (true)
    {
        cin >> entram;
        onibus += entram;
        if ( onibus == 0 ){
            cout << "vazio ";
        }
        else if (onibus < capacidade){
            cout << "ainda cabe ";
        }
        else if (onibus >= capacidade && onibus < 2 * capacidade){
            cout << "lotado capaciade ";
        }
        else if ( onibus  >= 2 * capacidade){
            cout << "hora de partir ";
            break;
        }
    }
    
    
}