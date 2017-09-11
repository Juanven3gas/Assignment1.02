dun_program: gen_dun.o dun_ls.o
	gcc gen_dun.o dun_ls.o -o dun_program

gen_dun.o: gen_dun.c dun_utils.h
	gcc -Wall -Werror -ggdb gen_dun.c -c

dun_ls.o: dun_ls.c dun_utils.h
	gcc -Wall -Werror -ggdb dun_ls.c -c
	
clean: 
	rm -f *.o dun_program