CC := g++
NAME := libqm.a
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c++14
LIBFT := libft/libft.a
SRC := error.cpp timer.cpp

OBJECTS := $(patsubst %.cpp,%.o,$(SRC))


all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	make -C libft
	ar rc $@ $^ $(LIBFT)
	ranlib $(NAME)

sclean:
	rm -f $(OBJECTS)

clean:
	make -C libft clean
	rm -f $(OBJECTS)

fclean: clean
	rm -f libft/libft.a
	rm -f $(NAME)

re: fclean all


