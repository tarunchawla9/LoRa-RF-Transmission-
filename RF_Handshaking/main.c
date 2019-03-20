/*
Name : RF_Handshaking.c
Description : RF and PWM code for LPC1769
CTI One Corporation released for
Dr. Harry Li for CMPE 245 Class use ONLY!
*/
//#include "FreeRTOS.h"
//#include "FreeRTOS.h"
#ifdef __USE_CMSIS
//#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>
#include <stdio.h>
#include <stdbool.h>
#include "LoRa.h"
#include"common.h"
#include "timer.h"
#define RF_Receive 1
#define RF_Transmit 0
#define TransmittACk 0
#define ack_start_stop 0
int rfInit(void);
char receiveData=0;
int packetSize;
static void delay_ms(unsigned int ms)
{
unsigned int i,j;
for(i=0;i<ms;i++)
for(j=0;j<50000;j++);
}
static void delay(uint32_t delayInMs)
{
LPC_TIM0->TCR = 0x02;
LPC_TIM0->PR = 0x00;
LPC_TIM0->MR0 = delayInMs *
(9000000 / 1000-1);
LPC_TIM0->IR = 0xff;
LPC_TIM0->TCR = 0x01;

/* wait until delay time has elapsed */
while (LPC_TIM0->TCR & 0x01);
}
uint32_t gnSendPackCount = 0;
void sendData(int SFNew)
{
char buffer[1024];
int nSendPackSize = snprintf(buffer, 1024,"WIRE*LESS* 100*CMP%d*;P=%dSF=%d",gnSendPackCount++ % 10,getTxPower(),SFNew);
//char Acknowledgement;
//Acknowledgement = ’A’;
printf("Start Sending data TXPow is %d SF is %d \n", getTxPower(), SFNew);
//delay_ms(1000);
LoRabeginPacket(0);
//writebyte(Acknowledgement);
write(buffer, nSendPackSize);
LoRaendPacket();
printf("Data sent \n");
}
void improveTxPower()
{
int TxPowerCurrent = getTxPower();
//printf("TxPower was %d" ,TxPowerCurrent);
setTxPower(++TxPowerCurrent);
//printf("TxPower new is %d" ,TxPowerCurrent);
}
int calculateNewSF()
{
if(getTxPower() >= 17)
{
int newSF;
if(getSpreadingFactor() >=8)
{
newSF = getSpreadingFactor() -1;
return newSF;
}
}
else
{
return getSpreadingFactor();
}
}
int main(void)
{
printf("System clock is %d\n",SystemCoreClock);
uint64_t nTimeElapsedBetweenPackets = 0;
uint64_t nTimeTickCount1 = 0;
double fPerformanceIndex = 100.0;
double fDelayPerformanceDrop = 0.0;
double fCorruptionDrop = 0.0;
//LoRabegin(1040000000);
//LoRabegin(1020000000);
//LoRabegin(724000000);
//LoRabegin(750000000);
//LoRabegin(790000000);
//LoRabegin(800000000);
//LoRabegin(845000000);
//LoRabegin(850000000);
//LoRabegin(910000000);
//LoRabegin(868000000);
LoRabegin(869000000);
//LoRabegin(915000000);
int counter =0;
timer_initialise();
int nCount = 0;
float recdPerformance;
int SFNew = getSpreadingFactor();
/* Start the tasks running. */
//vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
#if RF_Receive
while(1)
{
if(getTimeTickCount() - nCount < 10)
{
sendData(SFNew);
}
else
{
setSpreadingFactor(SFNew);
while(1)
{
rxModeCheck();
packetSize = parsePacket(0);
if (packetSize)
{
int count = 0;
counter = 0;
//NVIC_EnableIRQ(TIMER0_IRQn);
//received a packet
//printf("Received packet \n");
// read packet
if(nTimeTickCount1)
{
nTimeElapsedBetweenPackets= getTimeTickCount() -nTimeTickCount1;
}
nTimeTickCount1 = getTimeTickCount();
char recdbuffer[1024]=""; int index =0;
recdPerformance =0;
while (available() && (++count<= packetSize))
{
counter = 0;
receiveData = read();
recdbuffer[index] = receiveData; index++;
if(nTimeElapsedBetweenPackets > 3)
{
fDelayPerformanceDrop += 5.0;
}
else
{
fDelayPerformanceDrop = 0.0;
}
fPerformanceIndex -= fDelayPerformanceDrop;
}
if(count == packetSize)
{
sscanf(recdbuffer,"%f",&recdPerformance);
if(recdPerformance < 85)
{
improveTxPower(recdPerformance);
SFNew = calculateNewSF();
}
nCount = getTimeTickCount();
break;
}
}
}
}
}
#if TransmittACk
const char buffer[] =
\\"Data from LPC1769";
char Acknowledgement;
Acknowledgement = ’A’;

while(1)
{
printf("Start Sending data \n");
delay_ms(1000);
LoRabeginPacket(0);
//writebyte(Acknowledgement);
write(buffer,
sizeof(buffer));
LoRaendPacket();
printf("Data sent \n");
}
#endif
#endif
#if RF_Transmit
const char buffer[] =
\\"Data from LPC1769";
char Acknowledgement;
Acknowledgement = ’A’;
while(1)
{
printf("Start Sending data \n");
delay_ms(1000);
printf("delay done\n");
LoRabeginPacket(0);
//writebyte(Acknowledgement);
printf("begin packet\n");
size_t ret = write(buffer,
\\sizeof(buffer));
printf("write done %d \n",ret);
LoRaendPacket();
printf("Data sent \n");
}
#endif
}
void check_ack()
{
printf("1 \n");
// NVIC_EnableIRQ(TIMER0_IRQn);
//NVIC_DisableIRQ(TIMER0_IRQn);
}
