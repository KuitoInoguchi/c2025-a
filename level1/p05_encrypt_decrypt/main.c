#include <stdio.h>
#include <string.h>

void encrypt(const char* str, const size_t len, char* enc) {
    for (int i = 0; i < len; i++) {
        enc[i] = str[i] + 'A';
    }
    enc[len] = '\0';
}

void decrypt(const char* enc_str, const size_t len, char* dec) {
    for (int i = 0; i < len; i++) {
        dec[i] = enc_str[i] - 'A';
    }
    dec[len] = '\0';
}

int main0() {
    const int SIZE = 1000;
    char str[SIZE];
    char enc_str[SIZE];
    char dec_str[SIZE];

    fgets(str, sizeof(str), stdin);
    size_t len = strlen(str);

    encrypt(str, len, enc_str);
    decrypt(enc_str, len, dec_str);

    printf("The encrypted string: %s\n", enc_str);
    printf("The decrypted (original) string: %s", dec_str);

    return 0;
}