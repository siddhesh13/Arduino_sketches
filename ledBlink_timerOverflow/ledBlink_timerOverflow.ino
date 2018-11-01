//blink led for 1s using timer overflow interrupt.

const byte led = PB5;
const int counterValue = 3035;
void setup() {
  // put your setup code here, to run once:
  DDRB |= (1<<led);
  TCCR1A = 0;
  TCCR1B |= (1<<CS12);   // 256 prescaler
  TCCR1B &= ~(1<<CS10);
  TCCR1B &= ~(1<<CS11);
  TCNT1 = counterValue;
  TIMSK1 |= (1<<TOIE1);
  sei();
}

ISR(TIMER1_OVF_vect){
  TCNT1 = counterValue;
  PORTB ^= (1<<led);
}
void loop() {
  // put your main code here, to run repeatedly:
 
}
