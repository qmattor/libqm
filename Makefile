CC := g++
NAME := libqm.a
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c++14
LIBFT := libft/libft.a
GNL := get_next_line/get_next_line.a
SRC := error.cpp timer.cpp logging.cpp fraction.cpp complex.cpp

OBJECTS := $(patsubst %.cpp,%.o,$(SRC))


all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	# make -C libft
	# make -C get_next_line
	ar rc $@ $^
	ranlib $(NAME)

lclean:
	rm -f *.log

clean:
	# make -C libft clean
	# make -C get_next_line clean
	rm -f test.o
	rm -f $(OBJECTS)

fclean: clean lclean
	# make -C libft fclean
	# make -C get_next_line fclean
	rm -f tests
	rm -f main.out
	rm -f $(NAME)

re: fclean all

tests: test

test: $(OBJECTS)
	$(CC) $(CFLAGS) -c test.cpp -o test.o
	$(CC) $(CFLAGS) $^ test.o -lboost_unit_test_framework -o tests

main_test: $(OBJECTS)
	$(CC) $(CFLAGS) -g $^ main.cpp -o main.out
