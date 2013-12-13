//
//  main.c
//  Assignment_1
//
//  Created by David Bulnes on 12/12/13.
//  Copyright (c) 2013 David Bulnes. All rights reserved.
//

/*
 Assignment:
 You may be familiar with the following C function from stdlib.h:
 
 int atoi(const char * str);
 
 This function parses a C string, interprets its content as an integral number, then returns this number as an 
 int value. Provide another implementation of this function (using a different name) along with a small main() 
 function that demonstrates its use.  Your solution should be a single C source file that may be compiled 
 using a standard C compiler.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int stringToInt (const char * numberString)
{
    //Tracks the power of ten we are multiplying each digit by. Initialized to one less than the length
    //of the string input to account for 1s place of an integer.
    //See below negative number check and power of ten math in the while loop.
    int powerOfTen;
    int convertedInt = 0; //The int that will be returned.
    int digitFromString; //The int that holds each initial ASCII conversion for a char converted to a single digit int.
    
    int negativeNumber; //Negative number flag.
    //Handle negative integers. If found, raise the negativeNumber flag and increment the pointer to the next character.
    //If negative, also decrement the power of ten exponent by 2 instead of 1, since there is one less numeric character in the string
    //than the length of the whole string.
    if ((negativeNumber = *numberString == '-')){
        //negativeNumber = 1;
        powerOfTen = (int) strlen(numberString) - 2;
        numberString++;
    } else {
        //negativeNumber = 0;
        powerOfTen = (int) strlen(numberString) - 1;
    }
        
    //Iterate over the string until we hit the NULL character at the end of the string.
    while (*numberString != '\0') {
        //Get the character digit and subtract '0', as the integer characters in the ASCII table are sequential.
        //Therefore, if we subtract the '0' character, then the difference will be the integer value of the character at hand.
        digitFromString = *numberString - '0';
        
        /* 
         * Sanity check- if there is a non-numeric character that we run into, return our converted number thus far,
         * ignoring the non-numeric character. We need to divide by 10^(-powerOfTen+1) to get this partially 
         * complete integer conversion.
         * The standard atoi function behaves in this way. Example: atoi("124a52") returns integer 124.
         */
        if (digitFromString < 0 || digitFromString > 9)
            return convertedInt * pow(10, -(double)(powerOfTen + 1));
        
        /*
         * Mathematically, we are performing (realValueTerm = digitFromString * (10^powerOfTen))
         * If math.h was not included, and we don't have the pow() function, we could do something clever
         * like continually bitshift left by 3, then bitshift left again by 1, thus multiplying by 10, and add our digit.
         * Formally: (convertedInt = (convertedInt<<3) + (convertedInt<<1) + digitFromString).
         * It was chosen not to do the conversion this way as it is not as readable or immediately transparent
         * in terms of the logic underlying the code.
         */
        int realValueTerm = digitFromString * pow(10, (double)powerOfTen);
        convertedInt += realValueTerm; //Add the new term to the converted integer.
        powerOfTen--; //Decrement the power of ten since we go from highest order of magnitude to lowest.
        numberString++; //Increment the char pointer.
    }
    
    return negativeNumber ? -convertedInt : convertedInt;
}

int main(int argc, const char * argv[])
{
    const char * intString = "-3906";
    int stringInt = stringToInt(intString);
    printf("%d\n", stringInt);
    return 0;
}

