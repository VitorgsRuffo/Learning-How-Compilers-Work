CC = gcc

obj = main.o lexer.o parser.o

l9e1: $(obj)
	$(CC) $(obj) -o l9e1 -lm

main.o: main.c  
	$(CC) -c main.c

lexer.o: lexer.c  
	$(CC) -c lexer.c

parser.o: parser.c  
	$(CC) -c parser.c

clean: 
	rm $(obj) l9e1