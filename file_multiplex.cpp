/*******
	File multiplex[IO] between Processes

	fds:  ID        file status table       v-node table
		 +--+		+----------------+      +--------+
		 | 1| -->	|	1			 |--->	| file	 |
		 +--+		+----------------+	/->	|		 |
		 | 2|						   /	+--------+
		 +--+		+----------------+/
		 | 3| -->	|	2			 |		+--------+
		 +--+		+----------------+		|		 |
		 | 4|								+--------+
		 +--+	
		
	dup ==> = [ weak reference ]


	g++ -W file_multiplex.cpp -o file_plex
*******/

#include <iostream>
#include <map>

using namespace std;


struct inode
{
	int id;

};

struct file_status
{
	int offset;
	int flag;
};

struct file
{
	int count; // reference cout
	int id;
	inode ino;

	file_status fstatus;
};

struct Process
{
	//TSS tss;
	//LDT ldt;
	file fds[100];			//opened typed file

	int time_;
	int status;
	int pid;
	int ppid;				//tree--parent process

	//BufferNode Buffer[100];	//List or HashTable --COW

	int fork(){
		// Create A new Typed Process
		// 1. create  a new process 
		// 2. backup , pid , ppid, add to slot
		// 3. wait to schedule 

	}

	Process(map<string, int> &d, inode **i_t, file **file_table):dirs(d), inode_table(i_t){}

	int iopen(string filename){
		file tmp;
		
		tmp.ino.id = dirs["/dev/tty0"]; // inode ID
		tmp.id = 0;
		
		fds[0] = tmp; // 0 is file descriptor
		file_table[0] = &fds[0];

		inode_table[0] = &(tmp.ino);

		return tmp.id;
	}

	int dup(int id)
	{
		file_table[id]->count++;
		fds[id] = *file_table[id];		// logic operation with a new file status table!!
	}

	map<string, int> &dirs;
	inode **inode_table;
	file **file_table;

	char in[100];		//communication between processes
	char out[100];		//pipe
};

int main(int argc ,char *argv[])
{
	// directory to inode num
	map<string, int> dirs;
	dirs["/dev/tty0"] = 0;

	inode *inode_table[32];
	file *file_table[64];	// opened fds management

	Process zero(dirs, inode_table, file_table);
	Process one(dirs, inode_table, file_table);

	zero.iopen("/dev/tty0");





	return 0;
}



