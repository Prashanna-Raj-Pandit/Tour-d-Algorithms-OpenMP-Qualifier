CC = g++
CFLAGS = -fopenmp
TARGETS = bbs bbp qss qsp reference mss msp

all: $(TARGETS)

# Pattern rule to compile each target from its respective .cpp file
%: %.cpp
	@echo "Compiling $@ from $@.cpp"
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGETS)
