#include <at89c5131.h>
#include "lcd.h"

sbit INP = P3^4;
sbit ON = P1^0;

code unsigned char start[] = "Start StopWatch";
code unsigned char counting[] = "    YES...?    ";

void update_lcd(unsigned int* t, unsigned char *s);
void timerDelay(void);

void main(void){

    unsigned int time;
    unsigned char time_string[] = "     00:00     ";

	while(1){
				lcd_init();
        lcd_cmd(0x80);
        lcd_write_string(start);
        lcd_cmd(0xC0);
        lcd_write_string(time_string);

        while(ON == 0);

        lcd_cmd(0x80);
        lcd_write_string(counting);

        time = 0;
        TMOD = 0x01;

        while(ON){
            timerDelay();
            time++;
            update_lcd(&time, time_string);
        }
        msdelay(2000);
				time_string[5] = '0';
				time_string[6] = '0';
				time_string[8] = '0';
				time_string[9] = '0';
    }
}

void timerDelay(void){
    TH0 = 0xFF;
    TL0 = 0xC4;
    TR0 = 1;
    while(TF0 == 0); // Waits for one second
    TR0 = 0;
    TF0 = 0;
}

void update_lcd(unsigned int* t, unsigned char *s){
    s[5] = (((*t) / 60)/10) + '0';
    s[6] = (((*t) / 60)%10) + '0';
    s[8] = (((*t) % 60)/10) + '0';
    s[9] = (((*t) % 60)%10) + '0';
    lcd_cmd(0xC0);
    lcd_write_string(s);
}
	