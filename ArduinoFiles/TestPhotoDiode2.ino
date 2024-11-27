#define LED_1 PD2    // Arduino UNO pin 2
#define LED_2 PD3    // Arduino UNO pin 3
#define LED_3 PD4    // Arduino UNO pin 4
#define LED_4 PD5    // Arduino UNO pin 5
#define LED_5 PD6    // Arduino UNO pin 6
#define SENSOR_1 PB0 // Arduino UNO pin 8
#define SENSOR_2 PB1 // Arduino UNO pin 9
#define SENSOR_3 PB2 // Arduino UNO pin 10
#define SENSOR_4 PB3 // Arduino UNO pin 11
#define SENSOR_5 PB4 // Arduino UNO pin 12

uint32_t millisCounter = 0;
uint32_t lastMillis = 0;

// Turns selected led on
void led_on(int led)
{
  PORTD |= _BV(led);
}

// Turns selected led off
void led_off(int led)
{
  PORTD &= ~_BV(led);
}

// Turns all leds off
void led_off_all(void)
{
  PORTD &= ~(_BV(LED_1) | _BV(LED_2) | _BV(LED_3) | _BV(LED_4) | _BV(LED_5));
}

void setup()
{
  // Outputs
  DDRD |= (_BV(LED_1) | _BV(LED_2) | _BV(LED_3) | _BV(LED_4) | _BV(LED_5));
  // Inputs
  DDRB &= ~(_BV(SENSOR_1) | _BV(SENSOR_2) | _BV(SENSOR_3) | _BV(SENSOR_4) | _BV(SENSOR_5));

  led_off_all();
}

void loop()
{
  uint32_t currentMillis = millis();
  uint8_t readsensor = PINB;

  if (readsensor & _BV(SENSOR_1))
  {
    led_on(LED_1);
  }
  if (readsensor & _BV(SENSOR_2))
  {
    led_on(LED_2);
  }

  if (readsensor & _BV(SENSOR_3))
  {
    led_on(LED_3);
  }

  if (readsensor & _BV(SENSOR_4))
  {
    led_on(LED_4);
  }

  if (readsensor & _BV(SENSOR_5))
  {
    led_on(LED_5);
  }

  if (millisCounter % 1000 == 0)
  {
    turn_off_all();
  }

  // ms counter
  if (currentMillis - lastMillis >= 1)
  {
    millisCounter++;
    lastMillis = currentMillis;
  }
}
