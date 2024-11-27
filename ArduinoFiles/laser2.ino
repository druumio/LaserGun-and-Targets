#define LASER_PIN PD7  // Arduino UNO pin 7
#define BUTTON_PIN PD2 // Arduino UNO pin 2

#define READ_BUTTON (PIND & _BV(PD2))

void setup()
{
  // output
  DDRD |= _BV(LASER_PIN);
  // input
  DDRD &= ~_BV(BUTTON_PIN);
}

void loop()
{
  static uint8_t fire = 0;
  static uint8_t reload = 0;
  static uint8_t bullet = 1;
  // read and debounce button
  uint8_t btnState0 = READ_BUTTON;
  delay(50);
  uint8_t btnState1 = READ_BUTTON;

  // fire
  if (btnState0 == 1 && btnState1 == 1)
  {
    fire = 1;
    reload = 0;
  }
  // reload
  if (btnState0 == 0 && btnState1 == 0)
  {
    fire = 0;
    reload = 1;
  }
  // fire
  if (fire && bullet)
  {
    PORTD |= _BV(LASER_PIN);
    bullet = 0;
    delay(10);
    PORTD &= ~_BV(LASER_PIN);
  }
  // reload
  if (reload)
  {
    bullet = 1;
  }
}
