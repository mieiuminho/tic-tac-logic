CC         = gcc
CFLAGS     = -std=c11 -O2 -Wall -Wextra -pedantic -g
OBJS       = main.o puzzle.o solver.o historico.o valida.o generator.o
BIB        = --filter pandoc-citeproc --bibliography=relatorio/references.bib
OPTIONS    = --latex-engine pdflatex --template relatorio/styles/template.tex
EXECUTAVEL = gerar

$(EXECUTAVEL): $(OBJS)
	$(CC) -o $(EXECUTAVEL) $(OBJS)

report:
	pandoc $(OPTIONS) $(BIB) -s relatorio/report.md -o relatorio.pdf

config:
	sudo apt-get update
	sudo apt-get install pandoc pandoc-citeproc texlive-full

clean:
	@echo "Cleaning..."
	@echo ""
	@curl https://raw.githubusercontent.com/nelsonmestevao/spells/master/art/maid.ascii
	@rm -rf *.o $(EXECUTAVEL) Doxyfile latex html
	@echo ""
	@echo "...✓ done!"
