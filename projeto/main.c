//COMPILAR: gcc main.c -lcrypto
#include <string.h>
#include <math.h>
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

void preencheZeros(unsigned char vetor[], int tam) {
    for(int i = 0; i < tam; i++)
        vetor[i] = 0;
}

void copiaHash(unsigned char destino[], unsigned char origem[], int tam) {
    for(int i = 0; i < tam; i++)
        destino[i] = origem[i];
}

void printHash(unsigned char hash[], int length) {
    int i;
    for(i=0;i<length;++i)
        printf("%02x", hash[i]);
    
    printf("\n");
}

void printVetor(unsigned char hash[], int length) {
    int i;
    for(i=0;i<length;++i)
        printf("%d ", hash[i]);
    
    printf("\n");
}

BlocoMinerado mineraBloco(unsigned int num, unsigned char hashAnterior[]) {
    BlocoNaoMinerado bloco;

    //Preenchendo dados no bloco
    bloco.numero = num;
    bloco.nonce = 0;

    preencheZeros(bloco.data, 184);
    MTRand r = seedRand(1234567);
    bloco.data[0] = genRandLong(&r) % 256;
    bloco.data[1] = genRandLong(&r) % 256;
    bloco.data[2] = 3;
    bloco.data[3] = genRandLong(&r) % 256;
    bloco.data[4] = genRandLong(&r) % 256;
    bloco.data[5] = 6;
    bloco.data[6] = 7;
    bloco.data[7] = 25;
    bloco.data[8] = 50;
    bloco.data[183] = genRandLong(&r) % 256;

    copiaHash(bloco.hashAnterior, hashAnterior, SHA256_DIGEST_LENGTH);

    //Obtendo hash do bloco
    unsigned char hash[SHA256_DIGEST_LENGTH];
    while(bloco.nonce < pow(2,32)) {
        SHA256((unsigned char *) &bloco, sizeof(BlocoNaoMinerado), hash);
        printHash(hash, SHA256_DIGEST_LENGTH);

        if(hash[0] == 0) {
            BlocoMinerado minerado;
            minerado.bloco = bloco;
            copiaHash(minerado.hash, hash, SHA256_DIGEST_LENGTH);
            return minerado;
        }

        (bloco.nonce)++;
    }
    
}

int main() {
    int contBlocos = 1;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    preencheZeros(hash, SHA256_DIGEST_LENGTH);
    BlocoMinerado minerados[16]; //16*256 = 4096
    minerados[0] = mineraBloco(contBlocos, hash);

    //Imprimindo bloco
    printf("%d\n", minerados[0].bloco.numero);
    printVetor(minerados[0].bloco.data, 184);
    printf("%d\n", minerados[0].bloco.nonce);
    printHash(minerados[0].hash, SHA256_DIGEST_LENGTH);
    printHash(minerados[0].bloco.hashAnterior, SHA256_DIGEST_LENGTH);
    return 0;
}