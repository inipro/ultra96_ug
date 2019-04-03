#include "xparameters.h"
#include "xuartlite.h"
#include "xil_printf.h"

XUartLite UartLite;		/* Instance of the UartLite Device */

int main(void)
{
	int Status;
	u8 Buffer[32];
	unsigned int ReceivedCount = 0;
	unsigned int OldReceivedCount = 0;

	xil_printf("Start Uartlite polled Example\r\n");
	/*
	 * Initialize the UartLite driver so that it is ready to use.
	 */
	Status = XUartLite_Initialize(&UartLite, XPAR_UARTLITE_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartLite_SelfTest(&UartLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	while (1) {
		ReceivedCount += XUartLite_Recv(&UartLite, Buffer, 1);
		if(OldReceivedCount != ReceivedCount){
			xil_printf("%s : %d\r\n",Buffer,ReceivedCount);
			XUartLite_Send(&UartLite, Buffer, 1);
			OldReceivedCount = ReceivedCount;
		}
	}
}
