#ifndef BIGINTC_H
#define BIGINTC_H

#include <stdint.h>
// base 256
typedef struct BigInt {
    uint16_t numOfDigits;
    uint8_t *digits;
    uint8_t sign; // should only ever take on the values 0 and 1
} BigInt;

BigInt hexToBigInt(const char *hex);
BigInt addBigInts(const BigInt lhs, const BigInt rhs);
BigInt subtractBigInts(const BigInt lhs, const BigInt rhs);
// BigInt incrementBigInt(const BigInt lhs, const BigInt rhs);
// BigInt decrementBigInt(const BigInt lhs, const BigInt rhs);

uint8_t mostDigits(const BigInt lhs, const BigInt rhs);
uint8_t signCheckEquality(const BigInt lhs, const BigInt rhs);
uint8_t signCheckOrder(const BigInt lhs);
uint8_t hexToInt(const char hexDigit);
void additionCleanUp(BigInt *toClean, uint16_t temp);
void additionCaseLoops(BigInt *sum, const BigInt lhs, const BigInt rhs,
        const uint8_t caseNum);
void printBigInt(const BigInt BigNum);
void printBigIntHex(const BigInt BigNum);

#endif
