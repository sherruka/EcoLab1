ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
	TOOLCHAIN = $(ECO_TOOLCHAIN)
	TOOL = arm-none-eabi-
	GNU = $(TOOLCHAIN)$(SLASH)xpack-arm-none-eabi-gcc-13.2.1-1.1$(SLASH)bin$(SLASH)
	ECO = $(TOOLCHAIN)$(SLASH)eco_tools_1_0_0$(SLASH)
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = /
	SWALLOW_OUTPUT =
	TOOLCHAIN = $(ECO_TOOLCHAIN)
	TOOL = arm-none-eabi-
	GNU = $(TOOLCHAIN)$(SLASH)xpack-arm-none-eabi-gcc-13.2.1-1.1$(SLASH)bin$(SLASH)
	ECO = $(TOOLCHAIN)$(SLASH)eco_tools_1_0_0$(SLASH)
endif 

ifeq ($(TARGET), 1)
OUT_TARGET = libD39330A106574FC38508EC1C37BBB18A.a
ifeq ($(DEBUG), 1)
CONFIG_TARGET = StaticDebug
CCFLAGS_TARGET = -Wall -g -DECO_LIB
LDFLAGS_TARGET =
ARCH_TARGET = arm-v7m
else
CONFIG_TARGET = StaticRelease
CCFLAGS_TARGET = -O3 -DECO_LIB
LDFLAGS_TARGET =
ARCH_TARGET = arm-v7m
endif
else
OUT_TARGET = D39330A106574FC38508EC1C37BBB18A.so
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -fPIC -g -DECO_DLL
LDFLAGS_TARGET = -shared
ARCH_TARGET = arm-v7m
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -O3 -fPIC -DECO_DLL
LDFLAGS_TARGET = -shared
ARCH_TARGET = arm-v7m
endif
endif

# include directories
INC = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)SharedFiles 


# source files.
SRC = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoLab2.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoLab2Factory.c

OBJ = $(SRC:.c=.o)

OUT = $(OUT_TARGET)
OUT_DIR = ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET)

 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = $(CCFLAGS_TARGET) -Wall -Wno-missing-braces -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DECO_OS -DECO_STM32 -DUGUID_UTILITY
 
# compiler
CC = $(TOOL)gcc
AR = $(TOOL)gcc-ar

ifeq ($(TARGET), 1)
CMD_TARGET=$(GNU)$(AR) rcs
else
CMD_TARGET=$(GNU)$(CC) -o
endif

# library paths
LIBS = -lc -lm -lgcc
 
# compile flags
LDFLAGS = $(LDFLAGS_TARGET)
 
.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(GNU)$(CC) $(INC) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(CMD_TARGET) $(OUT_DIR)$(SLASH)$(OUT) $(OBJ) $(LDFLAGS)
	rm $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT_DIR)$(SLASH)$(OUT)
