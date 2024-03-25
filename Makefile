# Makefile é script para compilar tudo junto de uma vez, em vez de estar a compilar cada ficheiro

CFLAGS = -Wall -Wextra -pedantic-errors 
CFLAGSI = -I/home/pergih/Code/sChool/CC105/include   # Add o diretório de inclusão

# diretoria do src

SRC_DIR = src

# diretoria do output

BUILD_DIR = build

# Lista de arquivos fonte
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# output do executavel

TARGET = final

# compilar tudo (exceto o clean)
all: $(TARGET)

# final é o .exe com tudo
$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/Pedro.o
	@echo "A Linkar e a compilar tudo"
	gcc $(CFLAGS) $(CFLAGSI) $^ -o $@
	@chmod +x $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "A compilar o $<"
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) $(CFLAGSI) -c $< -o $@


# remover os .o
clean:
	@echo "A remover todos ficheiros exceto src"
	rm -rf $(BUILD_DIR)
