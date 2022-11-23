
#ifndef __FONTS_H
#define __FONTS_H
   
#include <stdint.h>

//ASCII
typedef struct tFont
{    
  const uint8_t *table;
  uint16_t size;
  uint16_t w; //width
  uint16_t h; //height
  
}FONT;

typedef struct
{
unsigned char context[2];
const char pix[72];  
}CH_CN24;

//CN
typedef struct tCN_Font
{    
  const CH_CN24 *table;
  uint16_t size;
  uint16_t w; //width
  uint16_t h; //height
  
}CN_FONT;

extern FONT Font24;
extern CN_FONT CN_Font24;

#endif 
 
