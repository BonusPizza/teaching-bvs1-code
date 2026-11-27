#include "trap.h"
#define STACK_SIZE 4096

typedef void (*process_entry_t)(void); //erstelle process_entry_t als typ der auf eine funktion pointet welche void returned

enum process_state { READY, RUNNING, FINISHED }; //typ für den state des prozesses

struct process {
	process_entry_t entry;
	unsigned char stack[STACK_SIZE];
	struct trap_frame frame;
	enum process_state state;
	int exit_status;
};

void process_create(struct process *process, process_entry_t entry);
void os_run();
void process_yield(void);
//void process_exit(short int status);

