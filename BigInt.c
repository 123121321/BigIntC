#include <stdlib.h>
#include "BigIntC.h"
#include <stdio.h>
#include <string.h>
#define CATCH(x) catch++; printf("catch:%i, %i\n", x, catch);

// debug variable
uint8_t catch = 0;

BigInt hexToBigInt(const char *hex){
    BigInt BigNum;
    uint8_t hexDigits = 0, numDigits = 0;
    const char *run=hex;
    uint8_t uneven = 0, temp=0, i = 0;
    while (*run != '\0'){
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
            BigNum.digits[i] = temp;
            temp = 0;
        }
    }
    BigNum.sign=0;
    return BigNum;
}

BigInt addBigInts(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    sum.numOfDigits = (lhs.numOfDigits > rhs.numOfDigits)
        ? lhs.numOfDigits + 1 : rhs.numOfDigits + 1;
    sum.digits=malloc(sizeof(uint8_t)*sum.numOfDigits);
    switch ( mostDigits(lhs, rhs) ){
        case(0):
            additionCaseLoops(&sum, lhs, rhs, 0);
            return sum;
        case(1):
            additionCaseLoops(&sum, lhs, rhs, 1);
            return sum;
        case(2):
            additionCaseLoops(&sum, lhs, rhs, 2);
            return sum;
        default:
            printf("something went wrong in addBigInts!\n");
            break;
    }
    return sum;
}
BigInt subtractBigInts(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    return sum;
}
/*
BigInt incrementBigInt(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    return sum;
}
BigInt decrementBigInt(const BigInt lhs, const BigInt rhs){
    BigInt sum;
    return sum;
} */

/* HELPER FUNCTIONS ***********************************************************/
// returns which number (1 for lhs, 2 for rhs, 0 for equality)
// has more digits
uint8_t mostDigits(const BigInt lhs, const BigInt rhs){
    return (lhs.numOfDigits == rhs.numOfDigits) ? 0 :
        (lhs.numOfDigits > rhs.numOfDigits) ? 1 : 2;
}
// check whether signs are the same
uint8_t signCheckEquality(const BigInt lhs, const BigInt rhs){
    return (lhs.sign == rhs.sign) ? 1 : 0;
}
// should only be used in conjunction w/above to determine which
// number is negative, i.e.
// 1 0, only need to pass the respective lhs as if the lhs is neg,
// 0 1  the rhs must be pos and vice versa.
uint8_t signCheckOrder(const BigInt lhs){
    return (lhs.sign == 0) ? 2 : 1;
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

void additionCaseLoops(BigInt *sum, const BigInt lhs, const BigInt rhs,
        const uint8_t caseNum){
    uint16_t offset=0, temp=0;
    uint8_t carry=0;
    switch (caseNum){
        case(0):
            for (uint16_t i=lhs.numOfDigits; i > 0; i--){
                temp = lhs.digits[i-1] + rhs.digits[i-1] + carry;
                if (temp > 255){
                    sum->digits[i] = temp - 256;
                    carry = 1;
                } else {
                    sum->digits[i] = temp;
                    carry = 0;
                }
            }
            (carry != 0) ? sum->digits[0] = 1 : 0;
            additionCleanUp(sum, temp);
            break;
        case(1):
            offset = lhs.numOfDigits - rhs.numOfDigits;
            for (uint16_t i=rhs.numOfDigits; i > 0; i--){
                temp = lhs.digits[i-1+offset] + rhs.digits[i-1] + carry;
                if (temp > 255){
                    sum->digits[i+offset] = temp - 256;
                    carry = 1;
                } else {
                    sum->digits[i+offset] = temp;
                    carry = 0;
                }
            }
            for (uint16_t i=offset; i > 0; i--){
                temp = lhs.digits[i-1] + carry;
                if (temp > 255){
                    sum->digits[i+offset] = temp - 256;
                    carry = 1;
                } else {
                    sum->digits[i] = temp;
                    carry = 0;
                }
            }
            (carry != 0) ? sum->digits[0] = 1 : 0;
            additionCleanUp(sum, temp);
            break;
        case(2):
            offset = rhs.numOfDigits - lhs.numOfDigits;
            for (uint16_t i=lhs.numOfDigits; i > 0; i--){
                temp = lhs.digits[i-1] + rhs.digits[i-1+offset] + carry;
                if (temp > 255){
                    sum->digits[i+offset] = temp - 256;
                    carry = 1;
                } else {
                    sum->digits[i+offset] = temp;
                    carry = 0;
                }
            }
            for (uint16_t i=offset; i > 0; i--){
                temp = rhs.digits[i-1] + carry;
                if (temp > 255){
                    sum->digits[i+offset] = temp - 256;
                    carry = 1;
                } else {
                    sum->digits[i] = temp;
                    carry = 0;
                }
            }
            (carry != 0) ? sum->digits[0] = 1 : 0;
            additionCleanUp(sum, temp);
            break;
        default:
            printf("something went wrong in additionCaseLoops!\n");
            break;
    }
}

void additionCleanUp(BigInt *toClean, uint16_t temp){
    if (toClean->digits[0] == 0){
        toClean->numOfDigits--;
        memmove(&(toClean->digits[0]), &(toClean->digits[1]),
                toClean->numOfDigits);
        toClean->digits=realloc(&(toClean->digits[0]), toClean->numOfDigits);
    } else {
        toClean->digits[1] = temp - 256;
    }
}

/* PRINTING FUNCTIONS *********************************************************/
void printBigInt(const BigInt BigNum){
    if (BigNum.sign != 0){
        printf("(-) ");
    }
    for (uint8_t i=0; i<BigNum.numOfDigits; i++){
            printf("%i ", BigNum.digits[i]);
    }
}
void printBigIntHex(const BigInt BigNum){
    // placeholder
}


