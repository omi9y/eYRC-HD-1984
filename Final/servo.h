/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: armMovement.h (Header File)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: servo1_pin_config (void), servo2_pin_config (void), timer1_init(void), servo_1(unsigned char degrees), servo_2(unsigned char degrees),
  place_block(), place_to_sort(), pick_block(int angle), pick_at_sort(), drop_weight() 
* Global Variables: i,grip_switch
*/


#include "buzzer.h"
unsigned char i = 0;
unsigned char grip_switch = 0x40;

/*
 * Function Name: servo1_pin_config (void) 
 * Input :  None
 * Output : servo1 pins are configured 
 * Logic:  make PORTB 5 pin output
 * Example Call: servo1_pin_config ();
 */ 
void servo1_pin_config (void)
{
 DDRB  = DDRB | 0x20;  //making PORTB 5 pin output
 PORTB = PORTB | 0x20; //setting PORTB 5 pin to logic 1
}

/*
 * Function Name: servo2_pin_config (void) 
 * Input :  None
 * Output : servo2 pins are configured 
 * Logic:  make PORTB 6 pin output
 * Example Call: servo2_pin_config ();
 */ 
void servo2_pin_config (void)
{
 DDRB  = DDRB | 0x40;  //making PORTB 6 pin output
 PORTB = PORTB | 0x40; //setting PORTB 6 pin to logic 1
 DDRL  = DDRL | 0xBF;  //making PORTL 6 pin input
 PORTL = PORTL | 0x40; //PORTL 6 internal pull-up enabled
}

/*
 * Function Name: timer1_init(void) 
 * Input :  None
 * Output : Timer1 is initialized
 * Logic: Set the timer1 in 10bit PWM mode 
 * Example Call: timer1_init();
 */
//TIMER1 initialization in 10 bit fast PWM mode  
//prescale:256
// WGM: 7) PWM 10bit fast, TOP=0x03FF
// actual value: 52.25Hz 
void timer1_init(void)
{
 TCCR1B = 0x00; //stop
 TCNT1H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
 TCNT1L = 0x01;	//Counter low value to which OCR1xH value is to be compared with
 OCR1AH = 0x03;	//Output compare Register high value for servo 1
 OCR1AL = 0xFF;	//Output Compare Register low Value For servo 1
 OCR1BH = 0x03;	//Output compare Register high value for servo 2
 OCR1BL = 0xFF;	//Output Compare Register low Value For servo 2
 OCR1CH = 0x03;	//Output compare Register high value for servo 3
 OCR1CL = 0xFF;	//Output Compare Register low Value For servo 3
 ICR1H  = 0x03;	
 ICR1L  = 0xFF;
 TCCR1A = 0xAB; /*{COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0}
 					For Overriding normal port functionality to OCRnA outputs.
				  {WGM11=1, WGM10=1} Along With WGM12 in TCCR1B for Selecting FAST PWM Mode*/
 TCCR1C = 0x00;
 TCCR1B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
}

/*
 * Function Name: servo_1(unsigned char degrees)
 * Input : char type data degrees 
 * Output : Servo motor1 rotates upto the specified degree 
 * Logic: Give the required angle and load it in OCR1AL
 * Example Call: servo_1(90);
 */ 
void servo_1(unsigned char degrees)  
{
 float PositionPanServo = 0;
  PositionPanServo = ((float)degrees / 1.86) + 35.0;
 OCR1AH = 0x00;
 OCR1AL = (unsigned char) PositionPanServo;
}

/*
 * Function Name: servo_2(unsigned char degrees)
 * Input : char type data degrees 
 * Output : Servo motor2 rotates upto the specified degree 
 * Logic: Give the required angle and load it in OCR1BL
 * Example Call: servo_2(90);
 */ 
void servo_2(unsigned char degrees)
{
 float PositionTiltServo = 0;
 PositionTiltServo = ((float)degrees / 1.86) + 35.0;
 OCR1BH = 0x00;
 OCR1BL = (unsigned char) PositionTiltServo;
}

/*
 * Function Name: place_block() 
 * Input :  None
 * Output : Places a block on the ground
 * Logic: Rotate the motor upto 84 degree
 * Example Call: place_block();
 */ 
void place_block()
{
	for (i = 160; i > 84; i--)
	{
		servo_1(i);
		_delay_ms(60);
	}
	servo_2(100);
	_delay_ms(500);
	for (i = 84; i < 130; i++)
	{
		servo_1(i);
		_delay_ms(30);
	}
	servo_2(120);
}

/*
 * Function Name: place_to_sort() 
 * Input :  None
 * Output : Places a block in the sorting area
 * Logic: Rotate the motor upto 84 degree
 * Example Call: place_to_sort();
 */ 
void place_to_sort()
{
	for (i = 160; i > 84; i--)
	{
		servo_1(i);
		_delay_ms(30);
	}
	servo_2(85);
	_delay_ms(500);
	for (i = 84; i < 130; i++)
	{
		servo_1(i);
		_delay_ms(30);
	}
}

/*
 * Function Name: pick_block(int angle) 
 * Input : angle
 * Output : Picks a block 
 * Logic: Rotate the motor upto the required angle 
 * Example Call: pick_block(87);
 */ 
void pick_block(int angle)
{
	for (i = 130; i > angle; i--)
	{
		servo_1(i);
		_delay_ms(30);
	}
	 i=120;
	 while(grip_switch == 0x40)
	 {
		 if (i == 45){
			 buzzer_off();
			break;
		 }			
		 servo_2(i);
		 _delay_ms(45);
		 i--;
		 grip_switch = PINL;
		 grip_switch = grip_switch & 0x40;
		
	 }
	  buzzer_on();
	 _delay_ms(40);
	buzzer_off();
	for (i = angle; i < 160; i++)
	{
		servo_1(i);
		_delay_ms(25);
	}
}

/*
 * Function Name: pick_at_sort()
 * Input : None
 * Output : Picks a block at sorting area
 * Logic: Rotate the motor 
 * Example Call: pick_at_sort();
 */ 
void pick_at_sort()
{
	for (i = 130; i > 86; i--)
	{
		servo_1(i);
		_delay_ms(30);
	}
	i=90;
	while(grip_switch == 0x40)
	{
		if (i == 55){
			buzzer_off();
			break;
		}
		servo_2(i);
		_delay_ms(45);
		i--;
		grip_switch = PINL;
		grip_switch = grip_switch & 0x40;
		
	}
	buzzer_on();
	_delay_ms(40);
	buzzer_off();
	for (i = 86; i < 160; i++)
	{
		servo_1(i);
		_delay_ms(25);
	}
}

/*
 * Function Name: drop_weight()
 * Input : None
 * Output : drops a weight block in the deposition zone
 * Logic: Rotate the motors 
 * Example Call: drop_weight();
 */ 
void drop_weight()
{
	for (i = 160; i > 115; i--)
	{
		servo_1(i);
		_delay_ms(70);
	}
	servo_2(120);
	_delay_ms(100);
	for (i = 108; i < 160; i++)
	{
		servo_1(i);
		_delay_ms(30);
	}
}
