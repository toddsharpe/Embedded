######################################
# target
######################################
TARGET = App


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
#OPT = -Og
OPT = -O3


#######################################
# paths
#######################################
# Build path
BUILD_DIR = ../../../build/HiFive/App

######################################
# source
######################################
# C sources
C_SOURCES = \
../sysmem.c \
../../syscalls.c \
../../../External/printf/printf.c \

CXX_SOURCES = \
Main.cpp \
../HiFive1RevB.cpp \
../RiscV.cpp \
../RiscVKernel.cpp \
../SystemTimer.cpp \
../Uart.cpp \
../../Rtos/Kernel.cpp \
../../Rtos/KThread.cpp \
../../Rtos/Scheduler.cpp \
../start.cpp

# ASM sources
ASM_SOURCES = \
../KernelInterrupts.s

#######################################
# binaries
#######################################
PREFIX = riscv64-unknown-elf-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
CXX = $(GCC_PATH)/$(PREFIX)g++
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
DMP = $(GCC_PATH)/$(PREFIX)objdump
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
DMP = $(PREFIX)objdump
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
ifdef OS
   RM = del /Q
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
   endif
endif

#######################################
# Settings
#######################################
RISCV_ARCH = rv32imac
RISCV_ABI = ilp32
RISCV_CMODEL = medlow
RISCV_SERIES = sifive-3-series

TARGET_TAGS = board jlink
TARGET_DHRY_ITERS = 20000000
TARGET_CORE_ITERS = 5000
TARGET_FREERTOS_WAIT_MS = 1000
TARGET_INTR_WAIT_CYCLE  = 0

MTIME_RATE_HZ_DEF=32768

#######################################
# CFLAGS
#######################################

# mcu
MCU = -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_CMODEL)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DMTIME_RATE_HZ_DEF=$(MTIME_RATE_HZ_DEF)

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I../../../Inc \
-I../../../Src \
-I../../../External/printf \

CXX_INCLUDES = $(C_INCLUDES) 


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -ffunction-sections -fdata-sections --specs=nano.specs

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -ffunction-sections -fdata-sections -fcommon --specs=nano.specs

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

CXXFLAGS = $(MCU) $(C_DEFS) $(CXX_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -std=c++17


ifeq ($(DEBUG), 1)
CXXFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = linker.lds

# libraries
LIBS = -lc -lgcc -lm -lstdc++
LIBDIR = 
LDFLAGS = $(MCU) --specs=nano.specs -nostartfiles -T$(LDSCRIPT) $(LIBDIR) -Wl,--start-group $(LIBS) -Wl,--end-group -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
LDFLAGS += -Xlinker --defsym=__heap_max=1

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	$(DMP) -S --disassemble $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).disasm
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	$(RM) $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
