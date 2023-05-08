//COMPILAR: gcc main.c -lcrypto
#include <string.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "mtwister.h"

typedef struct blocoNaoMinerado {
    unsigned int numero;
    unsigned int nonce;
    unsigned char data[184];
    unsigned char hashAnterior[SHA256_DIGEST_LENGTH];
} BlocoNaoMinerado;

typedef struct blocoMinerado {
    BlocoNaoMinerado bloco;
    unsigned char hash[SHA256_DIGEST_LENGTH];
} BlocoMinerado;

void preencheZeros(unsigned char vetor[],int tam) {
    for(int i = 0; i < tam; i++)
        vetor[i] = 0;
}

void printHash(unsigned char hash[], int length) {
    int i;
    for(i=0;i<length;++i)
        printf("%02x", hash[i]);
    
    printf("\n");
}

int main() {
    BlocoNaoMinerado bloco;

    //Preenchendo dados no bloco
    bloco.numero = 1;
    bloco.nonce = 426;
    preencheZeros(bloco.data, 184);
    bloco.data[0] = 1;
    bloco.data[1] = 2;
    bloco.data[2] = 3;
    bloco.data[3] = 4;
    bloco.data[4] = 5;
    bloco.data[5] = 6;
    bloco.data[7] = 255;
    bloco.data[8] = 50;
    bloco.data[183] = 125;
    preencheZeros(bloco.hashAnterior, SHA256_DIGEST_LENGTH);

    //Obtendo hash do bloco
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *) &bloco, sizeof(BlocoNaoMinerado), hash);

    //Imprimindo hash
    printHash(hash, SHA256_DIGEST_LENGTH);

    BlocoMinerado minerados[16]; //16*256 = 4096
    minerados[0].bloco = bloco;
    strcpy(minerados[0].hash, hash);
    printHash(minerados[0].hash, SHA256_DIGEST_LENGTH);
    printHash(minerados[0].bloco.hashAnterior, SHA256_DIGEST_LENGTH);

    MTRand r = seedRand(1234567);
    for(int i = 0; i < 1000; i++) {
        printf("%lf\n", genRandLong(&r));
    }

    return 0;
}