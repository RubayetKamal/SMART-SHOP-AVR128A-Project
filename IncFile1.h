/*
 * IncFile1.h
 *
 * Created: 07/12/2023 11:01:28
 *  Author: $RHEK00-BS9TAG427UBC
 */ 


#ifndef BUZZER_H
#define BUZZER_H



#define DDR_BUZZER DDRB
#define BIT_BUZZER PORTB4

void buzzer_init(void);
void buzzer_tone(void);

int main(void)

void buzzer_init(void)
{
	DDR_BUZZER |= (1 << BIT_BUZZER); // set Pin as output
	
	TCCR0 = 0; // Reset Timer Register
	TCCR0 |= (1 << WGM01); // CTC mode
	TCCR0 |= (1 << COM00); // Toggle Mode
	TCCR0 |= (1 << CS00); // no prescaler ==>Timer2 clock is 1MHz
	
	OCR0 = 0x00;
}

void ring_alarm(void){
	OCR0 = 220;
	_delay_ms(100);
	OCR0 = 0;
	_delay_ms(100);
	OCR0 = 220;
	_delay_ms(100);
	OCR0 = 0;
	_delay_ms(200);
	OCR0 = 220;
	_delay_ms(200)    ;
	OCR0 = 0;
	_delay_ms(200);
	OCR0 = 150;
	_delay_ms(1000);
	return;
}



#endif /* INCFILE1_H_ */