#ifndef LWE_INHA_H
#define LWE_INHA_H

#define Mod_Q 112
#define num 10

void Encryption(int Message[], int MessageSize, int SecKey[], int* ParamMatrix, int EncMessage[]);
void SecretKeyGenerator(int Setkey[]);
void MessageGenerator(int n, int m[]);
void ParamGenerator(int* a, int m, int n);


#endif

