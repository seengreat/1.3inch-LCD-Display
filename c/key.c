/********************************
 *  Seengreat 1.3 Inch LCD Display demo
 *  Author(s):Andy Li from Seengreat
 * ********************/
 
#include <string.h>
#include <stdlib.h>		
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "lcd_gui.h"
#include "lcd_1inch3.h"
#include "key.h"

/*******************
#define K1_PIN    = 0
#define K2_PIN    = 3
#define K3_PIN    = 1
#define UP_PIN    = 23
#define LEFT_PIN  = 21
#define DOWN_PIN  = 25
#define RIGHT_PIN = 24
#define CENTER_PIN= 22
**********/
	
void Key_Init(void)
{
    if(wiringPiSetup() < 0)//use wiringpi Pin number
    { 
        printf("wiringPi lib init failed! \r\n");
    }
    
    printf("Key Init\r\n");
    pinMode(K1_PIN, INPUT);
    pullUpDnControl(K1_PIN, PUD_UP);
    pinMode(K2_PIN, INPUT);
    pullUpDnControl(K2_PIN, PUD_UP);
    pinMode(K3_PIN, INPUT);
    pullUpDnControl(K3_PIN, PUD_UP);
    pinMode(K4_PIN, INPUT);
    pullUpDnControl(K4_PIN, PUD_UP);
    pinMode(L_PIN, INPUT);
    pullUpDnControl(L_PIN, PUD_UP);
    pinMode(R_PIN, INPUT);
    pullUpDnControl(R_PIN, PUD_UP);
    pinMode(UP_PIN, INPUT);
    pullUpDnControl(UP_PIN, PUD_UP);
    pinMode(LEFT_PIN, INPUT);
    pullUpDnControl(LEFT_PIN, PUD_UP);
    pinMode(DOWN_PIN, INPUT);
    pullUpDnControl(DOWN_PIN, PUD_UP);
    pinMode(RIGHT_PIN, INPUT);
    pullUpDnControl(RIGHT_PIN, PUD_UP);
    pinMode(CENTER_PIN, INPUT);
    pullUpDnControl(CENTER_PIN, PUD_UP);
}

void Key_Task(void)
{
	Gui_Clear(WHITE);
	Gui_draw_rectangle(170, 60, 210, 80, BLACK, 1, FULL); //K1
	Gui_draw_rectangle(150, 100, 170, 140, BLACK, 1, FULL); //K2
	Gui_draw_rectangle(210, 100, 230, 140, BLACK, 1, FULL);//K3
	Gui_draw_rectangle(170, 160, 210, 180, BLACK, 1, FULL);//K4
	Gui_draw_rectangle(30, 10, 70, 30, BLACK, 1, FULL);//L
	Gui_draw_rectangle(170, 10, 210, 30, BLACK, 1, FULL);//R
	Gui_draw_rectangle(40, 70, 80, 90, BLACK, 1, FULL); //UP
	Gui_draw_rectangle(10, 100, 30, 140, BLACK, 1, FULL); //LEFT
	Gui_draw_rectangle(90, 100, 110, 140, BLACK, 1, FULL);//RIGHT
	Gui_draw_rectangle(40, 150, 80, 170, BLACK, 1, FULL); //DOWN
	Gui_draw_rectangle(40, 100, 80, 140, BLACK, 1, FULL);// CENTER
	Display(Image.img);
	int k1_flag = 0;
	int k2_flag = 0;
	int k3_flag = 0;
	int k4_flag = 0;
	int l_flag = 0;
	int r_flag = 0;
	int center_flag = 0;
	int up_flag = 0;
	int left_flag = 0;
	int right_flag = 0;
	int down_flag = 0;
	printf("Key Task\r\n");
	for(;;)
	{
	    //K1 key
	    if(digitalRead(K1_PIN) == LOW && k1_flag == 0)
	    {
	        delay(10);
		if(digitalRead(K1_PIN) == LOW) // make sure the button has been pressed
		{
		     k1_flag = 1;
		     Gui_draw_rectangle(170, 60, 210, 80, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K1 Press\r\n");
		}
	    }
	    else if(digitalRead(K1_PIN) == HIGH && k1_flag == 1) // key has been released
	    {
		k1_flag = 0;
		Gui_draw_rectangle(170, 60, 210, 80, BLACK, 1, FULL);
		Display(Image.img);
	    }
            //K2 key
	    if(digitalRead(K2_PIN) == LOW && k2_flag == 0)
	    {
	        delay(10);
		if(digitalRead(K2_PIN) == LOW) // make sure the button has been pressed
		{
		     k2_flag = 1;
		     Gui_draw_rectangle(150, 100, 170, 140, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K2 Press\r\n");
		}
	    }
	    else if(digitalRead(K2_PIN) == HIGH && k2_flag == 1) // key has been released
	    {
		k2_flag = 0;
		Gui_draw_rectangle(150, 100, 170, 140, BLACK, 1, FULL);
		Display(Image.img);
	    }
	    //K3 key
	    if(digitalRead(K3_PIN) == LOW && k3_flag == 0)
	    {
		delay(10);
		if(digitalRead(K3_PIN) == LOW) // make sure the button has been pressed
		{
		     k3_flag = 1;
		     Gui_draw_rectangle(210, 100, 230, 140, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K3 Press\r\n");
		}
	    }
	    else if(digitalRead(K3_PIN) == HIGH && k3_flag == 1) // key has been released
	    {
		k3_flag = 0;
		Gui_draw_rectangle(210, 100, 230, 140, BLACK, 1, FULL);
		Display(Image.img);
	    }
	    //K4 key
	    if(digitalRead(K4_PIN) == LOW && k4_flag == 0)
	    {
		delay(10);
		if(digitalRead(K4_PIN) == LOW) // make sure the button has been pressed
		{
		     k4_flag = 1;
		     Gui_draw_rectangle(170, 160, 210, 180, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K3 Press\r\n");
		}
	   }
	   else if(digitalRead(K4_PIN) == HIGH && k4_flag == 1) // key has been released
	   {
		k4_flag = 0;
		Gui_draw_rectangle(170, 160, 210, 180, BLACK, 1, FULL);
		Display(Image.img);
	   }
	   //L key
	  if(digitalRead(L_PIN) == LOW && l_flag == 0)
	  {
		delay(10);
		if(digitalRead(L_PIN) == LOW) // make sure the button has been pressed
		{
		     l_flag = 1;
		     Gui_draw_rectangle(30, 10, 70, 30, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("L Press\r\n");
		}
	  }
	 else if(digitalRead(L_PIN) == HIGH && l_flag == 1) // key has been released
	 {
	     l_flag = 0;
	     Gui_draw_rectangle(30, 10, 70, 30, BLACK, 1, FULL);
	     Display(Image.img);
	 }
	 //R key
	 if(digitalRead(R_PIN) == LOW && r_flag == 0)
	 {
	     delay(10);
	     if(digitalRead(R_PIN) == LOW) // make sure the button has been pressed
	     {
		 r_flag = 1;
		 Gui_draw_rectangle(170, 10, 210, 30, GREEN, 1, FULL);
		 Display(Image.img);
		 printf("R Press\r\n");
	     }
        }
	else if(digitalRead(R_PIN) == HIGH && r_flag == 1) // key has been released
	{
	    r_flag = 0;
	    Gui_draw_rectangle(170, 10, 210, 30, BLACK, 1, FULL);
	    Display(Image.img);
	}
	//UP key
	if(digitalRead(UP_PIN) == LOW && up_flag == 0)
	{
	    delay(10);
	    if(digitalRead(UP_PIN) == LOW) // make sure the button has been pressed
	    {
		up_flag = 1;
		Gui_draw_rectangle(40, 70, 80, 90, GREEN, 1, FULL);
		Display(Image.img);
		printf("UP Press\r\n");
	    }
	}
	else if(digitalRead(UP_PIN) == HIGH && up_flag == 1) // key has been released
	{
	    up_flag = 0;
	    Gui_draw_rectangle(40, 70, 80, 90, BLACK, 1, FULL);
	    Display(Image.img);
	}

	//LEFT key
	if(digitalRead(LEFT_PIN) == LOW && left_flag == 0)
	{
	    delay(10);
	    if(digitalRead(LEFT_PIN) == LOW) // make sure the button has been pressed
	    {
		 left_flag = 1;
		 Gui_draw_rectangle(10, 100, 30, 140, GREEN, 1, FULL);
		 Display(Image.img);
		 printf("LEFT Press\r\n");
	    }
	}
	else if(digitalRead(LEFT_PIN) == HIGH && left_flag == 1) // key has been released
	{
	    left_flag = 0;
	    Gui_draw_rectangle(10, 100, 30, 140, BLACK, 1, FULL);
	    Display(Image.img);
	}
	    
	//RIGHT key
	if(digitalRead(RIGHT_PIN) == LOW && right_flag == 0)
	{
	    delay(10);
	    if(digitalRead(RIGHT_PIN) == LOW) // make sure the button has been pressed
	    {
		 right_flag = 1;
		 Gui_draw_rectangle(90, 100, 110, 140, GREEN, 1, FULL);
		 Display(Image.img);
		 printf("RIGHT Press\r\n");
	    }
	}
	else if(digitalRead(RIGHT_PIN) == HIGH && right_flag == 1) // key has been released
	{
	    right_flag = 0;
	    Gui_draw_rectangle(90, 100, 110, 140, BLACK, 1, FULL);
	    Display(Image.img);
	}

	//DOWN key
	if(digitalRead(DOWN_PIN) == LOW && down_flag == 0)
	{
	    delay(10);
	    if(digitalRead(DOWN_PIN) == LOW) // make sure the button has been pressed
	    {
		 down_flag = 1;
		 Gui_draw_rectangle(40, 150, 80, 170, GREEN, 1, FULL);
		 Display(Image.img);
		 printf("DOWN Press\r\n");
	    }
	}
	else if(digitalRead(DOWN_PIN) == HIGH && down_flag == 1) // key has been released
	{
	    down_flag = 0;
	    Gui_draw_rectangle(40, 150, 80, 170, BLACK, 1, FULL);
	    Display(Image.img);
	}
	//CENTER key
	if(digitalRead(CENTER_PIN) == LOW && center_flag == 0)
	{
	    delay(10);
	    if(digitalRead(CENTER_PIN) == LOW) // make sure the button has been pressed
	    {
		 center_flag = 1;
		 Gui_draw_rectangle(40, 100, 80, 140, GREEN, 1, FULL);
		 Display(Image.img);
		 printf("Center Press\r\n");
	    }
	}
	else if(digitalRead(CENTER_PIN) == HIGH && center_flag == 1) // key has been released
	{
	    center_flag = 0;
	    Gui_draw_rectangle(40, 100, 80, 140, BLACK, 1, FULL);
	    Display(Image.img);
	}

    } 		
}
