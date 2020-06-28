snake: snake.c
	gcc -o snake snake.c -lncurses
	./ snake
clean:
	rm -f snake
