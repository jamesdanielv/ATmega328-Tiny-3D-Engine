#ifndef TYPE_H
#define TYPE_H

// ----------------------------------------------
// defines
// ----------------------------------------------
#define PRES             16384
#define PSHIFT           14
#define PROUNDBIT        (1 << (PSHIFT-1))

// ----------------------------------------------
// typedef
// ----------------------------------------------
typedef struct {
  int16_t x, y, z;
} Vector3;

typedef struct {
  long x, y, z;
} Vector3i;

// fixed point identity matrix
typedef struct {
  int16_t m[4][4] = {
      {PRES,    0,    0,    0},
      {   0, PRES,    0,    0},
      {   0,    0, PRES,    0},
      {   0,    0,    0, PRES}
  };
} Matrix4;

// ----------------------------------------------
// functions
// ----------------------------------------------
// fixed point multiplication
static long pMultiply(int32_t x, int32_t y) {
 
//return ( (x * y) + PROUNDBIT) >> PSHIFT;
bool NEG_SIGN;

if (x<0 & y>0){NEG_SIGN=true;}//if both negative it is posative, so we only want neg if x is negative.
if (x>0 & y<0){NEG_SIGN=true;}//if both negative it is posative
//x=x& 0b011111111111111111111111111111111;//we do abs //no check on last bit anyways..
//y=y& 0b011111111111111111111111111111111;//we do abs //so no need to do abs......
uint32_t total=0;                          //we just dont check sign bit in algorithum.
uint32_t accum=y;
if (y>x){uint32_t accum=x,x=y;}//we move lower number to x and larger to accum 
if (x<1<<15){//if x fits in 16 bits we do 16bit numbers...
uint16_t temp_x;//we make unsigned for now..
}
else{//if x needs 32 bits we store all 32 bits.
uint32_t temp_x;//we make unsigned for now..  
}
if (x&0b00000000000000000000000000000001){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000000000010){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000000000100){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000000001000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000000010000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000000100000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000001000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000010000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000000100000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000001000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000010000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000000100000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000001000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000010000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000000100000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000001000000000000000){total=total+accum;};accum=accum+accum;//we double
if( x> 1<<15){//if x is 32bit number we process 32 bits path.
if (x&0b00000000000000010000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000000100000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000001000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000010000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000000100000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000001000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000010000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000000100000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000001000000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000010000000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00000100000000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00001000000000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00010000000000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b00100000000000000000000000000000){total=total+accum;};accum=accum+accum;//we double
if (x&0b01000000000000000000000000000000){total=total+accum;};accum=accum+accum;//we double
//if (x&0b10000000000000000000000000000000){total=total+accum;};//int32_t turne to unit32_t.. no chance upper bit set other than sign.
}
  //we send out 16 bits but it could als do long... just the answer currently is 16bit
  //decided to allow longs again if data shift is lesser than 14bits (equivlent to dividing by 15 bits in a singed number)
#if PSHIFT > (1<<14)-1
if (NEG_SIGN){ return -int32_t(( total + PROUNDBIT) >> PSHIFT);}else{return int32_t(( total + PROUNDBIT) >> PSHIFT);}
#else
 if (NEG_SIGN){ return -int32_t(( total + PROUNDBIT) >> PSHIFT);}else{return int32_t(( total + PROUNDBIT) >> PSHIFT);}
#endif 
}

int16_t fast_8unit_multi(uint8_t x, uint8_t y){//useful for hidden triangle and some other functions
  uint16_t accumulator=0;
  uint16_t solver=x;
 if (y&0b00000001){ accumulator+=solver;};solver=solver+solver;
 if (y&0b00000010){ accumulator+=solver;};solver=solver+solver;
 if (y&0b00000100){ accumulator+=solver;};solver=solver+solver;
 if (y&0b00001000){ accumulator+=solver;};solver=solver+solver;
 if (y&0b00010000){ accumulator+=solver;};solver=solver+solver;
 if (y&0b00100000){ accumulator+=solver;};solver=solver+solver;
 if (y&0b01000000){ accumulator+=solver;};solver=solver+solver;
 if (y&0b10000000){ accumulator+=solver;};
 return accumulator;
}

#endif // TYPE_H
