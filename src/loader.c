/*
 * Author: Felipe Pena <felipensp at gmail.com>
 */

#include <dlfcn.h>
#include <bfd.h>
#define HAVE_DECL_BASENAME 1
#include <demangle.h>
#include <string.h>
#include <stdlib.h>
#include "loader.h"

int (*get_func_addr(const char *filename, const char *funcname))()
{
	bfd *ibfd;
	bfd_symbol **symtab;
	symbol_info info;
	void *symaddress = NULL;
	long  size, syms;
	unsigned int i;

	bfd_init();

	ibfd = bfd_openr(filename, NULL);
	bfd_check_format(ibfd, bfd_object);

	size   = bfd_get_symtab_upper_bound(ibfd);
	symtab = (asymbol**)malloc(size);
	syms   = bfd_canonicalize_symtab(ibfd, symtab);

	for (i = 0; i < syms; ++i) {
		const char *unmangled = cplus_demangle(symtab[i]->name, 0);
		if ((unmangled && strcmp(unmangled, funcname) == 0)
			|| strcmp(symtab[i]->name, funcname) == 0) {
			bfd_symbol_info(symtab[i], &info);
			symaddress = (void *)info.value;
		}
	}

	bfd_close(ibfd);
	return (int(*)())symaddress;
}

void *load_object(const char *objfile)
{
	void *handle;

	handle = dlopen(objfile, RTLD_GLOBAL | RTLD_LAZY);

	return handle;
}

int (*load_function(void *handle, const char *funcname))()
{
	return (int(*)())dlsym(handle, funcname);
}
