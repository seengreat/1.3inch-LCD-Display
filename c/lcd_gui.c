/********************************
 *  Seengreat 1.3 Inch LCD Display demo
 *  Author(s):Andy Li from Seengreat
 * ********************/
 
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <wiringPi.h>
#include "lcd_gui.h"
#include "lcd_1inch3.h"

IMAGE Image;
void Image_Init(u_int16_t img_w, u_int16_t img_h, u_int16_t rotate, u_int16_t mirror )
{
    Image.w = img_w;
    Image.h = img_h;
    Image.rotate = rotate;
    Image.mirror = mirror;
    if (Image.rotate == ROTATE_90 || Image.rotate == ROTATE_270)
    {
        Image.h = img_w;
        Image.w = img_h; 
    }
    printf("img w*h-%d*%d \r\n", Image.w,Image.h);
}
//set pixel color x:0~127 y:0~127
void Gui_set_pix(u_int16_t x, u_int16_t y, u_int16_t color)
{
    u_int16_t xx=0;
    u_int16_t yy=0;
    if(x>Image.w || y>Image.h)
    {
        printf("ERR:set_pix point out of screen area!\r\n");
        return ;
    }
    color = ((color<<8)&0xff00)|(color>>8);
    switch(Image.rotate)
    {
        case ROTATE_90:
            xx = LCD_W-y-1;
            yy = x;
            break;
        case ROTATE_180:
            xx = LCD_W-x-1;
            yy = LCD_H-y-1;
            break;
        case ROTATE_270:
            xx = y;
            yy = LCD_H-x-1;
            break;
        default:
            xx = x;
            yy = y;
            break;
    }
    if(xx > LCD_W || yy > LCD_H)
    {
        printf("exceed screen area x:%d y:%d\r\n",xx,yy);
        return;
    }
    Image.img[xx+yy*LCD_W] = color;
}

void Gui_draw_point(u_int16_t x, u_int16_t y, u_int16_t color, u_int16_t width)
{
    u_int16_t xd, yd;
    if(x>Image.w || y > Image.h)
    {
        printf("ERR:point out of screen area! x:%d y:%d\r\n",x, y);
        return ;
    }
    for(xd = 0;xd<width; xd++)
    {
        for(yd=0;yd<width; yd++)
        {
            if(x+xd>Image.w || y+yd>Image.h )
            {
               continue;    
            }
            Gui_set_pix(x+xd-1, y+yd-1, color);     
        }
    }
}

void Gui_Clear( u_int16_t color)
{
    u_int16_t x,y;
    color = ((color<<8)&0xff00)|(color>>8);
    for (y = 0; y < Image.h; y++) 
    {
        for (x = 0; x < Image.w; x++) 
        {
            Image.img[x + y*Image.w] = color;
        }
    }
}

void Gui_line(u_int16_t x1, u_int16_t y1, u_int16_t x2, u_int16_t y2, u_int16_t color, u_int16_t width, LINE_STYLE type)
{
    u_int16_t i;
    double k;
    if(x1>Image.w || y1 > Image.h || x2 > Image.w || y2 > Image.h)
    {
        printf("ERR:line point out of screen area!\r\n");
        return ;
    }    
    if(x1==x2)
    {
        if(y1<y2)
        {
            for(i=y1;i<=y2;i++)
            {
                if(type==DOTTED) 
                {
                    if(i%3==0)
                        Gui_draw_point(x1, i, color, width);
                }
                else
                    Gui_draw_point(x1, i, color, width); 
                
            }
        }
        else
        {
            for(i=y2;i<=y1; i++)
            {
                if(type==DOTTED) 
                {
                    if(i%3==0)
                        Gui_draw_point(x1, i, color, width);
                }
                else
                    Gui_draw_point(x1, i, color, width);  
            }
        }            
    }
    else
    {
        if(y1==y2)
        {
            if(x1<x2)
            {
                for(i=x1;i<=x2;i++)
                {
                    if(type==DOTTED) 
                    {
                        if(i%3==0)
                            Gui_draw_point(i, y1, color, width);
                    }
                    else
                    {
                        Gui_draw_point(i, y1, color, width);
                    }   
                }
            }
            else
            {
                for(i=x2;i<=x1;i++)
                {
                    if(type==DOTTED) 
                    {
                        if(i%3==0)
                            Gui_draw_point(i, y1, color, width);
                    }
                    else
                        Gui_draw_point(i, y1, color, width);   
  
                }
            }            
        }
        else
        {
            k = (double)(y2-y1)/(x2-x1); 
            //printf("k:%f\r\n", k);
            if(x1<x2)
            {
                for(i=0;x1+i<=x2;i++)
                {
                    if(type==DOTTED)
                    {
                        if(i%3==0)
                            Gui_draw_point(x1+i, y1+i*k, color, width);
                    }
                    else
                        Gui_draw_point(x1+i, y1+i*k, color, width);   
                }
            }
            else
            {
                for(i=0;x2+i<=x1;i++)
                {
                    if(type==DOTTED)
                    {
                        if(i%3==0)
                            Gui_draw_point(x2+i, y2+i*k, color, width); 
                    }
                    else
                        Gui_draw_point(x2+i, y2+i*k, color, width);
                }
            }             
        }        
    }
}

//Bresenham circle algorithm draw line
void Gui_draw_line(u_int16_t x1, u_int16_t y1, u_int16_t x2, u_int16_t y2, u_int16_t color, u_int16_t width, LINE_STYLE type)
{
    u_int16_t x = x1;
    u_int16_t y = y1;
    u_int16_t dx = x2-x1>=0?x2-x1:x1-x2;
    u_int16_t dy = y2-y1>=0?y2-y1:y1-y2;
    int p = dx-dy;
    int e2;
    int xdir = x1>x2?-1:1;
    int ydir = y1>y2?-1:1;
    int dot_cnt = 0;
    for(;;)
    {
        dot_cnt++;
        if(type==DOTTED && dot_cnt%3==0)
        {
            Gui_draw_point(x, y, color, width);
        }
        else if(type==SOLID)
        {
            Gui_draw_point(x, y, color, width);
        }
        if(x==x2 && y==y2)
        {
            break;
        }
        e2 = 2*p;
        if(e2>= -dy)
        {
            p -= dy;
            x += xdir;
        }
        if(e2<=dx)
        {
            p += dx;
            y += ydir;
        }
    }
    
    
}
void Gui_draw_rectangle(u_int16_t x1, u_int16_t y1, u_int16_t x2, u_int16_t y2, u_int16_t color, u_int16_t width, FILL fill)
{
    u_int16_t i;
    if(x1>Image.w || y1 > Image.h || x2 > Image.w || y2 > Image.h)
    {
        printf("ERR:line point out of screen area!\r\n");
        return ;
    } 
    if(fill == FULL)
    {
        for(i=y1;i<y2;i++)
        {
            Gui_line(x1, i, x2, i, color, width, SOLID);
        }
    }
    else if(fill==EMPTY)
    {
        Gui_line(x1, y1, x2, y1, color, width, SOLID);
        Gui_line(x1, y1, x1, y2, color, width, SOLID);
        Gui_line(x1, y2, x2, y2, color, width, SOLID);
        Gui_line(x2, y1, x2, y2, color, width, SOLID);
    }
}

//Bresenham circle algorithm draw circle
void Gui_draw_circle(u_int16_t x, u_int16_t y, u_int16_t r, u_int16_t color, u_int16_t width, FILL fill)
{
    u_int16_t dx=0,dy=r;
    int d = 1-r;
    u_int16_t i;
    if(x>Image.w || y > Image.h)
    {
        printf("ERR:circle center point out of screen area!\r\n");
        return ;
    } 
    while(dy>dx)
    {
        if(fill==EMPTY)
        {
            Gui_draw_point(x+dx, y+dy, color, width);
            Gui_draw_point(x+dy, y+dx, color, width);
            Gui_draw_point(x-dx, y+dy, color, width);
            Gui_draw_point(x-dy, y+dx, color, width);
            Gui_draw_point(x-dx, y-dy, color, width);
            Gui_draw_point(x-dy, y-dx, color, width);
            Gui_draw_point(x+dx, y-dy, color, width);
            Gui_draw_point(x+dy, y-dx, color, width);
        }
        else if(fill==FULL)
        {
            for(i=dx;i<=dy;i++)
            {
                Gui_draw_point(x+dx, y+i, color, width);
                Gui_draw_point(x+i, y+dx, color, width);
                Gui_draw_point(x-dx, y+i, color, width);
                Gui_draw_point(x-i, y+dx, color, width);
                Gui_draw_point(x-dx, y-i, color, width);
                Gui_draw_point(x-i, y-dx, color, width);
                Gui_draw_point(x+dx, y-i, color, width);
                Gui_draw_point(x+i, y-dx, color, width);                
            }
        }
        if(d<0)
        {
            d += 2*dx+3;    
        }
        else
        {
            d += 2*(dx-dy)+5;
            dy--;
        }
        dx++;
    }
}


void Gui_draw_char(u_int16_t x, u_int16_t y, const char str_char, FONT* Font, u_int16_t color, u_int16_t background)
{
    u_int16_t row, col_bit;

    if (x > Image.w || y > Image.h) 
    {
        printf("ERR:draw char point out of screen area!\r\n");
        return;
    }
    //the number of bytes occupied by a character
    u_int16_t char_nbytes = Font->h * (Font->w / 8 + (Font->w % 8 ? 1 : 0));
    //the offset of the character
    u_int32_t offset = (str_char - ' ') * char_nbytes;
    const unsigned char *ptr = &Font->table[offset];

    for (row = 0; row < Font->h; row ++) 
    {
        for (col_bit = 0; col_bit < Font->w; col_bit++ )
        {
            if (FONT_BACKGROUND == background) 
            { 
                if (*ptr & (0x80 >> (col_bit % 8)))
                    Gui_set_pix(x+col_bit, y+row, color);
            } 
            else 
            {
                if (*ptr & (0x80 >> (col_bit % 8))) 
                {
                    Gui_set_pix(x+col_bit, y+row, color);
                } 
                else 
                {
                    Gui_set_pix(x+col_bit, y+row, background);
                }
            }            
            if (col_bit % 8 == 7) //next byte
                ptr++;
        }
        if(Font->w % 8 != 0)// next line
            ptr++;
    }
}

void Gui_draw_str(u_int16_t x, u_int16_t y, const char *str_char, FONT* Font, u_int16_t color, u_int16_t background)
{
    u_int16_t dx = x,dy = y;
    while(*str_char != '\0')
    {
        if((dx+Font->w)>Image.w)//wrap the line if the x direction has reached the boundary
        {
            dx = x;
            dy += Font->h;
        }
        if((dy+Font->h)>Image.h)//wrap the line if the y direction has reached the boundary
        {
            dy = y;
            dx += Font->w;
        }
        Gui_draw_char(dx, dy, *str_char++, Font, color, background);
        dx += Font->w;
    }

}

void Gui_draw_str_cn(u_int16_t x, u_int16_t y, const char *str_cn, CN_FONT* Font, u_int16_t color, u_int16_t background)
{
    u_int16_t dx = x,dy = y;
    const char *p_str;
    u_int16_t i,row,col_bit;
    //const char *temp = "Éî¹ð¿Æ¼¼";
    //printf("test:%s\r\n",temp);
    printf("draw chinese:%s\r\n", str_cn);
    while(*str_cn != '\0')
    {
        for(i=0;i<Font->size;i++)
        {
            if(*str_cn == Font->table[i].context[0] && *(str_cn+1) == Font->table[i].context[1]) // one chinese character occupies 2 bytes
            {
                p_str = &Font->table[i].pix[0];
                if((dx+Font->w)>Image.w)//wrap the line if the x direction has reached the boundary
                {
                    dx = x;
                    dy += Font->h;
                }
                if((dy+Font->h)>Image.h)//wrap the line if the y direction has reached the boundary
                {
                    dy = y;
                    dx += Font->w;
                }
                for (row = 0; row < Font->h; row ++) 
                {
                    for (col_bit = 0; col_bit < Font->w; col_bit++ )
                    {
                        if (FONT_BACKGROUND == background) 
                        { 
                            if (*p_str & (0x80 >> (col_bit % 8)))
                                Gui_set_pix(dx+col_bit, dy+row, color);
                        } 
                        else 
                        {
                            if (*p_str & (0x80 >> (col_bit % 8))) 
                            {
                                Gui_set_pix(dx+col_bit, dy+row, color);
                            } 
                            else 
                            {
                                Gui_set_pix(dx+col_bit, dy+row, background);
                            }
                        }            
                        if (col_bit % 8 == 7) //next byte
                            p_str++;
                    }
                    if(Font->w % 8 != 0)// next line
                        p_str++;
                }
                break;
            }
        }
        str_cn += 2;
        dx += Font->w;
    }
}

int Gui_show_bmp(const char *path)
{
    FILE *bmp_fd;
    BMP_INFO bmp_info;
    BMP_HEADER  bmp_header;
    u_int16_t i,w,h,bits;
    u_int16_t x,y,k,index;
    u_int16_t color;
    
    char *bmp_buf;
    char palette[256][4];
    
    k=0;
    bmp_fd = fopen(path, "rb");
    if(bmp_fd == NULL)
    {
        printf("open bmp file failed\r\n");
        return -1;
    }
    printf("open file %s sucess\r\n",path);
    fread(&bmp_header, sizeof(BMP_HEADER), 1, bmp_fd);
    fread(&bmp_info, sizeof(BMP_INFO), 1, bmp_fd);
    printf("bmp w*h: %d x %d bit_coun:%d\r\n",bmp_info.width, bmp_info.height, bmp_info.bit_count);
    w =  bmp_info.width;
    h =  bmp_info.height;
    bits = bmp_info.bit_count;
    if(w > Image.w || h > Image.h)
    {
        printf("bmp file size larger than the size of screen!\r\n");
        return -1;
    }
    bmp_buf = (char *)malloc(w*h*4);
    if(bits>8)
    {
        u_int16_t len = bits/8;
        switch(4-(w*bits/8%4)) //read rgb data
        {
            case 1:
                for(i=0;i<h;++i)
                {
                    fread(bmp_buf+w*len*i, w*len, 1, bmp_fd);
                    fseek(bmp_fd, 1, SEEK_CUR);    
                }
                break;
            case 2:
                for(i=0;i<h;++i)
                {
                    fread(bmp_buf+w*len*i, w*len, 1, bmp_fd);
                    fseek(bmp_fd, 2, SEEK_CUR);    
                }
                break;
            case 3:
                for(i=0;i<h;++i)
                {
                    fread(bmp_buf+w*len*i, w*len, 1, bmp_fd);
                    fseek(bmp_fd, 3, SEEK_CUR);    
                }
                break;
            default:
                fread(bmp_buf, w*h*len, 1, bmp_fd);
        }
        if(bits==16)
        {
            //printf("info size:%x %d\r\n",bmp_info.size,bmp_info.compression);
            for (y = 0; y < Image.h; y++) 
            {
                for (x = 0; x < Image.w; x++) 
                {
                    if((bmp_info.size == 40) && (bmp_info.compression==0)) //XRGB1555
                    {
                        char r,g,b;
                        r = (bmp_buf[x*len + y*len*Image.w+1]>>2)&0x1F;
                        g = ((bmp_buf[x*len + y*len*Image.w+1]&0x03)<<3) + ((bmp_buf[x*len + y*len*Image.w]&0xE0)>>5);
                        b = (bmp_buf[x*len + y*len*Image.w]&0x1F);
                        color = ((r<<11)|(g<<6)|(b));                  
                    }
                    else if(bmp_info.size == 56)
                    {
                        color = (bmp_buf[x*len + y*len*Image.w]<<8) + bmp_buf[x*len + y*len*Image.w+1];
                    }
                    Gui_set_pix(x, h-y-1, color);
                }
            }        
        }
        else if(bits>=24) //BGR and ARGB format
        {
            for (y = 0; y < Image.h; y++) 
            {
                for (x = 0; x < Image.w; x++) 
                {
                    color = BGR888_TO_RGB565(bmp_buf[x*len + y*len*Image.w],bmp_buf[x*len + y*len*Image.w+1],bmp_buf[x*len + y*len*Image.w+2]);
                    Gui_set_pix(x, h-y-1, color);
                }
            }
        }
    }
    else
    {
        printf("palette:%d buf_size:%d \r\n", (1<<(bits+2)), (w*h/(8/bits)));
        fseek(bmp_fd, 54, SEEK_SET);
        fread(palette, (1<<(bits+2)), 1, bmp_fd);
        fread(bmp_buf, w*h/(8/bits), 1, bmp_fd);
        i = 0;
        for (y = 0; y < Image.h; y++) 
        {
            for (x = 0; x < Image.w; i++) 
            {
                if(bits==8)
                {
                    index = bmp_buf[x + y*Image.w];
                    color = BGR888_TO_RGB565(palette[index][0], palette[index][1], palette[index][2]);
                    Gui_set_pix(x, h-y-1, color);
                    x++;
                }
                else 
                {
                    index = bmp_buf[i];
                    u_int8_t num = 0;
                    for(k=0; (k<(8/bits))&&(x<Image.w); k++,x++)
                    {
                        if(bits==4)
                        {
                            num = (index <<(k*4)) >> 4;
                            num &= 0x0f; 
                        }
                        if(bits==1)
                        {
                            num = (index <<k) >> 7; 
                            num &= 0x01;
                        }
                        color = BGR888_TO_RGB565(palette[num][0], palette[num][1], palette[num][2]);
                        Gui_set_pix(x, h-y-1, color);
                    }
                }
            }
        }
    }
    free(bmp_buf);
    fclose(bmp_fd);
    return 0;
}

