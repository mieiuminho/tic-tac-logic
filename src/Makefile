CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=cgi.h boards.c boards.h estado.c estado.h graphics.c graphics.h historico.c historico.h main.c menu.c menu.h valida.c valida.h Makefile
EXECUTAVEL=GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install

$(EXECUTAVEL): main.o boards.o estado.o graphics.o historico.o menu.o valida.o
	cc -o $(EXECUTAVEL) main.o boards.o estado.o graphics.o historico.o menu.o valida.o

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp img/*.png /var/www/html/images
	sudo cp img/dracula/*.png /var/www/html/images/dracula

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


boards.o: boards.c boards.h cgi.h estado.h graphics.h historico.h valida.h
estado.o: estado.c estado.h
graphics.o: graphics.c graphics.h cgi.h estado.h
historico.o: historico.c historico.h cgi.h estado.h graphics.h menu.h valida.h
menu.o: menu.c menu.h boards.h cgi.h estado.h graphics.h historico.h valida.h
valida.o: valida.c valida.h estado.h
main.o: main.c boards.h cgi.h estado.h historico.h menu.h
