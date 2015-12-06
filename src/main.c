/*
 * Author: Felipe Pena <felipensp at gmail.com>
 */

#include <stdio.h>
#include <dlfcn.h>
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
		printf("%s\n", dlerror());
		return 1;
	}

	caller(func, argc, argv);

	dlclose(object);

	return 0;
}
