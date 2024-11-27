#define LASER_PIN PD7 //Arduino UNO pin 7
#define BUTTON_PIN PD2 //Arduino UNO pin 2
 
 #define READ_BUTTON (PIND & _BV(PD2))

void setup() {
  //output
  DDRD |= _BV(LASER_PIN);
  //input
  DDRD &= ~_BV(BUTTON_PIN);
}

void loop() {
  //read and debounce button
  uint8_t btnState0 = READ_BUTTON;
  delay(50);
  uint8_t btnState1 = READ_BUTTON;
  if (btnState0 && btnState1){
    PORTD |= _BV(LASER_PIN);
  }
  else{
    PORTD &= ~_BV(LASER_PIN);
  }
}
