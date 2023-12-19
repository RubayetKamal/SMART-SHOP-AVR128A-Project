#ifndef TIMER2_H
#define TIMER2_H

void Timer2Count();
void Timer2Count()
	{
		TCNT2 = 0x9C; //
		TCCR2 = 0x01;
		  
		TIMSK |= (1 << TOIE2);  // Enable Timer2 overflow interrupt
		while(!(TIFR & (1<<TOV2)));
		
		TCCR2 = 0;
	}
	
	void disableTimerOverflowInterrupt(){
		TIMSK &= ~(1 << TOIE2);
	}
#endif	