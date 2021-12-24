CC = gcc

obj = main.o lexer.o parser.o stack.o

l10e4: $(obj)
	$(CC) $(obj) -o l10e4 -lm

main.o: main.c  
	$(CC) -c main.c

lexer.o: lexer.c  
	$(CC) -c lexer.c

parser.o: parser.c  
	$(CC) -c parser.c

stack.o: stack.c  
	$(CC) -c stack.c

clean: 
	rm $(obj) l10e4