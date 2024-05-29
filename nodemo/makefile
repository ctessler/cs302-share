#
# A makefile for C++ projects, working with the following assumptions.
#
# (1) All C++ source files (*.cpp) are contained in the src directory.
# (2) All C++ header files (*.hpp,*.h) are contained in the inc directory.
#
# (3) The compilation of all source files creates a single executable,
#     i.e only ony source file contains a main.
#
# (4) The output executable will be named by the $(EXE) variable
#
# The make targets:
#     $ make
#     Will create $(EXE)
#
#     $ make clean
#     Will remove the object and dependency files
#

# The executable name, the only variable that needs changing
EXE := nodemo

#
# No changes are required below this line.
#
SRCDIR := src
INCDIR := inc
OBJDIR := obj
SRCS := $(shell \
    find $(SRCDIR) -name '*.cpp' \
        -or -name '*.h' \
        -or -name '*.hpp')

OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)
INCFLAGS := $(addprefix -I,$(INCDIR))
CXXFLAGS := $(INCFLAGS) -std=c++20 -ggdb

$(EXE) : $(OBJS)
	$(CXX) $(OBJS) -o $@ 

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR) depend
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean depend
clean:
	rm .depend
	rm -rf $(OBJDIR) $(EXE)

depend: .depend

.depend: $(SRCS)
	rm -f .depend
	$(CXX) $(CXXFLAGS) -MM $^ >> .depend

include .depend
