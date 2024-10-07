# Compilador e flags
CC = gcc
LDFLAGS =
BLDDIR = .
INCDIR = $(BLDDIR)/inc
SRCDIR = $(BLDDIR)/src
OBJDIR = $(BLDDIR)/obj
CFLAGS = -c -Wall -I$(INCDIR) -g
LIBFLAGS =

# Arquivos fonte e objetos
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Nome do executável
EXE = simplex

.PHONY: all clean compile run build entrada%

all: compile run

compile: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@ $(LIBFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJDIR)/*.o $(EXE)

run:
	./$(EXE)

entrada%: $(EXE)
	./$(EXE) < inputs/$@

build:
	@echo "\033[1;34mCriando estrutura de pastas...\033[0m"
	@mkdir -p $(INCDIR) $(SRCDIR) $(OBJDIR) inputs
	@echo "\033[1;34mMovendo arquivos...\033[0m"
	@mv *.c $(SRCDIR)/ 2>/dev/null || true
	@mv *.h $(INCDIR)/ 2>/dev/null || true
	@echo "\033[1;32mEstrutura criada e arquivos movidos!\033[0m"
