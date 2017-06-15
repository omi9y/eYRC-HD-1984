/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: adc.h (Header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: lcd_port_config (void), adc_pin_config (void), adc_init(), ADC_Conversion(unsigned char Ch), 
* Global Variables: none
*/


 /*
 * Function Name: lcd_port_config (void)
 * Input : None         
 * Output : Configured the lcd
 * Logic: Function to configure LCD port
 * Example Call: lcd_port_config();
 */ 
void lcd_port_config (void)
{
	DDRC = DDRC | 0xF7; 
	PORTC = PORTC & 0x80;
}

/*
 * Function Name: adc_pin_config (void) 
 * Input : None
 * Output : Configures the lcd port
 * Logic: Function to configure the adc pins
 * Example Call: adc_pin_config ();
 */ 
void adc_pin_config (void)
{
	DDRF = 0x00;
	PORTF = 0x00;
	DDRK = 0x00;
	PORTK = 0x00;
}

/*
 * Function Name: adc_init() 
 * Input :  None
 * Output :  Initializes the adc
 * Logic: Function to initialize the adc
 * Example Call: adc_init();
 */ 
void adc_init()
{
	ADCSRA = 0x00;
	ADCSRB = 0x00;		
	ADMUX = 0x20;		
	ACSR = 0x80;
	ADCSRA = 0x86;		
}

/*
 * Function Name: ADC_Conversion(unsigned char Ch)
 * Input : Analog data
 * Output :  Digital data
 * Logic:  Converts analog data into digital data 
 * Example Call:  ADC_Conversion('2');
 */ 
unsigned char ADC_Conversion(unsigned char Ch)
{
	unsigned char a;
	if(Ch>7)
	{
		ADCSRB = 0x08;
	}
	Ch = Ch & 0x07;
	ADMUX= 0x20| Ch;
	ADCSRA = ADCSRA | 0x40;		
	while((ADCSRA&0x10)==0);	
	a=ADCH;
	ADCSRA = ADCSRA|0x10; 
	ADCSRB = 0x00;
	return a;
}