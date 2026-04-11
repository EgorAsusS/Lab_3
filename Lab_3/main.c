#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char* convert_str_to_long_bv(char* str, int* len);
char* convert_long_bv_to_str(unsigned char* vec, size_t len);
unsigned char* log_mul(unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2);
unsigned char* log_add(unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2);
unsigned char* xor (unsigned char* vec1, size_t len1, unsigned char* vec2, size_t len2);
unsigned char* invert_bv(unsigned char* veci, size_t leni);
unsigned char* shift_left(unsigned char* veci, size_t leni);

int main() {
    //char* text1 = "111";
    //char* text2 = "111";
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
    char* text = "111";
    int leni = 0;
    unsigned char* veci = convert_str_to_long_bv(text, &leni);
    unsigned char* veco = invert_bv(veci, leni);
    int leno = leni;
    if (veco) {
        char* veci_str = convert_long_bv_to_str(veci, leni);
        char* veco_str = convert_long_bv_to_str(veco, leno);
        printf("%s\n", veci_str);
        printf("%s\n", veco_str);
        free(veci_str);
        free(veco_str);
    }
    else {
        printf("Error\n");
    }
    free(veci);
    free(veco);
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

unsigned char* invert_bv(unsigned char* veci, size_t leni) {
    unsigned char* veco = NULL;
    if (veci && leni) {
        int cells = ((leni - 1) / 8) + 1;
        veco = (unsigned char*)calloc(leni, sizeof(unsigned char));
        if (veco) {
            for (int i = 0; i < cells; i++) {
                veco[i] = ~veci[i];
            }
            int tail = cells * 8 - leni;
            unsigned char mask = 0;
            if (tail) {
                mask = -1;
                mask = mask >> tail;
                veco[cells - 1] = veco[cells - 1] & mask;
            }
        }
    }
    return veco;
}

//unsigned char* shift_k_left(unsigned char* veci, size_t leni, size_t k) {
//    unsigned char* veco = NULL;
//    if (veci && leni) {
//        int cells = ((leni - 1) / 8) + 1;
//        veco = (unsigned char*)calloc(leni, sizeof(unsigned char));
//        if (veco) {
//            size_t j = k / 8;
//            size_t i = 0;
//            size_t bit = k & 8;
//            while (j < cells) {
//                veco[i] = veci[j];
//            }
//            while (i < cells) {
//
//            }
//
//            //for (int i = 0; i < cells; i++) {
//            //    veco[i] = ~veci[i];
//            //}
//            //int tail = cells * 8 - leni;
//            //unsigned char mask = 0;
//            //if (tail) {
//            //    mask = -1;
//            //    mask = mask >> tail;
//            //    veco[cells - 1] = veco[cells - 1] & mask;
//            //}
//        }
//    }
//    return veco;
//}