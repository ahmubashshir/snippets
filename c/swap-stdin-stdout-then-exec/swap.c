/*
 * This is an useless program that jusr swaps
 * STDIN and STDOUT before forking a process.
 *
 * Copyright 2022 Ahmad Hasan Mubashshir <ahmubashshir@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		return EINVAL; // Exit if argument is less than 2
	}

	char **eargv = malloc(argc * sizeof(char*)); // Allocate exec argument array

	for(int i=0; i<argc-1; i++)
	{
		eargv[i] = argv[i+1]; // slice argv[1:]
	}
	eargv[argc-1] = NULL; // denote the end of arguments with NULL

	// Swap FD(File descriptor)s
	dup2(1, 3);		// FD(1) aka STDOUT		-> FD(3) (unassigned)
	dup2(2, 1);		// FD(2) aka STDERR 	-> FD(1) aka STDOUT
	dup2(3, 2);		// FD(3) (copied STDOUT)-> FD(2) aka STDERR
	close(3);		// close FD(3) to prevent leak

	execvp((const char*)eargv[0], (char* const*)eargv); /* Execute the target
														 * program with swapped
														 * STDOUT and STDERR
														 */
	return 0;
}
