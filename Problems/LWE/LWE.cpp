/*<------------- Library -------------->*/
#include <iostream>
#include <ctime>
using namespace std;

/*<---------------- Parameter ----------------->*/
#define Mod_Q 112 // 임의로 정함 추후 변경필요

/*<----------------- function Prototype ------------------>*/
void SecretKeyGenerator();
void MessageGenerator();
void hello();

int main(){

    return 0;
}

/*<------------- function Definition -------------->*/
void SecretKeyGenerator(int Setkey[]){
    /* 시크릿 키를 생성하는 함수, SetKey배열을 인자로 받으며 SetKey에 임의의 시크릿 키를 생성하여 리턴*/
    /* n : 시크릿 키 담을 배열의 크기 */
    int n = sizeof(Setkey);

    for(int i=0; i<n; i++){
        Setkey[i] = rand() % Mod_Q;
    }
}

void MessageGenerator(int n, int m[]) {
    /*메세지를 생성하는 함수, 메세지의 길이인 n과 m배열을 인자로 받으며 m에 임의의 메세지를 생성하여 리턴*/
    for (int i = 0;i < n;i++) {
        m[i] = rand() % 2;
    }
}

void hello(){
    cout << "hello Cryptology!\n";
}