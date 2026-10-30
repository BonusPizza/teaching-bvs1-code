#include "process.h"
#include "context.h"




struct process *current_process;
struct context OS_context;


void process_start(void){
	current_process->entry();
	process_exit(0);
}


void process_create(struct process *process, process_entry_t entry){
	process->entry = entry;
	process->context.sp = (uintptr_t) &process->stack[STACK_SIZE];
	process->context.ra = (uintptr_t) process_start;
	process->state = READY;
}



void process_run(struct process *process){
	if(process->state != FINISHED){
		current_process = process;
		current_process->state = RUNNING;
		context_switch(&OS_context, &(current_process->context)); //speichere den aktuellen Kontext im OS_context und lade den context aus dem context des aktuellen prozesses
	}
}

void process_yield(void){
	current_process->state = READY;
	context_switch(&(current_process->context), &OS_context);
}

void process_exit(short int status){
	current_process->exit_status = status;
	current_process->state = FINISHED;
	context_switch(&(current_process->context), &OS_context);
}

