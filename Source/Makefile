CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC = main.c Function.c
OBJ = $(SRC:.c=.o)
EXEC = SystemTournois
DEFAULT_FILE = default.txt

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	@if [ -z "$(USER_ARGS)" ]; then \
		./$(EXEC) $(DEFAULT_FILE); \
	else \
		./$(EXEC) $(USER_ARGS); \
	fi

doxyfile:
	doxygen -g Doxyfile.in

doc: doxyfile
	doxygen Doxyfile

clean:
	rm -f $(OBJ)

mrproper: clean
	rm -f $(EXEC)
	rm -rf html/
	rm -rf latex/
	rm -f Doxyfile
	rm -f Doxyfile.in
	rm -f Doxyfile.in.bak
	rm -f resultatT.txt
