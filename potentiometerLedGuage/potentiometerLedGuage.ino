#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 
const byte adcChannel = 2;
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);

  DDRB |= (0B00011111);
  DDRD |= (0B11111110);
  PORTD = 0;
  PORTB = 0;
}

int ADCread(uint8_t adcTouse){
  int adcVal;
  ADCSRA = 0;
  ADCSRB = 0;
  ADMUX = adcTouse;
  ADMUX |= (1<<REFS0);
  ADMUX |= (1<<ADLAR);
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC);

  while(ADCSRA & (1<<ADSC));
  adcVal |= (ADCL>>6);
  adcVal |= (ADCH<<2);
  return adcVal;
}
void loop() {
  int potValue = 0;
  // put your main code here, to run repeatedly:
  potValue = ADCread(adcChannel);

  byte ledRing = map(potValue, 0, 1023, 1, 13);

  for(byte i=1; i<ledRing; i++){
     writeToPort(i,1);
  }
  for(byte i=12; i>=ledRing; i--){
     writeToPort(i,0);
  }

}

void writeToPort(uint8_t pin, int mode){
 
  if(pin >= 1 && pin<=12){
    if(mode == 1){
      if(pin <= 7){
        sbi(PORTD, pin);
      }
      else{
        sbi(PORTB, pin-8);
      }
    }
    if(mode == 0){
      if(pin <= 7){
        cbi(PORTD,pin);
      }
      else{
        cbi(PORTB,pin-8);
      }
    }
    
    
  }
}
