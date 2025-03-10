CFLAGS = -Wall -Wextra -Wno-missing-braces
LDFLAGS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -L lib/ -lraylib -lm -lpthread

build:
	@gcc main.c -o game $(CFLAGS) $(LDFLAGS)

run: build
	@./Game

clean:
	@rm game
