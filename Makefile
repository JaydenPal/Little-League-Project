output: projectPart2.o
	gcc projectPart2.o -o output

Baseball.o: projectPart2.c
	gcc -c projectPart2.c

clean: 
	rm *.o output