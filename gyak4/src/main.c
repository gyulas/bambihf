#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_system.h"
#include "em_timer.h"
#include "InitDevice.h"
#include "InitDevice.h"

#include "em_usart.h"
#include "em_gpio.h"
#include "em_emu.h"

#include "segmentlcd.h"
#include "segmentlcd_spec.h"
#include "segmentlcdconfig.h"

#include "main.h"			//global variables, typedefs



/////////////////////////// interrupt handlers //////////////////////////
// Triggered when:
/*
 * 	- new char received
 * 	- timer time elapsed (every 0.2-0.5s)
 */
/**************************************************************************//**
 * @brief UART0_IRQHandler
 * Interrupt Service Routine UART0 Interrupt Line
 *****************************************************************************/
void UART0_RX_IRQHandler(void) {
	ch = USART_RxDataGet(UART0);
	new_char = true;
	//USART_IntClear(UART0, USART_IF_RXDATAV);
}


/**************************************************************************//**
 * @brief TIMER0_IRQHandler
 * Interrupt Service Routine TIMER0 Interrupt Line
 *****************************************************************************/
void TIMER0_IRQHandler(void)
{
  /* Clear flag for TIMER0 overflow interrupt */
  TIMER_IntClear(TIMER0, TIMER_IF_OF);

  /* Toggle LED ON/OFF */
  GPIO_PinOutToggle(LED0_PORT, LED0_PIN);
}

///////////////////////////// vadasz functions//////////////////////////
// These fuctions are invoked when user triggers "vadasz" event.

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
	// semmi mast nem kellene csinalnia mint elinditani egy lovedeket onnan ahol all

	shootingProcess lovedek;
	//scanning current state
	if(0==segmentField[vadaszPos].p){
		//not shooted yet
		lovedek=tuzel;
	}
	/*else if(1==segmentField[vadaszPos].p){
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
	*/
	switch(lovedek){
		case tuzel :
		{
			segmentField[vadaszPos].p=1; 		// loves elinditasa
			lovedek=golyoRepul;					// break miatt a kovetkezobe NEM lep be
			break;
		}
		/*case golyoRepul :
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
		}*/
	} //switch
}

/*void kacsaLeterites ()*/


///////////////////serial port///////////////////////
	/*
	 * Input: 	called when new char is got from buffer
	 *
	 * Does: 	decide what to do depending on the char and
	 * 			calls appropriate function to serve it.
	 *
	 *			blink some leds for fun
	 */

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
			//GPIO_PinOutSet(LED0_PORT, LED0_PIN);
			//GPIO_PinOutSet(LED1_PORT, LED1_PIN);

			 	//to perform appropriate cucc in Proc
			//vadaszLovesProcess();
			displaySegmentField(segmentField);
			//TODO: flying of the bullet, START A TIMER
			TIMER_Enable(TIMER0,1);

			break;
		//}
		case idle:
			break;
	}//end of switch

}

void handleTimerEvent()
{
	timer_it=false;

	// ha van repulo lovedek, kezeljuk le

	if(1==segmentField[vadaszPos].p)
	{
		//bullet already started
		segmentField[vadaszPos].p=0;
		segmentField[vadaszPos].j=1;
	}
	else if(1==segmentField[vadaszPos].j){
		segmentField[vadaszPos].j=0;
		if(1==segmentField[vadaszPos].a)
		{	//duck there
										//TODO: counter++ on segment
			halottMadarak++;
			//villoghat estleg
		}
		else
		{
			//miss
		}
	}
}

int main(void)
{
	CHIP_Init();
	enter_DefaultMode_from_RESET();				//InitDevice setups the timer, gpio, uart

	USART_IntEnable(UART0, USART_IF_RXDATAV);	// Init device (additional settings, not available in Configurator)
	NVIC_EnableIRQ(UART0_RX_IRQn);

	/* Enable overflow interrupt */
	TIMER_IntEnable(TIMER0, TIMER_IF_OF);

	/* Enable TIMER0 interrupt vector in NVIC */
	NVIC_EnableIRQ(TIMER0_IRQn);

	/* Set TIMER Top value */
	TIMER_TopSet(TIMER0, TOP);


	// Init board
	GPIO_PinOutSet(LED0_PORT, LED0_PIN);
	SegmentLCD_Init(false);


	//initial values
	vadaszPos=0;
	halottMadarak=0;

	while (1) {
			EMU_EnterEM1();
			if (new_char) {
				handleNewChar();
			}
			if (timer_it)
			{
				handleTimerEvent();
			}

  }
}
