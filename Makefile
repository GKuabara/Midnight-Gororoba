CC = g++
VFLAGS = --show-leak-kinds=all --leak-check=full --track-origins=yes -s
CFLAGS = -Wall -Wextra -Werror
CFILES = main.cpp
TARGET = out

all: $(OFILES)
	@$(CC) $(CFILES) -o $(TARGET) -g

$(OFILES): $(CFILES)
	@$(CC)  $(CFLAGS) $(CFILES) -g

run:
	@./$(TARGET)

val:
	@valgrind ./$(TARGET) $(VFLAGS)

clean:
	@rm $(TARGET)

zip:
	@zip -r MidnightGororoba $(INCLUDE) Makefile $(CFILES)