

/**
 * main.c
 */

#define REG volatile unsigned long int* //volatile to eliminate optimization

#define SCR_base 0x400FE000
#define GPIO_portF_base 0x4005D000
#define FB(Base,offset) Base+offset

REG RCC= FB(SCR_base,0x060); //access RCC register
REG GPIOHBCTL= FB(SCR_base,0x06C); //access GPIOHBCTL register
REG RCGCGPIO= FB(SCR_base,0x608); //access RCGCGPIO register
REG GPIODIR_F= FB(GPIO_portF_base,0x400);
REG GPIOAFSEL= FB(GPIO_portF_base,0x420);
REG GPIODR8R= FB(GPIO_portF_base,0x508);
REG GPIODEN_F= FB(GPIO_portF_base,0x51C);
REG GPIODATA_F= FB(GPIO_portF_base,0x020);//????? WHAT IS THAT
//REG GPIO_F = 0x4005D018;
int main(void)
{
    //OSCSRC
    (*RCC) |= (1<<4);
    (*RCC) &= ~(1<<5);
    //BYPASS
    (*RCC) |= (1<<11);
    //PWRDN
    (*RCC) |= (1<<13);
    //USESYSDIV
    (*RCC) &= ~(1<<22);
    //active portF on(AHB)
    (*GPIOHBCTL) |= (1<<5);
    //enable portF
    (*RCGCGPIO) |= (1<<5);
    //pin 1(red) in portF as output
    (*GPIODIR_F) |= (1<<3);
    //The associated pin functions as a GPIO
    (*GPIOAFSEL) &= ~(1<<3);
    //The corresponding GPIO pin has 8-mA drive
    (*GPIODR8R) |= (1<<3);
    //The digital functions for the corresponding pin are enabled.
    (*GPIODEN_F) |= (1<<3);
    (*GPIODATA_F) |= (0xFF);
    //(*GPIO_F) |=;

	return 0;
}
