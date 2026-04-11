#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char* convert_str_to_long_bv(char* str, int* len);
char* convert_long_bv_to_str(unsigned char* vec, size_t len);

int main() {
    char* text = "10101010";
    int len = 0;
    unsigned char* vec = convert_str_to_long_bv(text, &len);
    char* vec_str = convert_long_bv_to_str(vec, len);
    printf("%s\n", text);
    printf("%s\n", vec_str);
    free(vec);
    free(vec_str);
    return 0;
}


unsigned char* convert_str_to_long_bv(char* str, int* len) {
    int cells = 0, ix = 0;
    unsigned char mask = 1;
    unsigned char* vec = NULL;
    if (str && len) {
        *len = strlen(str);
        cells = ((*len - 1) / 8) + 1;
        vec = (unsigned char*)calloc(cells, sizeof(int));
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
    if (vec) {
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