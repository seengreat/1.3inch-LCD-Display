# Seengreat 1.3 Inch LCD Display demo
# Author(s):Andy Li from Seengreat

import os
import sys
import spidev
import time
import wiringpi as wpi
import numpy as np
"""the following pin definiting use wiringpi"""
RST_PIN  = 2
DC_PIN   = 6
BL_PIN   = 5
class LCD_1Inch3():
    def __init__(self):
        # gpio init
        wpi.wiringPiSetup()
        wpi.pinMode(DC_PIN, wpi.OUTPUT)  # D/C pin
        wpi.pinMode(RST_PIN, wpi.OUTPUT)  # reset pin
        wpi.pinMode(BL_PIN, wpi.OUTPUT)  # back light control pin
        wpi.softPwmCreate(BL_PIN, 0, 100)
        wpi.softPwmWrite(BL_PIN, 90)
        # spi init
        self.bus = 0
        self.dev = 0
        self.spi_speed = 8000000
        self.spi = spidev.SpiDev()
        self.spi.open(self.bus, self.dev)
        self.spi.max_speed_hz = self.spi_speed
        self.spi.mode = 0b00
        # self.spi.xfer([4000000, 10, 8])
        # define width and height of the 2 inch lcd
        self.w = 240
        self.h = 240 
        
    def write_cmd(self, cmd):
        """write command"""
        wpi.digitalWrite(DC_PIN,wpi.LOW)
        self.spi.writebytes([cmd])
        
    def write_data(self, value):
        """write data"""
        wpi.digitalWrite(DC_PIN,wpi.HIGH)
        self.spi.writebytes([value])
        
    def reset(self):
        """reset the lcd"""
        wpi.digitalWrite(RST_PIN,wpi.HIGH)
        time.sleep(0.01)
        wpi.digitalWrite(RST_PIN,wpi.LOW)
        time.sleep(0.01)
        wpi.digitalWrite(RST_PIN,wpi.HIGH)
        time.sleep(0.01)
    def lcd_init(self):
        """lcd init..."""
        self.reset()
        
        self.write_cmd(0x11)# sleep out 
        time.sleep(1)
        
        self.write_cmd(0x36) 
        self.write_data(0x60)# MY=0,MX=1,MV=1,ML=0,RGB Order
        time.sleep(0.05)
        self.write_cmd(0x3A) 
        self.write_data(0x05) #65k-colors
        # FRMCTR1:Frame Rate Control in normal mode
        self.write_cmd(0xB2) # PORCTRL(Porch Setting)
        self.write_data(0x0C)
        self.write_data(0x0C)
        self.write_data(0x00)
        self.write_data(0x33)
        self.write_data(0x33)
        
        # FRMCTR2:Frame Rate Control in idle mode
        self.write_cmd(0xB7) # GCTRL:Gate control
        self.write_data(0x35)

        self.write_cmd(0xBB) # VCOMS:VCOM Setting
        self.write_data(0x37)
        
        self.write_cmd(0xC0) # LCMCTRL:LCM Control
        self.write_data(0x2C)
        
        self.write_cmd(0xC2) # VDVVRHEN:VDV and VRH Command Enable
        self.write_data(0x01)
        
        self.write_cmd(0xC3) # VRHS:VRH Set
        self.write_data(0x12)
        
        self.write_cmd(0xC4) # VDVS: VDV Set
        self.write_data(0x20)
        
        self.write_cmd(0xC6) # FRCTRL2:Frame Rate Control in Normal Mode
        self.write_data(0x0F) # 60Hz
        
        self.write_cmd(0xD0) # PWCTRL1:Power Control 1
        self.write_data(0xA4) # default
        self.write_data(0xA1) # 
        
        self.write_cmd(0xE0) # Positive Voltage Gamma Control
        self.write_data(0xD0)
        self.write_data(0x04)
        self.write_data(0x0D)
        self.write_data(0x11)
        self.write_data(0x13)
        self.write_data(0x2B)
        self.write_data(0x3F)
        self.write_data(0x54)
        self.write_data(0x4C)
        self.write_data(0x18)
        self.write_data(0x0D)
        self.write_data(0x0B)
        self.write_data(0x1F)
        self.write_data(0x23)
        
        self.write_cmd(0xE1) # NVGAMCTRL:Negative Voltage Gamma Control
        self.write_data(0xD4)
        self.write_data(0x04)
        self.write_data(0x0C)
        self.write_data(0x11)
        self.write_data(0x13)
        self.write_data(0x2C)
        self.write_data(0x3F)
        self.write_data(0x44)
        self.write_data(0x51)
        self.write_data(0x2F)
        self.write_data(0x1F)
        self.write_data(0x1F)
        self.write_data(0x20)
        self.write_data(0x23)
        
        self.write_cmd(0x21)
        time.sleep(0.12)
        self.write_cmd(0x29)
        time.sleep(0.05)
        
    def set_windows(self, start_x, start_y, end_x, end_y):
        """display the windows of start point and end point"""
        end_x -= 1
        end_y -= 1
        # set the start point and end point of x
        self.write_cmd(0x2A) 
        self.write_data(start_x >> 8)  # x address start
        self.write_data(start_x & 0xff)
        self.write_data(end_x >> 8)  # x address end
        self.write_data(end_x & 0xff)
        # set the start point and end point of y
        self.write_cmd(0x2B) 
        self.write_data(start_y >> 8)  # y address start
        self.write_data(start_y & 0xff)
        self.write_data(end_y >> 8)  # y address end
        self.write_data(end_y & 0xff)
        
        self.write_cmd(0x2C)
        
    def img_show(self, img):
        img_w, img_h = img.size
        
        image = np.asarray(img)
        pixel = np.zeros((self.w, self.h, 2), dtype = np.uint8)
        pixel[..., [0]] = np.add(np.bitwise_and(image[..., [0]], 0xf8), np.right_shift(image[..., [1]], 5))
        
        pixel[..., [1]] = np.add(np.bitwise_and(np.left_shift(image[..., [1]], 3), 0xe0), np.right_shift(image[..., [2]], 3))       
        
        pixel = pixel.flatten().tolist()
        
        self.set_windows(0, 0, self.w, self.h) 
        wpi.digitalWrite(DC_PIN,wpi.HIGH)
        for i in range(0, len(pixel), 4096):
            self.spi.writebytes(pixel[i:i+4096])
                
    def clear(self):
        self.set_windows(0, 0, self.w, self.h)  
        wpi.digitalWrite(DC_PIN,wpi.HIGH)
        buf = [0xFF]*(self.w*self.h*2)
        for i in range(0, len(buf), 4096):
            self.spi.writebytes(buf[i:i+4096])


    