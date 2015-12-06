#include <stdio.h>
#include "caller.h"

void caller(int (*func)(), int argc, char **argv)
{
	long ret;

	switch (argc - 3) {
		case 1:
			__asm__ __volatile__ (
				"movq %2,%%rdi\n\t"
				"xor %%rax,%%rax\n\t"
				"call *%1\n\t"
				"movq %0, %%rax"
				: "=r" (ret)
				: "r" (func), "m" (argv[3])
				: "rax", "rcx", "rdi");
			break;
		case 2:
			__asm__ __volatile__ (
				"movq %3,%%rsi\n\t"
				"movq %2,%%rdi\n\t"
				"xor %%rax,%%rax\n\t"
				"call *%1\n\t"
				"movq %0, %%rax"
				: "=r" (ret)
				: "r" (func), "m" (argv[3]), "m" (argv[4])
				: "rax", "rcx", "rsi", "rdi");
			break;
		case 3:
			__asm__ __volatile__ (
				"movq %4,%%rdx\n\t"
				"movq %3,%%rsi\n\t"
				"movq %2,%%rdi\n\t"
				"xor %%rax,%%rax\n\t"
				"call *%1\n\t"
				"movq %0, %%rax"
				: "=r" (ret)
				: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5])
				: "rax", "rcx", "rdx", "rsi", "rdi");
			break;
	}
}
