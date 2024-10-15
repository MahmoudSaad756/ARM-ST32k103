


CC=C:\WorkSet\Arm\102021.10\bin\arm-none-eabi-gcc
CPY=C:\WorkSet\Arm\102021.10\bin\arm-none-eabi-objcopy

OUTPUT_DIR := build

INC_DIR=./Includes
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -I$(INC_DIR) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nosys.specs -T stm32_ls.ld -Wl,-Map=$(OUTPUT_DIR)/final.map

# Source files
SRCS = $(wildcard *.c)

# Object files directory
OBJ_DIR = build

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)


# Executable name
TARGET = build\final.elf

all:$(OBJ_DIR) $(TARGET) 

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ 
	$(CPY) -O ihex build\final.elf build\final.hex

# Compile source files into object files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


	
#final.elf: 
#	$(CC) $(LDFLAGS) -o $@ $^
#	$(CPY) -O ihex $(OUTPUT_DIR)/final.elf $(OUTPUT_DIR)/final.hex


# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)