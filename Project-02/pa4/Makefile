WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
TESTFALGS = 

SRCS = tree.c main.c file.c eval.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(OBJS) -o pa4

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3 test4 test5 test6 test7 test8 test9

b0: pa4
	./pa4 -b examples/ops0.b outputs/output0.b
	diff outputs/output0.b examples/ops0.b
b1: pa4
	./pa4 -b examples/ops1.b outputs/output1.b
	diff outputs/output1.b examples/ops1.b
b2: pa4
	./pa4 -b examples/ops2.b outputs/output2.b
	diff outputs/output2.b examples/ops2.b
b3: pa4
	./pa4 -b examples/ops3.b outputs/output3.b
	diff outputs/output3.b examples/ops3.b
b: b0 b1 b2 b3
e0: pa4
	./pa4 -e examples/tree0.b
e1: pa4
	./pa4 -e examples/tree1.b
e2: pa4
	./pa4 -e examples/tree2.b
e3: pa4
	./pa4 -e examples/tree3.b
e0i: pa4
	./pa4 -e examples/invalidtree0.b
e1i: pa4
	./pa4 -e examples/invalidtree1.b
e2i: pa4
	./pa4 -e examples/invalidtree2.b
ei: e0i e1i e2i
e: e0 e1 e2 e3 ei

memory: pa1
	$(VAL) ./pa1 -l examples/15.b output1.b
