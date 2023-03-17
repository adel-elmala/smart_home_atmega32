# SRC = 	main.c\
# 		APP/MP.c\
# 		APP/test.c\
# 		HAL/FingerPrint/FP.c\
# 		HAL/LCD/LCD.c\
# 		HAL/UltraSonic/UltraSonic.c\
# 		HAL/LM35/LM35.c\
# 		MCAL/PWM/PWM.c\
# 		MCAL/UART/UART.c\
# 		MCAL/StopWatch/StopWatch.c\
# 		MCAL/SPI/SPI.c\
# 		MCAL/TIMER/timer.c\
# 		MCAL/EXT_INT/External_INT.c\
# 		MCAL/ADC/ADC.c\
# 		MCAL/GIE/GIE.c\
# 		MCAL/DIO/dio.c\
# 		LIB/Queue/Queue.c\
# 		# MCAL/EEPROM_Internal/EEPROM.c\
# 		# HAL/OLED/OLED.c\
# 		# MCAL/I2C/I2C.c\
# 		# HAL/Servo/Servo.c\

SRC = 	main.c\
		APP/test.c\
		APP/MP.c\
		HAL/FingerPrint/FP.c\
		HAL/LCD/LCD.c\
		HAL/UltraSonic/UltraSonic.c\
		LIB/Queue/Queue.c\
		MCAL/GIE/GIE.c\
		MCAL/DIO/dio.c\
		MCAL/TIMER/timer.c\
		MCAL/PWM/PWM.c\
		MCAL/UART/UART.c\
		MCAL/EXT_INT/External_INT.c\
		MCAL/StopWatch/StopWatch.c\
		HAL/Servo/Servo.c\
		HAL/LM35/LM35.c\
		MCAL/ADC/ADC.c\
		HAL/OLED/OLED.c\
		MCAL/EEPROM_Internal/EEPROM.c\
		MCAL/I2C/I2C.c\
		# MCAL/TWI/TWI.c\
		# MCAL/SPI/SPI.c\




OBJ = $(subst .c,.o, $(SRC))

MCU = atmega32
FLASHER = usbasp
F_CPU = 16000000UL 
HFUSE = 0xc2
HFUSE_BITS = hfuse:w:$(HFUSE):m

# CFLAGS = -Og -ggdb -Wall -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DBAUD=$(BAUD)
CFLAGS = -Os -Wall -mmcu=$(MCU) -DF_CPU=$(F_CPU) 
# CFLAGS += -Wno-pointer-sign #disable pointer mismatch warning

INCLUDE  = -I./utils
INCLUDE += -I./MCAL
INCLUDE += -I./HAL
# INCLUDE += -I/lib/avr/include

# LD_AVR = -L/lib/avr/lib/avr5 -latmega32a
LD_AVR = 

all: compile build flash

# default:
# 	@echo $(filter %led,$(SRC))
	
compile:$(OBJ)
	
	@avr-gcc $(CFLAGS) $(INCLUDE) $(LD_AVR) $(OBJ)  -o ./bin/main.elf
%.o:%.c
	@echo "compiling $^"
	@avr-gcc $(CFLAGS) $(INCLUDE) $(LD_AVR) $^ -c  -o $@ 

build:
	@echo " building Hex file ... "

	@avr-objcopy  -j .text -j .data -O ihex ./bin/main.elf ./bin/main.hex

flash:build
	# avrdude -c $(FLASHER) -p $(MCU) -U $(HFUSE_BITS) -U flash:w:./bin/main.hex
	avrdude -c $(FLASHER) -p $(MCU)  -U flash:w:./bin/main.hex

clean:
	$(foreach file,$(OBJ),$(shell rm $(file)))


sim:
	simavr -g -m $(MCU) ./bin/main.elf
gdb:
	avr-gdb -x gdb-commands -tui 
