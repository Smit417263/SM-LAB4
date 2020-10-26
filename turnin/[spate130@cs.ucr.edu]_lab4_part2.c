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

enum States{init, INC, DEC, DEP, wait, wait2} state;

unsigned char button0;
unsigned char button1;
unsigned char tempC = 0x07;


void Tick(){
	switch(state){ // Transitions
		case init:
			if(!button0 && !button1){
				state = init;
			}
			else if(button0 && !button1){
				state = INC;
			}
			else if(!button0 && button1){
				state = DEC;
			}
			else if(button0 && button1){
				state = DEP;
			}
			break;
		case INC:
			if(button0 && button1){
				state = DEP;
			}
			else{
				state = wait2;
			}
			break;
		case DEC:
			if(button0 && button1){
				state = DEP;
			}
			else{
				state = wait2;
			}
			break;
		case DEP:
			if(!button0 && !button1){
				state = init;
			}
			else if (button0 && !button1){
				state = INC;
			}
			else if(!button0 && button1){
				state = DEC;
			}
			else if(button0 && button1){
				state = DEP;
			}
			break;
		case wait:
			if(button0 && button1){
				state = DEP;
			}
			else if(button0 && !button1){
				state = INC;
			}
			else if(!button0 && button1){
				state = DEC;
			}
			else{
				state = wait;
			}
			break;
		case wait2:
			if(!button0 && !button1){
				state = wait;
			}
			else if(button0 && button1){
				state = DEP;
			}
			else{
				state = wait2;
			}
			break;
		default:
			break;
			
	}
	switch(state){ // State actions
		case init:
			break;
		case INC:
			if(tempC < 9){
				tempC = tempC + 1;
			}
			break;
		case DEC:
			if(tempC > 0){
				tempC = tempC - 1;
			}
			break;
		case DEP:
			tempC = 0x00;
			break;
		default:
			break;
	}			
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTC = 0x00; 

	state = init;
    /* Insert your solution below */
    while (1) {
		button0 = PINA & 0x01;
		button1 = PINA & 0x02;		
		Tick();
		PORTC = tempC;
    }
    return 1;
}
