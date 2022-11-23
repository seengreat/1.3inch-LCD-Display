import lcd_1inch3
from PIL import ImageDraw, Image, ImageFont
import time

if __name__ == '__main__':
    lcd = lcd_1inch3.LCD_1Inch3()
    lcd.lcd_init()
    lcd.clear()
    img0 = Image.new("RGB", (lcd.w, lcd.h), "WHITE")
    lcd_draw = ImageDraw.Draw(img0)
    Font = ImageFont.truetype("MiSans-Light.ttf",32) # read chinese font file
    #text= u"深桂科技"
    img1 = Image.open('1.3inch_demo1.jpg') # open jpg file
    while True:
        lcd_draw.line([(5, 5),(50, 60)], fill = "RED",width = 2)
    
        lcd_draw.rectangle([(70,20),(110,60)],fill = "WHITE",outline="BLUE")
        lcd_draw.rectangle([(120,20),(160,60)],fill = "BLUE")
        lcd_draw.rectangle([(100,90),(120,110)],fill = "GREEN")    
        lcd_draw.arc((170,20,230,80), 0, 360, fill =(0,255,255))
        lcd_draw.ellipse((20,70,80,110), fill = (255,255,0))
    
        lcd_draw.text((10, 130), 'SEENGREAT', fill = "BLUE",font=Font)
        lcd_draw.text((10, 170), 'ABcd321', fill = "RED",font=Font)
    
        #lcd_draw.text((2, 105),text, fill = "BLUE",font=Font)
    
        lcd.img_show(img0.rotate(180))
      
        time.sleep(3)
        lcd.img_show(img1.rotate(180)) # show image
        time.sleep(3)