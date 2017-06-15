/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: velocity.h (Header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: motion_pin_config (void), timer5_init(), motion_set (unsigned char Direction), forward(), back(), left(), right(), soft_right(), soft_left(),
  stop(), soft_left_2(), soft_right_2(), velocity()
* Global Variables: none
*/

#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
 * Function Name: motion_pin_config (void)
 * Input : None 
 * Output : Pins are configured 
 * Logic: set the pins
 * Example Call: motion_pin_config ();
 */ 
void motion_pin_config (void) 
{
 DDRA = DDRA | 0x0F;
 PORTA = PORTA & 0xF0;
 DDRL = DDRL | 0x18;  
 PORTL = PORTL | 0x18;
}

/*
 * Function Name: timer5_init(void) 
 * Input :  None
 * Output : Timer5 is initialized
 * Logic: Set the timer5 in 10bit PWM mode 
 * Example Call: timer5_init();
 */
void timer5_init()
{
	TCCR5B = 0x00;	
	TCNT5H = 0xFF;	
	TCNT5L = 0x01;	
	OCR5AH = 0x00;	
	OCR5AL = 0xFF;	
	OCR5BH = 0x00;	
	OCR5BL = 0xFF;	
	OCR5CH = 0x00;	
	OCR5CL = 0xFF;	
	TCCR5A = 0xA9;	
	TCCR5B = 0x0B;	
}

/*
 * Function Name: motion_set (unsigned char Direction)
 * Input : Direction 
 * Output :  robot moves in the specified direction
 * Logic: Send signals on PORTA to set robot directions  
 * Example Call: motion_set (0x06);
 */ 
void motion_set (unsigned char Direction)
{
 unsigned char PortARestore = 0;

 Direction &= 0x0F; 			
 PortARestore = PORTA; 			
 PortARestore &= 0xF0; 			
 PortARestore |= Direction; 	
 PORTA = PortARestore; 			
}

/*
 * Function Name: forward (void) 
 * Input : None
 * Output :  Robot moves forward
 * Logic: Send the signals through motion_set function 
 * Example Call: forward ();
 */ 
void forward (void)
{
  motion_set(0x06);
}

/*
 * Function Name: back (void)
 * Input : None
 * Output :  Robot moves backward
 * Logic: Send the signals through motion_set function 
 * Example Call: back ();
 */ 
void back (void)
{
  motion_set(0x09);
}

/*
 * Function Name: left (void)
 * Input : None
 * Output :  Robot rotates left
 * Logic: Send the signals through motion_set function 
 * Example Call: left ();
 */ 
void left (void)
{
  motion_set(0x05);
}

/*
 * Function Name: right (void)
 * Input : None
 * Output :  Robot rotates right
 * Logic: Send the signals through motion_set function 
 * Example Call: right ();
 */ 
void right (void) 
{
  motion_set(0x0A);
}

/*
 * Function Name: soft_left (void)
 * Input : None
 * Output :  Robot rotates left softly
 * Logic: Send the signals through motion_set function 
 * Example Call: soft_left ();
 */
void soft_left (void) 
{
 motion_set(0x04);
}

/*
 * Function Name: stop (void)
 * Input : None
 * Output :  Robot stops moving
 * Logic: Send the signals through motion_set function 
 * Example Call: stop ();
 */
void stop()
{
motion_set(0x00);
}

/*
 * Function Name: soft_right (void)
 * Input : None
 * Output :  Robot rotates right softly
 * Logic: Send the signals through motion_set function 
 * Example Call: soft_right ();
 */
void soft_right (void) //Left wheel forward, Right wheel is stationary
{
	motion_set(0x02);
}

/*
 * Function Name: soft_left_2 (void)
 * Input : None
 * Output :  Robot rotates left softly
 * Logic: Send the signals through motion_set function 
 * Example Call: soft_left_2 ();
 */
void soft_left_2 (void) //Left wheel backward, right wheel stationary
{
	motion_set(0x01);
}

/*
 * Function Name: soft_right_2 (void)
 * Input : None
 * Output :  Robot rotates right softly
 * Logic: Send the signals through motion_set function 
 * Example Call: soft_right_2 ();
 */
void soft_right_2 (void) //Left wheel stationary, Right wheel backward
{
	motion_set(0x08);
}

/*
 * Function Name: velocity (unsigned char left_motor, unsigned char right_motor) 
 * Input : left_motor & right_motor
 * Output : PWM signals are given to both the dc motors
 * Logic: Load the input data in OCR5AL & OCR5BL registers
 * Example Call: velocity (177,180);
 */ 
void velocity (unsigned char left_motor, unsigned char right_motor)
{
	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}
