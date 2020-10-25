/*Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{init, LED1, wait, LED0} state;

unsigned char button;
unsigned char tempB;

void Tick(){
	switch(state){
		case init:
			if(button == 1){
				state = LED1;
			}
			else{
				state = init;
			}
			break;
		case LED1:
			if(button == 1){
				state = LED1;
			}
			else{
				state = wait;
			}
			break;
		case wait:
			if(button == 1){
				state = LED0;
			}
			else{
				state = wait;
			}
			break;
		case LED0:
			if(button == 1){
				state = LED0;
			}
			else{
				state = init;
			}
			break;
		default:
			state = init;
			break;
	}
	switch(state){
		case init:
			tempB = 0x01;
			break;
		case LED1:
			tempB = 0x02;
			break;
		case wait:
			tempB = 0x02;
			break;
		case LED0:
			tempB = 0x01;
			break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00; 

	state = init;
    /* Insert your solution below */
    while (1) {
		button = PINA & 0x01;
		Tick();
		PORTB = tempB;
    }
    return 1;
}
