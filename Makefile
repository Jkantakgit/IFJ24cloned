# Compiler settings - Can be customized.
CC = gcc
CXXFLAGS = -std=c11 -Wall
LDFLAGS = -lcunit

# Makefile settings - Can be customized.
APPNAME = myapp
TESTNAME = tests
EXT = .c
SRCDIR = src
TESTDIR = test
OBJDIR = obj
TESTOBJDIR = obj/tests

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

# Test files
TESTSRC = $(wildcard $(TESTDIR)/*$(EXT))
TESTOBJ = $(TESTSRC:$(TESTDIR)/%$(EXT)=$(TESTOBJDIR)/%.o)

# UNIX-based OS variables & settings
RM = rm -rf
DELOBJ = $(OBJ) $(TESTOBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o) $(TESTSRC:$(TESTDIR)/%$(EXT)=$(TESTOBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

# Ensure the obj and obj/tests directories exist
.PHONY: directories
directories:
	mkdir -p $(OBJDIR) $(TESTOBJDIR)

# Builds the app without linking tests
all: directories $(APPNAME)

# Builds the application (without tests)
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Builds the test executable
$(TESTNAME): $(OBJ) $(TESTOBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

build_tests: directories $(TESTNAME)


# Creates the dependency rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Building rule for test .o files
$(TESTOBJDIR)/%.o: $(TESTDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME) $(TESTNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

# Target to run tests after building
.PHONY: run_tests
run_tests: directories $(TESTNAME)
	./$(TESTNAME)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE) $(TESTNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)
