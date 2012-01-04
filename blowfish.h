#define MAXKEYBYTS 56 /* 448 bits*/
#define big_endian 1

short opensubkeyfile(void);
unsigned long F(unsigned long x);
void blowfish_encipher(unsigned long *xl, unsigned long *xr);
void blowfish_decipher(unsigned long *xl, unsigned long *xr);
