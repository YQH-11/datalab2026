/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);//只有两个都是1才行,|只有00是特殊的
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y)& ~(x&y);//要一个0一个1,&只有11是特殊的
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x)
        return !y;//排除x=0
    if(!y)
        return 0;
    return !((x>>31)^(y>>31));//取最高位,int
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int record=0;
    int tool;

    tool=(v>0xFFFF)<<4;
    record=record|tool;
    v=v>>tool;

    tool=(v>0xFF)<<3;
    record=record|tool;
    v=v>>tool;

    tool=(v>0xF)<<2;
    record=record|tool;
    v=v>>tool;

    tool=(v>0x3)<<1;
    record=record|tool;
    v=v>>tool;

    record=record|(v>0x1);

    return record;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int tool_zero,tool_m,tool_n;//先存m,n.再清零，再填
    m=m<<3;
    n=n<<3;
    tool_zero=~((0xFF<<m)|(0xFF<<n));//清零的
    tool_m=(x>>m)&0xFF;
    tool_n=(x>>n)&0xFF;
    x=tool_zero&x;//清零
    x=x|(tool_m<<n);
    x=x|(tool_n<<m);
    return x;
    /*fangfa2
    int tool;
    n = n << 3;
    m = m << 3;
    tool = ((x >> n) ^ (x >> m)) & 0xFF;
    return x ^ (tool << n) ^ (tool << m);*/
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned int res,tool;
    res=0;
    for(int i=32;i;i-=1)
    {
        tool=(v>>(i-1))&1;
        tool=tool<<(32-i);
        res=res|tool;
    }
    return res;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int tool=((1<<31)>>n)<<1;
    x=x>>n;
    x=(~tool)&x;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int rec=0;
    int tool;
    x=~x;

    tool=x>>16;
    rec=rec|((!tool)<<4);
    x=x>>((!(!tool))<<4);

    tool=x>>8;
    rec=rec|((!tool)<<3);
    x=x>>((!(!tool))<<3);

    tool=x>>4;
    rec=rec|((!tool)<<2);
    x=x>>((!(!tool))<<2);

    tool=x>>2;
    rec=rec|((!tool)<<1);
    x=x>>((!(!tool))<<1);

    tool=x>>1;
    rec=rec|(!tool);
    rec = rec + !x;//防止x=-1

    return rec;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned int a=x;
    unsigned int res,e,m;
    if(x<0){
        res=0x80000000;
        a=~a+1;}
    else if (x>0)res=0;
    else return 0;
    
    int i;
    for (i=31;i>0;i=i-1)
    {
        if(a>>i)break;
    }
    e=(i+127)<<23;
    m = a & ~(1 << i);
    if(i>23)
    {
        unsigned int tip=0xFFFFFFFF;
        tip=tip>>(55-i);
        tip=m&tip;
        unsigned int t=1<<(i-24);
        m=m>>(i-23);
        if(tip==t)
        {
            if(m&1)
            {
                m=m+1;                
            }
        }
        else if(tip>t)
        {
            m=m+1;
        }
    }
    else if(i<23)m=m<<(23-i);
    return res+e+m;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned int u;
    u=0x7FFFFFFF&uf;
    if(!u)return uf;

    unsigned int e;
    e=(u>>23);
    if(e==0)
    {
        unsigned int m=(0xFFFFFFFF>>9)&uf;
        m=m<<1;
        uf=(uf&(0xFFFFFFFF<<23))|m;
        return uf;
    }
    if(e==(0xFE))
    {
        if(uf>>31)return 0xFF800000;
        else return  0x7F800000;
    }
    if(e==0xFF)return uf;
    return uf+(1<<23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sig=(uf2 & 0x80000000);
    int e=((uf2 & 0x7FFFFFFF)>>20)-1023;
    if(e<0) return 0;
    if (!e) 
    {
        if (sig) return ~0;  /* -1 */
        else return 1;
    }   
    if(e>30)return 0x80000000;

    unsigned int a=uf2&0x000FFFFF;
    a=(a<<12)|(uf1>>20);

    //unsigned int tool=a&(0xFFFFFFFF>>e);//不需要四舍五入
    a=a>>(32-e);
    /*if (tool>(1<<(31-e)))a=a+1;
    else if(tool>(1<<(31-e)));
    else 
    {
        if(a&1) a=a+1;
    }*/
    a=a|(1<<e);
    if (sig)
        return ~a + 1;
    return a;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x<=-150)return 0;
    else if(x>127)return 0x7F800000;
    else if(x>-127)return (x+127)<<23;
    else if(x<=-127)return 1<<(x+149);
}
