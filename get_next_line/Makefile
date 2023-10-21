CC := g++
NAME := get_next_line.a
CFLAGS := -Wall -Wextra -Werror
LIBFT := ../libft/libft.a
SOURCE := get_next_line.cpp

OBJECTS := $(patsubst %.cpp,%.o,$(SOURCE))

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rc $@ $^
	ranlib $(NAME)

debug:
	$(CC) $(CFLAGS) -g $(SOURCE) $(LIBFT) -o $(NAME)

sanitize:
	$(CC) $(CFLAGS) -fsanitize=address $(SOURCE) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJECTS)

sclean:
	rm -f $(OBJECTS)

fclean: dclean
	rm -f $(NAME)

dclean: clean
	rm -rf $(NAME).dSYM

re: fclean all

sre: sclean all
