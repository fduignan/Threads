/* tasks.h */
void createThread(void (*ThreadFn )(), uint32_t *ThreadStack, uint32_t StackSize);
void startSwitcher(void);
