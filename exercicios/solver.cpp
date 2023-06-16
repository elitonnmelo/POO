#include <iostream>
#include <vector>

int divi(int a, int b) {
    try{
        
        int result;
        result = a / b;
        if ( b == 0){
            throw std::runtime_error("fail: divisao por zero");
        }
        return result;
    }
    catch (std::invalid_argument& e) {
        throw std::invalid_argument("fail: não é u numero.");
    }
    
    
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

        } catch (std::runtime_error& e) {
            std::cout <<  e.what() << std::endl;

        } catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }

    }
}