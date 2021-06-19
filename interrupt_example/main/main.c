#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"


/**
* @Brief : The builtin LED blinks when interruption activated in pin GPIO_IO_0
* in case GPIO_IO_0 make a falling edge  

* GPIO status : 
* GPIO2 : output
* GPIO0 : Interrupt input 


**/


#define GPIO_IO_2_OUTPUT 2 
#define GPIO_OUTPUT_PIN_SEL    (1ULL<<GPIO_IO_2_OUTPUT)
#define GPIO_IO_0_INPUT 0 
#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_IO_0_INPUT)


#define HIGH 0
#define LOW 1



static void gpio_isr_handler(void *arg){
    int i ;
    while(1)
    {
        gpio_set_level(GPIO_IO_2_OUTPUT, HIGH); 
        for(i=0; i<0xfffff; i++);
        gpio_set_level(GPIO_IO_2_OUTPUT, LOW); 
        for(i=0; i<0xfffff; i++);    
    }
}




void app_main(void)
{

    gpio_config_t io_conf;
   

    // Led ouput configuration 

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


    // Configuration input interrupt

    //interrupt of anyedge type 
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    //bit mask of the pins
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(GPIO_IO_0_INPUT, gpio_isr_handler, (void *) GPIO_IO_0_INPUT);


    while (1) 
    {
        gpio_set_level(GPIO_IO_2_OUTPUT, LOW); 

    }
}
