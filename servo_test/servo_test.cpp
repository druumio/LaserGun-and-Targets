#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "pico_servo/pico_servo.h"
#include <tusb.h>

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

#define SERVO_PIN 15

int main()
{
    const uint min = 30;
    const uint max = 150;

    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    pico_servo::servo_enable(SERVO_PIN);

    bool clockwise = true;
    uint angle = 0;

    pico_servo::servo_set_position(SERVO_PIN, angle);

    // Block until usb serial is open
    while (!tud_cdc_connected())
    {
        sleep_ms(100);
    }

    printf("Servo test Starting!\n");
    

    while (true)
    {

        pico_servo::servo_set_position(SERVO_PIN, angle);

        sleep_ms(20);

        if (clockwise)
        {
            angle++;
            printf("Current angle: %d\n", angle);
        }
        else
        {
            angle--;
        }
        if (angle == 0 || angle == 180)
        {
            clockwise = !clockwise;
            printf("Current angle: %d\n", angle);
        }
    }
}