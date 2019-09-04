#include <avr/io.h>           //--- Include Reg file of Atmega16
#include <avr/delay.h>
#include <stdlib.h>#include <stdio.h>


#include <avr/io.h> //Trengs denne?
#include <stdio.h>
#include <stdlib.h> // Abort
#include <stdio.h>
#include <avr/interrupt.h>





//--- F_CPU & BAUD RATE ---//

#define F_CPU  4915200   //--- CPU Clock Frequency
//#define F_CPU 1843200

#define BAUD 9600        //--- Transmission Baud Rate
#define URSEL
#include <UTIL/setbaud.h>

//--- Proto Type Declaration ---//
void usart_init(void);      //--- Usart Initialize
void usart_tx(unsigned char x);      //--- Usart Transmit
char usart_rx(void);        //--- Usart Receive
void usart_msg(unsigned char *c);    //--- Usart Transmit String

//--- Glodal Delecaration ---//

char tx_data;
char test; 

//--- Main Program ---//

int main(void)
{
	//usart_init();                       //--- Usart initializing
	//usart_msg("INITIALIZING USART");    //--- Send a set of String
	//usart_tx(0x0d);                     //--- Cmd to jump to next line
	//PORTA = (1 == PE1);
	//PORTA = (1 == PA0
	
	DDRA |= (1 << PE1) | (1 << PA0);   // SETTER SOM UTGANG
    PORTA &= ~(1 << PE1	);	
	
    
	//PORTA |= (1 << n);  // HIGH
	
	
	while(1)
	{
	  
	//  tx_data = usart_rx();      // test at man mottar fra pc
   //   usart_tx(tx_data);      // test at man kan sende til pc
	 /*
	  PORTA &= ~(1 << PE1	);  // LOW
	  PORTA &= ~(1 << PA0);  // LOW
	  _delay_ms(2000);
	 PORTA |= (1 << PE1);  // HIGH
	 PORTA |= (1 << PA0);  // HIGH
	*/
	
	 PORTA ^= (1 << PA0); //flip state of pin PA0
     // printf("b");                // test at printf (fdevopen) fungere
	//  _delay_ms(1000);
   //   usart_tx(0x0d);   

   _delay_ms(10000);
			
	}
	
}

//--- Proto Type Declaration ---//

void usart_init( ) //text
{
	UBRR0H = UBRRH_VALUE;                     //--- Initialize UBRR 
    UBRR0L = UBRRL_VALUE;         //--- Baud Rate 

	UCSR0B = (1<<TXEN0) | (1<<RXEN0);      //--- Transmit and Receive Enable
	UCSR0C = (1<<URSEL0)| (1<<USBS0)| (3<<UCSZ00);    //--- 8 bit data and UCSR0C is selected
	fdevopen(usart_tx,usart_rx);                        // Fdevopen to use printF
}

void usart_tx(unsigned char x)
{
	                          
	while (!(UCSR0A & (1<<UDRE0)));     //--- Check whether UDR is empty
	UDR0 = x;                 //--- Move data to UDR Data Reg
}

char usart_rx()
{
	while (!(UCSR0A & (1<<RXC0)));      //--- Check whether Receive is complete
	
	
	
	return(UDR0);                        //--- Return Data from UDR

}

void usart_msg(unsigned char *c)
{
	while (*c != 0)                     //--- Check for null
	usart_tx(*c++);                 //--- Increment the pointer
}