CC         = gcc
CFLAGS     = -std=c11 -Wall -Wextra -pedantic -g
OBJS       = main.o boards.o estado.o graphics.o historico.o menu.o solver.o valida.o
EXECUTAVEL = GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install

$(EXECUTAVEL): $(OBJS)
	$(CC) -o $(EXECUTAVEL) $(OBJS)

utilizadores:
	sudo mkdir -p /var/www/html/utilizadores
	sudo chmod -R a+rwx  /var/www/html/utilizadores

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp -r img/* /var/www/html/images/

tabuleiros:
	sudo mkdir -p /var/www/html/tabuleiros
	sudo cp -r tab/* /var/www/html/tabuleiros/
	sudo chmod -R a+rwx  /var/www/html/tabuleiros

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install
