all: phone.o
	gcc -o phone.out phone.o

phone.o: write.o
	gcc -c phone.c
	
write.o:
	gcc -c write.c

run:
	./phone.out
	
clean:
	rm *.o