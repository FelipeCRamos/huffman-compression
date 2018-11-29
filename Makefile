# Makefile for the Binary Tree project

# Author:
# + Felipe Ramos

# Makefile conventions
SHELL = /bin/sh

# Directories
INCDIR = ./include
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
DOCDIR = ./Documentation

# Macros
CC = g++	# for compatibility
CFLAGS = -Wall -g -ggdb -std=c++14 -I. -I$(INCDIR)
RM = -rm
PROJ_NAME = huf

HEADERS := $(wildcard $(INCDIR)/*)
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: project # documentation

project: $(OBJECTS) $(HEADERS) | $(BINDIR)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(BINDIR)/$(PROJ_NAME)
	@ln -sfv $(BINDIR)/$(PROJ_NAME) $(PROJ_NAME)

documentation:
	@mkdir -p $(DOCDIR)
	@doxygen config
	@ln -sfv $(DOCDIR)/html/index.html $(DOC_NAME)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# Clean PHONY targets
.PRONY: clean clean_proj

clean: clean_proj 

clean_proj:
	@echo "Removing OBJDIR..."
	@$(RM) -r $(OBJDIR)
	@echo "Removing BINDIR..."
	@$(RM) -r $(BINDIR)
	@echo "Removing documentation files..."
	@$(RM) -r Documentation/
	@echo "Removing symlink..."
	@$(RM) -f $(PROJ_NAME)
	@$(RM) -f $(DOC_NAME) 
	@echo "Clean-up completed!"
