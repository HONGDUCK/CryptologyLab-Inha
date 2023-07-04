/*<------------- Library -------------->*/
#include <iostream>
#include <ctime>
using namespace std;

/*<---------------- Parameter ----------------->*/
#define Mod_Q 112 // 임의로 정함 추후 변경필요

/*<----------------- function Prototype ------------------>*/
void Encryption(int Message[], int SecKey[], int* ParamMatrix, int EncMessage[]);
void SecretKeyGenerator(int Setkey[]);
void MessageGenerator(int n, int m[]);
void ParamGenerator(int* a, int m, int n);
void hello();

int main(){

    return 0;
}

/*<------------- function Definition -------------->*/
void Encryption(int Message[], int SecKey[], int* ParamMatrix, int EncMessage[]){
    /* 암호화 함수 메세지, 시크릿 키, Matrix A를 인자로 받으며 암호화된 정보인 EncMessage를 생성 */
    int tempError[3] = {-1,0,1}; /* 임의의 Err값 */
    int m = sizeof(Message); /* Message의 크기 : bit */
    int n = sizeof(SecKey); /* Security Value */

    for(int i=0; i<m; i++){
        int tempNum = Message[i]; /* DotProduct의 값 */

        if(Message[i] == 1){ /* Message가 1일 경우 ---> m + <a,s> + e + [q/2] */
            for(int j=0; j<n; j++){
                tempNum += SecKey[j] * *(ParamMatrix+(i*m)+j);
            }
            tempNum += tempError[rand()%3] + (Mod_Q/2); /* 임의의 Error + [q/2] */
            tempNum = tempNum % Mod_Q;

            EncMessage[i] = tempNum;

        }else{ /* Message가 0일 경우 ---> m + <a,s> + e */
            for(int j=0; j<n; j++){
                tempNum += SecKey[j] * *(ParamMatrix+(i*m)+j);
            }
            tempNum += tempError[rand()%3]; /*임의의 Error 추가*/
            tempNum = tempNum % Mod_Q;

            EncMessage[i] = tempNum;

        }
    }
}

void SecretKeyGenerator(int Setkey[]){
    /* 시크릿 키를 생성하는 함수, SetKey배열을 인자로 받으며 SetKey에 임의의 시크릿 키를 생성하여 리턴*/
    /* n : 시크릿 키 담을 배열의 크기 */
    int n = sizeof(Setkey);

    for(int i=0; i<n; i++){
        Setkey[i] = rand() % Mod_Q;
    }
}

void ParamGenerator(int* a, int m, int n){
    /* 공개되는 파라미터인 Matrix A를 생성하는 함수 */
    /* 배열을 포인터로서 받으며, 해당 포인터를 통해 파라미터값을 갱신 후 리턴 */
    /* m : 보내고자 하는 메세지 수, n : Security Value */

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            *(a + (i*m) + j) = rand() % Mod_Q; 
        }
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