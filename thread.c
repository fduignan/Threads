#include "tilm4f120hqr.h"
#include <stdint.h>
#define MAX_THREADS 10


uint32_t ThreadIndex = 0;
uint32_t ThreadCount = 0;
typedef struct {
    uint32_t *ThreadStack;
    void (*ThreadFn )();
     uint32_t Attributes;   
} ThreadControlBlock;


ThreadControlBlock Threads[MAX_THREADS];
uint32_t TCB_Size = sizeof(ThreadControlBlock);

void createThread(void (*ThreadFn )(), uint32_t *ThreadStack, uint32_t StackSize)
{
    uint32_t Index;
    if (ThreadCount < MAX_THREADS)
    {
        asm(" cpsid i "); // disable interrupts during thread creation
        Threads[ThreadCount].ThreadFn = ThreadFn;
        
        // The thread stack needs to be set up so that it can be context switched back to later
        // First zero the stack (assuming 32 bit accesses.  Stacksize expressed in 32 bit words
        for (Index=0;Index < StackSize; Index++)
            ThreadStack[Index]=0;
        ThreadStack[StackSize-1] = (1 << 24); // Set the arithmetic flags to zero and ensure Thumb bit is set in PSR
        ThreadStack[StackSize-2] = (uint32_t) ThreadFn; // The "Stacked" PC goes here.
        // Fill in some test values to help debugging
        ThreadStack[StackSize-3] = 1; // LR
        ThreadStack[StackSize-4] = 2; // R12
        ThreadStack[StackSize-5] = 3; // R3
        ThreadStack[StackSize-6] = 4; // R2
        ThreadStack[StackSize-7] = 5; // R1
        ThreadStack[StackSize-8] = 6; // R0
        ThreadStack[StackSize-9] = 7; // R11
        ThreadStack[StackSize-10] = 8;// R10
        ThreadStack[StackSize-11] = 9;// R9
        ThreadStack[StackSize-12] = 10;// R8
        ThreadStack[StackSize-13] = 11;// R7
        ThreadStack[StackSize-14] = 12;// R6
        ThreadStack[StackSize-15] = 13;// R5
        ThreadStack[StackSize-16] = 14;// R4        
        Threads[ThreadCount].ThreadStack = &ThreadStack[StackSize-16];               
        Threads[ThreadCount].Attributes = 1; // lets say 1 means "schedulable"
        ThreadCount++;
        asm(" cpsie i "); // enable interrupts
    }
}
void initSysTick()
{
	// Default power up clock status is as follows:
	// PIOSC runs at 16MHz.  This supplies the system clock
	// The systick timer is driven by PIOSC/4 (4MHz)
	// enable systick and its interrupts
	SET_BIT(SYS_STCTRL,BIT0+BIT1); 
	SYS_STRELOAD=4000;  // generate 1 millisecond time base
	SYS_STCURRENT=1000; // start the counter off at a low(ish) figure
	
}
void startSwitcher()
{

    // At the end of this function, the routine enters a never-ending while loop.
    // At the next interrupt, the contents of xPSR, PC, LR, R12 and R0-R3 are dumped
    // on the thread stack.  This consumes 32 bytes of stack on this stack.
    // If we do not take this into account, the stack pointer for the first thread will
    // be off by this amount so we need to adjust it in advanace by
    initSysTick();
    asm(" LDR R0,=Threads "); // point to start of TCB array    
    asm(" LDR R0,[R0] ");   // read first Thread Stack pointer
    
    asm(" ADD R0,#32 ");    // Adjust first thread stack
    asm(" MSR PSP,R0 ");    // write first stack pointer to process stack pointer        
    enable_interrupts();                
    while(1);    
}



// Want the systick handler to be "pure assembler without any stack shenanigans by the compiler (hence the naked attribute)
__attribute__((naked)) void SysTick_Handler(void) 
{
  

// Thread switching will happen here
// On entry, R0,R1,R2,R3 and R12 for Thread 'A' (whichever one that may be) are on the thread stack

// Preserve remaining registers on stack of thread that is being suspended (Thread A)     
    asm(" cpsid i "); // disable interrupts during thread switch
    asm(" MRS R0,PSP ");  // get Thread A stack pointer
    asm(" SUB R0,#32");   // Make room for the other registers : R4-R11 = 8 x 4 = 32 bytes
    asm(" STMIA R0! , { R4-R7 } "); // Can only do a multiple store on registers up to R7
    asm(" MOV R4,R8 "); // Copy higher registers to lower ones
    asm(" MOV R5,R9 ");
    asm(" MOV R6,R10 ");
    asm(" MOV R7,R11 ");
    asm(" STMIA R0! , { R4-R7 } "); // and repeat the multiple register store
// Locate the Thread Control Block (TCB) for Thread A
    asm(" LDR R0,=TCB_Size "); // get the size of each TCB
    asm(" LDR R0,[R0] ");
    asm(" LDR R1,=ThreadIndex "); // Which one is being used right now?
    asm(" LDR R1,[R1] ");   
    asm(" MUL R1,R0,R1 "); // Calculate offset of Thread A TCB from start of TCB array
    asm(" LDR R0,=Threads "); // point to start of TCB array
    asm(" ADD R1,R0,R1 ");  // add offset to get pointer to Thread A TCB
    asm(" MRS R0,PSP ");   // get Thread A stack pointer
// Save Thread A's stack pointer (adjusted for new registers being pushed
    asm(" SUB R0,#32 ");   // Adjust for the other registers : R4-R11 = 8 x 4 = 32 bytes
    asm(" STR R0,[R1] ");  // Save Thread A Stack pointer to the TCB (first entry = Saved stack pointer)
    
// Update the ThreadIndex
    ThreadIndex++;
    if (ThreadIndex >= ThreadCount)
        ThreadIndex = 0;

// Locate the Thread Control Block (TCB) for Thread B
    asm(" LDR R0,=TCB_Size "); // get the size of each TCB
    asm(" LDR R0,[R0] ");
    asm(" LDR R1,=ThreadIndex "); // Which one is being used right now?
    asm(" LDR R1,[R1] ");   
    asm(" MUL R1,R0,R1 ");  // Calculate offset of Thread A TCB from start of TCB array
    asm(" LDR R0,=Threads "); // point to start of TCB array
    asm(" ADD R1,R0,R1 ");  // add offset to get pointer to Thread B TCB
    asm(" LDR R0,[R1] ");   // read saved Thread B Stack pointer
    asm(" ADD R0,#16 ");    // Skip past saved low registers for the moment
    asm(" LDMIA R0!,{R4-R7} "); // read saved registers
    asm(" MOV R8,R4 "); // Copy higher registers to lower ones
    asm(" MOV R9,R5 ");
    asm(" MOV R10,R6 ");
    asm(" MOV R11,R7 ");
    asm(" LDR R0,[R1] ");   // read saved Thread B Stack pointer
    asm(" LDMIA R0!,{R4-R7} "); // read saved LOW registers
    asm(" LDR R0,[R1] ");   // read saved Thread B Stack pointer
    asm(" ADD R0,#32 ");    // re-adjust saved stack pointer
    asm(" MSR PSP,R0 ");    // write Thread B stack pointer
    
    // The following is only really necessary for the first run of the scheduler.
    asm(" MOV R0,#0 ");     // Force LR to 0xffffffd so that
    asm(" SUB R0,#3 ");     // on return from interrupt the CPU
    asm(" MOV LR,R0 ");     // will switch to thread stack
    

    asm(" cpsie i "); // enable interrupts
    asm(" BX LR ");  // return to Thread B
    
    
}
