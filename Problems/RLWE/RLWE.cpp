#include <iostream>
#include <ctime>
#include <cstdlib>
#define Q 112
#define Demension_N  4
using namespace std;

int* polyMulti(int a[], int a_size, int b[], int b_size);
void polyMod(int a[], int a_size);
int* polyDiv(int a[], int a_size, int b[], int b_size);
void printPoly(int poly[], int size);
void MesGen(int m[], int m_size);
int* ParamGen();
int* SecretKeyGen();
void Encryption(int message[], int m_size, int paramA[], int SK[], int* EncMes[]);

int main(){

    // srand(time(NULL));

    /* TEST 1 */
    // int tempPoly1[4] = {3, 4, 2, 4};
    // int tempPoly2[4] = {8, 4, 2, 5};

    // int* poly = polyMulti(tempPoly1, 4, tempPoly2, 4);

    // cout << sizeof(poly) << " " <<  sizeof(poly)/sizeof(int) << "\n";

    // printPoly(poly, 7);
    
    /* TEST 2 */
    // int tempPoly1[4] = {4,3,2,4};
    // int tempPoly2[3] = {1,0,1};

    // polyDiv(tempPoly1, 4, tempPoly2, 3);


    /* TEST 3*/
    int message[4] = {1, 0, 1, 0};
    int* paramA = ParamGen();
    int* SK = SecretKeyGen();
    int* Enc[4];
    
    // cout << "Param = ";
    // printPoly(paramA, Demension_N);
    // cout << "SK = ";
    // printPoly(SK, Demension_N);

    Encryption(message, 4, paramA, SK, Enc);

    // for(int i=0; i<4; i++){
    //     cout << "Enc[" << i << "] = ";
    //     printPoly(Enc[i], Demension_N);
    // }


    return 0;
}

void MesGen(int m[], int m_size){
    for(int i=0; i<m_size; i++){
        m[i] = rand() % 2;
    }
}

int* ParamGen(){
    int* a = new int[Demension_N];
    for(int i=0; i<Demension_N; i++){
        a[i] = rand() % Q;
    }

    return a;
}

int* SecretKeyGen(){
    int* SK = new int[Demension_N];
    for(int i=0; i<Demension_N; i++){
        SK[i] = rand() % Q;
    }

    return SK;
}

void Encryption(int message[], int m_size, int paramA[], int SK[], int* EncMes[]){
    int Err[3] = {-1, 0, 1};
    
    int* tempPoly = polyMulti(paramA, Demension_N, SK, Demension_N);
    int tempPolyLen = Demension_N * 2 - 1;

    // cout << "Multi Reuslt = ";
    // printPoly(tempPoly, tempPolyLen);

    int dividePoly[Demension_N+1] = {0};
    dividePoly[0] = 1;
    dividePoly[Demension_N] = 1;

    // cout << "Div Reuslt = ";
    // printPoly(dividePoly, Demension_N+1);



    for(int i=0; i<m_size; i++){
        
        int* remainPoly = polyDiv(tempPoly, tempPolyLen, dividePoly, Demension_N+1);
        int remainPolyLen = Demension_N;

        // cout << "Remain Reuslt = ";
        // printPoly(remainPoly, remainPolyLen);

        /* ADD ERROR */
        for(int i=0; i<remainPolyLen; i++){
            int err = Err[rand() % 3];
            remainPoly[i] += err;
        }

        if(message[i] == 1){
            remainPoly[0] += Q/2;
        }

        polyMod(remainPoly, remainPolyLen);

        EncMes[i] = remainPoly;
    }
}

/* 생각 필요 */
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