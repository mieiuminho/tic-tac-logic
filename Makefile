CC         = gcc
CFLAGS     = -std=c11 -O2 -Wall -Wextra -pedantic -g
OBJS       = src/main.o src/boards.o src/estado.o src/graphics.o src/historico.o src/menu.o src/solver.o src/valida.o
SRCDIR     = src
EXECUTAVEL = GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin

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

docs:
	doxygen -g
	doxygen

clean:
	@echo "Cleaning..."
	@echo ""
	@curl https://raw.githubusercontent.com/nelsonmestevao/spells/master/art/maid.ascii
	@rm -rf *.o $(EXECUTAVEL) Doxyfile latex html
	@echo ""
	@echo "...✓ done!"
