/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta
* Filename: ImplementationFile.c (C file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: detect_third_waste()
* Global Variables: value, sharp
*/

#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>							//calling math header file for using math functions
#include "adc.h"							//calling adc header file
#include "colorsensor.h"					//calling colorsensor header file
#include "encoder.h"						//calling encoder header file
#include "lcd.h"							//calling lcd header file
#include "servo.h"							//calling servo header file
#include "node.h"							//calling node header file


/*
* Function Name: detect_third_waste()
* Input : none
* Output :return values
* Logic: It is used to detect the third block as it is mutually exclusive
* Example Call: detect_third_waste();
*/
int detect_third_waste(){
	if (sortedFlag[0] == 1 && sortedFlag[1] == 2) {
		sortedFlag[2] = 3;
		return 3;
	} else if (sortedFlag[0] == 2 && sortedFlag[1] == 3) {
		sortedFlag[2] = 1;
		return 1;
	} else {
		sortedFlag[2] = 2;
		return 2;
	}			
}


/*Main function in which all the function are called from different header files*/
int main(void)
{
	//Initializes all the pins from different header files and working of each function is explained in their respective header file
	init_devices_color();
	lcd_set_4bit();
	color_sensor_scaling();
	init_devices();
	lcd_port_config ();
	lcd_init();
	buzzer_pin_config();
	motion_pin_config ();
	timer5_init();
	adc_pin_config ();
	adc_init();
	servo1_pin_config();
	servo2_pin_config();
	timer1_init();
	
	_delay_ms(150);
	/************************FIRST RUN*******************************/
	node0_0(4);		//initial 180 degrees turn
	node0_0(1);
	node_m1_0(2);		//goes forward
	node_m2_0(1);	
	node_m1_0(3);
	forward_mm(30);		
	node0_0(0);
	velocity(180,180);
	node_0_1(0,1);
	node_0_1(1,0);
	node_m1_1(0,1);			//comes back
	fw_follow_black_line();
	
	/************************SECOND RUN**********************************/
	
		
		node0_0(5);
		node_m1_0(2);		//goes forward
		node_m2_0(1);
		node_m1_0(3);
		forward_mm(30);	
		node0_0(0);
	
		if(sortedFlag[1] == b_flag){
			buzzer_on();
			_delay_ms(200);
			buzzer_off();
			node_0_1(0,0);
			left_degrees(176,1);
			fw_follow_black_line();	
		}
		else if(sortedFlag[1] == c_flag){
			node_0_1(1,0);
			node_m1_1(0,0);
			node_0_1(2,0);
		}
		else{
			node_0_1(2,0);
			node_1_1(2);
			node_2_1(0);
			node_0_1(2,0);			//comes back
		}
	
	/************************THIRD RUN**********************************************/
	node0_0(6);
	
		if(detect_third_waste() == b_flag){
			buzzer_on();
			_delay_ms(200);
			buzzer_off();
			node_0_1(0,0);
		}
		else if(detect_third_waste() == c_flag){
			node_0_1(1,0);
			node_m1_1(0,0);
		}
		else{
			node_0_1(2,0);
			node_1_1(2);
			node_2_1(0);			//comes back
		}
		
	/**********************************************************************************/
	//Continuous Buzzer Beep........	
	buzzer_on();
	_delay_ms(6000);
	buzzer_off();
	return 0;
}