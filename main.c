#include <stdint.h>
#include "tilm4f120hqr.h"
#include "thread.h"

void ConfigPins();
// The stack size is expressed in 32 bit words
#define STACK_SIZE 64
uint32_t Thread1Stack[STACK_SIZE];
uint32_t Thread2Stack[STACK_SIZE];
uint32_t Thread3Stack[STACK_SIZE];


void Thread1(void)
{
    static uint32_t Counter1 = 0;    
    while(1) 
    {
        Counter1++;    
        if (Counter1 >100000)
        {// toggle the blue led 
            Counter1 = 0;
            disable_interrupts();
            GPIOF_DATA ^= 0x4;
            enable_interrupts();
        }
    }    
}
void Thread2(void)
{
    static uint32_t Counter2 = 0;
    while(1) 
    {
        Counter2++;
        if (Counter2 >200000)
        {// toggle the red led             
            Counter2 = 0;
            disable_interrupts();
            GPIOF_DATA ^= 0x2;
            enable_interrupts();
        }    
    }
}
void Thread3(void)
{
    static uint32_t Counter3 = 0;
    
    while(1) 
    {
        Counter3++;
        if (Counter3 >400000)
        {   // toggle the green led 
            Counter3 = 0;
            disable_interrupts();
            GPIOF_DATA ^= 0x8;
            enable_interrupts();
            
        }
    
    }
}
void main()
{

	ConfigPins();    
    createThread(Thread1,Thread1Stack,STACK_SIZE);
    createThread(Thread2,Thread2Stack,STACK_SIZE);
    createThread(Thread3,Thread3Stack,STACK_SIZE);          
    startSwitcher(); // start the thread switching (this does not return)	
}

void ConfigPins()
{
    SET_BIT(SYSCTL_RCGC2,BIT5); 		 // turn on GPIOF
	SET_BIT(SYSCTL_GPIOHBCTL,BIT5);      // turn on AHB access to GPIOF	
	SET_BIT(GPIOF_DEN,(BIT1+BIT2+BIT3)); // digital mode bits 1,2,3 of GPIOF
	SET_BIT(GPIOF_DIR,(BIT1+BIT2+BIT3)); // make bits 1,2,3 outputs on GPIOF
}
