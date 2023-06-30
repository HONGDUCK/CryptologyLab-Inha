/* q = 112, n = 10 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#define _q 112
#define _n 10
using namespace std;

int temp[3] = {-1, 0, 1};
int sk[_n];
int a[_n][_n];
int err[_n];
int EncMessage[_n];
int Message[_n];
int DecMessage[_n];

void printEncMessage(){
    cout << "Enc Message : " << "\n";
    for(int i=0; i<_n; i++){
        cout << EncMessage[i] << " ";
    }
    cout  << "\n\n";
}

void printSecretKey(){
    cout << "SecretKey : " << "\n";
    for(int i=0; i<_n; i++){
        cout << sk[i] << " ";
    }
    cout  << "\n\n";
}

void printMatrix(){
    cout << "--- Matrix ---" << "\n";
    for(int i=0; i<_n; i++){
        for(int j=0; j<_n; j++){
            if(j != _n-1){
                cout << a[i][j] << "S" << i << " + ";
            }else{
                cout << a[i][j] << "S" << i << "\n";
            }
        }
    }
    cout << "\n\n";
}

void printDecMessage(){
    cout << "DecMessage : " << "\n";
    for(int i=0; i<_n; i++){
        cout << DecMessage[i] << " ";
    }
    cout  << "\n\n";
}

void printInputData(){
    cout << "input data (bit) : ";
    for(int i=0; i<_n; i++){
        cout << Message[i] << " ";
    }
    cout << "\n\n";
}

void initMessage(){
    /*<--- 무작위 이진수 추출 -->*/
    for(int i=0; i<_n; i++){
        Message[i] = rand() % 2;
    }
}

void Encryption(){
    for(int i=0; i<_n; i++){
        for(int j=0; j<_n; j++){
            /* <-- 무작위 a벡터 추출 -->*/
            a[i][j] = rand() % _q;
        }
        /* <-- 무작위 err값 및 무작위 Secret Key 추출 -->*/
        /* err의 경우 -1, 0, 1 중 하나 */
        err[i] = temp[rand()%3];
        sk[i] = rand() % _q;
    }

    for(int i=0; i<_n; i++){
        int tempNum;
        
        /* 
            비트가 1일 경우 m + <a,s> + e + [q/2]
            비트가 0일 경우 m + <a,s> + e
        */

        /* <-- 비트가 1일 경우 --> */
        if(Message[i] == 1){
            tempNum = 1;
            for(int j=0; j<_n; j++){
                /* <-- <a,s> 값 계산 --> */
                tempNum += a[i][j] * sk[j] % _q;
            }
            /*<-- + e + [q/2] -->*/
            tempNum += (err[i] + (_q/2));
            tempNum = tempNum % _q;
            EncMessage[i] = tempNum;
        }else{
            tempNum = 0;
            for(int j=0; j<_n; j++){
                /* <-- <a,s> 값 계산 --> */
                tempNum += a[i][j] * sk[j] % _q;
            }
            /*<-- + e -->*/
            tempNum += err[i];
            tempNum = tempNum % _q;
            EncMessage[i] = tempNum;
        }

    }
}

void Decryption(){
    for(int i=0; i<_n; i++){
        int tempNum = 0;

        for(int j=0; j<_n; j++){
            /* <-- 사용자는 secret Key를 알고있으니 이를 통해 <a,s>를 쉽게 구함 --> */
            tempNum += a[i][j] * sk[j];
        }
        tempNum = tempNum % _q;

        /* LWE(m) - <a,s> = m + e ---> tempNum */
        tempNum = (EncMessage[i] - tempNum) % _q;
        /* 음수가 나올수도 있어 절댓값 */
        if(tempNum < 0){
            tempNum *= -1;
        }

        /* 
            [q/2] 보다 tempNum = m + e 가 0에 가까울 경우 m은 0,
            그 외에 m은 1
        */
        if(_q/4 > tempNum){
            cout << "Value : " << tempNum << " ---> 0\n";
            DecMessage[i] = 0; 
        }else{
            cout << "Value : " << tempNum << " ---> 1\n";
            DecMessage[i] = 1; 
        }
    }
    cout << "\n";
}

int main(){

    srand((unsigned int) time(NULL));

    initMessage();
    Encryption();

    printInputData();
    printEncMessage();

    cout << "<--- decryption Start --->\n\n";

    /* decryption Start */
    Decryption();
    printDecMessage();

    return 0;
}