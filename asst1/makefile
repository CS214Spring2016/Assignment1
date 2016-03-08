COMPILER = gcc
CCFLAGS = -Wall -g

all: sl

sorted-list.o: sorted-list.c sorted-list.h
	$(COMPILER) $(CCFLAGS) -c sorted-list.c
main.o: main.c sorted-list.h
	$(COMPILER) $(CCFLAGS) -c main.c
libsl.a: sorted-list.o
	ar r libsl.a sorted-list.o
sl: main.o libsl.a
	$(COMPILER) $(CCFLAGS) -o sl main.o libsl.a

transfer:
	cp sorted-list.h sorted-list.c main.c makefile testplan.txt readme.pdf asst1
	tar cfz Asst1.tgz asst1
	scp Asst1.tgz kpb81@java.cs.rutgers.edu:~/CS214

clean:
	@rm -f sort
	@rm -f *.o