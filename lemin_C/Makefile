CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -Ilibft/functions
TARGET = lem-in
LIBFT = libft/libft.a
SOURCES = main.c edge.c node.c graph.c parser.c simulation.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(TARGET)

$(LIBFT): $(wildcard libft/functions/*.c) libft/functions/libft.h
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	$(MAKE) -C libft clean

fclean: clean
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
