/*
 * Author: Felipe Pena <felipensp at gmail.com>
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "caller.h"

inline static long call_with_0_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"xor %%rax, %%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func)
		: "rax");
#else
	__asm__ __volatile__ (
		"xorl %%eax, %%eax\n\t"
		"call *%1\n\t"
		"movl %%eax, %0"
		: "=r" (ret)
		: "r" (func)
		: "eax");
#endif
	return ret;
}

inline static long call_with_1_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"movq %2, %%rdi\n\t"
		"xor %%rax, %%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func), "m" (argv[3])
		: "rax", "rcx", "rdi");
#else
	__asm__ __volatile__ (
		"push %2\n\t"
		"xorl %%eax, %%eax\n\t"
		"call *%1\n\t"
		"movl %%eax, %0\n\t"
		"addl $4, %%esp\n\t"
		: "=r" (ret)
		: "r" (func), "m" (argv[3])
		: "eax");
#endif
	return ret;
}

inline static long call_with_2_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"movq %3,%%rsi\n\t"
		"movq %2,%%rdi\n\t"
		"xor %%rax,%%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4])
		: "rax", "rcx", "rsi", "rdi");
#else
	__asm__ __volatile__ (
		"push %3\n\t"
		"push %2\n\t"
		"xorl %%eax, %%eax\n\t"
		"call *%1\n\t"
		"movl %%eax, %0\n\t"
		"addl $8, %%esp"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4])
		: "eax");
#endif
	return ret;
}

inline static long call_with_3_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"movq %4,%%rdx\n\t"
		"movq %3,%%rsi\n\t"
		"movq %2,%%rdi\n\t"
		"xor %%rax,%%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5])
		: "rax", "rcx", "rdx", "rsi", "rdi");
#else
	__asm__ __volatile__ (
		"pushl %4\n\t"
		"pushl %3\n\t"
		"pushl %2\n\t"
		"xorl %%eax, %%eax\n\t"
		"call *%1\n\t"
		"movl %%eax, %0\n\t"
		"add $12, %%esp"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5])
		: "eax");
#endif
	return ret;
}

inline static long call_with_4_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"movq %5,%%rcx\n\t"
		"movq %4,%%rdx\n\t"
		"movq %3,%%rsi\n\t"
		"movq %2,%%rdi\n\t"
		"xor %%rax,%%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5]), "m" (argv[6])
		: "rax", "rcx", "rdx", "rsi", "rdi");
#else
	__asm__ __volatile__ (
		"pushl %5\n\t"
		"pushl %4\n\t"
		"pushl %3\n\t"
		"pushl %2\n\t"
		"xorl %%eax, %%eax\n\t"
		"call *%1\n\t"
		"movl %%eax, %0\n\t"
		"add $16, %%esp"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5]), "m" (argv[6])
		: "eax");
#endif
	return ret;
}

inline static long call_with_5_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"movq %6,%%r8\n\t"
		"movq %5,%%rcx\n\t"
		"movq %4,%%rdx\n\t"
		"movq %3,%%rsi\n\t"
		"movq %2,%%rdi\n\t"
		"xor %%rax,%%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5]), "m" (argv[6]), "m" (argv[7])
		: "rax", "rcx", "rdx", "rsi", "rdi", "r8");
#else
	__asm__ __volatile__ (
		"pushl %6\n\t"
		"pushl %5\n\t"
		"pushl %4\n\t"
		"pushl %3\n\t"
		"pushl %2\n\t"
		"xorl %%eax, %%eax\n\t"
		"call *%1\n\t"
		"movl %%eax, %0\n\t"
		"add $20, %%esp"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5]), "m" (argv[6]), "m" (argv[7])
		: "eax");
#endif
	return ret;
}

inline static long call_with_6_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"movq %7,%%r9\n\t"
		"movq %6,%%r8\n\t"
		"movq %5,%%rcx\n\t"
		"movq %4,%%rdx\n\t"
		"movq %3,%%rsi\n\t"
		"movq %2,%%rdi\n\t"
		"xor %%rax,%%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5]), "m" (argv[6]), "m" (argv[7]), "m" (argv[8])
		: "rax", "rcx", "rdx", "rsi", "rdi", "r8", "r9");
#else
	__asm__ __volatile__ (
		"pushl %7\n\t"
		"pushl %6\n\t"
		"pushl %5\n\t"
		"pushl %4\n\t"
		"pushl %3\n\t"
		"pushl %2\n\t"
		"xorl %%eax, %%eax\n\t"
		"call *%1\n\t"
		"movl %%eax, %0\n\t"
		"add $24, %%esp"
		: "=r" (ret)
		: "r" (func), "m" (argv[3]), "m" (argv[4]), "m" (argv[5]), "m" (argv[6]), "m" (argv[7]), "m" (argv[8])
		: "eax");
#endif
	return ret;
}

static int is_illegal_pointer(void *ptr)
{
	int ret = 0;
	int randomfd = open("/dev/random", O_WRONLY);

	if (write(randomfd, ptr, sizeof(void*)) == -1 && errno == EFAULT)
		ret = 1;
	close(randomfd);

	return ret;
}

void caller(CALL_ARGS)
{
	long ret = 0;

	switch (argc - 3) {
		case 0:  ret = call_with_0_arg(func, argc, argv); break;
		case 1:	 ret = call_with_1_arg(func, argc, argv); break;
		case 2:	 ret = call_with_2_arg(func, argc, argv); break;
		case 3:	 ret = call_with_3_arg(func, argc, argv); break;
		case 4:	 ret = call_with_4_arg(func, argc, argv); break;
		case 5:	 ret = call_with_5_arg(func, argc, argv); break;
		case 6:	 ret = call_with_6_arg(func, argc, argv); break;
		default: break;
	}

	if (ret && is_illegal_pointer((void*)ret)) {
		printf("call returned %ld\n", ret);
	} else {
		printf("call returned '%s'\n", (char*)ret);
	}
}
