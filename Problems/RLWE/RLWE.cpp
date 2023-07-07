#include <iostream>
#include <ctime>
#include <cstdlib>
#define Q 112
#define Demension_N  4
using namespace std;

int* polyOperation(int polyA[], int a_size, int polyB[], int b_size);
int* polyMulti(int a[], int a_size, int b[], int b_size);
void polyMod(int a[], int a_size);
int* polyDiv(int a[], int a_size, int b[], int b_size);
void printPoly(int poly[], int size);
void polyAdd(int a[], int a_size, int b[], int b_size);
void polySub(int a[], int a_size, int b[], int b_size);

int* MesGen(int m_size);
int* ParamGen();
int* SecretKeyGen();
int* EphKeyGen();

void Decryption(int* PK_u[], int* PK_v[], int SK[], int DecMes[], int m_size);
void Encryption(int message[], int m_size, int SK[], int* PK_u[], int* PK_v[]);

int main(){
    int MessageSize = 8;

    srand(time(NULL));

    /* TEST 3*/
    int* message = MesGen(MessageSize);
    int* SK = SecretKeyGen();
    int* PK_v[MessageSize];
    int* PK_u[MessageSize];


    Encryption(message, MessageSize, SK, PK_u, PK_v);

    cout << "Message : ";
    for(int i=0; i<MessageSize; i++){
        cout << message[i] << " ";
    }
    cout << "\n";

    for(int i=0; i<MessageSize; i++){
        cout << "PK_u[" << i << "] = ";
        printPoly(PK_u[i], Demension_N);
    }

    for(int i=0; i<MessageSize; i++){
        cout << "PK_v[" << i << "] = ";
        printPoly(PK_v[i], Demension_N);
    }

    int DecMes[MessageSize];
    Decryption(PK_u, PK_v, SK, DecMes, MessageSize);

    cout << "DecMes : ";
    for(int i=0; i<MessageSize; i++){
        cout << DecMes[i] << " ";
    }

    return 0;
}


int* MesGen(int m_size){
    int* m = new int[m_size];
    for(int i=0; i<m_size; i++){
        m[i] = rand() % 2;
    }

    return m;
}

int* ParamGen(){
    int* a = new int[Demension_N];
    for(int i=0; i<Demension_N; i++){
        a[i] = rand() % Q;
    }

    return a;
}

int* SecretKeyGen(){
    int small_Val[3] = {Q-1, 0, 1};
    int* SK = new int[Demension_N];

    for(int i=0; i<Demension_N; i++){
        SK[i] = small_Val[rand() % 3];
    }

    return SK;
}

int* EphKeyGen(){
    int small_Val[3] = {Q-1, 0, 1};
    int* ep = new int[Demension_N];

    for(int i=0; i<Demension_N; i++){
        ep[i] = small_Val[rand() % 3];
    }

    return ep;
}

int* ErrGen(){
    int small_Val[3] = {Q-1, 0, 1};
    int* err = new int[Demension_N];

    for(int i=0; i<Demension_N; i++){
        err[i] = small_Val[rand() % 3];
    }

    return err;
}

/*-----------------------------*/

void Encryption(int message[], int m_size, int SK[], int* PK_u[], int* PK_v[]){
    int small_Val[3] = {Q-1, 0, 1};
    
    /* <------------- Generate PK a, b ----------------> */

    int *paramA = ParamGen();
    int *paramB = polyOperation(paramA, Demension_N, SK, Demension_N);
    int *Err0 = ErrGen();
    polyAdd(paramB, Demension_N, Err0, Demension_N);
    polyMod(paramB, Demension_N);

    /* <----------------- Generate New PK u, v ---------------------> */

    for(int i=0; i<m_size; i++){
        int* EphKey = EphKeyGen(); /* 임시 키 생성 Small Value */
        int* Err1 = ErrGen(); /* Error 생성 Small Value */
        int* Err2 = ErrGen();

        int* temp_u = new int[Demension_N];
        int* temp_v = new int[Demension_N];

        temp_u = polyOperation(paramA, Demension_N, EphKey, Demension_N);
        polyAdd(temp_u, Demension_N, Err1, Demension_N);
        polyMod(temp_u, Demension_N);

        temp_v = polyOperation(paramB, Demension_N, EphKey, Demension_N);
        polyAdd(temp_v, Demension_N, Err2, Demension_N);

        if(message[i] == 1){
            temp_v[0] += Q/2;
            polyMod(temp_v, Demension_N);
        }else{
            polyMod(temp_v, Demension_N);
        }

        PK_u[i] = temp_u;
        PK_v[i] = temp_v;
    }
}

void Decryption(int* PK_u[], int* PK_v[], int SK[], int DecMes[], int m_size){
    for(int i=0; i<m_size; i++){
        int tempNum = 0;

        int* poly_us = polyOperation(PK_u[i], Demension_N, SK, Demension_N);
        polySub(poly_us, Demension_N, PK_v[i], Demension_N);
        polyMod(poly_us, Demension_N);
        
        tempNum = poly_us[0];

        cout << "tempNum : " << tempNum << "\n";

        if(tempNum <= Q/4 || tempNum >= 75){
            DecMes[i] = 0;
        }else{
            DecMes[i] = 1;
        }
    }
}

/*-----------------------------*/

int* polyOperation(int polyA[], int a_size, int polyB[], int b_size){
    int* tempPoly = polyMulti(polyA, a_size, polyB, b_size);
    int tempPolyLen = a_size + b_size - 1;

    // cout << "Multi Reuslt = ";
    // printPoly(tempPoly, tempPolyLen);

    int dividePoly[Demension_N + 1] = {0};
    dividePoly[0] = 1;
    dividePoly[Demension_N] = 1;

    // cout << "Div Reuslt = ";
    // printPoly(dividePoly, Demension_N+1);

    int* paramB = polyDiv(tempPoly, tempPolyLen, dividePoly, Demension_N+1);
    int paramB_Len = Demension_N;

    return paramB;
}

void polyMod(int a[], int a_size){
    for(int i=0; i<a_size; i++){
        a[i] = a[i] % Q;
        if(a[i] < 0){
            a[i] = Q + a[i];
        }
    }
}

/*
    int형 정수만 다룰 수 있음
    간단한 RLWE Problem에만 접목 가능
    일반적인 Div함수가 아님.
*/
int* polyDiv(int a[], int a_size, int b[], int b_size){
    if(a_size < b_size){
        /*Error 처리*/
        cout << "Error Try Again\n";

        return nullptr;
    }

    int* tempArr = new int[a_size];
    for(int i=0; i<a_size; i++){
        tempArr[i] = a[i];
    }

    int* quo = new int[a_size - b_size + 1];
    int* remain = new int[b_size-1];

    int index = a_size-1;
    int indexForQuo = 1;
    while (index >= b_size-1){
        int divNum = tempArr[index] / b[b_size - 1];
        tempArr[index] = 0;

        quo[b_size-1 - indexForQuo] = divNum;

        for(int i=1; i<b_size; i++){
            tempArr[index - i] = tempArr[index - i] - (b[b_size-1 - i] * divNum);
        }

        index--;
        indexForQuo++;
    }

    for(int i=0; i<b_size-1; i++){
        remain[i] = tempArr[i];
    }

    /* print */
    // printPoly(quo, b_size-1); /* 몫 */
    // printPoly(remain, b_size-1); /* 나머지 */

    return remain; /* 나머지 리턴 */
}

int* polyMulti(int a[], int a_size, int b[], int b_size){

    int ansLength = a_size + b_size -1;
    int* ans = new int[ansLength];

    for(int i=0; i<ansLength; i++){
        ans[i] = 0;
    }

    for(int i=0; i<a_size; i++){
        for(int j=0; j<b_size; j++){
            ans[i+j] += a[i] * b[j];
        }
    }

    return ans;
}

void printPoly(int poly[], int size){
    
    for (int i=0; i<size; i++){

       cout << poly[i];

       if(i != 0){
            cout << "x^" << i ;
       }

       if (i != size-1){
           cout << " + ";
       }
    }
    cout << "\n";
}

void polyAdd(int a[], int a_size, int b[], int b_size){
    for(int i=0; i<Demension_N; i++){
        a[i] = a[i] + b[i];
    }
}

void polySub(int a[], int a_size, int b[], int b_size){
    for(int i=0; i<Demension_N; i++){
        a[i] = b[i] - a[i];
    }
}