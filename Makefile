CC := g++
NAME := libqm.a
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c++14
LIBFT := libft/libft.a
SRC := error.cpp timer.cpp logging.cpp

OBJECTS := $(patsubst %.cpp,%.o,$(SRC))


all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rc $@ $^
	ranlib $(NAME)

lclean:
	rm -f *.txt

clean:
	rm -f test.o
	rm -f $(OBJECTS)

fclean: clean lclean
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
