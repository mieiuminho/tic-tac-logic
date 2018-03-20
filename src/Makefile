CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=cgi.h estado.c estado.h graphics.c graphics.h historico.c historico.h main.c valida.c valida.h Makefile
EXECUTAVEL=GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install

$(EXECUTAVEL): main.o estado.o graphics.o historico.o valida.o
	cc -o $(EXECUTAVEL) main.o estado.o graphics.o historico.o valida.o

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp img/*.png /var/www/html/images

tabuleiros:
	sudo mkdir -p /var/www/html/tabuleiros
	sudo cp tab/*.txt /var/www/html/tabuleiros


GandaGalo.zip: $(FICHEIROS)
	zip -9 GandaGalo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install


estado.o: estado.c estado.h
graphics.o: graphics.c graphics.h estado.h cgi.h
historico.o: historico.c historico.h estado.h cgi.h graphics.h
valida.o: estado.h valida.c valida.h
main.o: main.c cgi.h estado.h historico.h
