paging: paging.o pagingHead.o
	gcc -o paging paging.o pagingHead.o

paging.o: paging.c pagingHead.h
	gcc -c paging.c

pagingHead.o: pagingHead.c pagingHead.h
	gcc -c pagingHead.c

