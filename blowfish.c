#ifdef little_endian
#include <doc.h>
#include <graphics.h>
#include <io.h>
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef little_endian
#include <alloc.h>
#endif

#include <ctype.h>

#ifdef little_endian
#include <dir.h>
#include <bios.h>
#endif

#ifdef big_endian
#include <Types.h>
#endif

#include "blowfish.h"

#define N 16
#define noerr 0
#define DATAERROR -1
#define KEYBYTES 8
#define subkeyfilename "blowfish.data"

unsigned long P[N+2];
unsigned long S[4][256];
FILE* subkeyfile;

short opensubkeyfile(void){
  short error = noerr;
  if((subkeyfile = fopen(subkeyfilename,"rb")) == NULL){
    error = DATAERROR;
  }
  return error;
}
unsigned long F(unsigned long x){
  unsigned short a;
  unsigned short b;
  unsigned short c;
  unsigned short d;
  unsigned short y;

  d = x & 0x00FF;
  x >>= 8;
  c = x & 0x00FF;
  x >>= 8;
  b = x & 0x00FF;
  x >>= 8;
  a = x & 0x00FF;
  y = S[0][a] + S[1][b];
  y = y ^ S[2][c];
  y = y + S[3][d];
  return y;
}

void blowfish_encipher(unsigned long *xl, unsigned long *xr){
  unsigned long Xl;
  unsigned long Xr;
  unsigned long temp;
  short i;
  Xl = *xl;
  Xr = *xr;
  
  for(i = 0; i < N; ++i){
    Xl = Xl ^ P[i];
    Xr = F(Xl) ^ Xr;
    
    temp = Xl;
    Xl = Xr;
  }
  temp = Xl;
  Xl = Xr;
  Xr = temp;
  
  Xr = Xr ^ P[N];
  Xl = Xl ^ P[N+1];
  
  *xl = Xl;
  *xr = Xr;
}
void blowfish_decipher(unsigned long *xl, unsigned long *xr){
  unsigned long Xl;
  unsigned long Xr;
  unsigned long temp;
  short i;
  
  Xl = *xl;
  Xr = *xr;
  
  for (i = N + 1; i > 1; --i){
    Xl = Xl ^ P[i];
    Xr = F(Xl) ^ Xr;
    
    temp = Xl;
    Xl = Xr;
    Xr = temp;
  }
  temp = Xl;
  Xl = Xr;
  Xr = Xr ^ P[1];
  Xl = Xl ^ P[0];
  *xl = Xl;
  *xr = Xr;
}

int main(int argc, char* arch[]){
  short x = 1;
  printf("%d \n", F(1745646234));
  return 0;
}
