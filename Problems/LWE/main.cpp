#include <iostream>
#include "LWE_INHA.h"
using namespace std;

void MesGenTest();
void ParamGenTest();
void SKGenTest();
void EncTest();
void DecTest();
void AddEncMTest();

int main() {

    // MesGenTest();
    // ParamGenTest();
    // SKGenTest();
    // EncTest();
    // DecTest();
    AddEncMTest();

    return 0;
}

void MesGenTest(){
    int m[num] = {0};
    MessageGenerator(num, m);

    cout << "MessageGenerator Test\nMessage : ";
    for(int i=0; i<num; i++){
        cout << m[i] << " ";
    }
    cout << "\n\n";
}

void ParamGenTest(){
    int paramA[num][num];
    ParamGenerator(*paramA, num, num);

    cout << "ParamGenerator Test\nParam Matrix : \n";
    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            cout << paramA[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void SKGenTest(){
    int SK[num];
    SecretKeyGenerator(SK);

    cout << "SecretKeyGenerator Test\nSeckretKey : ";
    for(int i=0; i<num; i++){
        cout << SK[i] << " ";
    }
    cout << "\n\n";
}

void EncTest(){

    int SK[num];
    SecretKeyGenerator(SK);

    int paramA[num][num];
    ParamGenerator(*paramA, num, num);

    int m[num] = {0};
    MessageGenerator(num, m);

    int EncM[num];
    Encryption(m, num, SK, *paramA, EncM);

    cout << "EncryptionTest\nMessage : ";
    for(int i=0; i<num; i++){
        cout << m[i] << " ";
    }
    cout << "\n";

    cout << "Encryption Message : ";
    for(int i=0; i<num; i++){
        cout << EncM[i] << " ";
    }
    cout << "\n\n";
}

void DecTest(){

    int SK[num];
    SecretKeyGenerator(SK);

    int paramA[num][num];
    ParamGenerator(*paramA, num, num);

    int m[num] = {0};
    MessageGenerator(num, m);

    int EncM[num];
    Encryption(m, num, SK, *paramA, EncM);

    int DecM[num];
    Decryption(EncM, num, SK, *paramA, DecM);

    cout << "DecryptionTest\nMessage : ";
    for(int i=0; i<num; i++){
        cout << m[i] << " ";
    }
    cout << "\n";

    cout << "Decryption Message : ";
    for(int i=0; i<num; i++){
        cout << DecM[i] << " ";
    }
    cout << "\n\n";

}

void AddEncMTest(){
    /*
        기대값과 다름. 추후 수정 필요.
    */


    int m1[num] = {0,0,0,0,0,1,1,1,1,1};
    int m2[num] = {1,1,1,1,1,0,0,0,0,0};

    int SK[num];
    SecretKeyGenerator(SK);

    int paramA[num][num];
    ParamGenerator(*paramA, num, num);

    int EncM1[num];
    int EncM2[num];
    Encryption(m1, num, SK, *paramA, EncM1);
    Encryption(m2, num, SK, *paramA, EncM2);

    int Result[num];
    AddEncMessage(EncM1, EncM2, num, Result);

    int DecRes[num];
    Decryption(Result, num, SK, *paramA, DecRes);

    cout << "EncMessage Add Test\nMessage1 : ";
    for(int i=0; i<num; i++){
        cout << m1[i] << " ";
    }
    cout << "\nMessage2 : ";
    for(int i=0; i<num; i++){
        cout << m2[i] << " ";
    }
    cout << "\n";

    cout << "Decryption Message : ";
    for(int i=0; i<num; i++){
        cout << DecRes[i] << " ";
    }
    cout << "\n\n";
}