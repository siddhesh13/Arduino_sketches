//analogRead using timer interrupt(output comare match)
//read LDR value every 2 secs.

const byte adcChannel = 3;
const int t1 = 0;
const int comp = 31250;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCCR1B |= (1<<CS12);
  TCCR1B &= ~(1<<CS11);
  TCCR1B |= (1<<CS10);
  TCNT1 = t1;
  OCR1A = comp;
  TIMSK1 |= (1<<OCIE1A);
  sei();  
}

int readADC(byte channelToUse){
  int val = 0;
  ADMUX = 0;
  ADMUX = channelToUse;
  ADMUX |= (1<<REFS0);
  ADMUX |= (1<<ADLAR);
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (ADPS0); // 128 prescaler
  ADCSRA |= (1<<ADPS2) | (ADPS0);  // 32 prescaler
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC);

  while(ADCSRA & (1<<ADSC));

  val |= (ADCL >> 6);
  val |= (ADCH<<2);

  return val;
  
}

ISR(TIMER1_COMPA_vect){
  TCNT1 = t1;
  Serial.print("LDR value: ");
  Serial.println(readADC(adcChannel));
}
void loop() {
  // put your main code here, to run repeatedly:
 
}
