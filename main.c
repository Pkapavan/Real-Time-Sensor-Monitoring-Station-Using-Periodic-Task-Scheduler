#include<lpc21xx.h>
#include "sensors_header.h" 
#define flame ((IOPIN0>>2)&1)
#define vibration ((IOPIN0>>3)&1)
#define led (IODIR0=1<<7)

extern unsigned int flag,flag1;
extern unsigned int tick,c;

int main()
{
	unsigned int temp=0,pot_value=0,ldr_value=0;
	IOSET0=led;
	uart0_init(9600);
	adc_init();
	timer0_init();
	config_vic_for_timer();
	uart0_tx_string("uart0  initialised..\r\n");

	while(1)
	{
		if(flag)
		{
			uart0_tx_string("\r\nSECONDS         :");
			uart0_tx_integer(tick);
			uart0_tx_string("\r\nSECONDS         :");
			uart0_tx_integer(c);

			uart0_tx_string("\r\nTEMPERATURE    :");
			if(flag==1)
			{
				flag=0;
				temp=temp_read(0);
			}

			uart0_tx_integer(temp);

			uart0_tx_string("\r\nPOTENTIOMETER  :");
			if(flag==2)
			{
				flag=0;
				pot_value=potentiometer_read(1);
			}
			uart0_tx_integer(pot_value);

			uart0_tx_string("\r\nLDR VALUE      :");
			if(flag==3)
			{
				flag=0;
				ldr_value=ldr_read(2);
			}

			uart0_tx_integer(ldr_value);

			/* if(temp>30)
			   {
			   uart0_tx_string("\r\nhigh temperature" );
			   IOCLR0=led;
			   uart0_tx_string("\r\nhigh temperature" );
			   }
			   else
			   {
			   uart0_tx_string("\r\nnormal temperature" );
			   IOSET0=led;
			   }*/

			if(flame)
				uart0_tx_string("\r\nFLAME          :ON ");
			else
				uart0_tx_string("\r\nFLAME          :OFF");
			if(vibration)
				uart0_tx_string("\r\nVIBRATION      :ON");
			else
				uart0_tx_string("\r\nVIBRATION      :OFF");


			if(temp>30)
			{
				uart0_tx_string("\r\nTEMPERATURE    :HIGH" );
				IOCLR0=led;
				uart0_tx_string("\r\nBUZZER         :ON\r\n" );
			}
			else
			{
				uart0_tx_string("\r\nTEMPERATURE    :NORMAL" );
				IOSET0=led;
				uart0_tx_string("\r\nBUZZER         :OFF\r\n" );
			}
		}
	}
}
