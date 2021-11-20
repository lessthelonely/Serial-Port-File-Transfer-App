#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BAUDRATE B9600
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
#define BIT(n) 1 << n
#define MAX_SIZE 255
#define MAX_FRAME_SIZE 1500 /*ASK TEACHER-->searched frame size tcp/ip for this value*/
#define MAX_SIZE_ALLOC      16000           /* Max size for the vector. always must be higher than (FRAME_SIZE-10)*2 */ 
#define FRAME_SIZE          400  

#define FLAG 0x7E

#define A_E 0x03 //Comandos do Emissor e Respostas do Receptor
#define A_R 0x01 //Comandos do Receptor e Respostas do Emissor

#define C_SET 0x03
#define C_DISC 0x0B
#define C_UA 0x07
#define C_RR_ONE 0x85
#define C_RR_ZERO 0x05
#define C_REJ_ONE 0x11
#define C_REJ_ZERO 0x01
#define C_I_ONE 0x40
#define C_I_ZERO 0x00

#define BCC_SET (A_E^C_SET) //SET is always sent by emissor
#define BCC_UA_E (A_E^C_UA)
#define BCC_UA_R (A_R^C_UA)
#define BCC_DISC_E (A_E^C_DISC)
#define BCC_DISC_R (A_R^C_DISC)
#define BCC_C_I_ONE (A_E^C_I_ONE)
#define BCC_C_I_ZERO (A_E^C_I_ZERO)
#define BCC_RR_ONE (A_E^C_RR_ONE)
#define BCC_RR_ZERO (A_E^C_RR_ZERO)
#define BCC_REJ_ONE (A_E^C_REJ_ONE)
#define BCC_REJ_ZERO (A_E^C_REJ_ZERO)

#define ESC 0x7D
#define FLAG_FOUND 0x5E    //FLAG ^ 0x20
#define ESC_FOUND 0x5D  //ESC ^ 0x20

#define TRANSMITTER 0
#define RECEIVER 1

#define CTRL_DATA 1
#define CTRL_START 2
#define CTRL_END 3

#define T_FILE_SIZE         0
#define T_FILE_NAME         1

#define SWITCH(s)           !s

#endif