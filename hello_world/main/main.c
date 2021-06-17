#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"


void app_main(void)
{
    while (1) {
        printf("Hello World !\n"); 
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        fflush(stdout); 
    }
}
