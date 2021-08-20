list: nodes.o flights.o main.c
	gcc -o flights nodes.o flights.o main.c

nodes.o: nodes.c flight.h LLNode.h 
	gcc -c nodes.c  

flights.o: flights.c LLNode.h flight.h
	gcc -c flights.c 



clean:
		/bin/rm -f *.o flights
		/bin/rm *.h.gch