//=========================================================
// inc/InitDevice.h: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================
#ifndef __INIT_DEVICE_H__
#define __INIT_DEVICE_H__

// USER CONSTANTS
// USER PROTOTYPES

// $[Mode Transition Prototypes]
extern void enter_DefaultMode_from_RESET(void);
// [Mode Transition Prototypes]$

// $[Config(Per-Module Mode)Transition Prototypes]
extern void HFXO_enter_DefaultMode_from_RESET(void);
extern void LFXO_enter_DefaultMode_from_RESET(void);
extern void CMU_enter_DefaultMode_from_RESET(void);
extern void ADC0_enter_DefaultMode_from_RESET(void);
extern void ACMP0_enter_DefaultMode_from_RESET(void);
extern void ACMP1_enter_DefaultMode_from_RESET(void);
extern void DAC0_enter_DefaultMode_from_RESET(void);
extern void BURTC_enter_DefaultMode_from_RESET(void);
extern void RTC_enter_DefaultMode_from_RESET(void);
extern void OPAMP0_enter_DefaultMode_from_RESET(void);
extern void OPAMP1_enter_DefaultMode_from_RESET(void);
extern void OPAMP2_enter_DefaultMode_from_RESET(void);
extern void USART0_enter_DefaultMode_from_RESET(void);
extern void USART1_enter_DefaultMode_from_RESET(void);
extern void USART2_enter_DefaultMode_from_RESET(void);
extern void UART0_enter_DefaultMode_from_RESET(void);
extern void UART1_enter_DefaultMode_from_RESET(void);
extern void LEUART0_enter_DefaultMode_from_RESET(void);
extern void LEUART1_enter_DefaultMode_from_RESET(void);
extern void VCMP_enter_DefaultMode_from_RESET(void);
extern void WDOG_enter_DefaultMode_from_RESET(void);
extern void I2C0_enter_DefaultMode_from_RESET(void);
extern void I2C1_enter_DefaultMode_from_RESET(void);
extern void LCD_enter_DefaultMode_from_RESET(void);
extern void TIMER0_enter_DefaultMode_from_RESET(void);
extern void TIMER1_enter_DefaultMode_from_RESET(void);
extern void TIMER2_enter_DefaultMode_from_RESET(void);
extern void TIMER3_enter_DefaultMode_from_RESET(void);
extern void LETIMER0_enter_DefaultMode_from_RESET(void);
extern void PCNT0_enter_DefaultMode_from_RESET(void);
extern void PCNT1_enter_DefaultMode_from_RESET(void);
extern void PCNT2_enter_DefaultMode_from_RESET(void);
extern void PRS_enter_DefaultMode_from_RESET(void);
extern void ETM_enter_DefaultMode_from_RESET(void);
extern void EBI_enter_DefaultMode_from_RESET(void);
extern void PORTIO_enter_DefaultMode_from_RESET(void);
// [Config(Per-Module Mode)Transition Prototypes]$

// $[User-defined pin name abstraction]

#define BTN0_PIN            (9)
#define BTN0_PORT           (gpioPortB)

#define BTN1_PIN            (10)
#define BTN1_PORT           (gpioPortB)

#define LED0_PIN            (2)
#define LED0_PORT           (gpioPortE)

#define LED1_PIN            (3)
#define LED1_PORT           (gpioPortE)

#define UART0_RX_PIN        (1)
#define UART0_RX_PORT       (gpioPortE)

#define UART0_TX_PIN        (0)
#define UART0_TX_PORT       (gpioPortE)

#define VCOM_EN_PIN         (7)
#define VCOM_EN_PORT        (gpioPortF)

// [User-defined pin name abstraction]$

#endif

