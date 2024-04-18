#include <stdio.h>
#include <driver/ledc.h>
#include "RGB_LED.h"

/*
#define-Section -- Set up for ESP32C3

Change to customize 
*/
#define LEDC_TIMER_NUM 1
#define LEDC_R_CHANNEL 0
#define LEDC_G_CHANNEL 1
#define LEDC_B_CHANNEL 2
#define LEDC_CHANNEL_AMNT 3

/*
Predefined colors 

Template: 

rgb_color RGB_COLOR_<COLOR> = {
    .red = <0 - 255>
    .green = <0 - 255>
    .blue = <0 - 255>    
}
*/
rgb_color RGB_COLOR_WHITE = {
    .red = 255,
    .green = 255,
    .blue = 255
};

rgb_color RGB_COLOR_BLUE = {
    .red = 0,
    .green = 0,
    .blue = 255
};

//Configuration for 3 PWM Channels (set up for ESP32C3)
ledc_channel_config_t ledc_channel[LEDC_CHANNEL_AMNT] = {
    {
        .channel = LEDC_R_CHANNEL,
        .duty = 0,
        .gpio_num = 0,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_NUM,
        .flags.output_invert = 0
    },
    {
        .channel = LEDC_G_CHANNEL,
        .duty = 0,
        .gpio_num = 0,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_NUM,
        .flags.output_invert = 0
    },
    {
        .channel = LEDC_B_CHANNEL,
        .duty = 0,
        .gpio_num = 0,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_NUM,
        .flags.output_invert = 0
    }
};

//Setup-Function -- run first before using other functions
void rgb_setup(unsigned char gpio_r, unsigned char gpio_g, unsigned char gpio_b)
{
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 500,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_NUM,
        .clk_cfg = LEDC_USE_RC_FAST_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel[LEDC_R_CHANNEL].gpio_num = gpio_r;
    ledc_channel[LEDC_G_CHANNEL].gpio_num = gpio_g;
    ledc_channel[LEDC_B_CHANNEL].gpio_num = gpio_b;

    for(int i = 0; i < LEDC_CHANNEL_AMNT; i++) {
        ledc_channel_config(&ledc_channel[i]);
    }

}

/*
Sets RGB LED Strip to specific color by adjusting duty cicle to value (0-255)

Arguments:
- unsigned char red_value: <0 - 255>
- unsigned char green_value: <0 - 255>
- unsigned char blue_value: <0 - 255>
*/
void rgb_set_color(unsigned char red_value, unsigned char green_value, unsigned char blue_value) {
    
    unsigned char colorArray[3] = {red_value, green_value, blue_value};

    for (int i_color = 0; i_color < LEDC_CHANNEL_AMNT; i_color++) {
        ledc_set_duty(ledc_channel[i_color].speed_mode, ledc_channel[i_color].channel, colorArray[i_color]);
        ledc_update_duty(ledc_channel[i_color].speed_mode, ledc_channel[i_color].channel);
    }
    
}

/*
Sets RGB LED Strip to specific color by adjusting duty cicle to value (0-255)

Arguments: 
- array of size 3 with r,g,b values from 0 - 255
*/
void rgb_set_color_array(unsigned char color[3]) {
    
    for (int a = 0; a < LEDC_CHANNEL_AMNT; a++) {
        ledc_set_duty(ledc_channel[a].speed_mode, ledc_channel[a].channel, color[a]);
        ledc_update_duty(ledc_channel[a].speed_mode, ledc_channel[a].channel);    
    }
    
}

/*
Sets RGB LED Strip to specific color by adjusting duty cicle to value (0-255)
Use with predefined color structs. 

Arguments:
rgb_color color: struct of type rgb_color
*/
void rgb_set_predefined_color(rgb_color color) {
    //Pointer zu ersten Element in color struct
    unsigned char *colorPtr = (unsigned char*)&color;

    for(unsigned char i_struct = 0; i_struct < LEDC_CHANNEL_AMNT; i_struct++) {
        ledc_set_duty(ledc_channel[i_struct].speed_mode, ledc_channel[i_struct].channel, *colorPtr); //Wert mit Pointer eingesetzt
        ledc_update_duty(ledc_channel[i_struct].speed_mode, ledc_channel[i_struct].channel);
        //Adresse in Pointer um 1 erhöht
        colorPtr++;
    }
}

//Disables RGB LED Strip by setting duty cycle to 0
void rgb_disable(void) {
    for (int b = 0; b < LEDC_CHANNEL_AMNT; b++) {
        ledc_set_duty(ledc_channel[b].speed_mode, ledc_channel[b].channel, 0);
        ledc_update_duty(ledc_channel[b].speed_mode, ledc_channel[b].channel);    
    }
}