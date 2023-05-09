#include "../_headers_/tm4c123gh6pm.h"
#include "../_headers_/UART_Functions.h"
#include "../_headers_/StringProcessing.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

char gps_dump[100];
char GPGLL[75];
char GPGSV[75];
char GPGGA[75];
bool GPGGA_Fix;
char GPRMC[75];
char GPVTG[75];

float longitude;
float latitude;

int main(void)
 {

    GPGGA_Fix = false;

    UART1_Init();

    Reset_Fields();
    memset(gps_dump,0,100);

    while(1)
    {
            UART1_InString(gps_dump,100);
            Message_Classifier(gps_dump);
        if(GPGGA_Fix)
        {
            longitude = Extract_Longitude(GPGGA);
            latitude = Extract_Latitude(GPGGA);
        }
    }
}
