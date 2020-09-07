/******************************************************************************
 *
 * Module: Calculator
 *
 * File Name: Calculator.c
 *
 * Description: File include all Calculator main task function prototype & variable declaration .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

/*					Modules Header Files						*/
#include "KeyPad.h"
#include  "LCD.h"
#include <math.h>

#define DELAY_TIME			300

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: Function to store operator type .
 */
void operator(void);

/*
 * Description: Function to calculate the result of equation that enter by user .
 */
void resultfun(void);

/*******************************************************************************
 *                         Variable Definition                                   *
 *******************************************************************************/

/* that variable use to store last pressed key*/
uint8 key_num = 0;

/* that variable use to store frist operand in equation that enter by user*/
sint32 num1 = 0;

/* that variable use to store second operand in equation that enter by user*/
sint32 num2 = 0;

/* that variable use to store opertor type in equation that enter by user*/
uint8 operand = 0;

/* that variable use to store the result of equation that enter by user*/
sint32 result = 0;

/*				main Calculator Function		*/
int main(void) {
	LCD_init();		/* initialize LCD module*/
	LCD_goToRowColumn(0, 3);		/*send cursor to row 0 , column 3*/
	LCD_displayString("Calculator");	/*print "Calculator" on screen */
	_delay_ms(DELAY_TIME);
	LCD_sendCommand(CURSOR_ON);	/* show cursor to kown location of start print */

	while (1) {
		LCD_clearScreen();	/*  clear LCD Screen to start enter equation */
		/* return cursor at row 0 , column 0*/
		LCD_sendCommand(CURSOR_HOME_LOCATION);

		do {
			/* receive press key from KeyPad */
			key_num = KeyPad_getPressedKey();
			/* check that pressed kry is number or operator */
			if ((key_num <= 57) && (key_num >= 48)) {
				LCD_displayCharacter(key_num);  	/* if pressed key is number show it in lcd screen */
				num1 = (sint32) (key_num - 48) + (num1 * 10); /* and update number 1 value*/
			}
			_delay_ms(DELAY_TIME); /* use delay that can user up his hand fron keypad */

		} while (((key_num <= 57) && (key_num >= 48)) || (num1 == 0));
		/* select operator type */
		operator();
		LCD_displayCharacter(key_num); /* display operator */
		/* use delay that can user up his hand fron keypad */
		_delay_ms(DELAY_TIME);

		do {
			key_num = KeyPad_getPressedKey(); /* receive press key from KeyPad */
			/* check that pressed kry is number or operator */
			if ((key_num <= 57) && (key_num >= 48)) {
				LCD_displayCharacter(key_num);		/* if pressed key is number show it in lcd screen */
				num2 = (sint32) (key_num - 48) + (num2 * 10);	/* and update number 2 value*/
			}
			/* use delay that can user up his hand fron keypad */
			_delay_ms(DELAY_TIME);

		} while (((key_num <= 57) && (key_num >= 48)) || (num2 == 0));

		/* stay in while loop untill user pressed on equal key*/
		while (key_num != '=') {
			key_num = KeyPad_getPressedKey();  /* receive press key from KeyPad */
		}
		LCD_displayCharacter(key_num);		/* display equal operator on lcd screen*/
		resultfun(); /* calculate the result */
		LCD_intgerToString(result);	/* print the result on lcd screen */
		/* stay in this while loop untill clear key */
		while (key_num != 8) {
			key_num = KeyPad_getPressedKey();	/* receive press key from KeyPad */
		}

		/* initalize all varable again*/
		key_num = 0;
		num1 = 0;
		num2 = 0;
		operand = 0;
		result = 0;

	}

	return 0;
}

/*
 * Description: Function to store operator type .
 */
void operator(void) {
	operand = key_num; /* stor operator type */

	return;
}

/*
 * Description: Function to calculate the result of equation that enter by user .
 */
void resultfun(void) {

	switch (operand) {
	case 43:
		result = num1 + num2;
		break;
	case 45:
		result = num1 - num2;
		break;
	case 42:
		result = num1 * num2;
		break;
	case 47:
		result = num1 / num2;
		break;
	default:
		result = 0;
		break;
	}

	return;
}

