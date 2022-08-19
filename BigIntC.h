#ifndef BIGINTC_H
#define BIGINTC_H

#include <stdint.h>
// base 256
typedef struct BigInt {
    uint16_t numOfDigits;
    uint8_t *digits;
    uint8_t sign;
} BigInt;

BigInt hexToBigInt(const char *hex);
BigInt AddBigInts(const BigInt lhs, const BigInt rhs);
BigInt SubtractBigInts(const BigInt lhs, const BigInt rhs);
BigInt incrementBigInt(const BigInt lhs, const BigInt rhs);
BigInt decrementBigInt(const BigInt lhs, const BigInt rhs);
void printBigInt(const BigInt BigNum);
void printBigIntInDecimal(const BigInt BigNum);
uint8_t hexToInt(const char hexDigit);

#endif
