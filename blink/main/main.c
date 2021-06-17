#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"


/**
* @Brief : This code just makes an external LED in 
* GPIO_IO_1 blink every 1 second

* GPIO status : 
* GPIO2 : output 


**/


#define GPIO_IO_2_OUTPUT 2 
#define GPIO_OUTPUT_PIN_SEL    (1ULL<<GPIO_IO_2_OUTPUT)
#define HIGH 1 
#define LOW 0

void app_main(void)
{

    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set, GPIO1
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);



    while (1) 
    {
        gpio_set_level(GPIO_IO_2_OUTPUT, HIGH); 
        vTaskDelay(1000 / portTICK_RATE_MS); 
        gpio_set_level(GPIO_IO_2_OUTPUT, LOW); 
        vTaskDelay(1000 / portTICK_RATE_MS);  
    }
}
