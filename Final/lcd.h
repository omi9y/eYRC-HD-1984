/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: lcd.h (Header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: init_ports(), lcd_reset(), lcd_init(), lcd_wr_command(unsigned char), lcd_wr_char(char), lcd_line1(), lcd_line2(), lcd_string(char*)
* Global Variables: temp, unit, hundred, thousand, million
*/

#define RS 0
#define RW 1
#define EN 2
#define lcd_port PORTC

#define sbit(reg,bit)	reg |= (1<<bit)			
#define cbit(reg,bit)	reg &= ~(1<<bit)		

void init_ports();
void lcd_reset();
void lcd_init();
void lcd_wr_command(unsigned char);
void lcd_wr_char(char);
void lcd_line1();
void lcd_line2();
void lcd_string(char*);

unsigned int temp;
unsigned int unit;
unsigned int tens;
unsigned int hundred;
unsigned int thousand;
unsigned int million;

/*
 * Function Name: lcd_set_4bit() 
 * Input :  None 
 * Output :  Sets the lcd in 4 bit mode
 * Logic: Send the required signals to the lcd 
 * Example Call: lcd_set_4bit();
 */ 
void lcd_set_4bit()
{
	_delay_ms(1);

	cbit(lcd_port,RS);				
	cbit(lcd_port,RW);				
	lcd_port = 0x30;				
	sbit(lcd_port,EN);				
	_delay_ms(5);					
	cbit(lcd_port,EN);				

	_delay_ms(1);

	cbit(lcd_port,RS);				
	cbit(lcd_port,RW);				
	lcd_port = 0x30;				
	sbit(lcd_port,EN);				
	_delay_ms(5);					
	cbit(lcd_port,EN);				

	_delay_ms(1);

	cbit(lcd_port,RS);				
	cbit(lcd_port,RW);				
	lcd_port = 0x30;				
	sbit(lcd_port,EN);				
	_delay_ms(5);					
	cbit(lcd_port,EN);				

	_delay_ms(1);

	cbit(lcd_port,RS);				
	cbit(lcd_port,RW);				
	lcd_port = 0x20;				
	sbit(lcd_port,EN);				
	_delay_ms(5);					
	cbit(lcd_port,EN);					
}

/*
 * Function Name: lcd_init() 
 * Input : None 
 * Output :  Initializes the lcd 
 * Logic: call the functions to initialize the lcd 
 * Example Call: lcd_init();
 */ 
void lcd_init()
{
	lcd_set_4bit();
	_delay_ms(1);

	lcd_wr_command(0x28);			
	lcd_wr_command(0x01);
	lcd_wr_command(0x06);
	lcd_wr_command(0x0E);
	lcd_wr_command(0x80);
		
}

/*
 * Function Name: lcd_wr_command(unsigned char cmd) 
 * Input :  Char type data cmd 
 * Output : Command is given to the lcd  
 * Logic: Send the signals to write command on the lcd 
 * Example Call: lcd_wr_command(0x28); 
 */ 	 
void lcd_wr_command(unsigned char cmd)
{
	unsigned char temp;
	temp = cmd;
	temp = temp & 0xF0;
	lcd_port &= 0x0F;
	lcd_port |= temp;
	cbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);
	
	cmd = cmd & 0x0F;
	cmd = cmd<<4;
	lcd_port &= 0x0F;
	lcd_port |= cmd;
	cbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);
}

/*
 * Function Name: lcd_wr_char(char letter) 
 * Input :  Char type data letter 
 * Output : Data is given to the lcd  
 * Logic: Send the signals to write Data on the lcd 
 * Example Call: lcd_wr_command('A'); 
 */
void lcd_wr_char(char letter)
{
	char temp;
	temp = letter;
	temp = (temp & 0xF0);
	lcd_port &= 0x0F;
	lcd_port |= temp;
	sbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);

	letter = letter & 0x0F;
	letter = letter<<4;
	lcd_port &= 0x0F;
	lcd_port |= letter;
	sbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);
}

/*
 * Function Name: lcd_home() 
 * Input : None 
 * Output : LCD cursor moves to home position   
 * Logic: send 0x80 command to LCD to bring cursor at home position 
 * Example Call: lcd_home(); 
 */
void lcd_home()
{
	lcd_wr_command(0x80);
}

/*
 * Function Name: lcd_string(char *str) 
 * Input : Char type string str
 * Output : Prints String on LCD   
 * Logic: Write string to LCD 
 * Example Call: lcd_string("Green"); 
 */
void lcd_string(char *str)
{
	while(*str != '\0')
	{
		lcd_wr_char(*str);
		str++;
	}
}

/*
 * Function Name: lcd_cursor (char row, char column)
 * Input :  row and column
 * Output : Position the LCD cursor at "row", "column".
 * Logic: Send command signals to the lcd
 * Example Call: lcd_cursor (1,2)
 */ 
void lcd_cursor (char row, char column)
{
	switch (row) {
		case 1: lcd_wr_command (0x80 + column - 1); break;
		case 2: lcd_wr_command (0xc0 + column - 1); break;
		case 3: lcd_wr_command (0x94 + column - 1); break;
		case 4: lcd_wr_command (0xd4 + column - 1); break;
		default: break;
	}
}

/*
 * Function Name: lcd_print (char row, char coloumn, unsigned int value, int digits) 
 * Input : row, coloumn, value, digits
 * Output :  Prints the data on the lcd
 * Logic: send write signals to lcd
 * Example Call: lcd_print (1,2,23,3)
 */ 
//Function To Print Any input value upto the desired digit on LCD
void lcd_print (char row, char coloumn, unsigned int value, int digits)
{
	unsigned char flag=0;
	if(row==0||coloumn==0)
	{
		lcd_home();
	}
	else
	{
		lcd_cursor(row,coloumn);
	}
	if(digits==5 || flag==1)
	{
		million=value/10000+48;
		lcd_wr_char(million);
		flag=1;
	}
	if(digits==4 || flag==1)
	{
		temp = value/1000;
		thousand = temp%10 + 48;
		lcd_wr_char(thousand);
		flag=1;
	}
	if(digits==3 || flag==1)
	{
		temp = value/100;
		hundred = temp%10 + 48;
		lcd_wr_char(hundred);
		flag=1;
	}
	if(digits==2 || flag==1)
	{
		temp = value/10;
		tens = temp%10 + 48;
		lcd_wr_char(tens);
		flag=1;
	}
	if(digits==1 || flag==1)
	{
		unit = value%10 + 48;
		lcd_wr_char(unit);
	}
	if(digits>5)
	{
		lcd_wr_char('E');
	}
	
}


