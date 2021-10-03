myprog : myprog.o line.o solve.o
	gcc -g $^ -o $@

%.o : %.c
	gcc -g -c $<

myprog.o : line.h solve.h
solve.o : solve.h line.h
line.o : line.h