#include <stdio.h>
#include <stdlib.h>
#include <tusb.h>
#include "pico/stdlib.h"

#define MAX_MESSAGE_LENGTH 4

int16_t getint(void);

int main()
{
    stdio_init_all();

    while (!tud_cdc_connected())
    {
        sleep_ms(100);
    }

    printf("Started\n");

    uint8_t state = 0;
    int16_t current_angle = 0;
    uint8_t previous_angle = 0;

    while (true)
    {
        switch (state)
        {
        case 0:
            printf("Angle to move servo:\n");
            state = 1;
        case 1:
            current_angle = getint();
            if (current_angle >= 0 && current_angle != previous_angle && current_angle < 255)
            {
                state = 2;
            }
            else if (current_angle > 0)
            {
                printf("Wrong input: %d\n", current_angle);
            }
            break;
        case 2:
            printf("Servo angle set to: %d\n", current_angle);
            previous_angle = current_angle;
            state = 0;
            break;
        default:
            break;
        }
    }
}

int16_t getint(void)
{
    // Create a place to hold the incoming message
    char message[MAX_MESSAGE_LENGTH];
    uint8_t message_pos = 0;
    int8_t changed = 0;
    while (tud_cdc_available())
    {
        // Read the next available byte in the serial receive buffer
        char inByte = getchar();
        // Message coming in (check not terminating character) and guard for over message size
        if (inByte != '\n' && (message_pos < (MAX_MESSAGE_LENGTH - 1)))
        {
            // Add the incoming byte to our message
            message[message_pos] = inByte;
            message_pos++;
        }
        // Full message received...
        else
        {
            // Add null character to string
            message[message_pos] = '\0';
            printf("MESSAGE: %s\n", message);
            changed = 1;
        }
    }
    if (!changed)
    {
        return -1;
    }
    char *endptr;
    int num = strtol(message, &endptr, 10);
    return num;
}