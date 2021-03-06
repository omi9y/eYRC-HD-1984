/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: colorSensor.h (Header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions:color_sensor_pin_config(void), color_sensor_pin_interrupt_init(void), color_sensor_pin_interrupt_init(void), ISR(INT0_vect),init_devices_color(void),
			filter_red(void), filter_green(void),filter_blue(void), color_sensor_scaling(), red_read(void), green_read(void), blue_read(void), detect_color(),
			print_color(int color).		    
* Global Variables: pulse,red,blue,green,RED,GREEN,BLUE
*/

#define __OPTIMIZE__ -O0

volatile unsigned long int pulse = 0; //to keep the track of the number of pulses generated by the color sensor
volatile unsigned long int red;       // variable to store the pulse count when read_red function is called
volatile unsigned long int blue;      // variable to store the pulse count when read_blue function is called
volatile unsigned long int green;     // variable to store the pulse count when read_green function is called
volatile unsigned long int RED, BLUE,GREEN;


/*
 * Function Name:color_sensor_pin_config()  
 * Input :  None 
 * Output :  Sets the pins of the color sensor
 * Logic: Send the required signals to the color sensor pin
 * Example Call: color_sensor_pin_config();
 */
void color_sensor_pin_config(void)
{
	DDRD  = DDRD | 0xFE; //set PD0 as input for color sensor output
	PORTD = PORTD | 0x01;//Enable internal pull-up for PORTD 0 pin
}

/*
 * Function Name:port_init_color()  
 * Input :  None 
 * Output :  initializes the ports of atmega2560
 * Logic: Send the required signals to the color sensor pin
 * Example Call: port_init_color();
 */
void port_init_color(void)
{
	lcd_port_config();//lcd pin configuration
	color_sensor_pin_config();//color sensor pin configuration
}

/*
 * Function Name: color_sensor_pin_interrupt_init()  
 * Input :  None 
 * Output :  Enables the interrupt
 * Logic:  Enables the interrupt
 * Example Call: color_sensor_pin_interrupt_init();
 */
void color_sensor_pin_interrupt_init(void) //Interrupt 0 enable
{
	cli(); //Clears the global interrupt
	EICRA = EICRA | 0x02; // INT0 is set to trigger with falling edge
	EIMSK = EIMSK | 0x01; // Enable Interrupt INT0 for color sensor
	sei(); // Enables the global interrupt
}

/*
 * Function Name: ISR(INT0_vect)
 * Input :  None 
 * Output :  ISR for color sensor
 * Logic:  ISR for color sensor
 * Example Call: Automatically called
 */
ISR(INT0_vect)
{
	pulse++; //increment on receiving pulse from the color sensor
}

/*
 * Function Name:init_devices_color(void) 
 * Input :  None 
 * Output :  Enables the interrupt
 * Logic: Enables the interrupt 
 * Example Call: init_devices_color();
 */
void init_devices_color(void)
{
	cli(); //Clears the global interrupt
	port_init_color();  //Initializes all the ports
	color_sensor_pin_interrupt_init();
	sei();   // Enables the global interrupt
}

//Filter Selection

/*
 * Function Name:filter_red()
 * Input :  None 
 * Output :  it detects the red color
 * Logic: sets s2 and s3 low  
 * Example Call: filter_red();
 */
void filter_red(void)    //Used to select red filter
{
	//Filter Select - red filter
	PORTD = PORTD & 0xBF; //set S2 low
	PORTD = PORTD & 0x7F; //set S3 low
}

/*
 * Function Name:filter_green()
 * Input :  None 
 * Output :  it detects the green color
 * Logic: sets s2 and s3 high  
 * Example Call: filter_green();
 */
void filter_green(void)	//Used to select green filter
{
	//Filter Select - green filter
	PORTD = PORTD | 0x40; //set S2 High
	PORTD = PORTD | 0x80; //set S3 High
}

/*
 * Function Name:filter_blue()
 * Input :  None 
 * Output :  it detects the blue color
 * Logic: sets s2 low and s3 high  
 * Example Call: filter_blue();
 */
void filter_blue(void)	//Used to select blue filter
{
	//Filter Select - blue filter
	PORTD = PORTD & 0xBF; //set S2 low
	PORTD = PORTD | 0x80; //set S3 High
}

/*
 * Function Name:color_sensor_scaling()
 * Input :  None 
 * Output : Color Sensing Scaling
 * Logic: sets s0  and s1 high  
 * Example Call: color_sensor_scaling();
 */
void color_sensor_scaling()		//This function is used to select the scaled down version of the original frequency of the output generated by the color sensor, generally 20% scaling is preferable, though you can change the values as per your application by referring datasheet
{
	PORTD = PORTD | 0x10; //set S0 high
	PORTD = PORTD | 0x20; //set S1 high
}

/*
 * Function Name:red_read(void)
 * Input :  None 
 * Output : to read the red pulse
 * Logic: counts the reflected pulse with delay of few ms 
 * Example Call: red_read();
 */
volatile unsigned long int red_read(void) // function to select red filter and display the count generated by the sensor on LCD. The count will be more if the color is red. The count will be very less if its blue or green.
{
	//Red
	filter_red(); //select red filter
	pulse=0; //reset the count to 0
	_delay_ms(100); //capture the pulses for 100 ms or 0.1 second
	red = pulse;  //store the count in variable called red
	return red;
}

/*
 * Function Name:green_read(void)
 * Input :  None 
 * Output : to read the green pulse
 * Logic: counts the reflected pulse with delay of few ms 
 * Example Call: green_read();
 */
volatile unsigned long int green_read(void) // function to select green filter and display the count generated by the sensor on LCD. The count will be more if the color is green. The count will be very less if its blue or red.
{
	//Green
	filter_green(); //select green filter
	pulse=0; //reset the count to 0
	_delay_ms(100); //capture the pulses for 100 ms or 0.1 second
	green = pulse;  //store the count in variable called green
	return green;
}

/*
 * Function Name:blue_read(void)
 * Input :  None 
 * Output : to read the blue pulse
 * Logic: counts the reflected pulse with delay of few ms 
 * Example Call: blue_read();
 */
volatile unsigned long int blue_read(void) // function to select blue filter and display the count generated by the sensor on LCD. The count will be more if the color is blue. The count will be very less if its red or green.
{
	//Blue
	filter_blue(); //select blue filter
	pulse=0; //reset the count to 0
	_delay_ms(100); //capture the pulses for 100 ms or 0.1 second
	blue = pulse;  //store the count in variable called blue
	return blue;
}

/*
 * Function Name:detect_color()
 * Input :  None 
 * Output : to detect the color
 * Example Call: detect_color();
 */
int detect_color() {
	int detected = 0;
	RED = red_read();
	BLUE = blue_read();
	GREEN = green_read();
	lcd_cursor(2,1);
	lcd_print(2,1,RED,3);
	lcd_print(2,6,BLUE,3);
	lcd_print(2,10,GREEN,3);
	lcd_cursor(2,13);
	if (RED > BLUE) {
		if (RED > GREEN) {
			detected = 1;
		}
		else {
			detected = 2;
		}
	} else {
		if (BLUE > GREEN) {
			detected = 3;
		}
		else {
			detected = 2;
		}
	}
	return detected;
	
}

/*
 * Function Name:print_color()
 * Input :  color
 * Output : prints the color on lcd
 * Logic: simply passes the value to be printed on lcd by calling lcd_string function from lcd header file 
 * Example Call: print_color(int color);
 */
void print_color(int color) {
	lcd_cursor(2,1);
	if (color == 1)
	lcd_string("Red");
	else if (color == 2)
	lcd_string("Green");
	else
	lcd_string("Blue");
}