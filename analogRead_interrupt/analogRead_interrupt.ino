int numSamples = 0;
long t, t0;
byte x;
int adcVal=0;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

 ADCSRA = 0;
 ADCSRB = 0;

 ADMUX |= (1<<REFS0);
 ADMUX |= (1<<ADLAR);
 ADMUX |= (1<<MUX1);

 //smapling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
 // for arduino uno ADC clock is 16Mhz and a conversion takes 13 clcok cycles.
 ADCSRA |= (1<<ADPS2) | (1<< ADPS1) | (1<<ADPS0);  //128 prescaler
 //ADCSRA |= (1<<ADPS2) | (1<< ADPS1);  // 64 prescaler
 //ADCSRA |= (1<<ADPS2) | (1<<ADPS0); // 32 prescaler
 //ADCSRA |= (1<<ADPS2);   //16 prescaler
 //ADCSRA |= (1<<ADPS1) | (1<<ADPS0);  // 8 prescaler

 ADCSRA |= (1 << ADATE); // enable auto trigger
 ADCSRA |= (1 << ADIE); //enable interrupts when measuremnt complete
 ADCSRA |= (1 << ADEN); //enable ADC
 ADCSRA |= (1 << ADSC); // start ADC conversion
  
}

ISR(ADC_vect){
  adcVal |= (ADCL>>6);
   adcVal |= (ADCH<<2);
  numSamples++;
}
void loop() {
  // put your main code here, to run repeatedly:
  if(numSamples >= 1000){
    t = micros() - t0;

    Serial.print("Time per smaple: ");
    Serial.println((float)t/1000);
    Serial.print("Sampling frequency: ");
    Serial.print((float)1000000/t);
    Serial.println(" KHz");
    Serial.print("potValue: ");
    Serial.println(adcVal);
    Serial.println();
    delay(2000);

    t0 = micros();
    numSamples = 0;
    
  }
}
