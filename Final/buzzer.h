/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: buzzer.h (Header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: buzzer_pin_config(), buzzer_on(), buzzer_off()
* Global Variables: none
*/

/*
 * Function Name: buzzer_pin_config() 
 * Input :  None
 * Output :  Configures the pins connected to buzzer
 * Logic: DDRC pin 3 is configured as output
 * Example Call: buzzer_pin_config();
 */ 
void buzzer_pin_config(){
	
	DDRC = DDRC | 0x08;
	PORTC = PORTC & 0xF7;	
}

/*
 * Function Name: buzzer_on()
 * Input : None
 * Output : Turns on the buzzer 
 * Logic: Setting the pin 3 of port C to high
 * Example Call: buzzer_on();
 */ 
void buzzer_on(){
	
	PORTC = 0x08;
}

/*
 * Function Name:  buzzer_off()
 * Input :  None 
 * Output :  Turns off the buzzer  
 * Logic: Reset the pin 3 of port C to high 
 * Example Call: buzzer_off();
 */ 
void buzzer_off(){
	PORTC = 0x00;
}
