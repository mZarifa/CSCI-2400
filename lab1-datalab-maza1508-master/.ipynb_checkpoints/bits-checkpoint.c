/* 
 * CS:APP Data Lab 
 * 
 * <Matthew Zarifa
 *  maza1508>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
         
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */         
int bitNor(int x, int y)
{
  return (~x & ~y); //return the opposite of x and y bitwise compared. We use NOT to flip, and then the & to bitwise compare. 
         //This finds the bits that are not present in either number and sets them to 1 in the result.
}


/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) 
{
    return !(((x << 16) >> 16) ^ x); //return the negation of the following...shift the bits of input value x by 16 places to the left. Take that
                                     // set of bits, shift it to the right 16 bits. Use "exclusive or" to compare the results of the two bianaries
                                     //to see if they are opposite of each other. Return 1 if that is true. 
}


/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void)
{
/*
what we want:  0100 1001 0010 0100 1001 0010 0100 1001
 *   Step 1:   0000 0000 0000 0000 0000 0000 0100 1001  0x49
 *   Step 2:   0000 0000 0000 0000 1001 0010 0100 1001  Shift << 9, use "|" to bring the 1's.  
 *   Step 3:   0100 1001 0010 0100 1001 0010 0100 1001  Shift << 18 (we want to keep our first 18 binary), use "|" to 'add' previous x bit value.
*/
    int x = 0x49; //set x to 0x49 (73 in decimal). Every 3rd bit is now 1 for the first 9 bits. 
    x = x | (x << 9); //set x to the result of x compared with x shifted by 9 using bitwise or (copy the 1's babyyyyy) 
    x = x | (x << 18); //set x to the result of x compared with x shifted by 18 using bitwise or (copy the 1's AGAIN BABYYYYY)
    return x;
}


/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x)
{
    int mask = 0x55; // that is 1010101 in binary, or 85. (x86???)
    mask |= (mask << 8); //set the mask to the mask shifted 8 using bitwise or.
    mask |= (mask << 16);//set the mask to the mask shifted by 16 using bitwise or.
    return !!(x & mask); //output the bool result of the number and the bit value of 'mask' being compared using bitwise and. 
}


/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) //(Int is signed right? So always arithmatic shift?)
{
    return ((x << 31) >> 31); //shift x by 31 bits to the left (keep only last sig bit), then shift right by 31 to copy that bit to all. 
    //shifts the LSB to MSB
    //exploits the arithmatic shift
}


/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y)
{
    return y | !(x^y); //true if y is true OR if x and y are same value
}


/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit)
{
    int mask1 = ~0 << highbit; //masks bits above highbit (shifting left) to not 0
    int mask2 = ~(~0 << lowbit); // masks bits below lowbit (shifting left) to not not 0.
    int mask3 = ~(1 << highbit); //masks all but highest bit (shifting left)
    //combine masks to get 1's above and below.
    mask1 = mask1 & mask3; //bitwise comparison. Set mask1 to bitwise mask 1 and 3. 
    return ~(mask1 | mask2); //return mask 1 or mask 2, but opposite. 
}


/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x)
{
    int y = 3; //set y to 3.
    int z = 0; //set z to 0.
    x = x + x + x; //set x to x*3.
    z = x >> 31; //set z to x shifted 31 bits to the left. This is done to find the leading bit, use bias to correct a negative number being right shifted.
    //x + ((1 << k) -1) >> k is the ceilling x/2^k [used for negative, leading bit is 1]. x >> k results in floor 2^k [positive, leading bit is 0].
    
    z = y & z; //set z to the bitwise compairson of y and z (when comparing all the bits, if both bits in the same position are 1, bring it down, else the bit result is 0). 
    //1 << 2-1. z will turn into 0 if the bias is 0. 
    x = z + x; //set x to z + x. 
    x = x >> 2; //set x to x shifted 2 bits to the right  (that is dividing by 4). 
    return x;
    //note: When I try to initilize z like so: int z = x >> 31; , it refuses to compile, saying 'z' is undeclared. So I have to initilize it as 0 first. Not sure why. Please LMK.
    
    /*
    Bias is z and 3.
    if z is 1 then you have to bias to round up.
    if z is 0 you have no bias to round down.
    Then you bitwise compare 3 and z, t
    */
}


/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x)
{
    int xMul2 = x << 1; //set xMul2 to x shifted to the left by 1 bit.
    int xMul3 = xMul2 + x; //set xMul3 to xMul2 plus x.
    int overflowMasker = ((xMul2 ^ x) | (xMul3 ^ x)) >> 31;
    int TMax = ~(1 << 31); //set Tmax to the opposite of 1 shifted 31 to the left
    int negCheck = x >> 31;
    return (~overflowMasker & xMul3) | (overflowMasker & (TMax ^ (negCheck))); 
}


/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x)
{ 
    //use XOR to return 1 if the two input bits are different
    x = x ^ (x >> 16); //set x to XOR of x shifted 16 bits to the right 
    x = x ^ (x >> 8); //set x to XOR of x shifted 8 bits to the right
    x = x ^ (x >> 4); //set x to XOR of x shifted 4 bits to the right
    x = x ^ (x >> 2); //set x to XOR of x shifted 2 bits to the right
    x = x ^ (x >> 1); //set x to XOR of x shifted 1 bit to the right
    return x & 1; //return the compairson of x bitwise and 1 (lets see if the first binary is 1)
}


/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x)
{
    int result = (!!(x >> 16)) << 4;
    result = result + ((!!(x >> (result + 8))) << 3);
    result = result + ((!!(x >> (result + 4))) << 2);
    result = result + ((!!(x >> (result + 2))) << 1);
    result = result + (!!(x >> (result + 1)));
    return result;
    /*
    The use of the double negation is to get a boolean result, and then add it to itself to "count" the number of times we can get something to be base 2.
    If its true (yea we can take it down another 8 or 4 or 2) then we add 1 to the result, else we're gonna add 0. 
    */
}


/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
    int div4 = x >> 2; //take the int, shift it by 2 bits to the right (diving it by 4)
    int rem = x & 0x3;  //take the remainder using bitwise and. 0x3 is 3 in decimal, and 011 in binary. This brings only remainder down. 
    int div4Mul3 = (div4 << 1) + div4; //shift the bits to the left by 1, add the value to itself. 
    int neg = x >> 31; //ensure x is not negative by shifting everything 31 to the right
    int remMul3 = (rem << 1) + rem; //take the previous remainder, shift it to the left by 1, then add the previous remainder.
    int carry = (remMul3 + (neg & 0x3)) >> 2; //take the previous remMul3, add the int that to (neg and 0011 compared using bitwise and). Shift all of that over 2.
    return div4Mul3 + carry; //return both those things added
    
    /* EXAMPLE TIME: LETS USE 8. Binary code: 1000
    *   1. 0010 = 2
    *   2. 8 bitwise and 3
           1000
         & 0011
          =0000 = 0.
    *   3. shift 0010 to the left 1, makes it 0100 = 4. Add div4 = 6.
    *   4. still 6.
    *   5. stil 0.
    *   6. 
        0110
      & 0011
      = 0010 (4). Shift to the right by 2 = 0.
    *   7. (6 + 0) = 6. Amazing. I hate this problem so much why are you like this.
    */
}



/*
 * Extra credit
 */
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
