#include <iostream>
#include <vector>

int divi(int a, int b) {
    int result;
    result = a / b;
    if ( b == 0){
        throw std::invalid_argument("fail: divisao por zero");
    }
    if (std::out_of_range& ){
        throw std::invalid_argument("fail: falta de argumentos");
    }
    return result;
    
}

int main(){
    std::vector<int> v;
    while (true) {
        try {

           int n1, n2;
            std::cin >> n1;
            std::cin >> n2;
            auto result = divi(n1, n2);
            std::cout << result;

        } catch (std::invalid_argument& e) {
            std::cout <<  e.what() << std::endl;

        } catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
        }

    }
}