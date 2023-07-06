/*<------------- Library -------------->*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "LWE_INHA.h"
using namespace std;

/*<------------- function Definition -------------->*/
void Encryption(int Message[], int MessageSize, int SecKey[], int* ParamMatrix, int EncMessage[]) {
    /* 암호화 함수 메세지, 시크릿 키, Matrix A를 인자로 받으며 암호화된 정보인 EncMessage를 생성 */
    int tempError[3] = { -1,0,1 }; /* 임의의 Err값 */
    srand(time(NULL));

    for (int i = 0; i < MessageSize; i++) {
        int tempNum = Message[i]; /* DotProduct의 값 */

        if (Message[i] == 1) { /* Message가 1일 경우 ---> m + <a,s> + e + [q/2] */
            for (int j = 0; j < num; j++) {
                tempNum += SecKey[j] * *(ParamMatrix + (i * MessageSize) + j);
            }
            tempNum += tempError[rand() % 3] + (Mod_Q / 2); /* 임의의 Error + [q/2] */
            tempNum = tempNum % Mod_Q;

            EncMessage[i] = tempNum;

        }
        else { /* Message가 0일 경우 ---> m + <a,s> + e */
            for (int j = 0; j < num; j++) {
                tempNum += SecKey[j] * *(ParamMatrix + (i * MessageSize) + j);
            }
            tempNum += tempError[rand() % 3]; /*임의의 Error 추가*/
            tempNum = tempNum % Mod_Q;

            EncMessage[i] = tempNum;

        }   
    }
}

void SecretKeyGenerator(int Setkey[]) {
    /* 시크릿 키를 생성하는 함수, SetKey배열을 인자로 받으며 SetKey에 임의의 시크릿 키를 생성하여 리턴*/
    /* n : 시크릿 키 담을 배열의 크기 */
    srand(time(NULL));

    for (int i = 0; i < num; i++) {
        Setkey[i] = rand() % Mod_Q;
    }
}

void ParamGenerator(int* a, int m, int n) {
    /* 공개되는 파라미터인 Matrix A를 생성하는 함수 */
    /* 배열을 포인터로서 받으며, 해당 포인터를 통해 파라미터값을 갱신 후 리턴 */
    /* m : 보내고자 하는 메세지 수, n : Security Value */
    srand(time(NULL));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            *(a + (i * m) + j) = rand() % Mod_Q;
        }
    }
}

void Decryption(int EncMessage[], int MessageSize, int SecKey[], int* ParamMatrix, int DecMessage[])
{

    for (int i = 0; i < MessageSize; i++) {
        int tempNum = 0;
        int DecVal = 0;
        /*  <a,s> 계산*/
        for (int j = 0; j < num; j++) {
            tempNum += SecKey[j] * *(ParamMatrix + (i * MessageSize) + j);
        }
        
        tempNum = tempNum % Mod_Q;
        DecVal = EncMessage[i] - tempNum;

        cout << "DecVal : " << DecVal << "\n";

        if(DecVal < 0){
            DecVal *= -1;
        }

        /* 수정 필요.. 절댓값 대체
        if (DecVal >= -Mod_Q / 2 - 1 && DecVal <= -Mod_Q / 2 + 2)
        {
            DecVal += Mod_Q;
        }
        */

        if (DecVal >= Mod_Q / 4)
            DecMessage[i] = 1;
        else
            DecMessage[i] = 0;
    }
}

void MessageGenerator(int n, int m[]) {
    /*메세지를 생성하는 함수, 메세지의 길이인 n과 m배열을 인자로 받으며 m에 임의의 메세지를 생성하여 리턴*/
    srand(time(NULL));
    
    for (int i = 0; i < n; i++) {
        m[i] = rand() % 2;
    }
}

void Operator(int m0[], int m1[], int MessageSize, int result[]) {
    int carry = 0;

    for (int i = 0; i < MessageSize; i++) {
        int sum = m0[i] + m1[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }

    if (carry > 0) {
        result[MessageSize] = carry;
    }
}

void AddEncMessage(int EncMessage1[], int EncMessage2[], int MessageSize, int result[]) {
    /*
        int carry = 0;

        for (int i = 0; i < MessageSize; i++) {
            int sum = EncMessage1[i] + EncMessage2[i] + carry;
            result[i] = sum % Mod_Q;
            carry = sum / Mod_Q;
        }
        if (carry > 0) {
            result[MessageSize] = carry;
        }
    */

    for(int i=0; i<MessageSize; i++){
        result[i] = (EncMessage1[i] + EncMessage2[i]) % Mod_Q;
    }
}

void hello() {
    cout << "hello Cryptology!\n";
}