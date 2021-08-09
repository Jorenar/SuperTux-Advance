.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/gba_rules

#------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# DATA is a list of directories containing binary data
# MUSIC
# GRAPHICS is a list of directories containing files to be processed by grit
#---------------------------------------------------------------------------------
TARGET   := supertux
BUILD    := build
SOURCES  := src
INCLUDES :=
DATA     := data data/levels
MUSIC    :=
GRAPHICS := data/images $(wildcard data/images/*)

# options for code generation {{{
ARCH     := -mthumb -mthumb-interwork

CFLAGS   := -g -Wall -O2                   \
            -mcpu=arm7tdmi -mtune=arm7tdmi \
            -fomit-frame-pointer           \
            -ffast-math                    \
            $(ARCH)

CFLAGS   += $(INCLUDE)

CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

ASFLAGS  := -g $(ARCH)
LDFLAGS   = -g $(ARCH) -Wl,-Map,$(notdir $*.map)

# }}}

# any extra libraries we wish to link with the project
LIBS := -lgba -lm

# directories containing libraries (must be the top level containing include and lib)
LIBDIRS := $(LIBGBA)

#------------------------------------------------------------------------------

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT  := $(CURDIR)/$(TARGET)
export VPATH   := $(foreach dir, $(SOURCES),  $(CURDIR)/$(dir)) \
                  $(foreach dir, $(DATA),     $(CURDIR)/$(dir)) \
                  $(foreach dir, $(GRAPHICS), $(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(BUILD)

CFILES   := $(foreach dir, $(SOURCES),  $(notdir $(wildcard $(dir)/*.c)))
CPPFILES := $(foreach dir, $(SOURCES),  $(notdir $(wildcard $(dir)/*.cpp)))
SFILES   := $(foreach dir, $(SOURCES),  $(notdir $(wildcard $(dir)/*.s)))
BINFILES := $(foreach dir, $(DATA),     $(notdir $(wildcard $(dir)/*.bin)))
PNGFILES := $(foreach dir, $(GRAPHICS), $(notdir $(wildcard $(dir)/*.png)))

ifneq ($(strip $(MUSIC)),)
	export AUDIOFILES := $(foreach dir,$(notdir $(wildcard $(MUSIC)/*.*)),$(CURDIR)/$(MUSIC)/$(dir))
	BINFILES += soundbank.bin
endif

export LD := $(CXX)

export OFILES_BIN     := $(addsuffix .o,$(BINFILES)) $(PNGFILES:.png=.o)
export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES         := $(OFILES_BIN) $(OFILES_SOURCES)
export HFILES         := $(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE := $(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
                  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                  -I$(CURDIR)/$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

#------------------------------------------------------------------------------

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba $(TARGET).sav

else

$(OUTPUT).gba: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES)

$(OFILES_SOURCES): $(HFILES)


soundbank.bin soundbank.h : $(AUDIOFILES)
	@mmutil $^ -osoundbank.bin -hsoundbank.h


# This rule creates assembly source files using grit
%.s %.h : %.png
	@echo $(notdir $<)
	@grit $< -fts -gt -p -gu16 -o$*

# This rule links in binary data with the .bin extension
%.bin.o %_bin.h : %.bin
	@echo $(notdir $<)
	@$(bin2o)


-include $(DEPSDIR)/*.d

endif
