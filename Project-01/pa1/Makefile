# ***
# *** DO NOT modify this file 
# ***
GCC = gcc -g -std=c99 -Wall -Wshadow -Wvla -pedantic 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose

#TESTFALGS = -DTEST_MAIN -DTEST_ARRAY_LOAD -DTEST_ARRAY_SAVE -DTEST_ARRAY_SHELLSORT -DTEST_LIST_LOAD -DTEST_LIST_SAVE -DTEST_LIST_SHELLSORT  

SRCS = pa1.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(OBJS) -o pa1

#.c.o: 
#	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3

test1: pa1
	./pa1 -a inputs/15.b output1
	diff -w output1 expected/15sa.b
test2: pa1
	./pa1 -a inputs/1K.b output2
	diff -w output2 expected/1Ksa.b
testread: pa1
	./pa1 -l inputs/15.b output3
	diff -w output3 inputs/15.b 
test3: pa1
	./pa1 -l inputs/15.b output4
	diff -w output4 expected/15sl.b 
test4: pa1
	./pa1 -l inputs/1K.b output5
	diff -w output5 expected/1Ksl.b
memory: pa1
	$(VAL) ./pa1 -a inputs/15.b myresult 

clean: # remove all machine generated files
	rm -f pa1 *.o output? vallog testgen
