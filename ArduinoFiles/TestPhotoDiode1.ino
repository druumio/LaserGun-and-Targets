#define LED_RED PD2 //Arduino UNO pin 2
#define LED_YELLOW PD3 //Arduino UNO pin 3
#define LED_ORANGE PD4 //Arduino UNO pin 4
#define LIGHT_0 A0
#define LIGHT_1 A1

// Turns selected led on
void led_on(int led){
  PORTD |= _BV(led);
}

// Turns selected led off
void led_off(int led){
  PORTD &= ~_BV(led);
}

// Turns all leds on
void led_on_all(void){
  PORTD |= (_BV(LED_RED) | _BV(LED_YELLOW) | _BV(LED_ORANGE));
}

// Turns off leds on
void led_off_all(void){
  PORTD &= ~(_BV(LED_RED) | _BV(LED_YELLOW) | _BV(LED_ORANGE));
}

void setup() {
  Serial.begin(9600);
  // Outputs
  DDRD |= (_BV(LED_RED) | _BV(LED_YELLOW) | _BV(LED_ORANGE)); 
  led_on_all();
}

void loop() {
  int light0, light1;
  light0 = analogRead(LIGHT_0);
  light1 = analogRead(LIGHT_1);
  if (light0 < light1) {led_off_all(); led_on(LED_RED);}else{led_off_all(); led_on(LED_YELLOW);}
  Serial.print("Light0 = ");
  Serial.println(light0);
  Serial.print("Light1 = ");
  Serial.println(light1);
  delay(100);
}
