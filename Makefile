mcu1_hal = ./HAL/FingerPrint/FP.c ./HAL/OLED/OLED.c ./HAL/RFID/RFID.c ./HAL/LCD/LCD.c
# mcu1_hal = ./HAL/FingerPrint/FP.c ./HAL/RFID/RFID.c ./HAL/LCD/LCD.c

mcu1_mcal = ./MCAL/EEPROM_Internal/EEPROM.c  ./MCAL/I2C/I2C.c\
			./MCAL/SPI/SPI.c ./MCAL/UART/UART.c ./MCAL/TIMER/timer.c ./MCAL/GIE/GIE.c ./MCAL/DIO/dio.c

mcu1_lib = ./LIB/Queue/Queue.c

mcu1_app = ./APP/mcu_1/MP.c


SRC = main.c $(mcu1_app) $(mcu1_hal) $(mcu1_mcal) $(mcu1_lib)


OBJ = $(subst .c,.o, $(SRC))



MCU = atmega32
FLASHER = usbasp
F_CPU = 16000000UL 

HFUSE_BITS = 0xc2
HFUSE = hfuse:w:$(HFUSE_BITS):m
AVRDUDE_ARGS = $(HFUSE)

CFLAGS = -Os  -Wall -mmcu=$(MCU) -DF_CPU=$(F_CPU)  
CFLAGS += -Wno-pointer-sign -Wno-strict-aliasing #disable pointer mismatch warning

INCLUDE  = -I./utils
INCLUDE += -I./MCAL
INCLUDE += -I./HAL

# avr lib
LD_AVR =  
TARGET = mcu1
all: compile build flash

# default:
# 	@echo $(filter %led,$(SRC))

compile:$(TARGET)

$(TARGET):$(OBJ)
	@avr-gcc $(CFLAGS) $(INCLUDE) $(LD_AVR) $(OBJ)  -o ./bin/$@.elf
	
%.o:%.c
	@echo "compiling $^"
	@avr-gcc $(CFLAGS) $(INCLUDE) $(LD_AVR) $^ -c  -o $@ 

build:
	@echo " building Hex file ... "
	@avr-objcopy  -j .text -j .data -O ihex ./bin/$(TARGET).elf ./bin/$(TARGET).hex


flash:build
	avrdude -c $(FLASHER) -p $(MCU) -U $(AVRDUDE_ARGS) -U flash:w:./bin/$(TARGET).hex -F
	# avrdude -c $(FLASHER) -p $(MCU)  -U flash:w:./bin/$(TARGET).hex 

clean:
	$(foreach file,$(OBJ),$(shell rm $(file)))


sim:
	simavr -g -m $(MCU) ./bin/main.elf
gdb:
	avr-gdb -x gdb-commands -tui 
