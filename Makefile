CFLAGS = -Wall -Wextra -Wno-missing-braces
LDFLAGS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -L lib/ -lraylib -lm -lpthread

build:
	@gcc main.c -o sim $(CFLAGS) $(LDFLAGS)

run: build
	@./sim

clean:
	@rm sim
