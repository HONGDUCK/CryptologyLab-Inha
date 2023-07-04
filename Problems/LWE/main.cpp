#include <iostream>
#include "LWE_INHA.h"

int main() {

    int message[num];
    int secretkey[num];
    int a[num][num];
    int EncMessage[num];

    MessageGenerator(num, message);
    ParamGenerator(*a, num, num);
    SecretKeyGenerator(secretkey);
    Encryption(message, 10, secretkey, *a, EncMessage);

    for (int i = 0; i < num; i++)
    {
        std::cout << "Message: " << message[i] << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < num; i++)
    {
        std::cout << "Secretkey: " << secretkey[i] << "\n";
    }
    std::cout << "\n";
    
    std::cout << "Matrix A\n";
    for (int i = 0; i < num; i++){
        for(int j = 0; j<num; j++){
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    for (int i = 0; i < num; i++)
    {
        std::cout << "EncrypedMessage " << EncMessage[i] << "\n";
    }
    
    return 0;
}