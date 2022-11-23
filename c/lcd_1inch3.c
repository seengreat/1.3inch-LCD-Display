/********************************
 *  Seengreat 1.3 Inch LCD Display demo
 *  Author(s):Andy Li from Seengreat
 * ********************/
 
#include <string.h>
#include <stdlib.h>		
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "lcd_1inch3.h"

void Lcd_Gpio_Init(void)
{
	printf("Init gpio for wiringpi\r\n");
    if(wiringPiSetup() < 0)//use wiringpi Pin number
    { 
        printf("wiringPi lib init failed! \r\n");
    } 
    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_RST, OUTPUT);
    pinMode(PIN_DC, OUTPUT);
    pinMode(PIN_BL, OUTPUT);
    wiringPiSPISetup(0,8000000);
    softPwmCreate(PIN_BL, 0, 100); //black light pwm
    softPwmWrite(PIN_BL, 80);
}

/*******************************************************************************
function:
	Hardware reset
*******************************************************************************/
static void Lcd_Reset(void)
{
	digitalWrite(PIN_CS, 1);
	delay(100);
	digitalWrite(PIN_RST, 0);
	delay(100);
	digitalWrite(PIN_RST, 1);
	delay(100);
}

/*******************************************************************************
function:
		Write data and commands
*******************************************************************************/
static void Spi_write_cmd(u_char data)	 
{	
	digitalWrite(PIN_CS, 0);
	digitalWrite(PIN_DC, 0);
	wiringPiSPIDataRW(0,&data,1);
}

static void Spi_write_data(u_char data) 
{	
	digitalWrite(PIN_CS, 0);
	digitalWrite(PIN_DC, 1);
	wiringPiSPIDataRW(0,&data,1); 
	digitalWrite(PIN_CS,1);
}  

void Spi_write_word(u_int16_t data)
{
	u_char temp = 0;
	digitalWrite(PIN_CS, 0);
	digitalWrite(PIN_DC, 1);
	temp = (data>>8) & 0xff;
	wiringPiSPIDataRW(0,&temp,1);
	temp = data & 0xff;
	wiringPiSPIDataRW(0,&temp,1); 
	digitalWrite(PIN_CS, 1);
}	  


/******************************************************************************
function:	
		Common register initialization
******************************************************************************/
void Lcd_Init(void)
{
	Lcd_Gpio_Init();
	Lcd_Reset();

	Spi_write_cmd(0x11);// sleep out 
	delay(1000);
	
	Spi_write_cmd(0x36); 
	Spi_write_data(0x60);// MY=0,MX=1,MV=1,ML=0,RGB Order
	delay(50);
	Spi_write_cmd(0x3A); 
	Spi_write_data(0x05); //65k-colors
	// FRMCTR1:Frame Rate Control in normal mode
	Spi_write_cmd(0xB2); // PORCTRL(Porch Setting)
	Spi_write_data(0x0C);
	Spi_write_data(0x0C);
	Spi_write_data(0x00);
	Spi_write_data(0x33);
	Spi_write_data(0x33);
        
	// FRMCTR2:Frame Rate Control in idle mode
	Spi_write_cmd(0xB7); // GCTRL:Gate control
	Spi_write_data(0x35);

	Spi_write_cmd(0xBB); // VCOMS:VCOM Setting
	Spi_write_data(0x37);
	
	Spi_write_cmd(0xC0); // LCMCTRL:LCM Control
	Spi_write_data(0x2C);
	
	Spi_write_cmd(0xC2); // VDVVRHEN:VDV and VRH Command Enable
	Spi_write_data(0x01);
	
	Spi_write_cmd(0xC3); // VRHS:VRH Set
	Spi_write_data(0x12);
	
	Spi_write_cmd(0xC4); // VDVS: VDV Set
	Spi_write_data(0x20);
	
	Spi_write_cmd(0xC6); // FRCTRL2:Frame Rate Control in Normal Mode
	Spi_write_data(0x0F); // 60Hz
	
	Spi_write_cmd(0xD0); // PWCTRL1:Power Control 1
	Spi_write_data(0xA4); // default
	Spi_write_data(0xA1); // 
        
	Spi_write_cmd(0xE0); // Positive Voltage Gamma Control
	Spi_write_data(0xD0);
	Spi_write_data(0x04);
	Spi_write_data(0x0D);
	Spi_write_data(0x11);
	Spi_write_data(0x13);
	Spi_write_data(0x2B);
	Spi_write_data(0x3F);
	Spi_write_data(0x54);
	Spi_write_data(0x4C);
	Spi_write_data(0x18);
	Spi_write_data(0x0D);
	Spi_write_data(0x0B);
	Spi_write_data(0x1F);
	Spi_write_data(0x23);
        
	Spi_write_cmd(0xE1); // NVGAMCTRL:Negative Voltage Gamma Control
	Spi_write_data(0xD4);
	Spi_write_data(0x04);
	Spi_write_data(0x0C);
	Spi_write_data(0x11);
	Spi_write_data(0x13);
	Spi_write_data(0x2C);
	Spi_write_data(0x3F);
	Spi_write_data(0x44);
	Spi_write_data(0x51);
	Spi_write_data(0x2F);
	Spi_write_data(0x1F);
	Spi_write_data(0x1F);
	Spi_write_data(0x20);
	Spi_write_data(0x23);
	
	Spi_write_cmd(0x21);
	delay(120);
	Spi_write_cmd(0x29);
	delay(50);
}


//select the srceen area(from point(start_x,start_y) to point(end_x,end_y))
void Set_Window(u_int16_t start_x, u_int16_t start_y, u_int16_t end_x, u_int16_t  end_y)
{ 
	//start_x += 1;
	end_x -= 1;
	//start_y += 2;
	end_y -= 2;
	Spi_write_cmd(0x2a);
	Spi_write_data(start_x >>8);
	Spi_write_data(start_x & 0xff);
	Spi_write_data(end_x >> 8);
	Spi_write_data(end_x & 0xff);

	Spi_write_cmd(0x2b);
	Spi_write_data(start_y >>8);
	Spi_write_data(start_y & 0xff);
	Spi_write_data(end_y >> 8);
	Spi_write_data(end_y & 0xff);

	Spi_write_cmd(0x2C);
}


//set cursor to the point(x, y)
void Set_Cursor(u_int16_t x, u_int16_t y)
{ 
	//x += 1;
	//y += 2;
	Spi_write_cmd(0x2a);
	Spi_write_data(x >> 8);
	Spi_write_data(x);
	Spi_write_data(x >> 8);
	Spi_write_data(x);

	Spi_write_cmd(0x2b);
	Spi_write_data(y >> 8);
	Spi_write_data(y);
	Spi_write_data(y >> 8);
	Spi_write_data(y);

	Spi_write_cmd(0x2C);
}

//refresh the entire screen to color
void Lcd_Clear(u_int16_t color)
{
	u_int16_t i;
	u_int16_t image[LCD_W];
	for(i=0;i<LCD_W;i++)
	{
		image[i] = color>>8 | (color&0xff)<<8;
	}
	u_char *p = (u_char *)(image);
	Set_Window(0, 0, LCD_W, LCD_H);
	digitalWrite(PIN_DC, 1);
	for(i = 0; i < LCD_H; i++)
	{
		wiringPiSPIDataRW(0, (unsigned char *)p, LCD_W*2);
	}
}


//display the image to whole screen 
void Display(u_int16_t *image)
{
	u_int16_t i;
	u_int16_t p[LCD_SIZE];
    memcpy(p,image,LCD_SIZE);
	Set_Window(0, 0, LCD_W, LCD_H);
	digitalWrite(PIN_DC, 1);
	for(i = 0; i < LCD_H; i++)
	{
		wiringPiSPIDataRW(0, (unsigned char *)p+LCD_W*2*i, LCD_W*2);
	}
}

//set the point(x,y) to color
void Draw_Point(u_int16_t x, u_int16_t y, u_int16_t Color)
{
	Set_Cursor(x, y);
	Spi_write_word(Color); 	    
}

