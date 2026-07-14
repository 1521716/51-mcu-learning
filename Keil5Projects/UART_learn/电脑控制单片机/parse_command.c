#include <stdio.h>
#include <string.h>
#include <REGX52.H>
#include "parse_command.h"

void parse_command(unsigned char *cmd)
{
	if(strstr(cmd,"LED1 ON"))
		LED1 = LED_ON;
	else if(strstr(cmd,"LED1 OFF"))
		LED1 = LED_OFF;
	else if(strstr(cmd,"LED2 ON"))
		LED2 = LED_ON;
	else if(strstr(cmd,"LED2 OFF"))
		LED2 = LED_OFF;
	else if(strstr(cmd,"STATUS"))
		printf("LED1=%s\r\nLED2=%s\r\n",LED1?"OFF":"ON",LED2?"OFF":"ON");
	else
		printf("%s\r\n","The command is error!");
}