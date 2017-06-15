/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: encoder.h (Header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: init_devices(), left_encoder_pin_config (void), right_encoder_pin_voidconfig (), port_init(), left_position_encoder_interrupt_init (void), 
  right_position_encoder_interrupt_init (void), ISR(INT5_vect), ISR(INT4_vect), linear_distance_mm(),  forward_mm(), backward_mm(), angle_rotate(unsigned int Degrees,int k),
  flag_angle_rotate(unsigned int Degrees), left_degrees(unsigned int Degrees,int flag), right_degrees(unsigned int Degrees,int flag), rotate_at_flag(),
  soft_left_degrees(unsigned int Degrees), soft_right_degrees(unsigned int Degrees), soft_left_2_degrees(unsigned int Degrees), soft_right_2_degrees(unsigned int Degrees)
* Global Variables:ShaftCountLeft, ShaftCountRight, Degrees,left_dir, right_dir 
*/

#include "velocity.h"
#include "line.h"

volatile unsigned long int ShaftCountLeft = 0; //to keep track of left position encoder
volatile unsigned long int ShaftCountRight = 0; //to keep track of right position encoder
volatile unsigned int Degrees; //to accept angle in degrees for turning

/*
 * Function Name: init_devices()
 * Input :  None
 * Output : Initializes all the pins connected to the devices
 * Logic:  Set the pins
 * Example Call: init_devices();
 */ 
void init_devices()
{
	cli(); //Clears the global interrupt
	port_init();  //Initializes all the ports
	left_position_encoder_interrupt_init();
	right_position_encoder_interrupt_init();
	sei();   // Enables the global interrupt
}

/*
 * Function Name: left_encoder_pin_config (void) 
 * Input : None
 * Output : Configures the pin 4 of PORTE as input  
 * Logic: Set the direction of the PORTE pin 4 as input for the left position encoder
 * Example Call: left_encoder_pin_config();
 */ 
void left_encoder_pin_config (void)
{
	DDRE  = DDRE & 0xEF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x10; //Enable internal pull-up for PORTE 4 pin
}

/*
 * Function Name: right_encoder_pin_config (void) 
 * Input : None
 * Output : Configures the pin 5 of PORTE as input  
 * Logic: Set the direction of the PORTE pin 5 as input for the left position encoder
 * Example Call: right_encoder_pin_config();
 */ 
void right_encoder_pin_config (void)
{
	DDRE  = DDRE & 0xDF;  //Set the direction of the PORTE 5 pin as input
	PORTE = PORTE | 0x20; //Enable internal pull-up for PORTE 5 pin
}

/*
 * Function Name: port_init() 
 * Input :  None
 * Output : Configures the ports 
 * Logic: Send the appropriate signals
 * Example Call: port_init(); 
 */ 
void port_init()
{
	motion_pin_config(); //robot motion pins config
	left_encoder_pin_config(); //left encoder pin config
	right_encoder_pin_config(); //right encoder pin config
}

/*
 * Function Name: left_position_encoder_interrupt_init () 
 * Input : None 
 * Output : Enables Interrupt INT4 for left position encoder
 * Logic: Set INT4 to trigger with falling edge
 * Example Call: left_position_encoder_interrupt_init ();
 */ 
void left_position_encoder_interrupt_init (void) //Interrupt 4 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x02; // INT4 is set to trigger with falling edge
	EIMSK = EIMSK | 0x10; // Enable Interrupt INT4 for left position encoder
	sei();   // Enables the global interrupt
}

/*
 * Function Name: right_position_encoder_interrupt_init () 
 * Input : None 
 * Output : Enables Interrupt INT5 for right position encoder
 * Logic: Set INT5 to trigger with falling edge
 * Example Call: right_position_encoder_interrupt_init ();
 */
void right_position_encoder_interrupt_init (void) //Interrupt 5 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x08; // INT5 is set to trigger with falling edge
	EIMSK = EIMSK | 0x20; // Enable Interrupt INT5 for right position encoder
	sei();   // Enables the global interrupt
}

/*
 * Function Name: ISR(INT5_vect) 
 * Input : pulses from the encoder
 * Output :  increment right shaft position count
 * Logic: increment right shaft position count on detecting a pulse from the encoder 
 * Example Call:  None
 */ 
ISR(INT5_vect)
{
	ShaftCountRight++;  //increment right shaft position count
}


/*
 * Function Name: ISR(INT4_vect) 
 * Input : pulses from the encoder
 * Output :  increment left shaft position count
 * Logic: increment left shaft position count on detecting a pulse from the encoder 
 * Example Call:  None
 */
ISR(INT4_vect)
{
	ShaftCountLeft++;  //increment left shaft position count
}

/*
 * Function Name: linear_distance_mm(unsigned int DistanceInMM)
 * Input : Distance to be travelled in mm
 * Output : Firebird V moves a specified distance  
 * Logic: The slotted disc pins are counted
 * Example Call: linear_distance_mm(50);
 */ 
void linear_distance_mm(unsigned int DistanceInMM)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = DistanceInMM / 5.338; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
	
	ShaftCountRight = 0;
	while(1)
	{
		if(ShaftCountRight > ReqdShaftCountInt)
		{
			break;
		}
	}
	stop(); //Stop robot
}

/*
 * Function Name: forward_mm(unsigned int DistanceInMM)
 * Input :  Distance to be travelled in mm
 * Output :  forward movement
 * Logic: Call forward function and linear_distance_mm 
 * Example Call: forward_mm(50);
 */ 
void forward_mm(unsigned int DistanceInMM)
{
	forward();
	linear_distance_mm(DistanceInMM);
}

/*
 * Function Name: backward_mm(unsigned int DistanceInMM)
 * Input :  Distance to be travelled in mm
 * Output :  backward movement
 * Logic: Call back function and linear_distance_mm 
 * Example Call: backward_mm(50);
 */ 
void backward_mm(unsigned int DistanceInMM) {
	back();
	linear_distance_mm(DistanceInMM);
}

/*
 * Function Name: angle_rotate(unsigned int Degrees,int k)
 * Input :  Angle by which the robot has to rotate
 * Output : Firebird V rotates by specified degrees
 * Logic:  The slotted disc pins are counted
 * Example Call: angle_rotate(85,3);
 */ 
void angle_rotate(unsigned int Degrees,int k)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
	ShaftCountRight = 0;
	ShaftCountLeft = 0;

	while (1)
	{
		
		if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt) | ADC_Conversion(k) > 55)
		break;
	}


	stop(); //Stop robot
}

/*
 * Function Name: angle_rotate(unsigned int Degrees)
 * Input :  Angle by which the robot has to rotate
 * Output : Firebird V rotates by specified degrees
 * Logic:  The slotted disc pins are counted
 * Example Call: angle_rotate(85);
 */
void flag_angle_rotate(unsigned int Degrees)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
	ShaftCountRight = 0;
	ShaftCountLeft = 0;

	while (1)
	{
		if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt))
		break;
	}


	stop(); //Stop robot
}

/*
 * Function Name: left_degrees(unsigned int Degrees,int flag)
 * Input :  Angle by which the robot has to rotate left
 * Output : Firebird V rotates left by specified degrees
 * Logic:  The slotted disc pins are counted 
 * Example Call: left_degrees(85,1)
 */ 
void left_degrees(unsigned int Degrees,int flag)
{
	
	forward_mm(40);
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	left(); //Turn left
	_delay_ms(300);
	
	if(flag==0){
		angle_rotate(Degrees,3);		//normal rotation
	}
	else{
		flag_angle_rotate(Degrees);		//rotation at flag
	}
	
	buzzer_on();
	_delay_ms(50);
	buzzer_off();

	//adjust_bot(Left_white_line,Center_white_line,Right_white_line);

}

/*
 * Function Name: right_degrees(unsigned int Degrees,int flag)
 * Input :  Angle by which the robot has to rotate right
 * Output : Firebird V rotates right by specified degrees
 * Logic:  The slotted disc pins are counted 
 * Example Call: right_degrees(85,1)
 */
void right_degrees(unsigned int Degrees,int flag)
{
	
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	forward_mm(50);
	right(); //Turn left
	_delay_ms(300);
	if(flag==0){
		angle_rotate(Degrees,1);		//normal rotation
	}
	else{
		flag_angle_rotate(Degrees);		//rotation at flag
	}
	buzzer_on();
	_delay_ms(50);
	buzzer_off();


	//adjust_bot(Left_white_line,Center_white_line,Right_white_line);

}

/*
 * Function Name: rotate_at_flag() 
 * Input : None
 * Output : Brings the robot in front of the flag to sense its color
 * Logic: perform proper rotations and movements 
 * Example Call:  rotate_at_flag();
 */ 
void rotate_at_flag() {
	velocity(180,180);
	left_degrees(88,1);//105
	forward_mm(20);//30
	velocity(180,180);
	right_degrees(195,1);//195/178
	forward_mm(5);//19
	_delay_ms(500);
	stop();
	velocity(255,255);	
}

/*
 * Function Name: soft_left_degrees(unsigned int Degrees)
 * Input :  Angle by which the robot has to rotate softly left
 * Output : Firebird V rotates softly left by specified degrees
 * Logic:  The slotted disc pins are counted 
 * Example Call: soft_left_degrees(85)
 */
void soft_left_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left(); //Turn soft left
	Degrees=Degrees*2;
	angle_rotate(Degrees,3);
}

/*
 * Function Name: soft_right_degrees(unsigned int Degrees)
 * Input :  Angle by which the robot has to rotate softly right
 * Output : Firebird V rotates softly right by specified degrees
 * Logic:  The slotted disc pins are counted 
 * Example Call: soft_right_degrees(85)
 */
void soft_right_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right(); //Turn soft right
	Degrees=Degrees*2;
	angle_rotate(Degrees,1);
}

/*
 * Function Name: soft_left_2_degrees(unsigned int Degrees)
 * Input :  Angle by which the robot has to rotate softly left
 * Output : Firebird V rotates softly left by specified degrees
 * Logic:  The slotted disc pins are counted 
 * Example Call: soft_left_2_degrees(85)
 */
void soft_left_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left_2(); //Turn reverse soft left
	Degrees=Degrees*2;
	angle_rotate(Degrees,3);
}

/*
 * Function Name: soft_right_2_degrees(unsigned int Degrees)
 * Input :  Angle by which the robot has to rotate softly right
 * Output : Firebird V rotates softly right by specified degrees
 * Logic:  The slotted disc pins are counted 
 * Example Call: soft_right_2_degrees(85)
 */
void soft_right_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right_2(); //Turn reverse soft right
	Degrees=Degrees*2;
	angle_rotate(Degrees,1);
}