#include <at89c5131.h>
#include "lcd.h"

code unsigned char enter_password[] = "Enter Password:";
code unsigned char correct_password[] = "Correct Password";
code unsigned char wrong_password[] = "Wrong Password";
code unsigned char access[] = "Access Granted";
code unsigned char denied[] = "Access Denied";
code unsigned char keys[4][4] = {{'1', '2', '3', 'A'},
                                 {'4', '5', '6', 'B'},
                                 {'7', '8', '9', 'C'},
                                 {'*', '0', '#', 'D'}
                                };

void main(){
	unsigned char password[8] = "15A8*D6#";
    unsigned char inp[8] = "";
    unsigned char num, i, j, key, flag = 1, count = 0;

    lcd_init();  
	lcd_cmd(0x80);							
	lcd_write_string(enter_password);

    for(i=0; i<8; i++){
        lcd_cmd(0xC0);
        lcd_write_string(inp);

        P3 = 0x0F;
        while(1){
            num = P3 & 0x0F;
            while(num != 0x0F){  // Checks for last key still pressed
                num = P3 & 0x0F;
                msdelay(1);
            }
            while(num == 0x0F){  // Checks if new key is pressed
                num = P3 & 0x0F; 
                msdelay(1);
            }
            msdelay(20); // Debounce
            num = P3 & 0x0F;
            if(num != 0x0F){
                break;
            }
        }

        for(j=4; j<8; j++){
            P3 = (0xFF) - (1<<j);
            num = P3 & 0x0F;
            count = 0;
            if(num != 0x0F){
                while(num & 1){
                    num >>= 1;
                    count++;
                }
                key = keys[3-count][j-4];
                break;
            }
        }

        inp[i] = key;
    }
		
	msdelay(300);

    for(i=0; i<8; i++){
        if(inp[i] != password[i]){
            flag = 0; 
            break;
        }
    }

    if(flag){
        lcd_cmd(0x80);
        lcd_write_string(correct_password);
        lcd_cmd(0xC0);
        lcd_write_string(access);
    }
    else{
        lcd_cmd(0x80);
        lcd_write_string(wrong_password);
        lcd_cmd(0xC0);
        lcd_write_string(denied);
    }

    msdelay(10000);
}

