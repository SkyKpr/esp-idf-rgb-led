#ifndef RGB_LED_H
#define RGB_LED_H

typedef struct rgb_color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} rgb_color;

extern rgb_color RGB_COLOR_WHITE;
extern rgb_color RGB_COLOR_BLUE;

void rgb_setup(unsigned char gpio_r, unsigned char gpio_g, unsigned char gpio_b);

void rgb_enable(void);
void rgb_disable(void);

void rgb_set_color(unsigned char red_value, unsigned char green_value, unsigned char blue_value); 
void rgb_set_color_array(unsigned char color[3]);
void rgb_set_predefined_color(rgb_color color);

rgb_color rgb_get_color();

#endif