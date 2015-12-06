#ifndef CALL_CALLER_H
#define CALL_CALLER_H

#define CALL_ARGS int (*func)(), int argc, char **argv

void caller(int(*)(), int, char**);

#endif
