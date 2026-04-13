#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char* convertStrToLongBv(char* str, int* bits);
char* convertLongBvToStr(unsigned char* vec, size_t bits);
void printLongBv(unsigned char* vec, size_t bits);
unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB);
unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB);
unsigned char* sumMod2 (unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB);
void inversion(unsigned char* vec, size_t bits);
void shiftLeft(unsigned char* vec, size_t bits, size_t k);
void shiftRight(unsigned char* vec, size_t bits, size_t k);
void set1(unsigned char* vec, size_t bits, size_t k);
void set0(unsigned char* vec, size_t bits, size_t k);

int main() {
    // & | ^
    //char text1[] = "111";
    //char text2[] = "111";
    //int bitsA = 0;
    //int bitsB = 0;
    //unsigned char* vecA = convertStrToLongBv(text1, &bitsA);
    //unsigned char* vecB = convertStrToLongBv(text2, &bitsB);
    //unsigned char* vec = sumMod2(vecA, bitsA, vecB, bitsB);
    //int bits = bitsA;
    //if (vec) {
    //    char* vec1_str = convertLongBvToStr(vecA, bitsA);
    //    char* vec2_str = convertLongBvToStr(vecB, bitsB);
    //    char* vec_str = convertLongBvToStr(vec, bits);
    //    printf("%s\n", vec1_str);
    //    printf("%s\n", vec2_str);
    //    printf("%s\n", vec_str);
    //    free(vec_str);
    //    free(vec1_str);
    //    free(vec2_str);
    //}
    //else {
    //    printf("Error\n");
    //}
    //free(vec);
    //free(vecA);
    //free(vecB);


    // ~
    //char text[] = "111";
    //int leni = 0;
    //unsigned char* veci = convertStrToLongBv(text, &leni);
    //inversion(veci, leni);
    //char* veci_str = convertLongBvToStr(veci, leni);
    //printf("%s\n", veci_str);
    //free(veci_str);
    //free(veci);


    // <<
    //char text[] = "11111111111111111111111111111111111111111";
    //int bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //shiftLeft(vec, bits, 40);
    //char* vec_str = convertLongBvToStr(vec, bits);
    //printf("%s\n", vec_str);
    //free(vec_str);
    //free(vec);

    // >>
    //char text[] = "00000000000000000";
    //int bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //inversion(vec, bits);
    //shiftRight(vec, bits, 9);
    //char* vec_str = convertLongBvToStr(vec, bits);
    //printf("%s\n", vec_str);
    //free(vec_str);
    //free(vec);

    // char text[] = "1111111111";
    // int bits = 0;
    // unsigned char* vec = convertStrToLongBv(text, &bits);
    // set0(vec, bits, 1);
    // char* vec_str = convertLongBvToStr(vec, bits);
    // printf("%s\n", vec_str);
    // free(vec_str);
    // free(vec);


    return 0;
}


unsigned char* convertStrToLongBv(char* str, int* bits) {
    int bytes = 0, ix = 0;
    unsigned char mask = 1;
    unsigned char* vec = NULL;
    if (str && bits) {
        *bits = strlen(str);
        bytes = ((*bits - 1) / 8) + 1;
        vec = (unsigned char*)calloc(bytes, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < bytes; i++) {
                mask = 1;
                for (int j = 0; j < 8 && (ix < *bits); j++) {
                    if (str[ix] != '0') {
                        vec[i] = vec[i] | mask;
                    }
                    mask = mask << 1;
                    ix++;
                }
            }
        }
    }
    return vec;
}

char* convertLongBvToStr(unsigned char* vec, size_t bits) {
    int ix = 0;
    unsigned char mask = 1;
    char* str = NULL;
    if (vec && bits) {
        str = (char*)calloc(bits + 1, sizeof(char));
        if (str) {
            for (int i = 0; i < bits; i++) {
                mask = 1;
                for (int j = 0; j < 8 && (ix < bits); j++) {
                    if (vec[i] & mask) {
                        str[ix] = '1';
                    }
                    else {
                        str[ix] = '0';
                    }
                    mask = mask << 1;
                    ix++;
                }
            }
            str[ix] = '\0';
        }
    }
    return str;
}


void printLongBv(unsigned char* vec, size_t bits) {
    if (vec && bits) {
        char* vec_str = convertLongBvToStr(vec, bits);
        if (vec_str) {
            printf("%s\n", vec_str);
        }
    }
}

unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    unsigned char* vec = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB) {
        int bytes = ((bitsA - 1) / 8) + 1;
        vec = (char*)calloc(bitsA, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < bytes; i++) {
                vec[i] = vecA[i] & vecB[i];
            }
        }
    }
    return vec;
}

unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    unsigned char* vec = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB) {
        int bytes = ((bitsA - 1) / 8) + 1;
        vec = (char*)calloc(bitsA, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < bytes; i++) {
                vec[i] = vecA[i] | vecB[i];
            }
        }
    }
    return vec;
}

unsigned char* sumMod2 (unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    unsigned char* vec = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB) {
        int bytes = ((bitsA - 1) / 8) + 1;
        vec = (char*)calloc(bitsA, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < bytes; i++) {
                vec[i] = vecA[i] ^ vecB[i];
            }
        }
    }
    return vec;
}

void inversion(unsigned char* vec, size_t bits) {
    if (vec && bits) {
        int bytes = ((bits - 1) / 8) + 1;
        for (int i = 0; i < bytes; i++) {
            vec[i] = ~vec[i];
        }
        int tail = bytes * 8 - bits;
        unsigned char mask = 0;
        mask = -1;
        mask = mask >> tail;
        vec[bytes - 1] = vec[bytes - 1] & mask;
    }
}

void shiftLeft(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k <= bits) {
        int bytes = ((bits - 1) / 8) + 1;
        size_t j = k / 8;
        size_t i = 0;
        size_t i_i = 0;
        if (j) {
            while (j < bytes) {
                vec[i] = vec[j];
                i++;
                j++;
            }
            i_i = i - 1;
            while (i < bytes) {
                vec[i] = 0;
                i++;
            }
        }
        size_t bit = k % 8;
        unsigned char ib = 0;
        unsigned char mask = -1;
        int ix = 0;
        for (ix = 0; ix < i_i; ix++) {
            mask = -1;
            vec[ix] = vec[ix] >> bit;
            mask = mask >> (8 - bit);
            ib = vec[ix + 1] & mask;
            ib = ib << (8 - bit);
            vec[ix] = vec[ix] | ib;
        }
        vec[ix] = vec[ix] >> bit;
        int tail = bytes * 8 - bits;
        mask = -1;
        mask = mask >> tail;
        vec[bytes - 1] = vec[bytes - 1] & mask;
    }
}

void shiftRight(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k <= bits) {
        int bytes = ((bits - 1) / 8) + 1;
        size_t j = k / 8;
        size_t i = 0;
        size_t i_i = 0;
        if (j) {
            while (j < bytes) {
                vec[j] = vec[i];
                i++;
                j++;
            }
            i_i = i - 1;
            i = 0;
            while (i < k / 8) {
                vec[i] = 0;
                i++;
            }
        }
        size_t bit = k % 8;
        unsigned char ibx = 0;
        unsigned char iby = 0;
        unsigned char mask = -1;
        int ix = 0;
        for (ix = i_i; ix < bytes; ix++) {
            mask = -1;
            mask = mask << (8 - bit);
            iby = vec[ix] & mask;
            iby = iby >> (8 - bit);
            vec[ix] = vec[ix] << bit;
            vec[ix] = vec[ix] | ibx;
            ibx = iby;
        }
        int tail = bytes * 8 - bits;
        mask = -1;
        mask = mask >> tail;
        vec[bytes - 1] = vec[bytes - 1] & mask;
    }
}

void set1(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k <= bits) {
        unsigned char mask = 1;
        size_t byte = k / 8;
        size_t bit = k % 8;
        mask = mask << bit;
        vec[byte] = vec[byte] | mask;
    }
}

void set0(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k <= bits) {
        unsigned char mask = 1;
        size_t byte = k / 8;
        size_t bit = k % 8;
        mask = mask << bit;
        vec[byte] = vec[byte] & ~mask;
    }
}