ORG 00H
LJMP MAIN

ORG 100H
MAIN:
MOV P0, #00H
MOV P1, #0FH
CALL MUSIC
HERE: SJMP HERE

ORG 130H
MUSIC:
MOV A, P1
ANL A, #0FH
CJNE A, #01H, RE
SA: 
CPL P0.7
CALL DELAY_255
JMP MUSIC

RE:
CJNE A, #03H, GA
CPL P0.7
CALL DELAY_290
JMP MUSIC

GA:
CJNE A, #07H, MA
CPL P0.7
CALL DELAY_325
JMP MUSIC

MA:
CPL P0.7
CALL DELAY_345
JMP MUSIC

DELAY_255:
PUSH 00H 
PUSH 01H 
MOV R0, #43  
D_255_2: MOV R1, #44  
D_255_1: DJNZ R1, D_255_1 
DJNZ R0, D_255_2 
POP 01H 
POP 00H 
RET 

DELAY_290:
PUSH 00H
PUSH 01H
MOV R0, #41
D_290_2: MOV R1, #40 
D_290_1: DJNZ R1, D_290_1 
DJNZ R0, D_290_2 
POP 01H
POP 00H
RET

DELAY_325:
PUSH 00H
PUSH 01H
MOV R0, #38
D_325_2: MOV R1, #39 
D_325_1: DJNZ R1, D_325_1 
DJNZ R0, D_325_2 
POP 01H
POP 00H
RET

DELAY_345:
PUSH 00H
PUSH 01H
MOV R0, #38
D_345_2: MOV R1, #36  
D_345_1: DJNZ R1, D_345_1 
DJNZ R0, D_345_2 
POP 01H
POP 00H
RET

END