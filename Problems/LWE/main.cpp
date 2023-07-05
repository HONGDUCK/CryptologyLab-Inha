#include <iostream>
#include "LWE_INHA.h"

int main() {
    int m0[num];
    int m1[num];
    int secretkey[num];
    int a[num][num];
    int EncMessage[num];
    int DecMessage[num];
    int XORresult[num];

    MessageGenerator(num, m0);
    MessageGenerator(num, m1);
    ParamGenerator(*a, num, num);
    SecretKeyGenerator(secretkey);

    Encryption(m0, 10, secretkey, *a, EncMessage);
    Decryption(EncMessage, 10, secretkey, *a, DecMessage);

    for (int i = 0; i < num; i++)
    {
        std::cout << "Message(m0): " << message[i] << "\n";
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
    std::cout << "\n";

    for(int i=0; i<num; i++){
        std::cout << "DecrypedMessage " << DecMessage[i] << "\n";
    }
    std::cout << "\n";

    //m1
    Encryption(m1, 10, secretkey, *a, EncMessage);
    Decryption(EncMessage, 10, secretkey, *a, DecMessage);
    Operator(m0, m1, 10, XORresult);
    for (int i = 0; i < num; i++)
    {
        std::cout << "Message(m1): " << m1[i] << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < num; i++)
    {
        std::cout << "EncrypedMessage " << EncMessage[i] << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < num; i++)
    {
        std::cout << "DecrypedMessage " << DecMessage[i] << "\n";
    }
    std::cout << "\n";

    std::cout << "XOR Result: ";
    for (int i = 0; i < num; i++) {
        std::cout << XORresult[i] << " ";
    }
    std::cout << "\n";
    
    return 0;
}