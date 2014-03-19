/*
	PL Perals in Unix/Linux PS

	g++ -W process_system.cpp -o process_type
*/

#include <iostream>

struct LDT
{
	int status;
};

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
	int count; //reference counter
	int dirty;
	int update;
	char *context;
};

struct Process
{
	TSS tss;
	LDT ldt;
	int time_;
	int status;
	int id;

	// List or HashTable
	BufferNode Buffer[100];
};

int main(int argc, char *argv[])
{
	GDT GDTable[100]; 	// 100 process~
	CPU cur_cpu(GDTable);		// the cpu

	Process zero;
	zero.tss.status = 0x001;
	zero.ldt.status = 0x010;
	zero.id = 0;

	GDTable[0].tss.status = zero.tss.status;	// pid = 0
	GDTable[0].ldt.status = zero.ldt.status;

	//Type && Semantics
	cur_cpu.schedule(0);
	cur_cpu.run();





	return 0;
}

