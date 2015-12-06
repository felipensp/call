#ifndef CALL_LOADER_H
#define CALL_LOADER_H

void* load_object(const char*);
int (*load_function(void*, const char*))();

#endif /* CALL_LOADER_H */
