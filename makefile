


CC=arm-none-eabi-gcc
CPY=arm-none-eabi-objcopy

OUTPUT_DIR := build

INC_DIR=./Includes
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -I$(INC_DIR) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nosys.specs -T stm32_ls.ld -Wl,-Map=$(OUTPUT_DIR)/final.map


all: $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/stm32_startup.o $(OUTPUT_DIR)/final.elf


$(OUTPUT_DIR)/main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

$(OUTPUT_DIR)/stm32_startup.o:stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

	
$(OUTPUT_DIR)/final.elf: $(OUTPUT_DIR)/main.o  $(OUTPUT_DIR)/stm32_startup.o 
	$(CC) $(LDFLAGS) -o $@ $^
	$(CPY) -O ihex $(OUTPUT_DIR)/final.elf $(OUTPUT_DIR)/final.hex


clean:
	rm -rf $(OUTPUT_DIR)\*.elf $(OUTPUT_DIR)\*.hex $(OUTPUT_DIR)\*.map $(OUTPUT_DIR)\*.o 
