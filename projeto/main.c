//COMPILAR: gcc main.c mtwister.c -lcrypto
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

void copiaVetor(unsigned char destino[], unsigned char origem[], int tam) {
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
    unsigned char data[184] = {0};

    MTRand r = seedRand(1234567);
    int quantTransacoes = genRandLong(&r) % 62;

    for(int i = 0; i < quantTransacoes; i++) {
        data[3*i+0] = genRandLong(&r) % 256;
        data[3*i+1] = genRandLong(&r) % 256;
        data[3*i+2] = genRandLong(&r) % 51;
    }
    
    data[183] = genRandLong(&r) % 256;
    copiaVetor(bloco.data, data, 184);
    copiaVetor(bloco.hashAnterior, hashAnterior, SHA256_DIGEST_LENGTH);

    //Obtendo hash do bloco
    unsigned char hash[SHA256_DIGEST_LENGTH];
    while(bloco.nonce < pow(2,32)) {
        SHA256((unsigned char *) &bloco, sizeof(BlocoNaoMinerado), hash);
        //printHash(hash, SHA256_DIGEST_LENGTH);

        if(hash[0] == 0) {
            BlocoMinerado minerado;
            minerado.bloco = bloco;
            copiaVetor(minerado.hash, hash, SHA256_DIGEST_LENGTH);
            return minerado;
        }

        (bloco.nonce)++;
    }
    
}

int main() {
    int contBlocos = 1;
    unsigned char hashAnterior[SHA256_DIGEST_LENGTH] = {0};
    BlocoMinerado minerados[16]; //16*256 = 4096

    for(int i = 0; i < 16; i++) {
        minerados[i] = mineraBloco(contBlocos, hashAnterior);
        copiaVetor(hashAnterior, minerados[i].hash, SHA256_DIGEST_LENGTH);
        contBlocos++;
    }

    for(int i = 0; i < 16; i++) {
        //Imprimindo bloco
        printf("%d\n", minerados[i].bloco.numero);
        printVetor(minerados[i].bloco.data, 184);
        printf("%d\n", minerados[i].bloco.nonce);
        printHash(minerados[i].hash, SHA256_DIGEST_LENGTH);
        printHash(minerados[i].bloco.hashAnterior, SHA256_DIGEST_LENGTH);
    }
    
    return 0;
}