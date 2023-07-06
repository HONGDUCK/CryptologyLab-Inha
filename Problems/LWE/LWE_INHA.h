#ifndef LWE_INHA_H
#define LWE_INHA_H

#define Mod_Q 112
#define num 10

void Decryption(int EncMessage[], int MessageSize, int SecKey[], int* ParamMatrix, int DecMessage[]);
void Encryption(int Message[], int MessageSize, int SecKey[], int* ParamMatrix, int EncMessage[]);
void SecretKeyGenerator(int Setkey[]);
void MessageGenerator(int n, int m[]);
void ParamGenerator(int* a, int m, int n);
void Operator(int m0[], int m1[], int MessageSize, int result[]);
void AddEncMessage(int EncMessage1[], int EncMessage2[], int MessageSize, int result[], int* param_a, int* param_b, int* newParam);


#endif

