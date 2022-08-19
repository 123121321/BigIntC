#include <stdlib.h>
#include "BigIntC.h"
#include <stdio.h>
#define CATCH(x) catch++; printf("catch:%i, %i\n", x, catch);

// debug variable
int catch = 0;

BigInt hexToBigInt(const char *hex){
    BigInt BigNum;
    uint8_t hexDigits = 0, numDigits = 0;
    const char *run=hex;
    uint8_t uneven = 0, temp=0, i = 0;
    while (*run != '\0'){
        // printf("hex[%i]:%c\n", hexDigits, hex[hexDigits]);
        hexDigits++;
        run=&hex[hexDigits];
    } 
    if (hexDigits % 2 == 0){
        numDigits = ( hexDigits >> 1 );
    } else {
        numDigits = 1 + ( hexDigits >> 1);
        uneven = 1;
    }
    BigNum.numOfDigits=numDigits;
    BigNum.digits=malloc(sizeof(uint8_t)*numDigits);
    // printf("num of base 256 digits in 0x%s : %i\n", &hex[0], numDigits);
    if (uneven == 1){
        BigNum.digits[0]=hexToInt(hex[i]);
        for (i=1; i<numDigits; i++){
            temp += hexToInt(hex[i*2 - 1]) << 4;
            temp += hexToInt(hex[i*2]);
            BigNum.digits[i] = temp;
            temp = 0;
        }
    } else {
        for (i=0; i<numDigits; i++){
            temp += hexToInt(hex[i*2]) << 4;
            temp += hexToInt(hex[i*2 + 1]);
            printf("index:%i\n", i);
            BigNum.digits[i] = temp;
            temp = 0;
        }
    }
    BigNum.sign=0;
    return BigNum;
}

BigInt AddBigInts(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    return sum;
}
BigInt SubtractBigInts(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    return sum;
}
BigInt incrementBigInt(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    return sum;
}
BigInt decrementBigInt(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    return sum;
}

void printBigInt(const BigInt BigNum){
    for (uint8_t i=0; i<BigNum.numOfDigits; i++){
            printf("%i ", BigNum.digits[i]);
        }
}

uint8_t hexToInt(const char hexDigit){
    if ('9' - hexDigit >= 0 && hexDigit - '0' >= 0){
        return hexDigit - '0';
    } else if ('f' - hexDigit >= 0 && hexDigit >= 'a'){
        return hexDigit + 10 - 'a';
    } else if ('F' - hexDigit >= 0 && hexDigit >= 'A'){
        return hexDigit + 10 - 'A';
    }
    printf("something went wrong in hexToInt! char:%i\n", hexDigit);
    return -1;
}
