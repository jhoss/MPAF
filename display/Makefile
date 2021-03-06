#
# Makefile for LUNE
#
# To link with other packages, add:
#
# CXXFLAGS   += -I${ANOTHERPKG}/src ... 
# ROOTGLIBS  += -lRooFitCore -lRooFit
# ROOTGLIBS  += -L../${ANOTHERPKG}/lib -l${ANOTHERPKG}
# ...

PKGNAME := MPAFDisplay

### global options

# Architecture
ARCH         := $(shell root-config --arch)

# File suffixes
OBJSUFFIX  := o
DEPSUFFIX  := d
DLLSUFFIX  := so

# File directories
OBJDIR     := .o
DEPDIR     := .d
BINDIR     := $(MPAFDisplay)/bin

# output directories
SOLIBDIR   := $(MPAFDisplay)/lib
PCMDIR     := $(MPAFDisplay)/lib
SOLIB      := $(SOLIBDIR)/lib$(PKGNAME).$(DLLSUFFIX)
PCM	   := $(PKGNAME)_dict_core_rdict.pcm

__dummy := $(shell mkdir -p $(OBJDIR) $(DEPDIR) $(BINDIR) $(SOLIBDIR))

### compilator, linker, flags and options
CXX        := g++
LD         := g++
OUTPUTOPT  := -o
OPTFLAGS   := -g -O2 -Wall -fPIC -Wno-deprecated
CXXFLAGS   := $(OPTFLAGS)
LDFLAGS    := -shared
LIBS       :=

# Architecture dependant options
-include $(ARCH).mk


### processing of the modules
# find the modules to include and compile
MODULES    := $(subst /module.mk,,$(wildcard */module.mk))

__dummy := $(shell ./genmak.sh $(MODULES))


ifneq (,$(findstring 5.3,$(ROOTSYS)))
all: lib
else
all: lib pcm
endif

# the source files to compile (without suffix)
SRC        :=
PROG       :=
PROGSRC    :=
#VPATH      :=

-include gen.mk

### build targets and include path for compilation
OBJS       := $(addprefix ${OBJDIR}/, $(addsuffix .$(OBJSUFFIX), $(SRC)))
DEPS       := $(addprefix ${DEPDIR}/, $(addsuffix .$(DEPSUFFIX), $(SRC)))
DEPS       += $(addprefix ${DEPDIR}/, $(addsuffix .$(DEPSUFFIX), $(PROGSRC)))
CXXFLAGS   += -I. -I.. $(patsubst %, -I%, $(MODULES))

### External libraries
# ROOT
ROOTCFLAGS := $(shell root-config --cflags)
ROOTGLIBS  := $(shell root-config --glibs) -lMinuit -lMinuit2 -lHtml -lEG -lThread -lRooFit -lRooFitCore -lFoam

# add possible new dependencies
# -lMinuit2

ROOTCINT   := rootcint
CXXFLAGS   += $(ROOTCFLAGS)
LIBS       += $(ROOTGLIBS) 

# libxml2
#CXXFLAGS   += $(shell xml2-config --cflags)
#LIBS       += $(shell xml2-config --libs)

### Rules
.PHONY: all clean

.PRECIOUS: ${OBJDIR}/%.bin %SK.cc %.hh

lib: $(SOLIB)
pcm: $(PCM)
prog: $(PROG)

#gen.mk dictgen.mk: $(MODULES)
#	./genmak.sh $(MODULES)

# the main library rule
$(SOLIB): $(OBJS)
	@echo "Linking $^"
	@$(LD) $(LDFLAGS) $^ $(LIBS) $(FLIBS) $(OUTPUTOPT) $@
	@echo "Successfully completed $@"

-include dictgen.mk

cleanAll:
	@echo "Cleaning up..."
	@echo $(DEPS)
	@echo $(OBJS)
	@echo $(SOLIB)
	@echo $(PROG)
	@echo $(PROGSRC)

# clean rule
clean:
	@echo "Cleaning up..."
	@echo $(DEPS)
	@echo $(OBJS)
	@echo $(SOLIB)
	@rm -f $(DEPS) $(OBJS) $(SOLIB) $(foreach i,$(MODULES),$(i)/dict_$(i).*) gen.mk dictgen.mk
	@rm core/MPAFDisplay_dict*
######

# .o building rules
${OBJDIR}/%.$(OBJSUFFIX) : %.cxx ${DEPDIR}/%.$(DEPSUFFIX)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

${OBJDIR}/%.$(OBJSUFFIX) : %.cpp ${DEPDIR}/%.$(DEPSUFFIX)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

${OBJDIR}/%.$(OBJSUFFIX) : %.cc ${DEPDIR}/%.$(DEPSUFFIX)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

${OBJDIR}/%.$(OBJSUFFIX) : %.C ${DEPDIR}/%.$(DEPSUFFIX)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# .d building rules
${DEPDIR}/%.$(DEPSUFFIX): %.cxx
#	@echo "Making $@"
	@$(CXX) -MM $(CXXFLAGS) $< \
	| sed 's|\('`basename $*`'\)\.o[ :]*|'$(OBJDIR)'/'`dirname $*`'/\1.o '$(DEPDIR)'/'`dirname $*`'/\1.d : |g' \
	> $@

${DEPDIR}/%.$(DEPSUFFIX): %.cpp
#	@echo "Making $@"
	@$(CXX) -MM $(CXXFLAGS) $< \
	| sed 's|\('`basename $*`'\)\.o[ :]*|'$(OBJDIR)'/'`dirname $*`'/\1.o '$(DEPDIR)'/'`dirname $*`'/\1.d : |g' \
	> $@

${DEPDIR}/%.$(DEPSUFFIX): %.cc
#	@echo "Making $@"
	@$(CXX) -MM $(CXXFLAGS) $< \
	| sed 's|\('`basename $*`'\)\.o[ :]*|'$(OBJDIR)'/'`dirname $*`'/\1.o '$(DEPDIR)'/'`dirname $*`'/\1.d : |g' \
	> $@

${DEPDIR}/%.$(DEPSUFFIX): %.C
#	@echo "Making $@"
	@$(CXX) -MM $(CXXFLAGS) $< \
	| sed 's|\('`basename $*`'\)\.o[ :]*|'$(OBJDIR)'/'`dirname $*`'/\1.o '$(DEPDIR)'/'`dirname $*`'/\1.d : |g' \
	> $@

# .bin building rules
${OBJDIR}/%.bin: ${OBJDIR}/%.$(OBJSUFFIX) | $(SOLIB)
	$(CXX) $(CXXFLAGS) $(LIBS) -L$(SOLIBDIR) -l$(PKGNAME) $^ -o $@

$(PCM): core/$(PKGNAME)_dict_core_rdict.pcm  #core/$(PKGNAME)_dict_core.cc
	cp $< $(PCMDIR)/$@
	cp $< $(MPAFDisplay)/$@
#	cp $< $(PCMDIR)/$@


ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

