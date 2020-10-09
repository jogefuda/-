override SOURCE = "$(FILE)"
a = $(shell find ./ -maxdepth 1 -type f -name '$(FILE)*' -printf "%f" | sed 's/ /?/g')

CC = gcc

.PHONY: all a.out build-run

all: a.out
	@./a.out

a.out: $(a)
	@$(CC) -g "$<"
	
