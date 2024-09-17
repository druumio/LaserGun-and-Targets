#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico-ssd1306/ssd1306.h"
#include "pico-ssd1306/textRenderer/TextRenderer.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9



int main()
{
    stdio_init_all();

    // Use i2c port with baud rate of 1Mhz
    i2c_init(I2C_PORT, 1000000);
    // Set pins for I2C operation
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    // Create a new display object
    sleep_ms(2000);
    pico_ssd1306::SSD1306 display = pico_ssd1306::SSD1306(I2C_PORT, 0x3D, pico_ssd1306::Size::W128xH32);
    display.setOrientation(0);

    // create a vertical line on x: 64 y:0-31
    for (int y = 0; y < 32; y++)
    {
        display.setPixel(64, y);
    }
    display.sendBuffer(); // Send buffer to device and show on screen

    pico_ssd1306::drawText(&display, font_12x16, "TEST text", 0 ,0);

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}