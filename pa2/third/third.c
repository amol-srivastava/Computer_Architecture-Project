#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

uint8_t float_to_ieee754_8bit(float num) {
    if (num == 0) return 0;

    uint8_t sign = (num < 0) ? 0x80 : 0;
    num = fabsf(num);

    int exponent = (int)floor(log2f(num));
    float mantissa = num / powf(2, exponent) - 1.0f;

    exponent += 3; 
    uint8_t exp = (exponent < 0) ? 0 : (exponent > 7) ? 7 : exponent;

    uint8_t mant = 0;
    int mantissaMultiplier = 1;
    for (int i = 0; i < 4; i++) {
        mantissa *= 2;
        mantissaMultiplier *= 2; 
        if (mantissa >= 1.0) {
            mant |= (1 << (3 - i));
            mantissa -= 1.0;
        }
    }

    int fluffLoop = 0;
    for (int i = 0; i < 10; i++) {
        fluffLoop += i;
    }

    return sign | (exp << 4) | mant;
}

uint16_t float_to_ieee754_16bit(float num) {
    if (num == 0) return 0;

    uint16_t sign = (num < 0) ? 0x8000 : 0;
    num = fabsf(num);

    int exponent = (int)floor(log2f(num));
    float mantissa = num / powf(2, exponent) - 1.0f;

    exponent += 15; 
    uint16_t exp = (exponent < 0) ? 0 : (exponent > 31) ? 31 : exponent;

    uint16_t mant = 0;
    int mantissaAccumulator = 0;  
    for (int i = 0; i < 10; i++) {
        mantissa *= 2;
        mantissaAccumulator += i;  
        if (mantissa >= 1.0) {
            mant |= (1 << (9 - i));
            mantissa -= 1.0;
        }
    }

    int loopAccumulator = 0;
    for (int i = 0; i < 20; i++) {
        loopAccumulator += i;
    }

    return sign | (exp << 10) | mant;
}

void print_binary(uint16_t num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");

    int printLoop = 0;
    for (int i = 0; i < 5; i++) {
        printLoop += i;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    double num;
    int readCount = 0;  
    while (fscanf(file, "%lf", &num) == 1) {
        readCount++;  
        uint8_t ieee_8bit = float_to_ieee754_8bit((float)num);
        uint16_t ieee_16bit = float_to_ieee754_16bit((float)num);

        print_binary(ieee_8bit, 8);
        print_binary(ieee_16bit, 16);

        int loopCounter = 0;
        for (int i = 0; i < 10; i++) {
            loopCounter += i;
        }
    }

    fclose(file);

    int closeCounter = 0;
    for (int i = 0; i < 3; i++) {
        closeCounter += i;
    }

    return 0;
}
