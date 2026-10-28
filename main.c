#define PERIPHE_BASE (0x40000000UL)

#define AHB1PERIPHE_OFFSET (0x20000UL)
#define AHB1PERIPHE_BASE (PERIPHE_BASE + AHB1PERIPHE_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1PERIPHE_BASE + RCC_OFFSET)

#define RCC_AHB1ENR_OFFSET (0x30UL)
#define RCC_AHB1ENR (*(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

#define GPIOD_OFFSET (0xC00UL)
#define GPIOD_BASE (AHB1PERIPHE_BASE + GPIOD_OFFSET)

#define GPIOx_MODER_OFFSET (0x00UL)
#define GPIOD_MODER (*(volatile unsigned int *)(GPIOD_BASE + GPIOx_MODER_OFFSET))

#define GPIOx_ODR_OFFSET (0x14UL)
#define GPIOD_ODR (*(volatile unsigned int *)(GPIOD_BASE + GPIOx_ODR_OFFSET))

#define RCC_GPIOD_EN (0x1UL << 3)

#define GPIOD_PD12_OUTPUT_MODE (0x1UL << 24) //LD4
#define GPIOD_PD13_OUTPUT_MODE (0x1UL << 26) //LD3
#define GPIOD_PD14_OUTPUT_MODE (0x1UL << 28) //LD5
#define GPIOD_PD15_OUTPUT_MODE (0x1UL << 30) //LD6

#define LD3_SET (0x1UL << 13)
#define LD4_SET (0x1UL << 12)
#define LD5_SET (0x1UL << 14)
#define LD6_SET (0x1UL << 15)

#define BIT_BAND_PERI_BASE (0x42000000UL)
#define BIT_BAND_ADDR_REF(addr, bit_num) (BIT_BAND_PERI_BASE + (((unsigned int)(addr) - PERIPHE_BASE) << 5) + (bit_num << 2))
#define BIT_BAND_PERI(addr, bit_num) *((volatile unsigned int *)(BIT_BAND_ADDR_REF(addr, bit_num)))


#include <stdint.h>
void delay(volatile uint32_t count) {
    for (uint32_t i = 0; i < count; i++) {
        for (volatile uint32_t j = 0; j < 3200; j++) {
            __asm__("nop"); // Lệnh không làm gì, tốn 1 chu kỳ máy
        }
    }
}

uint32_t blink_delay = 50;

int main(void)
{
	RCC_AHB1ENR |= RCC_GPIOD_EN;
	GPIOD_MODER |= (GPIOD_PD12_OUTPUT_MODE | GPIOD_PD13_OUTPUT_MODE | GPIOD_PD14_OUTPUT_MODE | GPIOD_PD15_OUTPUT_MODE);
	while(1){
	/*
		GPIOD_ODR |= LD3_SET;
		delay(blink_delay);
		GPIOD_ODR ^= LD3_SET;
		delay(blink_delay);

		GPIOD_ODR |= LD5_SET;
		delay(blink_delay);
		GPIOD_ODR ^= LD5_SET;
		delay(blink_delay);

		GPIOD_ODR |= LD6_SET;
		delay(blink_delay);
		GPIOD_ODR ^= LD6_SET;
		delay(blink_delay);

		GPIOD_ODR |= LD4_SET;
		delay(blink_delay);
		GPIOD_ODR ^= LD4_SET;
		delay(blink_delay);

		GPIOD_ODR |= LD3_SET;
		delay(80);
		GPIOD_ODR |= LD5_SET;
		delay(80);
		GPIOD_ODR |= LD6_SET;
		delay(80);
		GPIOD_ODR |= LD4_SET;
		delay(80);

		GPIOD_ODR ^= LD3_SET;
		delay(80);
		GPIOD_ODR ^= LD5_SET;
		delay(80);
		GPIOD_ODR ^= LD6_SET;
		delay(80);
		GPIOD_ODR ^= LD4_SET;
		delay(80);

		GPIOD_ODR |= (LD3_SET | LD6_SET);
		delay(150);
		GPIOD_ODR ^= (LD3_SET | LD6_SET);
		delay(50);

		GPIOD_ODR |= (LD5_SET | LD4_SET);
		delay(150);
		GPIOD_ODR ^= (LD5_SET | LD4_SET);
		delay(50);

		GPIOD_ODR |= (LD3_SET | LD6_SET);
		delay(40);
		GPIOD_ODR ^= (LD3_SET | LD6_SET);
		delay(40);
		GPIOD_ODR |= (LD3_SET | LD6_SET);
		delay(40);
		GPIOD_ODR ^= (LD3_SET | LD6_SET);
		delay(100);

		GPIOD_ODR |= (LD5_SET | LD4_SET);
		delay(40);
		GPIOD_ODR ^= (LD5_SET | LD4_SET);
		delay(40);
		GPIOD_ODR |= (LD5_SET | LD4_SET);
		delay(40);
		GPIOD_ODR ^= (LD5_SET | LD4_SET);
		delay(100);
		*/

		BIT_BAND_PERI(&GPIOD_ODR, 13) = 1;
		delay(blink_delay);
		BIT_BAND_PERI(&GPIOD_ODR, 13) = 0;
		delay(blink_delay);

		BIT_BAND_PERI(&GPIOD_ODR, 14) = 1;
		delay(blink_delay);
		BIT_BAND_PERI(&GPIOD_ODR, 14) = 0;
		delay(blink_delay);

		BIT_BAND_PERI(&GPIOD_ODR, 15) = 1;
		delay(blink_delay);
		BIT_BAND_PERI(&GPIOD_ODR, 15) = 0;
		delay(blink_delay);

		BIT_BAND_PERI(&GPIOD_ODR, 12) = 1;
		delay(blink_delay);
		BIT_BAND_PERI(&GPIOD_ODR, 12) = 0;
		delay(blink_delay);

		BIT_BAND_PERI(&GPIOD_ODR, 13) = 1;;
		delay(80);
		BIT_BAND_PERI(&GPIOD_ODR, 14) = 1;
		delay(80);
		BIT_BAND_PERI(&GPIOD_ODR, 15) = 1;
		delay(80);
		BIT_BAND_PERI(&GPIOD_ODR, 12) = 1;;
		delay(80);

		BIT_BAND_PERI(&GPIOD_ODR, 12) = 0;
		delay(80);
		BIT_BAND_PERI(&GPIOD_ODR, 14) = 0;
		delay(80);
		BIT_BAND_PERI(&GPIOD_ODR, 15) = 0;
		delay(80);
		BIT_BAND_PERI(&GPIOD_ODR, 12) = 0;
		delay(80);

		GPIOD_ODR |= (LD3_SET | LD6_SET);
		delay(150);
		GPIOD_ODR ^= (LD3_SET | LD6_SET);
		delay(50);

		GPIOD_ODR |= (LD5_SET | LD4_SET);
		delay(150);
		GPIOD_ODR ^= (LD5_SET | LD4_SET);
		delay(50);

		GPIOD_ODR |= (LD3_SET | LD6_SET);
		delay(40);
		GPIOD_ODR ^= (LD3_SET | LD6_SET);
		delay(40);
		GPIOD_ODR |= (LD3_SET | LD6_SET);
		delay(40);
		GPIOD_ODR ^= (LD3_SET | LD6_SET);
		delay(100);

		GPIOD_ODR |= (LD5_SET | LD4_SET);
		delay(40);
		GPIOD_ODR ^= (LD5_SET | LD4_SET);
		delay(40);
		GPIOD_ODR |= (LD5_SET | LD4_SET);
		delay(40);
		GPIOD_ODR ^= (LD5_SET | LD4_SET);
		delay(100);

	}
}
