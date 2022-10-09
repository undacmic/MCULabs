#include "MKL25Z4.h"
#include "Uart.h"


char suport_text1[] = "\rIntroduceti primul numar: ";
char suport_text2[] = "\rIntroduceti al doilea numar: ";
char suport_text3[] = "\rSuma este: ";
char suport_text4[] = "\r\nFin";

extern uint8_t c;
extern uint8_t end;
extern uint8_t numar1[100], numar2[100];

extern uint8_t write1, read1;
extern uint8_t write2, read2;

extern uint8_t complet1,complet2;

void put_string(char* data) {
	while(*data) {
				
		UART0->D = *data;
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));
				
		++data;
	}
}

uint8_t do_sum(uint8_t* first, uint8_t first_n, uint8_t* second, uint8_t second_n) {
	uint8_t carry = 0, sum_digit = 0;
	uint8_t temp;
	while (first_n > 0 && second_n > 0) {
		
		temp = first[--first_n] + second[--second_n] + carry - 2*0x30;
		sum_digit = temp % 10;
		carry = temp / 10;
		
		if(first_n >= second_n) {
			first[first_n] = sum_digit + 0x30;
		} else {
			second[second_n] = sum_digit + 0x30;
		}
	}
	return carry + 0x30;
	
}
int main()
{
	
	uint16_t i;

	UART0_Init(115200);
	complet1 = 0;
	complet2 = 0;
	while (1) 
	{
		if(complet1 == 0){ // Afisare sir premergator citirii primului numar
			put_string(suport_text1);
			complet1 = 1;
		}
		if(complet2 == 0 && complet1 == 2) { // Afisare sir premergator citirii celui de-al doilea numar
			put_string(suport_text2);
			complet2 = 1;
		}
		if(read1!=write1 && complet1!=2){ // Afisarea primului numar pe parcursul citirii caracterelor
			UART0_Transmit(numar1[read1]);
			read1++;
			read1= read1 % 100;
		}
		if(read2!=write2 && complet2!=2){ // Afisarea celui de-al doilea numar pe parcursul citirii caracterelor
			UART0_Transmit(numar2[read2]);
			read2++;
			read2= read2 % 100;
		}	
		

		
		if(complet1 == 2 && complet2 == 2){ // Calcul suma si afisarea acesteia 
			put_string(suport_text3);
			uint8_t overflow = do_sum(numar1, write1, numar2, write2);
			if(overflow != 0x30) 
				UART0_Transmit(overflow);
			if(write1 >= write2) {
				for(i=0;i<write1;i++){
					UART0_Transmit(numar1[i]);
				}
			} else {
				for(i=0;i<write2;i++){
					UART0_Transmit(numar2[i]);
				}
			}
			UART0_Transmit(0x0D);
			UART0_Transmit(0X0A);
			write1 = read1 = complet1 = 0;
			write2 = read2 = complet2 = 0;
		}
		
		if(end){
			put_string(suport_text4);
			break;
		}
		
	}
	
	return 0;
	
}