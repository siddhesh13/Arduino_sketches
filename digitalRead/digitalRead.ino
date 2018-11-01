const byte led = PD6;
void setup() {
  // put your setup code here, to run once:
  DDRD |= (1<<led);  //set led as optput and button pin as input
  //PORTD |= (1<<5); //set button pin as input pullup
}

void loop() {
  // put your main code here, to run repeatedly:
  if((PIND & (1<<5)) >> 5){
    PORTD |= (1<<led);
  }
  else{
    PORTD &= ~(1<<led);
  }
}
