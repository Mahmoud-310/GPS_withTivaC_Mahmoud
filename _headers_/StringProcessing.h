#include <string.h>
#include <stdio.h>
#include <stdbool.h>

extern char gps_dump[100];
extern char GPGLL[75];
extern char GPGSV[75];
extern char GPGGA[75];
extern char GPRMC[75];
extern char GPVTG[75];
extern bool GPGGA_Fix;

void Reset_Fields(void)
{
	memset(GPGLL,0,75);
	memset(GPGSV,0,75);
	memset(GPGGA,0,75);
	memset(GPRMC,0,75);
	memset(GPVTG,0,75);
}

void Message_Classifier(char* gps_dump)
{
	if(strncmp(gps_dump,"$GPGLL",6)==0)
	{
		strcpy(GPGLL,gps_dump);
	}
	else if (strncmp(gps_dump,"$GPGSV",6)==0)
	{
		strcpy(GPGSV,gps_dump);
	}
	else if (strncmp(gps_dump,"$GPGGA",6)==0)
	{
		strcpy(GPGGA,gps_dump);

		if(GPGGA[44]=='1')
		{
		    GPGGA_Fix = true;
		}
	}

	else if (strncmp(gps_dump,"$GPRMC",6)==0)
	{
		strcpy(GPRMC,gps_dump);
	}
	else if (strncmp(gps_dump,"$GPVTG",6)==0)
	{
		strcpy(GPVTG,gps_dump);
	}
	else
	{
		return;
	}
}

//%ID   ,UTC TIME  ,LATITUDE , ,Longitude ,  
//012345678901234567890123456789012345678901
//$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18
float Extract_Latitude(char *GPGGA_Sequence)
{
	float latitude  = 0;
	int i;
	for(i = 0; i<10;i++)
	{
		if(i==4) continue;
		
		latitude*=10;
		latitude+=(GPGGA[17+i]-48);
	}
	
	latitude/=10000000;
	latitude = (int)latitude + (latitude-(int)latitude)*10/6;
	return latitude;
}

float Extract_Longitude(char *GPGGA_Sequence)
{
    float longitude  = 0;
    int i;
    for(i = 0; i<11;i++)
    {
        if(i==5) continue;

        longitude*=10;
        longitude+=(GPGGA[30+i]-48);
    }

    longitude/=10000000;
    longitude = (int)longitude+(longitude-(int)longitude)*10/6;
    return longitude;
}
