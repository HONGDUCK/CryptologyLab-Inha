/*<------------- Library -------------->*/
#include <iostream>
#include <ctime>
using namespace std;

/*<---------------- Parameter ----------------->*/
#define Mod_Q 112 // 임의로 정함 추후 변경필요

/*<----------------- function Prototype ------------------>*/
void SecretKeyGenerator();
void hello();

int main(){

    return 0;
}

/*<------------- function Definition -------------->*/
void SecretKeyGenerator(int Setkey[]){
    /* n : 시크릿 키 담을 배열의 크기 */
    int n = sizeof(Setkey);

    for(int i=0; i<n; i++){
        Setkey[i] = rand() % Mod_Q;
    }
}

void hello(){
    cout << "hello Cryptology!\n";
}