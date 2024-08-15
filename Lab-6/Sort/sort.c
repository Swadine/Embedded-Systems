#include <at89c5131.h>
#include "lcd.h"

code unsigned char start_msg[] = "  START PROGRAM  ";
code unsigned char first_inp[] = "   FIRST INPUT   ";
code unsigned char next_inp[] = "  NEXT INPUT   ";
code unsigned char sort_msg[] = "    SORTING    ";
code unsigned char completed[] = "    COMPLETED   ";
code unsigned char num_msg[] = "  NUMBER TO BE  ";
code unsigned char searched_msg[] = "    SEARCHED    ";
code unsigned char idx_msg[] = "  THE INDEX IS  ";
code unsigned char number_msg[] = "     NUMBER     ";
code unsigned char ntfnd_msg[] = "    NOT FOUND   ";

void main(){
	
	unsigned char num, target;
	unsigned char arr[5];
	int i, j, flag;
	lcd_init();
	
	P1 = 0x0F;
	lcd_cmd(0x80);
	lcd_write_string(start_msg);
	msdelay(5000);
	
	lcd_cmd(0x80);
	lcd_write_string(first_inp);
	msdelay(5000);
	
	for(i=0; i<5; i++){
		P1 = 0x0F;
		num = P1 & 0x0F;
		arr[i] = num;
		
		lcd_cmd(0x80);
		if(i != 4){
			lcd_write_string(next_inp);
		}
		else{
			lcd_write_string(sort_msg);
		}
	
		num <<= 4;
		P1 = num;
		msdelay(5000);
		
		if(i!=4){
			lcd_cmd(0x01);
		}
		else{
			lcd_cmd(0x80);
			lcd_write_string(sort_msg);
			lcd_cmd(0xC0);
			lcd_write_string(completed);
		}
			
		P1 = 0x00;
		msdelay(1000);
	
	}
	
	for(i=4; i>=1; --i){
		for(j=0; j<i; ++j){
			if( arr[j] > arr[j+1] ){
				arr[j] = arr[j] ^ arr[j+1];
				arr[j+1] = arr[j] ^ arr[j+1];
				arr[j] = arr[j] ^ arr[j+1];
			}
		}
	} 
	
	lcd_cmd(0x01);
	
	for(i=0; i<5; i++){
		P1 = 0x0F;
		P1 = (arr[i]<<4);
		msdelay(5000);
		
		P1 = 0x00;
		msdelay(1000);
	}
	
	P1 = 0x0F;
	lcd_cmd(0x80);
	lcd_write_string(num_msg);
	lcd_cmd(0xC0);
	lcd_write_string(searched_msg);
	msdelay(5000);
	target = P1 & 0x0F; // You configure any pin as F for input and any pins configured as 0 is for output
	
	lcd_cmd(0x01);
	P1 = 0x00;
	msdelay(1000);
	
	flag = 0;
	for(i=0; i<5; i++){
		if(arr[i] == target){
			flag=1;
			break;
		}
	}
	
	if(flag==1){
		lcd_cmd(0x80);
		lcd_write_string(idx_msg);
		P1 = 0x00;
		P1 = ( (++i)<<4 );
	}
	else{
		lcd_cmd(0x80);
		lcd_write_string(number_msg);
		lcd_cmd(0xC0);
		lcd_write_string(ntfnd_msg);
		P1 = 0xFF;
	}
		
	msdelay(10000);
}
