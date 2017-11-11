/*
 * main.h
 *
 *  Created on: 2017. nov. 11.
 *      Author: student
 */
#include <stdbool.h>

#ifndef INC_MAIN_H_
#define INC_MAIN_H_


#define    	char_bal 	98 		//ascii code of 'b'
#define     char_jobb 	106		//ascii code of 'j'
#define 	char_lo 		108 	//ascii code of 'j'

/* 13671 Hz -> 14Mhz (clock frequency) / 1024 (prescaler)
  Setting TOP to 27342 results in an overflow each 2 seconds */
#define TOP 6835

//"state variables"
typedef enum  {idle=0, jobbrakell,balrakell,lonikell, /*TODO: harder, easier*/} 	inputCommand;
typedef enum  { tuzel, golyoRepul, out} 											shootingProcess;			//2 szegmens a golyo utja
typedef enum  {miss, DED} 															duckState; 	//a lovesnel ezeket vizsgaljuk

//instances, to handle more ducks, bullets, inputs
inputCommand task=idle;
shootingProcess puska;
duckState preda=miss;

//data of segments
SegmentLCD_SegmentData_TypeDef segmentField[7]={0,0,0,0,0,0,0};


uint8_t volatile ch;
bool volatile new_char = false;
bool volatile timer_it = false;


int vadaszPos;
int halottMadarak;

//delimiters of motion, can be a define, too: limits the moving space
const int jobbSzelen=5;
const int balSzelen=0;



#endif /* INC_MAIN_H_ */
