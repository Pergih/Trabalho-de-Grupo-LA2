# Makefile é script para compilar tudo junto de uma vez, em vez de estar a compilar cada ficheiro

CFLAGS = -Wall -Wextra -pedantic -O2

# Diretório dos arquivos fonte
SRC_DIR = src

# Diretório de saída
BUILD_DIR = build

# Lista de arquivos fonte
SRCS := $(wildcard $(SRC_DIR)/*.c)
INCS := $(wildcard $(SRC_DIR)/*.h)
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
	@echo "A criar arquivo zip com os arquivos fonte"
	@cd $(SRC_DIR) && zip -9r ../$@ *


# output do executavel

TARGET = cards

# compilar tudo (exceto o clean)
all: $(TARGET)

# final é o .exe com tudo
$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/Sort.o $(BUILD_DIR)/Combinacao.o
	@echo "A Linkar e a compilar tudo"
	gcc $(CFLAGS) $^ -o $@
	@chmod +x $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "A compilar o $<"
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -c $< -o $@

# Remove os arquivos .o e o executável
clean:
	@echo "A remover os temporarios e o zip"
	@rm -rf $(BUILD_DIR) $(TARGET) codigo.zip


