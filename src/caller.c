#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "caller.h"

 static long call_with_0_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"xor %%rax,%%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func)
		: "rax");
#else
#error Architecture not supported yet
#endif
	return ret;
}

inline static long call_with_1_arg(CALL_ARGS)
{
	long ret;
#ifdef __x86_64__
	__asm__ __volatile__ (
		"movq %2,%%rdi\n\t"
		"xor %%rax,%%rax\n\t"
		"call *%1\n\t"
		"movq %%rax, %0"
		: "=r" (ret)
		: "r" (func), "m" (argv[3])
		: "rax", "rcx", "rdi");
#else
#error Architecture not supported yet
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
#error Architecture not supported yet
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
#error Architecture not supported yet
#endif
	return ret;
}

inline static int is_illegal_pointer(void *ptr)
{
	int ret = 0;
	int randomfd = open("/dev/random", O_WRONLY);

	if (write(randomfd, ptr, sizeof(void*)) == -1 && errno == 14) /* EFAULT */
		ret = 1;
	close(randomfd);

	return ret;
}

void caller(CALL_ARGS)
{
	long ret = 0;

	switch (argc - 3) {
		case 1:	 ret = call_with_1_arg(func, argc, argv); break;
		case 2:	 ret = call_with_2_arg(func, argc, argv); break;
		case 3:	 ret = call_with_3_arg(func, argc, argv); break;
		default: ret = call_with_0_arg(func, argc, argv); break;
	}

	if (ret && is_illegal_pointer((void*)ret)) {
		printf("call returned %ld\n", ret);
	} else {
		printf("call returned '%s'\n", (char*)ret);
	}
}
