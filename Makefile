output: Assignment5.o
	gcc Assignment5.o -o output

Baseball.o: Assignment5.c
	gcc -c Assignment5.c

clean: 
	rm *.o output