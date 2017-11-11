#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "InitDevice.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_emu.h"


#include "segmentlcd.h"
#include "segmentlcd_spec.h"
#include "segmentlcdconfig.h"

#define    	char_bal 	98 		//ascii code of 'b'
#define     char_jobb 	106		//ascii code of 'j'
#define 	char_lo 		108 	//ascii code of 'j'

uint8_t volatile ch;
bool volatile new_char = false;

void UART0_RX_IRQHandler(void) {
	ch = USART_RxDataGet(UART0);
	new_char = true;
	//USART_IntClear(UART0, USART_IF_RXDATAV);
}

	SegmentLCD_SegmentData_TypeDef segmentField[7]={0,0,0,0,0,0,0};

	/*bool loves=0;
	bool jobbrakell=0;
	bool balrakell=0;
	bool tuzel=0;
	bool golyoRepul=0;
	bool kacsaWillDie=0;
	bool kacsaDED=0;
	int miss=0;*/

	int vadaszPos=0;
	int halottMadarak=0;

	//delimiters of motion, can be a define, too
	const int jobbSzelen=5;
	const int balSzelen=0;

	typedef enum  {idle=0, jobbrakell,balrakell,lonikell, /*TODO: harder, easier*/} inputCommand;
	typedef enum  { tuzel, golyoRepul, out} shootingProcess;			//2 szegmens a golyo utja
	typedef enum  {miss, DED} duckState; 	//a lovesnel ezeket vizsgaljuk

	duckState preda=miss;

	/*
	 * Input: 	direction to step with the hunter in the row of it
	 *
	 * output: 	write the LCD depending on segmentField[]
	 * 			modifies the vadaszPos value
	 *
	 *
	 */
	void vadaszLepes(signed char dir)
	{
		if(1==dir)
		{
			//jobbra lep
			if(vadaszPos!=jobbSzelen) //ha szelen van mar ne lepjen
			{
				//lepjen jobbra:
				segmentField[vadaszPos].d=0;		// raw-ban a jelenlegit kimaszkoljuk
				vadaszPos++;						// leptetjuk
				segmentField[vadaszPos].d=1;		// raw-ban a jelenlegit kimaszkoljuk
			}
		}
		else if (-1==dir)
		{
			//balra lep
			if(vadaszPos!=balSzelen) //ha szelen van mar ne lepjen
			{
				//lepjen: bal=-1 a kijelzon
				segmentField[vadaszPos].d=0;		// raw-ban a jelenlegit kimaszkoljuk
				vadaszPos--;						// leptetjuk
				segmentField[vadaszPos].d=1;		// az egyel odebb levot bealltjuk
			}
		}
	}

	/*
	 * Kezeli a loveseket, a kiovastol a leteritesig. Noveli a szamlalot ha eltalaltunk egy madarat
	 * atadtuk a puskat neki, itt lovedekkent vesszuk at ;)
	 */

void vadaszLovesProcess ()
{
	shootingProcess lovedek;
	//scanning current state
	if(0==segmentField[vadaszPos].p){
		//not shooted yet
		lovedek=tuzel;
	}
	else if(1==segmentField[vadaszPos].p){
		//bullet already started
		lovedek=golyoRepul;
	}
	else if(1==segmentField[vadaszPos].j){
		lovedek=out;
		if(1==segmentField[vadaszPos].a){
			//duck there
			preda=DED;
			//TODO: counter++

		}
		else
		{
			preda=miss; //global
		}
	}



	switch(lovedek){
	//most hol tartunk

	case tuzel :
	{
		segmentField[vadaszPos].p=1; 		// loves elinditasa
		lovedek=golyoRepul;					// break miatt a kovetkezobe NEM lep be
		break;
	}
	case golyoRepul :
	{
		segmentField[vadaszPos].p=0; 		// golyo leptetese
		segmentField[vadaszPos].j=1;
		if(1==segmentField[vadaszPos].a)	//VAN ott kacsa
		{
			preda=DED;
		}
		else
		{
			preda=miss;
		}
	}
	}
}

/*void kacsaLeterites ()*/


	/*
	 * Input: 	called when new char is got from buffer
	 *
	 * Does: 	decide what to do depending on the char
	 * 			calls appropriate fcn
	 *
	 *
	 */
inputCommand task;
shootingProcess puska;

void handleNewChar()
{
	new_char = false;
	USART_Tx(UART0, ch);

	switch (ch){
		case char_bal:
			task=balrakell;
			break;
		case char_jobb:
			task=jobbrakell;
			break;
		case char_lo:
			task=lonikell;
			break;
		default:
			task=idle;
	}
	/*if(ch==char_bal)	{	task=balrakell;		}
	if(ch==char_jobb)	{	task=jobbrakell;	}
	if(ch==char_lo)		{	task=lonikell;		}*/

	switch (task)
	{
		case balrakell :
		//{
			GPIO_PinOutToggle(LED1_PORT, LED1_PIN);
			vadaszLepes(-1);			// balra lepeshez - 1
			displaySegmentField(segmentField);
			break;
		//}
		case jobbrakell :
		//{

			GPIO_PinOutToggle(LED0_PORT, LED0_PIN);
			vadaszLepes(1);				//jobbra lep
			displaySegmentField(segmentField);
			break;
		//}
		case lonikell :
		//{
			GPIO_PinOutSet(LED0_PORT, LED0_PIN);
			GPIO_PinOutSet(LED1_PORT, LED1_PIN);

			 	//to perform appropriate cucc in Proc
			vadaszLovesProcess();
			displaySegmentField(segmentField);
			//TODO: flying of the bullet, START A TIMER

		//}
	}//end of switch

}

int main(void)
{
	CHIP_Init();
	// Init device using Configurator
	enter_DefaultMode_from_RESET();

	// Init device (additional settings, not available in Configurator)
		USART_IntEnable(UART0, USART_IF_RXDATAV);
		NVIC_EnableIRQ(UART0_RX_IRQn);

	// Init board
	GPIO_PinOutSet(LED0_PORT, LED0_PIN);
	SegmentLCD_Init(false);


	// Infinite loop
	while (1) {
			EMU_EnterEM1();
			if (new_char) {
				handleNewChar();

			}

  }
}
