void init(void);
void Default_Handler(void);

// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;
extern void SysTick_Handler(void);
extern int main(void);
// the section "vectors" is placed at the beginning of flash 
// by the linker script
const void * Vectors[] __attribute__((section(".vectors"))) ={
	(void *)0x20008000, 	/* Top of stack */ 
	init,   				/* Reset Handler */
    Default_Handler,		/* NMI */
	Default_Handler,		/* Hard Fault */
	Default_Handler,       	/* Memory management fault */
	Default_Handler,       	/* Bus Fault */
	Default_Handler,       	/* Usage Fault */
	0,                   	/* Reserved */
	0,                   	/* Reserved */
	0,                   	/* Reserved */
	0,                   	/* Reserved */
	Default_Handler,   		/* SVC */
	0,                   	/* Reserved */
	0,                   	/* Reserved */
	Default_Handler,   		/* PendSV */
	SysTick_Handler,   		/* SysTick */		
/* External interrupt handlers follow */
// See Table 2-9 in Stellaris LM4F120H5QR Data sheet (Rev G) 
	Default_Handler, 	/* IRQ	0	*/
	Default_Handler, 	/* IRQ	1	*/
	Default_Handler, 	/* IRQ	2	*/
	Default_Handler, 	/* IRQ	3	*/
	Default_Handler, 	/* IRQ	4	*/
	Default_Handler,	/* IRQ	5	UART 0 (vector 21)	*/
	Default_Handler, 	/* IRQ	6	*/
	Default_Handler, 	/* IRQ	7	*/
	Default_Handler, 	/* IRQ	8	*/
	Default_Handler, 	/* IRQ	9	*/
	Default_Handler, 	/* IRQ	10	*/
	Default_Handler, 	/* IRQ	11	*/
	Default_Handler, 	/* IRQ	12	*/
	Default_Handler, 	/* IRQ	13	*/
	Default_Handler, 	/* IRQ	14	*/
	Default_Handler, 	/* IRQ	15	*/
	Default_Handler, 	/* IRQ	16	*/
	Default_Handler, 	/* IRQ	17	*/
	Default_Handler, 	/* IRQ	18	*/
	Default_Handler, 	/* IRQ	19	*/
	Default_Handler, 	/* IRQ	20	*/
	Default_Handler, 	/* IRQ	21  */
	Default_Handler, 	/* IRQ	22	*/
	Default_Handler, 	/* IRQ	23	*/
	Default_Handler, 	/* IRQ	24	*/
	Default_Handler, 	/* IRQ	25	*/
	Default_Handler, 	/* IRQ	26	*/
	Default_Handler, 	/* IRQ	27	*/
	Default_Handler, 	/* IRQ	28	*/
	Default_Handler, 	/* IRQ	29	*/
	Default_Handler, 	/* IRQ	30	*/
	Default_Handler, 	/* IRQ	31	*/
	Default_Handler, 	/* IRQ	32	*/
	Default_Handler, 	/* IRQ	33	*/
	Default_Handler, 	/* IRQ	34	*/
	Default_Handler, 	/* IRQ	35	*/
	Default_Handler, 	/* IRQ	36	*/
	Default_Handler, 	/* IRQ	37	*/
	Default_Handler, 	/* IRQ	38	*/
	Default_Handler, 	/* IRQ	39	*/
	Default_Handler, 	/* IRQ	40	*/
	Default_Handler, 	/* IRQ	41	*/
	Default_Handler, 	/* IRQ	42	*/
	Default_Handler, 	/* IRQ	43	*/
	Default_Handler, 	/* IRQ	44	*/
	Default_Handler, 	/* IRQ	45	*/
	Default_Handler, 	/* IRQ	46	*/
	Default_Handler, 	/* IRQ	47	*/
	Default_Handler, 	/* IRQ	48	*/
	Default_Handler, 	/* IRQ	49	*/
	Default_Handler, 	/* IRQ	50	*/
	Default_Handler, 	/* IRQ	51	*/
	Default_Handler, 	/* IRQ	52	*/
	Default_Handler, 	/* IRQ	53	*/
	Default_Handler, 	/* IRQ	54	*/
	Default_Handler, 	/* IRQ	55	*/
	Default_Handler, 	/* IRQ	56	*/
	Default_Handler, 	/* IRQ	57	*/
	Default_Handler, 	/* IRQ	58	*/
	Default_Handler, 	/* IRQ	59	*/
	Default_Handler, 	/* IRQ	60	*/
	Default_Handler, 	/* IRQ	61	*/
	Default_Handler, 	/* IRQ	62	*/
	Default_Handler, 	/* IRQ	63	*/
	Default_Handler, 	/* IRQ	64	*/
	Default_Handler, 	/* IRQ	65	*/
	Default_Handler, 	/* IRQ	66	*/
	Default_Handler, 	/* IRQ	67	*/
	Default_Handler, 	/* IRQ	68	*/
	Default_Handler, 	/* IRQ	69	*/
	Default_Handler, 	/* IRQ	70	*/
	Default_Handler, 	/* IRQ	71	*/
	Default_Handler, 	/* IRQ	72	*/
	Default_Handler, 	/* IRQ	73	*/
	Default_Handler, 	/* IRQ	74	*/
	Default_Handler, 	/* IRQ	75	*/
	Default_Handler, 	/* IRQ	76	*/
	Default_Handler, 	/* IRQ	77	*/
	Default_Handler, 	/* IRQ	78	*/
	Default_Handler, 	/* IRQ	79	*/
	Default_Handler, 	/* IRQ	80	*/
	Default_Handler, 	/* IRQ	81	*/
	Default_Handler, 	/* IRQ	82	*/
	Default_Handler, 	/* IRQ	83	*/
	Default_Handler, 	/* IRQ	84	*/
	Default_Handler, 	/* IRQ	85	*/
	Default_Handler, 	/* IRQ	86	*/
	Default_Handler, 	/* IRQ	87	*/
	Default_Handler, 	/* IRQ	88	*/
	Default_Handler, 	/* IRQ	89	*/
	Default_Handler, 	/* IRQ	90	*/
	Default_Handler, 	/* IRQ	91	*/
	Default_Handler, 	/* IRQ	92	*/
	Default_Handler, 	/* IRQ	93	*/
	Default_Handler, 	/* IRQ	94	*/
	Default_Handler, 	/* IRQ	95	*/
	Default_Handler, 	/* IRQ	96	*/
	Default_Handler, 	/* IRQ	97	*/
	Default_Handler, 	/* IRQ	98	*/
	Default_Handler, 	/* IRQ	99	*/
	Default_Handler, 	/* IRQ	100	*/
	Default_Handler, 	/* IRQ	101	*/
	Default_Handler, 	/* IRQ	102	*/
	Default_Handler, 	/* IRQ	103	*/
	Default_Handler, 	/* IRQ	104	*/
	Default_Handler, 	/* IRQ	105	*/
	Default_Handler, 	/* IRQ	106	*/
	Default_Handler, 	/* IRQ	107	*/
	Default_Handler, 	/* IRQ	108	*/
	Default_Handler, 	/* IRQ	109	*/
	Default_Handler, 	/* IRQ	110	*/
	Default_Handler, 	/* IRQ	111	*/
	Default_Handler, 	/* IRQ	112	*/
	Default_Handler, 	/* IRQ	113	*/
	Default_Handler, 	/* IRQ	114	*/
	Default_Handler, 	/* IRQ	115	*/
	Default_Handler, 	/* IRQ	116	*/
	Default_Handler, 	/* IRQ	117	*/
	Default_Handler, 	/* IRQ	118	*/
	Default_Handler, 	/* IRQ	119	*/
	Default_Handler, 	/* IRQ	120	*/
	Default_Handler, 	/* IRQ	121	*/
	Default_Handler, 	/* IRQ	122	*/
	Default_Handler, 	/* IRQ	123	*/
	Default_Handler, 	/* IRQ	124	*/
	Default_Handler, 	/* IRQ	125	*/
	Default_Handler, 	/* IRQ	126	*/
	Default_Handler, 	/* IRQ	127	*/
	Default_Handler, 	/* IRQ	128	*/
	Default_Handler, 	/* IRQ	129	*/
	Default_Handler, 	/* IRQ	130	*/
	Default_Handler 	/* IRQ	131	*/

};
void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
	main();
}

void Default_Handler()
{
	while(1);
}
