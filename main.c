#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <wiringPi.h>
#include "main.h"

// wiring pi numbering GPIO14 = wiring pi 15
#define SENSOR 15


//--------------------------------------------------
// main entry
//--------------------------------------------------
int main(int argc, char * argv[])
{
	int   status = 1;
	char  txt[500];

	if (argc != 3)
	{
		printf("USAGE: alarmsensor ip-address port-nr\n");
		return 1;
	}

	if (wiringPiSetup() == -1)
	{
		printf("problem with the wiring pi lib\n");
		return 1;
	}

	pinMode(SENSOR, INPUT);

	while(1)
	{
		if (digitalRead(SENSOR) == 1)
		{
			sprintf(txt,"/home/pi/netsend/sendalarm %s %s ALARM", argv[1], argv[2]);
			printf("%s\n",txt);
			system(txt);
		}
		usleep(300000); // wait 0.3 seconds.
	}


    return status ;
}

