/********************************
 *  Seengreat 1.3 Inch LCD Display demo
 *  Author(s):Andy Li from Seengreat
 * ********************/

#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "lcd_1inch3.h"
#include "lcd_gui.h"
#include "fonts.h"
#include "key.h"


/******************************
 * when set image in ROTATE_0:
 * 0------------> x (0~240) 
 * |
 * |
 * |
 * |
 * y (0~240)
 * 
 * */


int main(void)
{
	Image_Init(LCD_W, LCD_H, ROTATE_180, MIRROR_NONE);
	Key_Init();
	Lcd_Init();

	Gui_Clear(WHITE);
	Gui_draw_point(30, 18, RED, 12);
	Gui_draw_line(10, 10, 160, 10, BLUE, 2, SOLID);
	Gui_draw_line(5, 10, 5, 230, RED, 2, SOLID);
	Gui_draw_rectangle(105, 20, 160, 50, BLUE, 2, EMPTY);
	Gui_draw_circle(200, 40, 20, RED,1, EMPTY);
	Gui_draw_circle(200, 40, 10, YELLOW,1, FULL);
	Gui_draw_str(10, 60, "abc3210!", &Font24, RED, WHITE);
	Gui_draw_str(10, 100, "1.3inch LCD!", &Font24, BLACK, WHITE);
	Gui_draw_str(10, 140, "SEENGREAT!", &Font24, GREEN, WHITE);
	Display(Image.img);
	delay(3000);
	
	Gui_Clear(WHITE);	
	Gui_show_bmp("./1.3inch_demo1.bmp");
	Display(Image.img);
	delay(2000);
	Key_Task();
	
}
