################################################################ 
#
# sensor.c unit tests (based on gcc)
#
################################################################


################################################################
# target
################################################################
TARGET = test_sensor


################################################################
# build variables 
################################################################

# Debug build?
DEBUG = 1
# Optimization
OPT   = -Og


################################################################
# paths 
################################################################

# build folder
BUILD_DIR = build

# base directory
ROOT_DIR  = ../../../..

# terminal directory
TERMINAL_DIR = $(ROOT_DIR)/terminal/rev4

# terminal mocked directory
MOCK_DIR = $(ROOT_DIR)/test/app/terminal/sensor/mock

# library directory
LIB_DIR = $(ROOT_DIR)/lib

# module directory
MOD_DIR = $(ROOT_DIR)/mod


################################################################
# source 
################################################################

# C sources
C_SOURCES =                                                                                \
test_sensor.c                                                                              \
$(ROOT_DIR)/Unity/src/unity.c                                                              \
$(MOCK_DIR)/mod/pressure/mock_pressure.c                                                   \
$(ROOT_DIR)/unit_tests/mock/lib/Drivers/STM32H7xx_HAL_Driver/Src/mock_stm32h7xx_hal_uart.c \
$(MOD_DIR)/sensor/sensor.c																   \
$(ROOT_DIR)/app/demo/pts/rev4/mod/sensor/sensor.c


################################################################
# Compiler 
################################################################
CC = gcc


################################################################
# C flags 
################################################################

# C Includes
C_INCLUDES =                                           \
-I.                                                    \
-I$(TERMINAL_DIR)                                      \
-I$(TERMINAL_DIR)/config/Inc                           \
-I$(LIB_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc          \
-I$(LIB_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy   \
-I$(LIB_DIR)/Drivers/CMSIS/Device/ST/STM32H7xx/Include \
-I$(LIB_DIR)/Drivers/CMSIS/Include                     \
-I$(TERMINAL_DIR)/mod/commands/                        \
-I$(TERMINAL_DIR)/mod/ignition/                        \
-I$(TERMINAL_DIR)/mod/led/                             \
-I$(TERMINAL_DIR)/mod/power/                           \
-I$(TERMINAL_DIR)/mod/flash/                           \
-I$(TERMINAL_DIR)/mod/pressure/                        \
-I$(TERMINAL_DIR)/mod/sensor/                          \
-I$(ROOT_DIR)/Unity/src/                               \
-I$(MOCK_DIR)/terminal/rev4							   \
-I$(ROOT_DIR)/app/terminal/rev3/lib/Core/inc           \
-I$(ROOT_DIR)/app/demo/pts/rev4/mod/sensor

# Preprocessor definitions
C_DEFS =         \
-DUSE_HAL_DRIVER \
-DSTM32H750xx    \
-DUNIT_TEST

CFLAGS = $(C_INCLUDES) $(C_DEFS) $(OPT) -Wall -g

# Disable some warnings
CFLAGS += -Wno-pointer-to-int-cast
CFLAGS += -Wno-int-to-pointer-cast
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-variable

# build all 
all: $(BUILD_DIR)/$(TARGET)


################################################################
# Build the application 
################################################################

# Setup the path for c files
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

$(BUILD_DIR):
	mkdir $@		

test:
	echo "$(BUILD_DIR)"


################################################################
# clean up 
################################################################

clean:
	-rm -fR $(BUILD_DIR)


################################################################
# EOF 
################################################################
