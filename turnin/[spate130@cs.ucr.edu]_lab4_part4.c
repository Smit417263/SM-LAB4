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

enum States{lock, wait, wait2, release, release2, unlock} state;

unsigned char tempB;
unsigned char buttonH;
unsigned char buttonX;
unsigned char buttonY;
unsigned char buttonIn;


void Tick(){
	
	switch(state){ 
		case lock:
			if(buttonIn){
				state = lock;
			}
			if(!buttonX && !buttonY && buttonH && !buttonIn){
				state = wait;
			}
			else{
				state = lock;
			}
			break;
		case wait:
			if(!buttonX && !buttonY && buttonH && !buttonIn){
				state = wait;
			}
			else if(!buttonX && !buttonY && !buttonH && !buttonIn){
				state = release;
			}
			else{
				state = lock;
			}
			break;
		case wait2:
			if(!buttonX && !buttonY && !buttonH && !buttonIn){
				state = release2;
			}
			else if(!buttonX && !buttonY && !buttonH && buttonIn){
				state = lock;
			}
			else if(!buttonX && !buttonY && buttonH && !buttonIn){
				state = wait2;
			}
			else{
				state = unlock;
			}
			break;

		case release:
			if(!buttonX && !buttonY && !buttonH && !buttonIn){
				state = release;
			}
			else if(!buttonX && buttonY && !buttonH && !buttonIn){
				state = unlock;
			}
			else{
				state = lock;
			}
			break;
		case unlock:
			if(!buttonX && !buttonY && !buttonH && buttonIn){
				state = lock;
			}
			else{
				state = unlock;
			}
			break;
		case release2:
			if((!buttonX && !buttonY && !buttonH && buttonIn) || (!buttonX && buttonY && !buttonH && !buttonIn)){
				state = lock;
			}
			else if(!buttonX && !buttonY && !buttonH && !buttonIn){
				state = release2;
			}
			else{
				state = unlock;
			}

			break;
		default:
			break;
	}
	switch(state){ 
		case lock:
			tempB = 0x00;
			break;
		case wait:
			break;
		case wait2:
			break;
		case release2:
			break;
		case release:
			break;
		case unlock:
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

	state = lock;
    /* Insert your solution below */
    while (1) {		
		buttonX = PINA & 0x01;
		buttonY = PINA & 0x02;
		buttonH = PINA & 0x04;
		buttonIn = PINA & 0x80;
	
	        Tick();
		PORTB = tempB;
    }
    return 1;
}
