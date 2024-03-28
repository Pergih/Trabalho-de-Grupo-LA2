# Makefile é script para compilar tudo junto de uma vez, em vez de estar a compilar cada ficheiro

CFLAGS = -Wall -Wextra -pedantic -O2

# Diretório dos arquivos fonte
SRC_DIR = src
INC_DIR = include

CFLAGSI := -I$(INC_DIR) # Adicionar o diretório de inclusão

# Adiciona o diretório base aos arquivos de inclusão
INCS_WITH_DIRS := $(patsubst $(INC_DIR)/%,%,$(INCS))

# Diretório de saída
BUILD_DIR = build

# Lista de arquivos fonte
INCS := $(wildcard $(INC_DIR)/*.h)
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Imprime a complexidade das funções
complexidade:
	@echo "Only printing when Modified McCabe Cyclomatic Complexity is above 5"
	@echo | pmccabe -v
	@for file in $(SRCS); do \
		echo "Complexidade do arquivo $$file:"; \
		pmccabe $$file | awk '{if($$1 > 5) print}' | sort -nr; \
		echo "------------------------"; \
	done
# Verifica o código em busca de problemas
check:
	@echo "Verificar o código em busca de problemas"
	@cppcheck --enable=all --suppress=missingIncludeSystem $(CFLAGSI) .

# Cria um arquivo zip com os arquivos fonte
codigo.zip: $(SRCS) $(INCS)
	@echo "Criando arquivo zip com os arquivos fonte e de inclusão"
	@zip -9r $@ $(SRCS) $(INCS) $(INCS_WITH_DIRS)

# output do executavel

TARGET = cards

# compilar tudo (exceto o clean)
all: $(TARGET)

# final é o .exe com tudo
$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/Pedro.o $(BUILD_DIR)/Joao.o $(BUILD_DIR)/Ze.o
	@echo "A Linkar e a compilar tudo"
	gcc $(CFLAGS) $(CFLAGSI) $^ -o $@
	@chmod +x $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "A compilar o $<"
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) $(CFLAGSI) -c $< -o $@

# Remove os arquivos .o e o executável
clean:
	@echo "A remover os temporarios e o zip"
	@rm -rf $(BUILD_DIR) $(TARGET) codigo.zip


