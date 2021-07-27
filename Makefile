# Clear the implicit built in rules
.SUFFIXES:

#------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif

include $(DEVKITARM)/gba_rules

# canned command sequence for binary data
define bin2o
	bin2s $< | $(AS) $(ARCH) -o $(@)
	echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"_end[];" > `(echo $(<F) | tr . _)`.h
	echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" >> `(echo $(<F) | tr . _)`.h
	echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(<F) | tr . _)`.h
endef

#------------------------------------------------------------------------------
# TARGET is the name of the output, if this ends with _mb a multiboot image is generated
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing extra header files
#------------------------------------------------------------------------------
TARGET   := supertux
BUILD    := build
SOURCES  := src
DATA     := data
INCLUDES :=

# options for code generation {{{
ARCH     := -mthumb -mthumb-interwork
CFLAGS   := -g -Wall -O3 \
            -mcpu=arm7tdmi -mtune=arm7tdmi \
            -fomit-frame-pointer \
            -ffast-math \
            $(ARCH) \
            $(INCLUDE)

CXXFLAGS := $(CFLAGS)
ASFLAGS  := $(ARCH)
LDFLAGS   = -g $(ARCH) -Wl,-Map,$(notdir $@).map

# }}}

# any extra libraries we wish to link with the project
LIBS := -lgba -lm

# directories containing libraries (must be the top level containing include and lib)
LIBDIRS := $(LIBGBA)

#------------------------------------------------------------------------------

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT  := $(CURDIR)/$(TARGET)
export VPATH   := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                  $(foreach dir,$(DATA),$(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(BUILD)

# automatically build a list of object files for our project
CFILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
RAWFILES := $(foreach dir,$(DATA),   $(notdir $(wildcard $(dir)/*.raw)))

export OFILES := $(RAWFILES:.raw=.o) $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

# use CXX for linking C++ projects
export LD := $(CXX)

# build a list of include paths
export INCLUDE := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
                  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                  -I$(CURDIR)/$(BUILD)

# build a list of library paths
export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

#------------------------------------------------------------------------------

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

all : $(BUILD)

clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba

else

DEPENDS := $(OFILES:.o=.d)

$(OUTPUT).gba: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES)

%.o: %.raw
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

endif
