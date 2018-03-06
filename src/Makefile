CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=cgi.h estado.c estado.h exemplo.c Makefile
EXECUTAVEL=GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install

$(EXECUTAVEL): exemplo.o estado.o
	cc -o $(EXECUTAVEL) exemplo.o estado.o

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp img/*.png /var/www/html/images

GandaGalo.zip: $(FICHEIROS)
	zip -9 GandaGalo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install

estado.o: estado.c estado.h
exemplo.o: exemplo.c cgi.h estado.h
