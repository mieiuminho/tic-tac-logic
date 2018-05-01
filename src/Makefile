CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=cgi.h boards.c boards.h estado.c estado.h graphics.c graphics.h historico.c historico.h main.c menu.c menu.h solver.c solver.h valida.c valida.h Makefile
EXECUTAVEL=GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install

$(EXECUTAVEL): main.o boards.o estado.o graphics.o historico.o menu.o solver.o valida.o
	cc -o $(EXECUTAVEL) main.o boards.o estado.o graphics.o historico.o menu.o solver.o valida.o

utilizadores:
	sudo mkdir -p /var/www/html/utilizadores
	sudo chmod -R a+rwx  /var/www/html/utilizadores

imagens:
	sudo mkdir -p /var/www/html/images/default
	sudo mkdir -p /var/www/html/images/dracula
	sudo mkdir -p /var/www/html/images/monokai
	sudo cp img/default/*.* /var/www/html/images/default
	sudo cp img/dracula/*.* /var/www/html/images/dracula
	sudo cp img/monokai/*.* /var/www/html/images/monokai

tabuleiros:
	sudo mkdir -p /var/www/html/tabuleiros/easy
	sudo mkdir -p /var/www/html/tabuleiros/medium
	sudo mkdir -p /var/www/html/tabuleiros/hard
	sudo chmod -R a+rwx  /var/www/html/tabuleiros
	sudo cp tab/easy/*.txt /var/www/html/tabuleiros/easy
	sudo cp tab/medium/*.txt /var/www/html/tabuleiros/medium
	sudo cp tab/hard/*.txt /var/www/html/tabuleiros/hard


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
menu.o: menu.c menu.h boards.h cgi.h estado.h graphics.h historico.h solver.h valida.h
solver.o: solver.c solver.h boards.h cgi.h estado.h graphics.h historico.h menu.h valida.h
valida.o: valida.c valida.h boards.h cgi.h estado.h graphics.h historico.h valida.h
main.o: main.c boards.h cgi.h estado.h historico.h menu.h solver.h
