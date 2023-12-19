/*
* dht.h
*
* Created: 07/12/2023 18:13:53
*  Author: $RHEK00-BS9TAG427UBC
*/


#ifndef DHT_H_
#define DHT_H_
#define F_CPU 1000000UL
#include "util/delay.h"

void initDHT();
void Request();
void Response();
void storeData();
void DisplaytData();
void displayTemperatureAndHumidity();
uint8_t Receive_data();

#define DHT11_PIN 6
uint8_t receivedByte=0,humidityHigh,humidityLow,temperatureHigh,temperatureLow,CheckSum;

void Request()					/* Microcontroller send start pulse or request */
{
	DDRD |= (1<<DHT11_PIN);  //output
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(20);				/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);	/* set to high pin */
}
void Response()					/* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);  //now the pin is input
	while(PIND & (1<<DHT11_PIN)); //wait as long as the pin is high
	while((PIND & (1<<DHT11_PIN))==0); //wait as long as it is low as this is just a response
	while(PIND & (1<<DHT11_PIN)); //same shit
}
uint8_t Receive_data()			/* receive data */ /* check received bit 0 or 1 */
{
	for (int bitIndex=0; bitIndex<8; bitIndex++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);	//wait it out as long as the pin is low
		_delay_us(30);                     //once the pin is high, wait 30 us
		
		if(PIND & (1<<DHT11_PIN)){	 /* if high pulse is greater than 30ms, after 30us, if pin is still high, we have a 1 */
			receivedByte = (receivedByte<<1)|(0x01);	}	     /* then its logic HIGH (00000001)|(*/
			else{				         /* otherwise its logic LOW */
			receivedByte = (receivedByte<<1);}
			while(PIND & (1<<DHT11_PIN));//if the signal is still high, wait it out
		}
		return receivedByte;                      //
	}
	
void initDHT(){
			Request();		                       /* send start pulse */
			Response();			                   /* receive response */
}	


void displayTemperatureAndHumidity(){
	 	initDHT();
	 	storeData();
	 	DisplaytData();
		
}
#endif /* DHT_H_ */