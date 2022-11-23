#ifndef __LCD_1INCH3_H
#define __LCD_1INCH3_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LCD_W   240 //LCD width
#define LCD_H   240 //LCD height

#define PIN_CS   10   
#define PIN_RST  2   
#define PIN_DC   6   
#define PIN_BL   5   

#define LCD_SIZE   (LCD_W*LCD_H*2)                  

void Lcd_Gpio_Init(void);
void Lcd_Init(void); 
void Lcd_Clear(u_int16_t Color);
void Display(u_int16_t *image);
void Draw_Point(u_int16_t x, u_int16_t y, u_int16_t Color);

void Spi_write_word(u_int16_t da);
void Set_Cursor(u_int16_t x, u_int16_t y);
void Set_Window(u_int16_t start_x, u_int16_t start_y, u_int16_t end_x, u_int16_t  end_y);


#endif
