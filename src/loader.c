#include <dlfcn.h>
#include "loader.h"

void* load_object(const char *objfile)
{
	void *handle;

	handle = dlopen(objfile, RTLD_LOCAL | RTLD_LAZY);

	return handle;
}

int (*load_function(void *handle, const char *funcname))()
{
	return (int(*)())dlsym(handle, funcname);
}
