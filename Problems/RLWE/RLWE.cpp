#include <iostream>
#include <ctime>
#include <cstdlib>
#include <complex>
#include <cmath>
#include <vector>

#define Q 112
#define PI acos(-1)
#define Demension_N  4

using namespace std;

typedef complex<double> cpdb;

void FFT(vector<cpdb>& a, cpdb w);
int* multi(int a[], int a_size, int b[], int b_size);

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
void Encryption(int message[], int m_size, int* PK_a, int* PK_b, int* PK_u[], int* PK_v[]);
void PreEnc(int SK[], int** PK_a, int** PK_b);


int main(){
    int MessageSize = 32;

    srand(time(NULL));

    /* TEST 3*/
    int* message = MesGen(MessageSize);
    int* SK = SecretKeyGen();
    int* PK_a = new int[Demension_N];
    int* PK_b = new int[Demension_N];
    int* PK_v[MessageSize / Demension_N];
    int* PK_u[MessageSize / Demension_N];

    PreEnc(SK, &PK_a, &PK_b);
    Encryption(message, MessageSize, PK_a, PK_b, PK_u, PK_v);

    cout << "Message : ";
    for(int i=0; i<MessageSize; i++){
        cout << message[i] << " ";
    }
    cout << "\n\n";

    for(int i=0; i<MessageSize/Demension_N; i++){
        cout << "PK_u[" << i << "] = ";
        printPoly(PK_u[i], Demension_N);
    }
    cout << "\n";

    for(int i=0; i<MessageSize/Demension_N; i++){
        cout << "PK_v[" << i << "] = ";
        printPoly(PK_v[i], Demension_N);
    }
    cout << "\n";

    int DecMes[MessageSize];
    Decryption(PK_u, PK_v, SK, DecMes, MessageSize);

    cout << "DecMes : ";
    for(int i=0; i<MessageSize; i++){
        cout << DecMes[i] << " ";
    }
    cout << "\n";

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

void PreEnc(int SK[], int** PK_a, int** PK_b){
    /* <------------- Generate PK a, b ----------------> */
    int *paramA = ParamGen();
    int *paramB = polyOperation(paramA, Demension_N, SK, Demension_N);

    int *Err0 = ErrGen();
    polyAdd(paramB, Demension_N, Err0, Demension_N);
    polyMod(paramB, Demension_N);

    /* Public Key A, B 생성 */
    *PK_a = paramA;
    *PK_b = paramB;
}

void Encryption(int message[], int m_size, int* PK_a, int* PK_b, int* PK_u[], int* PK_v[]){
    /* <----------------- Generate New PK u, v ---------------------> */

    for(int i=0; i<m_size/Demension_N; i++){
        int* EphKey = EphKeyGen(); /* 임시 키 생성 Small Value */
        int* Err1 = ErrGen(); /* Error 생성 Small Value */
        int* Err2 = ErrGen();

        int* temp_u = new int[Demension_N];
        int* temp_v = new int[Demension_N];

        temp_u = polyOperation(PK_a, Demension_N, EphKey, Demension_N);
        polyAdd(temp_u, Demension_N, Err1, Demension_N);
        polyMod(temp_u, Demension_N);

        temp_v = polyOperation(PK_b, Demension_N, EphKey, Demension_N);
        polyAdd(temp_v, Demension_N, Err2, Demension_N);

        for(int j=0; j<Demension_N; j++){

            if(message[i*Demension_N + j] == 1){
                temp_v[j] += Q/2;
            }

        }
        polyMod(temp_v, Demension_N);

        PK_u[i] = temp_u;
        PK_v[i] = temp_v;
    }
}

void Decryption(int* PK_u[], int* PK_v[], int SK[], int DecMes[], int m_size){
    for(int i=0; i<m_size/Demension_N; i++){
        int tempNum = 0;

        int* poly_us = polyOperation(PK_u[i], Demension_N, SK, Demension_N);
        polySub(poly_us, Demension_N, PK_v[i], Demension_N);
        polyMod(poly_us, Demension_N);
        
        for(int j=0; j<Demension_N; j++){
            tempNum = poly_us[j];

            // cout << "tempNum : " << tempNum << "\n";
    
            if(tempNum <= Q/4 || tempNum >= (Q*3)/4){
                DecMes[i*Demension_N + j] = 0;
            }else{
                DecMes[i*Demension_N + j] = 1;
            }
        }
    }
}

/*-----------------------------*/

int* polyOperation(int polyA[], int a_size, int polyB[], int b_size){
    int* tempPoly = multi(polyA, a_size, polyB, b_size);
    int tempPolyLen = a_size + b_size - 1;

    int dividePoly[Demension_N + 1] = {0};
    dividePoly[0] = 1;
    dividePoly[Demension_N] = 1;

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

void FFT(vector<cpdb>& a, cpdb w){
    int n = a.size();
    if(n == 1) return;

    vector<cpdb> even(n >> 1), odd(n >> 1);
    for(int i=0; i<n; i++){
        if(i & 1) odd[i >> 1] = a[i];
        else even[i >> 1] = a[i];
    }

    /*divide*/
    FFT(even, w*w), FFT(odd, w*w);

    cpdb cw(1, 0);
    for(int i=0; i<n/2; i++){
        a[i] = even[i] + cw * odd[i];
        a[i + n/2] = even[i] - cw * odd[i];

        cw *= w;
    }
}

int* multi(int a[], int a_size, int b[], int b_size){
    int n = 1;
    while (n < a_size || n < b_size){
        n = n << 1;
    }
    n = n << 1;

    vector<cpdb> _a(n), _b(n);
    for(int i=a_size-1; i>=0; i--){
        _a[i] = cpdb(a[i], 0);
    }

    for(int i=b_size-1; i>=0; i--){
        _b[i] = cpdb(b[i], 0);
    }

    // FFT 변환을 위한 w
    cpdb w( cos(2*PI/n), sin(2*PI/n) );
    FFT(_a, w), FFT(_b, w);

    vector<cpdb> c(n);
    for(int i=0; i<n; i++){
        c[i] = _a[i] * _b[i];
    }

    // FFT 역변환을 위한 rw
    cpdb rw( cos(-2*PI/n), sin(-2*PI/n) );
    FFT(c, rw);

    for(int i=0; i<n; i++){
        c[i] /= cpdb(n,0);
    }

    int* ans = new int[a_size + b_size - 1];
    for(int i=0; i<c.size(); i++){
        ans[i] = round(c[i].real());
    }

    return ans;
}