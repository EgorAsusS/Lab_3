#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char* convert_str_to_long_bv(char* str, int* len);
char* convert_long_bv_to_str(unsigned char* vec, size_t len);
unsigned char* log_mul(unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2);
unsigned char* log_add(unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2);
unsigned char* xor (unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2);
void invert_bv(unsigned char* vec, size_t len);
void shift_k_left(unsigned char* vec, size_t len, size_t k);
void shift_k_right(unsigned char* vec, size_t len, size_t k);
void set_k(unsigned char* vec, size_t len, size_t k);
void reset_k(unsigned char* vec, size_t len, size_t k);

int main() {
    // & | ^
    //char text1[] = "111";
    //char text2[] = "111";
    //int len1 = 0;
    //int len2 = 0;
    //unsigned char* vec1 = convert_str_to_long_bv(text1, &len1);
    //unsigned char* vec2 = convert_str_to_long_bv(text2, &len2);
    //unsigned char* vec = xor(vec1, len1, vec2, len2);
    //int len = len1;
    //if (vec) {
    //    char* vec1_str = convert_long_bv_to_str(vec1, len1);
    //    char* vec2_str = convert_long_bv_to_str(vec2, len2);
    //    char* vec_str = convert_long_bv_to_str(vec, len);
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
    //free(vec1);
    //free(vec2);


    // ~
    //char text[] = "111";
    //int leni = 0;
    //unsigned char* veci = convert_str_to_long_bv(text, &leni);
    //invert_bv(veci, leni);
    //char* veci_str = convert_long_bv_to_str(veci, leni);
    //printf("%s\n", veci_str);
    //free(veci_str);
    //free(veci);


    // <<
    //char text[] = "11111111111111111111111111111111111111111";
    //int len = 0;
    //unsigned char* vec = convert_str_to_long_bv(text, &len);
    //shift_k_left(vec, len, 40);
    //char* vec_str = convert_long_bv_to_str(vec, len);
    //printf("%s\n", vec_str);
    //free(vec_str);
    //free(vec);

    // >>
    //char text[] = "000000000";
    //int len = 0;
    //unsigned char* vec = convert_str_to_long_bv(text, &len);
    //invert_bv(vec, len);
    //shift_k_left(vec, len, 1);
    //char* vec_str = convert_long_bv_to_str(vec, len);
    //printf("%s\n", vec_str);
    //free(vec_str);
    //free(vec);

    char text[] = "1111111111";
    int len = 0;
    unsigned char* vec = convert_str_to_long_bv(text, &len);
    reset_k(vec, len, 0);
    char* vec_str = convert_long_bv_to_str(vec, len);
    printf("%s\n", vec_str);
    free(vec_str);
    free(vec);


    return 0;
}


unsigned char* convert_str_to_long_bv(char* str, int* len) {
    int cells = 0, ix = 0;
    unsigned char mask = 1;
    unsigned char* vec = NULL;
    if (str && len) {
        *len = strlen(str);
        cells = ((*len - 1) / 8) + 1;
        vec = (unsigned char*)calloc(cells, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < cells; i++) {
                mask = 1;
                for (int j = 0; j < 8 && (ix < *len); j++) {
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

char* convert_long_bv_to_str(unsigned char* vec, size_t len) {
    int ix = 0;
    unsigned char mask = 1;
    char* str = NULL;
    if (vec && len) {
       str = (char*)calloc(len + 1, sizeof(char));
        if (str) {
            for (int i = 0; i < len; i++) {
                mask = 1;
                for (int j = 0; j < 8 && (ix < len); j++) {
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

unsigned char* log_mul(unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2) {
    unsigned char* vec = NULL;
    if (vec1 && vec2 && len1 && len2 && len1 == len2) {
        int cells = ((len1 - 1) / 8) + 1;
        vec = (char*)calloc(len1, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < cells; i++) {
                vec[i] = vec1[i] & vec2[i];
            }
        }
    }
    return vec;
}

unsigned char* log_add(unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2) {
    unsigned char* vec = NULL;
    if (vec1 && vec2 && len1 && len2 && len1 == len2) {
        int cells = ((len1 - 1) / 8) + 1;
        vec = (char*)calloc(len1, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < cells; i++) {
                vec[i] = vec1[i] | vec2[i];
            }
        }
    }
    return vec;
}

unsigned char* xor(unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2) {
    unsigned char* vec = NULL;
    if (vec1 && vec2 && len1 && len2 && len1 == len2) {
        int cells = ((len1 - 1) / 8) + 1;
        vec = (char*)calloc(len1, sizeof(unsigned char));
        if (vec) {
            for (int i = 0; i < cells; i++) {
                vec[i] = vec1[i] ^ vec2[i];
            }
        }
    }
    return vec;
}

void invert_bv(unsigned char* vec, size_t len) {
    if (vec && len) {
        int cells = ((len - 1) / 8) + 1;
        for (int i = 0; i < cells; i++) {
            vec[i] = ~vec[i];
        }
        int tail = cells * 8 - len;
        unsigned char mask = 0;
        mask = -1;
        mask = mask >> tail;
        vec[cells - 1] = vec[cells - 1] & mask;
    }
}

void shift_k_left(unsigned char* vec, size_t len, size_t k) {
    if (vec && len && k <= len) {
        int cells = ((len - 1) / 8) + 1;
        size_t j = k / 8;
        size_t i = 0;
        if (j) {
            while (j < cells) {
                vec[i] = vec[j];
                i++;
                j++;
            }
            while (i < cells) {
                vec[i] = 0;
                i++;
            }
        }
        size_t bit = k % 8;
        unsigned char ib = 0;
        unsigned char mask = -1;
        int ix = 0;
        for (ix = 0; ix < cells - 1; ix++) {
            mask = -1;
            vec[ix] = vec[ix] >> bit;
            mask = mask >> (8 - bit);
            ib = vec[ix + 1] & mask;
            ib = ib << (8 - bit);
            vec[ix] = vec[ix] | ib;
        }
        vec[ix] = vec[ix] >> bit;
        int tail = cells * 8 - len;
        mask = -1;
        mask = mask >> tail;
        vec[cells - 1] = vec[cells - 1] & mask;
    }
}

void shift_k_right(unsigned char* vec, size_t len, size_t k) {
    if (vec && len && k <= len) {
        int cells = ((len - 1) / 8) + 1;
        size_t j = k / 8;
        size_t i = 0;
        if (j) {
            while (j < cells) {
                vec[j] = vec[i];
                i++;
                j++;
            }
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
        for (ix = 0; ix < cells; ix++) {
            mask = -1;
            mask = mask << (8 - bit);
            iby = vec[ix] & mask;
            iby = iby >> (8 - bit);
            vec[ix] = vec[ix] << bit;
            vec[ix] = vec[ix] | ibx;
            ibx = iby;
        }
        int tail = cells * 8 - len;
        mask = -1;
        mask = mask >> tail;
        vec[cells - 1] = vec[cells - 1] & mask;
    }
}

void set_k(unsigned char* vec, size_t len, size_t k) {
    if (vec && len && k <= len) {
        unsigned char mask = 1;
        size_t byte = k / 8;
        size_t bit = k % 8;
        mask = mask << bit;
        vec[byte] = vec[byte] | mask;
    }
}

void reset_k(unsigned char* vec, size_t len, size_t k) {
    if (vec && len && k <= len) {
        unsigned char mask = 1;
        size_t byte = k / 8;
        size_t bit = k % 8;
        mask = mask << bit;
        vec[byte] = vec[byte] & ~mask;
    }
}