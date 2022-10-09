#include "MKL25Z4.h"
#include "Uart.h"

extern char c;
extern char buffer[32];

extern int write, read;
extern int print_buffer;
extern int full;


int main()
{
	uint16_t i;
	UART0_Init(115200);
	while (1) 
	{
		if (read != write)	
		{
	
			if (buffer[read] == 0x0D)
			{
				//pt enter
				UART0_Transmit(0x0D); //Carriage Return
				UART0_Transmit(0x0A); //Line Feed
			}
			else 
				UART0_Transmit(buffer[read]);
			
			read++;
			read = read % 32;
		}
		
		if (print_buffer==1)
		{
			UART0_Transmit(0x0D); //Carriage Return
			UART0_Transmit(0x0A); //Line Feed
														
			for(i=0;i<write;i++)
			 {
				if (buffer[i] == 0x0D)
				{
					UART0_Transmit(0x0D); //Carriage Return
					UART0_Transmit(0x0A); //Line Feed
				}
				else 
					UART0_Transmit(buffer[i]);
			 }
			
			if (full==1)
				for(i=write;i<32;i++)
				 {
					if (buffer[i] == 0x0D)
					{
						//pt enter
						UART0_Transmit(0x0D); //Carriage Return
						UART0_Transmit(0x0A); //Line Feed
					}
					else 
						UART0_Transmit(buffer[i]);
				 }
			
			UART0_Transmit(0x0D); //Carriage Return
			UART0_Transmit(0x0A); //Line Feed
			
			read=write;
			print_buffer=0;
		} 
				
	}
	
	return 0;
	
}