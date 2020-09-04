all:
	@echo "Use 'build' to compile, 'run' to execute and 'clean' to remove"
build:
	gcc -o my_shell.out my_shell.c
run:
	./my_shell.out
clean:
	rm my_shell.out
