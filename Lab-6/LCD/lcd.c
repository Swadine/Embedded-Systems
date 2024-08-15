#include <at89c5131.h>
#include "lcd.h"

code unsigned char display_msg1[]="   Shanky   ";						  //Display msg on 1st line of lcd
code unsigned char display_msg2[]="    ramdi     ";						//Display msg on 1st line of lcd

void main()
{
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);
	lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
	msdelay(4);
	lcd_write_string(display_msg2);
	while(1);		
}

#include <at89c5131.h>
#include "lch.h"

code unsigned char disp[] = "hellomsfssfafsj";

void main(){
	lcd_init();
	
}