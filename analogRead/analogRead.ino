
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
ADCSRA = 0;
ADCSRB = 0;
ADMUX |= (1<<REFS0);
ADMUX &= ~(1<<ADLAR);
ADMUX |= (1<<MUX1);
ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
//ADCSRA |= (1 << ADATE); // enable auto trigger
ADCSRA |= (1<<ADEN);
ADCSRA |= (1<<ADSC);

}

void loop() {
  int adcVal = 0;
  long t0, t;
  
  // put your main code here, to run repeatedly:
 t0 = micros();
 for(int i=0; i<1000; i++){
   while(ADCSRA & (1<<ADSC));
   adcVal |= ADCL;
   adcVal |= (ADCH<<8);
   ADCSRA |= (1<<ADSC); 
 }
 t = micros()-t0;
 Serial.print("Time per smaple: ");
 Serial.println((float)t/1000);
 Serial.print("Frequency: ");
 Serial.println((float)1000000/t);
 Serial.print(" KHz");
 Serial.print("potValue: ");
 Serial.println(adcVal);
 Serial.println();
 delay(2000);
}
