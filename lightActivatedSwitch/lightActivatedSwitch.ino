int ldrValue=0;
const byte ldrPin = 3;
void setup() {
  // put your setup code here, to run once:
  DDRB |= (1<<PB5) | (1<<PB4);
  DDRD = 0;
  Serial.begin(9600);
}

int readADC(uint8_t channelToUse){
  int val=0;
  ADCSRA = 0;
  ADCSRB = 0;
  ADMUX = channelToUse;
  ADMUX |= (1<<REFS0);  // AVcc ref
  ADMUX |= (1<<ADLAR);
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (ADPS0); // 128 prescaler
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC);

  while(ADCSRA & (1<<ADSC));
  val |= (ADCL >> 6);
  val |= (ADCH << 2);

  return val;
  
}
void loop() {
  
  // put your main code here, to run repeatedly:
  if((PIND & (1<<4)) >>4){
    PORTB |= (1<<PB5);
    ldrValue = readADC(ldrPin);
    Serial.println(ldrValue);
  }
  else{
    PORTB &= ~(1<<PB5);
  }
  if(ldrValue > 512){
    PORTB |= (1<<PB4);
  }
  else{
    PORTB &= ~(1<<PB4);
  }
}
