################################################################
#
# servo unit tests (based on gcc)
#
################################################################

################################################################
# target
################################################################
TEST = servo
TARGET = servo.out


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
# depending on your test, this might not be correct.
ROOT_DIR  = ../../..

# directory shortcuts for includes and sources
LIB_DIR = $(ROOT_DIR)/lib
MOD_DIR = $(ROOT_DIR)/mod
INIT_DIR = $(ROOT_DIR)/init


################################################################
# source 
################################################################

# Always include $(ROOT_DIR)/Unity/src/unity.c
# Example path to source: $(MOD_DIR)/gps/gps.c
# Include the file being tested both in C_SOURCES and COV_C_SOURCES

# C sources
C_SOURCES =                                   						\
test_servo.c                       								  	\
mock/MOCK_hal.c													  	\
mock/MOCK_led.c													  	\
mock/MOCK_usb.c													  	\
$(ROOT_DIR)/mod/servo/servo.c           							\
$(ROOT_DIR)/Unity/src/unity.c    										

# Coverage Tested Source Files
# Whichever files are being unit tested should be listed here!
COV_C_SOURCES =														\
$(ROOT_DIR)/mod/servo/servo.c

################################################################
# Compiler 
################################################################

# You might be used to arm-none-eabi-gcc, but unit tests are run locally!
CC = gcc

################################################################
# C flags 
################################################################

# C Includes
# This should include a path to all of the headers used in your test
C_INCLUDES =                                           \
-I.                                                    \
-I$(ROOT_DIR)/mod/servo/							   \
-I$(ROOT_DIR)/mod/sensor/							   \
-I$(ROOT_DIR)/mod/imu/								   \
-I$(ROOT_DIR)/mod/usb/								   \
-I$(ROOT_DIR)/mod/led/								   \
-I$(ROOT_DIR)/init/blink/							   \
-I$(LIB_DIR)                                           \
-I$(LIB_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc          \
-I$(LIB_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy   \
-I$(LIB_DIR)/Drivers/CMSIS/Device/ST/STM32H7xx/Include \
-I$(LIB_DIR)/Drivers/CMSIS/Include                     \
-I$(ROOT_DIR)/init/terminal/config/inc				   \
-I$(INIT_DIR)/config/Inc                               \
-I$(ROOT_DIR)/Unity/src/                               \
-I$(ROOT_DIR)/test/mod/gps/mock/

# Preprocessor definitions
# Don't worry about the defs and flags unless you know what you're doing
C_DEFS =         \
-DUSE_HAL_DRIVER \
-DSTM32H750xx    \
-DFLIGHT_COMPUTER \
-DUNIT_TEST

CFLAGS = $(C_INCLUDES) $(C_DEFS) $(OPT) -Wall -g

# Disable some warnings
CFLAGS += -Wno-pointer-to-int-cast
CFLAGS += -Wno-int-to-pointer-cast
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-variable

# Get coverage report
CFLAGS += -ftest-coverage
CFLAGS += -fprofile-arcs

################################################################
# Build the application 
################################################################

# Build all 
# This is invoked with "make". Compiles and builds the test.
all: clean $(BUILD_DIR)/$(TARGET)

# Setup the path for c files
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ -lgcov

$(BUILD_DIR):
	mkdir $@		

# Run test
# This runs the test and generates the coverage report.
# Linux users may not need this
# This set of bash commands is why windows users should use Git Bash
test: $(BUILD_DIR)/$(TARGET)
	@echo THIS TEST MUST BE EXECUTED IN A BASH TERMINAL. CMD/PS do not work.
	"$(BUILD_DIR)/$(TARGET)" > "$(TEST)_results.txt"
	tail -n 3 "$(TEST)_results.txt"
	@echo -e "\nCOVERAGE SUMMARY:\n" >> "$(TEST)_results.txt"
	gcov -o $(BUILD_DIR) $(COV_C_SOURCES) | tee -a "$(TEST)_results.txt"

################################################################
# clean up 
################################################################

# Windows users should use git bash so this command works as expected.
clean:
	-rm -fR $(BUILD_DIR)


################################################################
# EOF 
################################################################