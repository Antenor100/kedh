CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lpthread -levdev

# Source directories
SRC_DIR = src
UTILS_DIR = $(SRC_DIR)/utils
SERVICES_DIR = $(SRC_DIR)/services
ENUMS_DIR = $(SRC_DIR)/enums

# Source files
SOURCES = $(SRC_DIR)/main.c \
					$(UTILS_DIR)/keyboard_device.c \
					$(UTILS_DIR)/config_properties.c \
					$(UTILS_DIR)/keybinds_parser.c \
					$(UTILS_DIR)/array_utils.c \
					$(SERVICES_DIR)/key_monitor_service.c \
					$(SERVICES_DIR)/keybind_command_service.c \
					$(ENUMS_DIR)/key_names.c


TARGET = build/kedh-v1.1.3

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

test:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET)
	@echo "\nRunning - Done."

test-c:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET) -c
	@echo "\nRunning - Done."

test-n:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET) -n "Compx 2.4G Wireless Receiver"
	@echo "\nRunning - Done."

test-h:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET) -h
	@echo "\nRunning - Done."

test-t:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET) -t
	@echo "\nRunning - Done."

test-v:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET) -v
	@echo "\nRunning - Done."

test-s:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET) -s
	@echo "\nRunning - Done."

test-k:
	clear
	@echo "\nCleaning up..."
	@make clean
	@echo "Cleaning - Done."

	@echo "\nCompiling..."
	@make
	@echo "Compiling - Done."

	@echo "\nRunning aplication...\n"
	./$(TARGET) -k
	@echo "\nRunning - Done."