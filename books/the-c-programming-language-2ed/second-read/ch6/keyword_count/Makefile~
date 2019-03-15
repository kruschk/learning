objects = main.o binsearch.o getch.o getword.o

keyword_count : $(objects)
	gcc -std=c89 -pedantic -Wall -Werror -Wextra -o keyword_count $(objects)

main.o : keyword_count.h
binsearch.o : keyword_count.h
getch.o : keyword_count.h
getword.o : keyword_count.h

.PHONY : clean
clean :
	rm keyword_count $(objects)
