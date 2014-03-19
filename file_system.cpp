/*
	PL Perals in Unix/Linux FS
	
	In processes :

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
	
	Shell is a map to unix api!
	open => new heap or stack
	close => reference delete 
	

	g++ -W file_system.cpp -o file_type
*/

#include <iostream>

struct file
{
	int count; // reference cout
	int id;
	inode ino;
};

struct super_block
{
	int s_ninodes;
	int s_nzones;
	int s_dev;
	int s_lock;

	int s_imap_blocks;
	int s_zmap_blocks;
	char *s_imap[8];
	char *s_zmap[8];

	int id;

	int s_isup;		// super table
	int s_imount;	// root -- inode
};

struct inode
{
	int id;

};
// How to be dynamic:
// semantics <====> id <=====> api [ os architecture ]

int main(int argc, char *argv[])
{
	// In kernel , process will initial the runtime environment of typed file	
	file *file_table[64];	// opened fds management

	super_block *super_block_table[8];
	inode *inode_table[32];

	// super_block
	super_block zero;
	zero.id = 0;
	super_block_table[0] = &zero;

	// root inode
	inode root;
	root.id = 0;
	inode_table[0] = &root;

	//mount root
	inode current_inode = root;

	file stdin; stdin.id = 0;
	file stdout; stdout.id = 1;
	file stderror; stderror.id = 2;
	file_table[0] = &stdin;
	file_table[1] = &stdout;
	file_table[2] = &stderror;



	return 0;
}


