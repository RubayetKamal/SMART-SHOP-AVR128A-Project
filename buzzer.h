
#ifndef BUZZER_H
#define BUZZER_H

#define DDR_BUZZER DDRB
#define BIT_BUZZER PORTB4

void buzzer_init(void);
void initBuzzerTimer();
void initBuzzerInterrupt();
void setBuzzerasOutput();
void ring_alarm(void);
void buzzerOff();
void holdAtoReset();
volatile int counter = 0;

void buzzer_init(void)
{
	setBuzzerasOutput();
	initBuzzerTimer();
	initBuzzerInterrupt();
	buzzerOff();
}

void ring_alarm(void)
{
	OCR0 = 250;
	OCR0 = 150;
	OCR0 = 100;
	OCR0 = 50;
	OCR0 = 100;
	OCR0 = 150;
	OCR0 = 250;
	return;
}

void initBuzzerInterrupt()
{
	EIMSK |= (1 << INT3);
	
	EICRA &= ~(1 << ISC30);
	EICRA &= ~(1 << ISC31);
}

void initBuzzerTimer()
{
	TCCR0 = 0;               // Reset Timer Register
	TCCR0 |= (1 << WGM01);   // CTC mode
	TCCR0 |= (1 << COM00);   // Toggle Mode
	TCCR0 |= (1 << CS00);    // no prescaler ==>Timer2 clock is 1MHz
}

void setBuzzerasOutput()
{
	DDR_BUZZER |= (1 << BIT_BUZZER); // set Pin as output
}

void buzzerOff()
{
	OCR0 = 0x00; // initally Buzzer is off
}

void disableBuzzerInterrupt(){
	EIMSK &= ~(1<<INT3);
}

void enableBuzzerInterrupt(){
	EIMSK |= (1<<INT3);
}
#endif /* BUZZER_H */





