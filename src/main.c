/*
 * Author: Felipe Pena <felipensp at gmail.com>
 */

#include <stdio.h>
#include <dlfcn.h>
#include <bfd.h>
#include "loader.h"
#include "caller.h"

int main(int argc, char **argv)
{
	void *object;
	int (*func)();

	if (argc < 2) return 0;

	object = load_object(argv[1]);
	if (object) {
		func = load_function(object, argv[2]);
	}

	if (object == NULL || func == NULL) {
		func = get_func_addr(argv[1], argv[2]);
		if (!func) {
			printf("Function not found!\n");
			return 1;
		}
	}

	caller(func, argc, argv);

	if (object) {
		dlclose(object);
	}

	return 0;
}
