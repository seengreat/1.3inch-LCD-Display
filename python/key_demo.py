# Seengreat 1.3 Inch LCD Display demo
# Author(s):Andy Li from Seengreat

import lcd_1inch3
from PIL import ImageDraw, Image, ImageFont
import wiringpi as wpi
import time

# define the key button pin in wiringpi number
K1_PIN    = 0
K2_PIN    = 1
K3_PIN    = 3
K4_PIN    = 4
R_PIN     = 28
L_PIN     = 29
UP_PIN    = 23
LEFT_PIN  = 21
DOWN_PIN  = 25
RIGHT_PIN = 24
CENTER_PIN= 22

def Key_Init():
    wpi.wiringPiSetup()
    wpi.pinMode(K1_PIN, wpi.INPUT)  # K1 pin
    wpi.pullUpDnControl(K1_PIN, wpi.PUD_UP)
    wpi.pinMode(K2_PIN, wpi.INPUT)  # K2 pin
    wpi.pullUpDnControl(K2_PIN, wpi.PUD_UP)
    wpi.pinMode(K3_PIN, wpi.INPUT)  # K3 pin
    wpi.pullUpDnControl(K3_PIN, wpi.PUD_UP)
    wpi.pinMode(K4_PIN, wpi.INPUT)  # K4 pin
    wpi.pullUpDnControl(K4_PIN, wpi.PUD_UP)
    wpi.pinMode(L_PIN, wpi.INPUT)  # K3 pin
    wpi.pullUpDnControl(L_PIN, wpi.PUD_UP)
    wpi.pinMode(R_PIN, wpi.INPUT)  # K3 pin
    wpi.pullUpDnControl(R_PIN, wpi.PUD_UP)
    wpi.pinMode(UP_PIN, wpi.INPUT)  # UP pin
    wpi.pullUpDnControl(UP_PIN, wpi.PUD_UP)
    wpi.pinMode(LEFT_PIN, wpi.INPUT)  # LEFT pin
    wpi.pullUpDnControl(LEFT_PIN, wpi.PUD_UP)
    wpi.pinMode(RIGHT_PIN, wpi.INPUT)  # RIGHT pin
    wpi.pullUpDnControl(RIGHT_PIN, wpi.PUD_UP)
    wpi.pinMode(DOWN_PIN, wpi.INPUT)  # DOWN pin
    wpi.pullUpDnControl(DOWN_PIN, wpi.PUD_UP)
    wpi.pinMode(CENTER_PIN, wpi.INPUT)  # CENTER pin
    wpi.pullUpDnControl(CENTER_PIN, wpi.PUD_UP)

if __name__ == '__main__':
    lcd = lcd_1inch3.LCD_1Inch3()
    Key_Init()
    lcd.lcd_init()
    lcd.clear()
    img0 = Image.new("RGB", (lcd.w, lcd.h), "WHITE")
    lcd_draw = ImageDraw.Draw(img0)
    k1_flag = 0
    k2_flag = 0
    k3_flag = 0
    k4_flag = 0
    l_flag = 0
    r_flag = 0
    up_flag = 0
    left_flag = 0
    right_flag = 0
    down_flag = 0
    center_flag = 0
    lcd_draw.rectangle([(170,60),(210,80)],outline=255, fill = 0) # K1
    lcd_draw.rectangle([(150,100),(170,140)],outline=255, fill = 0) # K2
    lcd_draw.rectangle([(210,100),(230,140)],outline=255, fill = 0) # K3
    lcd_draw.rectangle([(170,160),(210,180)],outline=255, fill = 0) # K4
    lcd_draw.rectangle([(30,10),(70,30)],outline=255, fill = 0) # L
    lcd_draw.rectangle([(170,10),(210,30)],outline=255, fill = 0) # R
    lcd_draw.rectangle([(40,70),(80,90)],outline=255, fill = 0) # up
    lcd_draw.rectangle([(10,100),(30,140)],outline=255, fill = 0) # left
    lcd_draw.rectangle([(90,100),(110,140)],outline=255, fill = 0) # right 
    lcd_draw.rectangle([(40,150),(80,170)],outline=255, fill = 0) # down  
    lcd_draw.rectangle([(40,100),(80,140)],outline=255, fill = 0) # center
    lcd.img_show(img0.rotate(180)) 
    while True:
        if wpi.digitalRead(K1_PIN) == 0 and k1_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(K1_PIN) == 0: # make sure the button has been pressed
                k1_flag = 1
                lcd_draw.rectangle([(170,60),(210,80)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K1 Press")
        elif wpi.digitalRead(K1_PIN) == 1 and k1_flag == 1: # key has been released
            k1_flag = 0
            lcd_draw.rectangle([(170,60),(210,80)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 
                
        if wpi.digitalRead(K2_PIN) == 0 and k2_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(K2_PIN) == 0: # make sure the button has been pressed
                k2_flag = 1
                lcd_draw.rectangle([(150,100),(170,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K2 Press")
        elif wpi.digitalRead(K2_PIN) == 1 and k2_flag == 1: # key has been released
            k2_flag = 0
            lcd_draw.rectangle([(150,100),(170,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if wpi.digitalRead(K3_PIN) == 0 and k3_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(K3_PIN) == 0: # make sure the button has been pressed
                k3_flag = 1
                lcd_draw.rectangle([(210,100),(230,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K3 Press")
        elif wpi.digitalRead(K3_PIN) == 1 and k3_flag == 1: # key has been released
            k3_flag = 0
            lcd_draw.rectangle([(210,100),(230,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if wpi.digitalRead(K4_PIN) == 0 and k4_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(K4_PIN) == 0: # make sure the button has been pressed
                k4_flag = 1
                lcd_draw.rectangle([(170,160),(210,180)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K4 Press")
        elif wpi.digitalRead(K4_PIN) == 1 and k4_flag == 1: # key has been released
            k4_flag = 0
            lcd_draw.rectangle([(170,160),(210,180)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))

        if wpi.digitalRead(L_PIN) == 0 and l_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(L_PIN) == 0: # make sure the button has been pressed
                l_flag = 1
                lcd_draw.rectangle([(30,10),(70,30)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("L Press")
        elif wpi.digitalRead(L_PIN) == 1 and l_flag == 1: # key has been released
            l_flag = 0
            lcd_draw.rectangle([(30,10),(70,30)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))

        if wpi.digitalRead(R_PIN) == 0 and r_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(R_PIN) == 0: # make sure the button has been pressed
                r_flag = 1
                lcd_draw.rectangle([(170,10),(210,30)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("R Press")
        elif wpi.digitalRead(R_PIN) == 1 and r_flag == 1: # key has been released
            r_flag = 0
            lcd_draw.rectangle([(170,10),(210,30)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))
            
        if wpi.digitalRead(UP_PIN) == 0 and up_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(UP_PIN) == 0: # make sure the button has been pressed
                up_flag = 1
                lcd_draw.rectangle([(40,70),(80,90)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("UP Press")
        elif wpi.digitalRead(UP_PIN) == 1 and up_flag == 1: # key has been released
            up_flag = 0
            lcd_draw.rectangle([(40,70),(80,90)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if wpi.digitalRead(LEFT_PIN) == 0 and left_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(LEFT_PIN) == 0: # make sure the button has been pressed
                left_flag = 1
                lcd_draw.rectangle([(10,100),(30,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("LEFT Press")
        elif wpi.digitalRead(LEFT_PIN) == 1 and left_flag == 1: # key has been released
            left_flag = 0
            lcd_draw.rectangle([(10,100),(30,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if wpi.digitalRead(RIGHT_PIN) == 0 and right_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(RIGHT_PIN) == 0: # make sure the button has been pressed
                right_flag = 1
                lcd_draw.rectangle([(90,100),(110,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("RIGHT Press")
        elif wpi.digitalRead(RIGHT_PIN) == 1 and right_flag == 1: # key has been released
            right_flag = 0
            lcd_draw.rectangle([(90,100),(110,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if wpi.digitalRead(DOWN_PIN) == 0 and down_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(DOWN_PIN) == 0: # make sure the button has been pressed
                down_flag = 1
                lcd_draw.rectangle([(40,150),(80,170)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("DOWN Press")
        elif wpi.digitalRead(DOWN_PIN) == 1 and down_flag == 1: # key has been released
            down_flag = 0
            lcd_draw.rectangle([(40,150),(80,170)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if wpi.digitalRead(CENTER_PIN) == 0 and center_flag == 0:
            time.sleep(0.01)
            if wpi.digitalRead(CENTER_PIN) == 0: # make sure the button has been pressed
                center_flag = 1
                lcd_draw.rectangle([(40,100),(80,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("CENTER Press")
        elif wpi.digitalRead(CENTER_PIN) == 1 and center_flag == 1: # key has been released
            center_flag = 0
            lcd_draw.rectangle([(40,100),(80,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))        

                