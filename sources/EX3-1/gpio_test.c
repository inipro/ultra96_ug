#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

int main (void)
{
	XGpio btns, leds;
	int btns_check;

	print("-- Start of the Program --\r\n");

	XGpio_Initialize(&leds, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&leds, 1, 0x00000000);

	XGpio_Initialize(&btns, XPAR_AXI_GPIO_1_DEVICE_ID);
	XGpio_SetDataDirection(&btns, 1, 0xffffffff);

	while (1)
	{
		btns_check = XGpio_DiscreteRead(&btns, 1);
		XGpio_DiscreteWrite(&leds, 1, btns_check);
		xil_printf("Switch Status : %x\r\n", btns_check);
		sleep(1);
	}
}
