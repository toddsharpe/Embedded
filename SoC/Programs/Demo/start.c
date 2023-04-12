#include <stdint.h>

void _enter(void) __attribute__ ((naked, section(".text.init.enter")));
void _start(void);
void _exit(int exit_code) __attribute__ ((noinline));

extern int main(void);

// The linker script will place this in the reset entry point.
// It will be 'called' with no stack or C runtime configuration.
// NOTE - this only supports a single hart.
// tp will not be initialized
void _enter(void)   {
    // Setup SP and GP
    // The locations are defined in the linker script
    __asm__ volatile  (
        ".option push;"
        // The 'norelax' option is critical here.
        // Without 'norelax' the global pointer will
        // be loaded relative to the global pointer!
        ".option norelax;"
        "la    gp, __global_pointer$;"
        ".option pop;"
        "la    sp, _sp;"
        "jal   zero, _start;"
        :  /* output: none %0 */
        : /* input: none */
        : /* clobbers: none */); 
    // This point will not be executed, _start() will be called with no return.
}

// At this point we have a stack and global poiner, but no access to global variables.
void _start(void) {

    // Jump to main
    int rc = main();

    // Don't expect to return, if so busy loop in the exit function.
    _exit(rc);
}

// This should never be called. Busy loop with the CPU in idle state.
void _exit(int exit_code) { 
    (void) exit_code;
    // Halt
    while (1) {
        __asm__ volatile ("wfi");
    }
}
