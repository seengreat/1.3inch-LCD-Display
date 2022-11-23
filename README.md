1.3inch LCD Display from seengreat:www.seengreat.com
 =======================================
# Instructions
## Overview
This LCD is a 1.3-inch TFT display, onboard a joystick and six buttons, resolution of 240*240, internal ST7789 controller, based on Raspberry Pi 40pin GPIO connector design, supported Raspberry Pi Zero/Zero W/Zero WH/2B/3B/3B+/4B, can use SPI interface communication, provide Raspberry Pi C, python version of the demo codes, it can realize points, lines, rectangles, circles painting, but also English characters, pictures display.<br>
## Product parameters
|Dimensions	|65mm(L)*30.3mm(W)|
|----------------------|-----------------------|
|Resolution	|240*240|
|Display Colors	|RGB，65K colors|
|Control chip	|ST7789|
|Screen type	|TFT|
|Backlight	|LED|
|Interface	|4 Line SPI|
|Supply Voltage	|3.3V|
|Operating Temp	|-20℃～+70℃|
|Storage Temp	|-30℃～+80℃|
|LCD display area	|23.4mm (W)*23.4mm (H)|
## Product size
65mm(L)*30.30mm(W)<br>
# Usages
## Hardware interface configuration description
### Wiring Instructions for Raspberry Pi
The sample program in the Raspberry Pi motherboard uses the wiringPi number pin definitions. The definition of the connection with the Raspberry Pi motherboard is shown in the following table:<br>
|LCD interface	|Pin function	|BCM number	|wiringPi number|
|----------------------|----------------------|-----------------------|------------------|
|VCC	|3.3V	|3.3V	|3.3V|
|GND	|GND	|GND	|GND|
|SDA	|MOSI	|10	|12|
|SCK	|SCK	|11	|14|
|CS	|CE0	|8	|10|
|A0	|P6	|25	|6|
|RESET	|P2	|27	|2|
|K1	|P0	|17	|0|
|K2	|P1	|18	|1|
|K3	|P3	|22	|3|
|K4	|P4	|23	|4|
|R	|P28	|20	|28|
|L	|P29	|21	|29|
|LEFT	|P21	|5	|21|
|DOWN	|P25	|26	|25|
|RIGHT	|P24	|19	|24|
|CENT	|P22	|6	|22|
|UP	|P23	|13	|23|
## Demo Codes Usage
### Wiringpi library installation
   sudo apt-get install wiringpi<br>
   wget https://project-downloads.drogon.net/wiringpi-latest.deb  # Version 4B upgrade of Raspberry Pi<br>
   sudo dpkg -i wiringpi-latest.deb<br>
   gpio -v # If version 2.52 appears, the installation is successful<br>
#For the Bullseye branch system, use the following command:<br>
git clone https://github.com/WiringPi/WiringPi<br>
cd WiringPi<br>
./build<br>
gpio -v<br>
# Running gpio - v will result in version 2.70. If it does not appear, it indicates an installation error
If the error prompt "ImportError: No module named 'wiring pi'" appears when running the python version of the example program, run the following command:<br>
# For Python 2. x version<br>
pip install wiringpi<br>
 
# For Python 3.x version<br>
pip3 install wiringpi<br>
Note: If the installation fails, you can try the following compilation and installation:<br>
git clone--recursive https://github.com/WiringPi/WiringPi-Python.git<br>
Note: --recursive option can automatically pull submodules, otherwise you need to download them manually.<br>
Go to the WiringPi-Python folder you just downloaded and enter the following command to compile and install:<br>
# For Python 2.x version<br>
sudo python setup.py install <br>
# For Python 3.x version<br>
sudo python3 setup.py install<br>
If the following error occurs:<br>
"Error:Building this module requires either that swig is installed<br>
        (e.g.,'sudo apt install swig') or that wiringpi_wrap.c from the<br>
        source distribution (on pypi) is available."<br>
At this time, enter the command sudo apt install swig to install swig. After that, compile and install sudo python3 setup.py install. If a message similar to the following appears, the installation is successful.<br>
"ges<br>
Adding wiringpi 2.60.0 to easy-install.pth file<br>
Installed /usr/local/lib/python3.7/dist-packages/wiringpi-2.60.0-py3.7-linux-armv7<br>
Processing dependencies for wiringpi==2.60.0<br>
Finished processing dependencies for wiringpi==2.60.0"<br>
### Turn on the SPI interface
sudo raspi-config<br>
Enable the SPI interface:<br>
Interfacing Options -> SPI -> Yes<br>
To view the enabled SPI devices:<br>
ls /dev/spi*  # prints: "/dev/spidev0.0" and "/dev/spidev0.1"<br>
### Installation of Python libraries
The demo codes uses the python environment, and to run the python sample program, you need to install pil, numpy, spidev libraries, and enter the following commands in order to install:<br>
sudo apt-get install python3-pil<br>
sudo apt-get install python3-numpy<br>
sudo apt-get install python3-pip<br>
sudo pip3 install spidev<br>
### C version demo codes
Note: For Raspberry Pi 4B and versions after raspbian_lite-2019-06-20, the following settings are required, otherwise the keys cannot be entered normally.<br>
sudo nano /boot/config.txt<br>
Add the following:<br>
gpio=17,22,18,13,26,5,19,6,20,21,23=pu<br>
Then save to exit.<br>
Go to the demo codes/c directory<br>
sudo make clean<br>
sudo make<br>
sudo ./main<br>
### Python version demo codes
Go to the demo codes/python directory<br>
python3 gui_demo.py<br>
python3 key_demo.py<br>
## Demo Codes Description
### C language version
The Demo Codes structure is divided into the bottom layer and the application layer, the underlying file is lcd_1inch3.c and lcd_1inch3.h, the underlying code implements the initialization of the Raspberry Pi motherboard control pin and LCD screen, and the application layer file lcd_gui.c and lcd_gui.h, mainly realizing the drawing of points, lines, rectangles, circles and the display function of English characters and pictures.<br>
The files whose file names begin with "font" are related to the font. The ". c" suffix corresponds to the data source files of the font. The data structures of multiple font data source files are defined in the "fonts. h" file. The file with the suffix ". bmp" in the Raspberry Pi motherboard example program is the picture source file used for display. The number in the file name represents the pixel number of color (bpp, bit per pixel), for example, 1.3inch_demo1.bmp represents the picture file in 24bpp true color format.<br>
### Python language version
The python language version of the sample program is only provided for the Raspberry Pi platform. At the same time, because the python platform can reference the PIL image processing library, many application layer API functions can be directly provided by the library, which greatly reduces the amount of code in the sample program. The python version of the demo code file has a gui_demo.py、key_demo.py、lcd_ 1inch3.py three files, gui_demo.py is mainly used to draw lines, rectangles and circles, and display English characters and key_demo.py is the function demonstration of on-board keys, lcd_1inch3.py is the driver to realize the bottom layer of LCD, including SPI initialization, LCD screen reset, initialization, etc.<br>
