all: cartesianTree

cartesianTree.o: cartesianTree.c
	gcc -c -o cartesianTree.o cartesianTree.c

cartesianTree: cartesianTree.o
	gcc -o cartesianTree cartesianTree.o

clean:
	rm -f *.o cartesianTree
