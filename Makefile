stone-paper-scissor: Stone-Paper-Scissor.c
	gcc -std=c11 -Wall -Wextra Stone-Paper-Scissor.c -o stone-paper-scissor

clean:
	rm -f stone-paper-scissor
