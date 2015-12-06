# call
Command-line utility to execute function from specified object file

#### Usage ####

```
$ ./call /lib/x86_64-linux-gnu/libc.so.6 puts "it works"
it works
call returned 0
```

```
$ ./call /lib/x86_64-linux-gnu/libc.so.6 printf $'[%s] %s\n' "`date`" `whoami`
[Sun Dec  6 10:46:34 BRST 2015] felipe
call returned 0
```

```
$ ./call /lib/x86_64-linux-gnu/libc.so.6 getcwd 0
call returned '/home/felipe/dev/call'
```
