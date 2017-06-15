/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: line.h (header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: print_sensor, fw_control_motor_speed(), black_line(), calculate_pid(), fw_follow_black_line()
* Global Variables: Left_white_line, Center_white_line, Right_white_line, Kp ,Ki , Kd, error, P, I, D, PID_value, previous_error, previous_I,
  initial_motor_speed,left_motor_speed,right_motor_speed
*/

unsigned char Left_white_line = 0;
unsigned char Center_white_line = 0;
unsigned char Right_white_line = 0;
float Kp=9,Ki=0.3,Kd=0.4;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int initial_motor_speed=200,left_motor_speed,right_motor_speed;

/*
* Function Name: print_sensor()
* Input : char row, char coloumn,unsigned char channel
* Output : It will print the data on lcd screen
* Logic: It will print the data on lcd screen
* Example Call: print_sensor(1,4,23,3);
*/
void print_sensor(char row, char coloumn,unsigned char channel)
{
	
	int ADC_Value = ADC_Conversion(channel);
	lcd_print(row, coloumn, ADC_Value, 3);
}

/*
* Function Name: fw_control_motor_speed()
* Input : none
* Output : none
* Logic: It will control the motor speed
* Example Call: fw_control_motor_speed();
*/
void fw_control_motor_speed()
{
	left_motor_speed = initial_motor_speed + PID_value;
	right_motor_speed = initial_motor_speed - PID_value + 20;
	if(left_motor_speed<=0)
	{
		left_motor_speed=0;
	}
	if (right_motor_speed<=0)
	{
		right_motor_speed=0;
	}
	if(left_motor_speed>=255)
	{
		left_motor_speed=255;
	}
	if (right_motor_speed>=255)
	{
		right_motor_speed=255;
	}
	forward();
	velocity(left_motor_speed,right_motor_speed);
}

/*
* Function Name: black_line()
* Input : none
* Output : none
* Logic: It will take the white sensor value and calculate the error which is then fed to the pid functions
* Example Call: black_line();
*/
void black_line()
{
	Left_white_line = ADC_Conversion(3);
	Center_white_line = ADC_Conversion(2);
	Right_white_line = ADC_Conversion(1);
	print_sensor(1,1,3);	//Prints value of White Line Sensor1
	print_sensor(1,5,2);	//Prints Value of White Line Sensor2
	print_sensor(1,9,1);	//Prints Value of White Line Sensor3
	
	if(Left_white_line<=45 && Center_white_line<=16 && Right_white_line>46)
	{
		error=2;
	}
	else if(Left_white_line<=45 && Center_white_line>46 && Right_white_line>46)
	{
		error=1;
	}
	else if(Left_white_line<=45 && Center_white_line>46 && Right_white_line<=45)
	{
		error=0;
	}
	else if(Left_white_line>46 && Center_white_line>46 && Right_white_line<=45)
	{
		error=-1;
	}
	else if(Left_white_line>46 && Center_white_line<=45 && Right_white_line<=45)
	{
		error=-2;
	}
	else if(Left_white_line<=45 && Center_white_line<=45 && Right_white_line<=45)
	{
		{
			if(error==-2)
			{
				error=-3;
			}
			else
			{
				error=3;
			}

		}
	}
}

/*
* Function Name: calculate_pid()
* Input : none
* Output : none
* Logic: It calculates the pid value
* Example Call: calculate_pid();
*/
void calculate_pid()
{
	P = error;
	I = I + previous_I;
	D = error - previous_error;
	
	PID_value = (Kp*P) + (Ki*I) + (Kd*D);
	
	previous_I=I;
	previous_error=error;
}

/*
* Function Name: fw_follow_black_line()
* Input : none
* Output : none
* Logic: It will make the bot to follow the black line
* Example Call: fw_follow_black_line(); 
*/
void fw_follow_black_line()	
 {
	while(1)
	{				
		black_line();
		calculate_pid();
		fw_control_motor_speed();
		if ((Left_white_line+Right_white_line+Center_white_line) >= 228)
		{		//240 added
			buzzer_on();
			_delay_ms(30);
			buzzer_off();
			break;
		}
	}
	stop();
}