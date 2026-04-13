#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char* convertStrToLongBv(char* str, size_t* bits);
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

size_t main() {
    // & | ^
    char text1[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    //char text1[] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    //char text2[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    char text2[] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    size_t bitsA = 0;
    size_t bitsB = 0;
    unsigned char* vecA = convertStrToLongBv(text1, &bitsA);
    unsigned char* vecB = convertStrToLongBv(text2, &bitsB);
    unsigned char* vec = sumMod2(vecA, bitsA, vecB, bitsB);
    size_t bits = bitsA;
    printLongBv(vecA, bitsA);
    printLongBv(vecB, bitsB);
    printLongBv(vec, bits);
    free(vec);
    free(vecA);
    free(vecB);
    vec = NULL;
    vecA = NULL;
    vecB = NULL;


    // ~
    //char text[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //printLongBv(vec, bits);
    //inversion(vec, bits);
    //printLongBv(vec, bits);
    //free(vec);
    //vec = NULL;


    // <<
    //char text[] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    //char text[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //inversion(vec, bits);
    //printLongBv(vec, bits);
    //shiftLeft(vec, bits, 97);
    //printLongBv(vec, bits);
    //free(vec);
    //vec = NULL;

    // >>
    //char text[] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    //char text[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //inversion(vec, bits);
    //printLongBv(vec, bits);
    //shiftRight(vec, bits, 97);
    //printLongBv(vec, bits);
    //free(vec);
    //vec = NULL;

    //
    //char text[] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //inversion(vec, bits);
    //printLongBv(vec, bits);
    //for (int i = 0; i < 100; i++) {
    //    shiftLeft(vec, bits, 1);
    //    printLongBv(vec, bits);
    //}
    //free(vec);
    //vec = NULL;

    //
    //char text[] = "0000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //shiftRight(vec, bits, 50);
    //shiftLeft(vec, bits, 50);
    //printLongBv(vec, bits);
    //free(vec);
    //vec = NULL;

    //
    //char text[] = "0000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //inversion(vec, bits);
    //shiftLeft(vec, bits, 50);
    //shiftRight(vec, bits, 50);
    //printLongBv(vec, bits);
    //free(vec);
    //vec = NULL;



    // set1
    //char text[] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //set1(vec, bits, 50);
    //printLongBv(vec, bits);
    //free(vec);
    //vec = NULL;

    //set0
    //char text[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    //size_t bits = 0;
    //unsigned char* vec = convertStrToLongBv(text, &bits);
    //set0(vec, bits, 50);
    //printLongBv(vec, bits);
    //free(vec);
    //vec = NULL;

    return 0;
}


unsigned char* convertStrToLongBv(char* str, size_t* bits) {
    size_t bytes = 0, ix = 0;
    unsigned char mask = 1;
    unsigned char* vec = NULL;
    if (str && bits) {
        *bits = strlen(str);
        bytes = ((*bits - 1) / 8) + 1;
        vec = (unsigned char*)calloc(bytes, sizeof(unsigned char));
        if (vec) {
            for (size_t i = 0; i < bytes; i++) {
                mask = 1;
                for (size_t j = 0; j < 8 && (ix < *bits); j++) {
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
    size_t bytes = 0, ix = 0;
    unsigned char mask = 1;
    char* str = NULL;
    if (vec && bits) {
        str = (char*)calloc(bits + 1, sizeof(char));
        bytes = ((bits - 1) / 8) + 1;
        if (str) {
            for (size_t i = 0; i < bytes; i++) {
                mask = 1;
                for (size_t j = 0; j < 8 && (ix < bits); j++) {
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
    size_t bytes = 0, ix = 0;
    unsigned char mask = 1;
    if (vec && bits) {
        bytes = ((bits - 1) / 8) + 1;
        for (size_t i = 0; i < bytes; i++) {
            mask = 1;
            for (size_t j = 0; j < 8 && (ix < bits); j++) {
                if (vec[i] & mask) {
                    printf("1");
                }
                else {
                    printf("0");
                }
                mask = mask << 1;
                ix++;
            }
        }
        printf("\n");
    }
}

unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    unsigned char* vec = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB) {
        size_t bytes = ((bitsA - 1) / 8) + 1;
        vec = (unsigned char*)calloc(bytes, sizeof(unsigned char));
        if (vec) {
            for (size_t i = 0; i < bytes; i++) {
                vec[i] = vecA[i] & vecB[i];
            }
        }
    }
    return vec;
}

unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    unsigned char* vec = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB) {
        size_t bytes = ((bitsA - 1) / 8) + 1;
        vec = (unsigned char*)calloc(bytes, sizeof(unsigned char));
        if (vec) {
            for (size_t i = 0; i < bytes; i++) {
                vec[i] = vecA[i] | vecB[i];
            }
        }
    }
    return vec;
}

unsigned char* sumMod2(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    unsigned char* vec = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB) {
        size_t bytes = ((bitsA - 1) / 8) + 1;
        vec = (unsigned char*)calloc(bytes, sizeof(unsigned char));
        if (vec) {
            for (size_t i = 0; i < bytes; i++) {
                vec[i] = vecA[i] ^ vecB[i];
            }
        }
    }
    return vec;
}

void inversion(unsigned char* vec, size_t bits) {
    if (vec && bits) {
        size_t bytes = ((bits - 1) / 8) + 1;
        for (size_t i = 0; i < bytes; i++) {
            vec[i] = ~vec[i];
        }
        size_t tail = bytes * 8 - bits;
        unsigned char mask = -1;
        mask = mask >> tail;
        vec[bytes - 1] = vec[bytes - 1] & mask;
    }
}

void shiftLeft(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k <= bits) {
        size_t bytes = ((bits - 1) / 8) + 1;
        size_t j = k / 8;
        size_t i = 0;
        size_t iy = bytes - 1;
        if (j) {
            while (j < bytes) {
                vec[i] = vec[j];
                i++;
                j++;
            }
            iy = i - 1;
            while (i < bytes) {
                vec[i] = 0;
                i++;
            }
        }
        size_t bit = k % 8;
        size_t _bit = 8 - bit;
        unsigned char ib = 0;
        unsigned char mask = -1;
        size_t ix = 0;
        if (bit) {
            for (ix = 0; ix < iy; ix++) {
                mask = -1;
                vec[ix] = vec[ix] >> bit;
                mask = mask >> _bit;
                ib = vec[ix + 1] & mask;
                ib = ib << _bit;
                vec[ix] = vec[ix] | ib;
            }
            vec[ix] = vec[ix] >> bit;
        }
        size_t tail = bytes * 8 - bits;
        mask = -1;
        mask = mask >> tail;
        vec[bytes - 1] = vec[bytes - 1] & mask;
    }
}

void shiftRight(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k <= bits) {
        size_t bytes = ((bits - 1) / 8) + 1;
        size_t ix = k / 8;
        size_t j = bytes - 1;
        size_t i = j - ix;
        if (j) {
            while (i > 0) {
                vec[j] = vec[i];
                i--;
                j--;
            }
            vec[j] = vec[i];
            i = 0;
            while (i < ix) {
                vec[i] = 0;
                i++;
            }
        }
        size_t bit = k % 8;
        size_t _bit = 8 - bit;
        unsigned char ibx = 0;
        unsigned char iby = 0;
        unsigned char mask = -1;
        if (bit) {
            for (; ix < bytes; ix++) {
                mask = -1;
                mask = mask << _bit;
                iby = vec[ix] & mask;
                iby = iby >> _bit;
                vec[ix] = vec[ix] << bit;
                vec[ix] = vec[ix] | ibx;
                ibx = iby;
            }
        }
        size_t tail = bytes * 8 - bits;
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