#ifndef __KEY_H
#define __KEY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//define the key button pin in wiringpi number
#define K1_PIN      0
#define K2_PIN      1
#define K3_PIN      3
#define K4_PIN      4
#define R_PIN       28
#define L_PIN       29
#define UP_PIN      23
#define LEFT_PIN    21
#define DOWN_PIN    25
#define RIGHT_PIN   24
#define CENTER_PIN  22

void Key_Init(void);
void Key_Task(void);


#endif

