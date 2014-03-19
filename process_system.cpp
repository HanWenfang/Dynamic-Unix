/*
	PL Perals in Unix/Linux PS

			p1
		  /  |  \
		 p1  p9  p2
		/ \     / |  \
	  p3  p4   p5 p7  p6

	Unix offers api , but we can map api to symbols!
	
	exit => delete p; should with a return value!
	aexit => ~p() in c++
	pid operations[ getpid getppid ] => id() function in python
	fork => new in heap or stack
	waitpid => retrieve

	g++ -W process_system.cpp -o process_type
*/

#include <iostream>

struct LDT
{
	int status;
};

// reisters
struct TSS
{
	int status;
};

struct GDT
{
	TSS tss;
	LDT ldt;
};

struct CPU
{
	int registers;
	GDT *GDTable;

	CPU(GDT *g):GDTable(g) {}

	void run(){
		while(true){
			std::cout << registers << std::endl;
			sleep(2);
		}
	}

	void schedule(int pid){
		registers = GDTable[pid].tss.status & GDTable[pid].ldt.status;
	}
};

struct BufferNode
{
	int count;		//reference counter
	int dirty;
	int update;
	char *context;	//COW

	int write() {}	//semantics support
	int read(){}
};

struct Process
{
	TSS tss;
	LDT ldt;
	int fds[100];			//opened typed file

	int time_;
	int status;
	int pid;
	int ppid;				//tree--parent process

	BufferNode Buffer[100];	//List or HashTable --COW

	int fork(){
		// Create A new Typed Process
		// 1. create  a new process 
		// 2. backup , pid , ppid, add to slot
		// 3. wait to schedule 

	}

	char in[100];		//communication between processes
	char out[100];		//pipe
};

// communicate only by id [int], so we have so many global tables

int main(int argc, char *argv[])
{
	GDT GDTable[100]; 			// 100 process~
	CPU cur_cpu(GDTable);		// the cpu
	
	Process *processSlot[64];				// Task Slot---unique pid management
	int last_pid = 0;

	Process zero;
	zero.tss.status = 0x001;
	zero.ldt.status = 0x010;
	zero.pid = 0;
	zero.ppid = -1;

	processSlot[last_pid] = &zero;
	++last_pid;

	GDTable[0].tss.status = zero.tss.status;	// pid = 0
	GDTable[0].ldt.status = zero.ldt.status;

	//Type && Semantics
	cur_cpu.schedule(0);
	cur_cpu.run();

	zero.fork();



	return 0;
}

