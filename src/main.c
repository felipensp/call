/*
 * Author: Felipe Pena <felipensp at gmail.com>
 */

#include <stdio.h>
#include "loader.h"
#include "caller.h"

int main(int argc, char **argv)
{
	void *object;
	int (*func)();

	if (argc < 2) return 0;

	object = load_object(argv[1]);
	func = load_function(object, argv[2]);
	caller(func, argc, argv);

	return 0;
}
